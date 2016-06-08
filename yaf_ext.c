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

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_yaf_ext.h"
#include "ext/yaf/php_yaf.h"
#include "ext/yaf/yaf_namespace.h"
#include "ext/yaf/yaf_bootstrap.h"
#include "ext/yaf/yaf_config.h"
#include "ext/yaf/yaf_controller.h"
#include "ext/yaf/yaf_action.h"
#include "ext/yaf/views/yaf_view_interface.h"
#include "ext/yaf/yaf_plugin.h"
#include "ext/yaf/yaf_request.h"
#include "ext/yaf/yaf_response.h"
#include "ext/yaf/routes/yaf_route_interface.h"

/* If you declare any globals in php_yaf_ext.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(yaf_ext)
*/

/* True global resources - no need for thread safety here */
static int le_yaf_ext;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("yaf_ext.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_yaf_ext_globals, yaf_ext_globals)
    STD_PHP_INI_ENTRY("yaf_ext.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_yaf_ext_globals, yaf_ext_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_yaf_ext_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_yaf_ext_compiled)
{
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "yaf_ext", arg);
	RETURN_STRINGL(strg, len, 0);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_yaf_ext_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_yaf_ext_init_globals(zend_yaf_ext_globals *yaf_ext_globals)
{
	yaf_ext_globals->global_value = 0;
	yaf_ext_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(yaf_ext)
{
    if (YAF_G(use_namespace)) {
        zend_register_class_alias("Yaf\\AbstractBootstrap", yaf_bootstrap_ce);
        zend_register_class_alias("Yaf\\AbstractConfig", yaf_config_ce);
        zend_register_class_alias("Yaf\\AbstractController", yaf_controller_ce);
        zend_register_class_alias("Yaf\\AbstractAction", yaf_action_ce);
        zend_register_class_alias("Yaf\\ViewInterface", yaf_view_interface_ce);
        zend_register_class_alias("Yaf\\AbstractPlugin", yaf_plugin_ce);
        zend_register_class_alias("Yaf\\AbstractRequest", yaf_request_ce);
        zend_register_class_alias("Yaf\\AbstractResponse", yaf_response_ce);
        zend_register_class_alias("Yaf\\RouteInterface", yaf_route_ce);
    }

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(yaf_ext)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(yaf_ext)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(yaf_ext)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(yaf_ext)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "yaf_ext support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ yaf_ext_functions[]
 *
 * Every user visible function must have an entry in yaf_ext_functions[].
 */
const zend_function_entry yaf_ext_functions[] = {
	PHP_FE(confirm_yaf_ext_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in yaf_ext_functions[] */
};
/* }}} */

static zend_module_dep yaf_ext_deps[] = {
    ZEND_MOD_REQUIRED("yaf")
    {NULL, NULL, NULL}
};

/* {{{ yaf_ext_module_entry
 */
zend_module_entry yaf_ext_module_entry = {
	STANDARD_MODULE_HEADER_EX, NULL,
    yaf_ext_deps,
	"yaf_ext",
	yaf_ext_functions,
	PHP_MINIT(yaf_ext),
	PHP_MSHUTDOWN(yaf_ext),
	PHP_RINIT(yaf_ext),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(yaf_ext),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(yaf_ext),
	PHP_YAF_EXT_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_YAF_EXT
ZEND_GET_MODULE(yaf_ext)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
