/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2015 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "string.h"

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "Zend/zend_interfaces.h"

#include "php_yext.h"
#include "yext_view.h"
#include "php_yaf.h"
#include "yaf_namespace.h"
#include "yaf_bootstrap.h"
#include "yaf_config.h"
#include "yaf_controller.h"
#include "yaf_action.h"
#include "views/yaf_view_interface.h"
#include "yaf_plugin.h"
#include "yaf_request.h"
#include "yaf_response.h"
#include "routes/yaf_route_interface.h"

ZEND_DECLARE_MODULE_GLOBALS(yext)

/* True global resources - no need for thread safety here */
static int le_yext;

zend_class_entry *yext_plugin_ce;
zend_class_entry *yext_controller_ce;

ZEND_BEGIN_ARG_INFO_EX(plugin_arginfo, 0, 0, 2)
ZEND_ARG_OBJ_INFO(0, request, Yaf_Request_Abstract, 0)
ZEND_ARG_OBJ_INFO(0, response, Yaf_Response_Abstract, 0)
ZEND_END_ARG_INFO()

#ifdef YAF_HAVE_NAMESPACE
ZEND_BEGIN_ARG_INFO_EX(plugin_arginfo_ns, 0, 0, 2)
ZEND_ARG_OBJ_INFO(0, request, Yaf\\Request_Abstract, 0)
ZEND_ARG_OBJ_INFO(0, response, Yaf\\Response_Abstract, 0)
ZEND_END_ARG_INFO()
#endif

ZEND_BEGIN_ARG_INFO_EX(controller_render_arginfo, 0, 0, 1)
ZEND_ARG_INFO(0, tpl)
ZEND_ARG_ARRAY_INFO(0, parameters, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(controller_display_arginfo, 0, 0, 1)
ZEND_ARG_INFO(0, tpl)
ZEND_ARG_ARRAY_INFO(0, parameters, 1)
ZEND_END_ARG_INFO()

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("yext.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_yext_globals, yext_globals)
    STD_PHP_INI_ENTRY("yext.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_yext_globals, yext_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_yext_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_yext_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "yext", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/

PHP_METHOD(yext_plugin, preDispatch) {
    zval *request, *response, *action, *z_new_action;
    zend_class_entry *request_ce;
    char *action_dup;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "oo", &request, &response) == FAILURE) {
        RETURN_FALSE;
    }

    request_ce = Z_OBJCE_P(request);
    action = zend_read_property(request_ce, request, ZEND_STRL(YAF_REQUEST_PROPERTY_NAME_ACTION), 1 TSRMLS_CC);

    char *needle = "-", *new_action = NULL;
    char *b = Z_STRVAL_P(action), *p;
    size_t n, len = 0;
    while (p = strpbrk(b, needle)) {
        if (!new_action) {
            new_action = emalloc(Z_STRLEN_P(action));
        }

        n = p - b;
        memcpy(new_action+len, b, n);
        len += n;

        if (b == Z_STRVAL_P(action)+Z_STRLEN_P(action)-1) {
            break;
        }

        b += (n+1);
    }

    if (new_action) {
        if (b != Z_STRVAL_P(action)+Z_STRLEN_P(action)-1) {
            n = Z_STRVAL_P(action)+Z_STRLEN_P(action)-b;
            memcpy(new_action+len, b, n);
            len += n;
        }

        new_action[len] = '\0';
    } else {
        RETURN_TRUE;
        return;
    }

    MAKE_STD_ZVAL(z_new_action);
    ZVAL_STRINGL(z_new_action, new_action, len, 0);

    action_dup = estrndup(Z_STRVAL_P(action), Z_STRLEN_P(action));
    zend_update_property(request_ce, request, ZEND_STRL(YAF_REQUEST_PROPERTY_NAME_ACTION), z_new_action TSRMLS_CC);

    YEXT_G(req_action) = action_dup;

    RETURN_TRUE;
}

PHP_METHOD(yext_plugin, postDispatch) {
    /* Why not trigger postDispatch */
    if (YEXT_G(req_action)) {
        efree(YEXT_G(req_action));
        YEXT_G(req_action) = NULL;
    }

    RETURN_TRUE;
}

#define CALL_YAF_CONTROLLER_RENDER_DISPLAY(name) \
    zval *tpl, *var_array = NULL, *ret = NULL;                          \
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z|z", &tpl, &var_array) == FAILURE) { \
        return; \
    } \
    if (YEXT_G(req_action)) { \
        ZVAL_STRING(tpl, YEXT_G(req_action), 0); \
    } \
    if (var_array) { \
        zend_call_method_with_2_params(&getThis(), yaf_controller_ce, NULL, #name, &ret, tpl, var_array); \
    } else { \
        zend_call_method_with_1_params(&getThis(), yaf_controller_ce, NULL, #name, &ret, tpl); \
    } \
    zval_ptr_dtor(return_value_ptr); \
    *return_value_ptr = ret; \
    RETURN_TRUE; \

PHP_METHOD(yext_controller, render) {
    CALL_YAF_CONTROLLER_RENDER_DISPLAY(render)
}

PHP_METHOD(yext_controller, display) {
    CALL_YAF_CONTROLLER_RENDER_DISPLAY(display)
}

static zend_function_entry yext_plugin_methods[] = {
    PHP_ME(yext_plugin, preDispatch, plugin_arginfo, ZEND_ACC_PUBLIC)
    PHP_ME(yext_plugin, postDispatch, plugin_arginfo, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};

#ifdef YAF_HAVE_NAMESPACE
static zend_function_entry yext_plugin_methods_ns[] = {
    PHP_ME(yext_plugin, preDispatch, plugin_arginfo_ns, ZEND_ACC_PUBLIC)
    PHP_ME(yext_plugin, postDispatch, plugin_arginfo_ns, ZEND_ACC_PUBLIC)
    {NULL, NULL, NULL}
};
#endif

static zend_function_entry yext_controller_methods[] = {
    PHP_ME(yext_controller, render, controller_render_arginfo, ZEND_ACC_PROTECTED)
    PHP_ME(yext_controller, display, controller_display_arginfo, ZEND_ACC_PROTECTED)
    {NULL, NULL, NULL}
};

/* {{{ php_yext_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_yext_init_globals(zend_yext_globals *yext_globals)
{
	yext_globals->global_value = 0;
	yext_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(yext)
{
    zend_class_entry ce;

    if (YAF_G(use_namespace)) {
        INIT_CLASS_ENTRY(ce, "Yext\\Plugin", yext_plugin_methods_ns);
        yext_plugin_ce = zend_register_internal_class_ex(&ce, yaf_plugin_ce, NULL TSRMLS_CC);

        INIT_CLASS_ENTRY(ce, "Yext\\AbstractController", yext_controller_methods);
        yext_controller_ce = zend_register_internal_class_ex(&ce, yaf_controller_ce, NULL TSRMLS_CC);

        zend_register_class_alias("Yaf\\AbstractBootstrap", yaf_bootstrap_ce);
        zend_register_class_alias("Yaf\\AbstractConfig", yaf_config_ce);
        zend_register_class_alias("Yaf\\AbstractController", yaf_controller_ce);
        zend_register_class_alias("Yaf\\AbstractAction", yaf_action_ce);
        zend_register_class_alias("Yaf\\ViewInterface", yaf_view_interface_ce);
        zend_register_class_alias("Yaf\\AbstractPlugin", yaf_plugin_ce);
        zend_register_class_alias("Yaf\\AbstractRequest", yaf_request_ce);
        zend_register_class_alias("Yaf\\AbstractResponse", yaf_response_ce);
        zend_register_class_alias("Yaf\\RouteInterface", yaf_route_ce);
    } else {
        INIT_CLASS_ENTRY(ce, "Yext_Plugin", yext_plugin_methods);
        yext_plugin_ce = zend_register_internal_class_ex(&ce, yaf_plugin_ce, NULL TSRMLS_CC);

        INIT_CLASS_ENTRY(ce, "Yext_AbstractController", yext_controller_methods);
        yext_controller_ce = zend_register_internal_class_ex(&ce, yaf_controller_ce, NULL TSRMLS_CC);
    }

    yext_controller_ce->ce_flags |= ZEND_ACC_EXPLICIT_ABSTRACT_CLASS;

    yext_register_view_class();

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(yext)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
    if (YEXT_G(req_action)) {
        /* efree(YEXT_G(req_action)); */
    }

    return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(yext)
{
    YEXT_G(req_action) = NULL;
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(yext)
{
    if (YEXT_G(req_action)) {
        /* efree(YEXT_G(req_action)); */
    }
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(yext)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "yext support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ yext_functions[]
 *
 * Every user visible function must have an entry in yext_functions[].
 */
const zend_function_entry yext_functions[] = {
	PHP_FE(confirm_yext_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in yext_functions[] */
};
/* }}} */

static zend_module_dep yext_deps[] = {
    ZEND_MOD_REQUIRED("yaf")
    {NULL, NULL, NULL}
};

/* {{{ yext_module_entry
 */
zend_module_entry yext_module_entry = {
	STANDARD_MODULE_HEADER_EX, NULL,
    yext_deps,
	"yext",
	yext_functions,
	PHP_MINIT(yext),
	PHP_MSHUTDOWN(yext),
	PHP_RINIT(yext),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(yext),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(yext),
	PHP_YEXT_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_YEXT
ZEND_GET_MODULE(yext)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
