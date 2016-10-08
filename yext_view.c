#include "php.h"

#include "yext_view.h"
#include "php_yaf.h"
#include "yaf_namespace.h"
#include "yaf_view.h"
#include "views/yaf_view_interface.h"

zend_class_entry *yext_view_ce;
zend_class_entry *yext_view_model_ce;

YAF_BEGIN_ARG_INFO_EX(view_construct_arginfo, 0, 0, 0)
ZEND_ARG_ARRAY_INFO(0, options, 1)
YAF_END_ARG_INFO()

YAF_BEGIN_ARG_INFO_EX(get_view_model_arginfo, 0, 0, 0)
YAF_END_ARG_INFO()

YAF_BEGIN_ARG_INFO_EX(set_view_model_arginfo, 0, 0, 1)
ZEND_ARG_OBJ_INFO(0, viewModel, VIEW_MODEL_CLASS, 0)
YAF_END_ARG_INFO()

YAF_BEGIN_ARG_INFO_EX(register_view_helper_arginfo, 0, 0, 2)
ZEND_ARG_INFO(0, name)
ZEND_ARG_INFO(0, callback)
YAF_END_ARG_INFO()

YAF_BEGIN_ARG_INFO_EX(register_view_helpers_arginfo, 0, 0, 1)
ZEND_ARG_ARRAY_INFO(0, callbacks, 0)
YAF_END_ARG_INFO()

YAF_BEGIN_ARG_INFO_EX(add_child_view_model_arginfo, 0, 0, 2)
ZEND_ARG_INFO(0, name)
ZEND_ARG_OBJ_INFO(0, viewModel, VIEW_MODEL_CLASS, 0)
YAF_END_ARG_INFO()

#ifdef YAF_HAVE_NAMESPACE
YAF_BEGIN_ARG_INFO_EX(set_view_model_arginfo_ns, 0, 0, 1)
ZEND_ARG_OBJ_INFO(0, viewModel, VIEW_MODEL_CLASS_NS, 0)
YAF_END_ARG_INFO()

YAF_BEGIN_ARG_INFO_EX(add_child_view_model_arginfo_ns, 0, 0, 2)
ZEND_ARG_INFO(0, name)
ZEND_ARG_OBJ_INFO(0, viewModel, VIEW_MODEL_CLASS_NS, 0)
YAF_END_ARG_INFO()
#endif

PHP_METHOD(yext_view, assign) {
  RETURN_TRUE;
}

PHP_METHOD(yext_view, display) {
  RETURN_TRUE;
}

PHP_METHOD(yext_view, render) {
  RETURN_TRUE;
}

PHP_METHOD(yext_view, setScriptPath) {
  RETURN_TRUE;
}

PHP_METHOD(yext_view, getScriptPath) {
  RETURN_TRUE;
}

PHP_METHOD(yext_view, setViewModel) {
  RETURN_TRUE;
}

PHP_METHOD(yext_view, registerViewHelper) {
  RETURN_TRUE;
}

PHP_METHOD(yext_view, registerViewHelpers) {
  RETURN_TRUE;
}

PHP_METHOD(yext_view, getViewModel) {
  RETURN_TRUE;
}

PHP_METHOD(yext_view_model, assign) {
  RETURN_TRUE;
}

PHP_METHOD(yext_view_model, addChild) {
  RETURN_TRUE;
}

static zend_function_entry yext_view_methods[] = {
  /* PHP_ME(yext_view, __construct, view_construct_arginfo, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR) */
  PHP_ME(yext_view, assign, yaf_view_assign_arginfo, ZEND_ACC_PUBLIC)
  PHP_MALIAS(yext_view, __set, assign, yaf_view_assign_arginfo, ZEND_ACC_PUBLIC)
  PHP_ME(yext_view, display, yaf_view_display_arginfo, ZEND_ACC_PUBLIC)
  PHP_ME(yext_view, render, yaf_view_render_arginfo, ZEND_ACC_PUBLIC)
  PHP_ME(yext_view, setScriptPath, yaf_view_setpath_arginfo, ZEND_ACC_PUBLIC)
  PHP_ME(yext_view, getScriptPath, yaf_view_getpath_arginfo, ZEND_ACC_PUBLIC)
  PHP_ME(yext_view, setViewModel, set_view_model_arginfo, ZEND_ACC_PUBLIC)
  PHP_ME(yext_view, getViewModel, get_view_model_arginfo, ZEND_ACC_PUBLIC)
  PHP_ME(yext_view, registerViewHelper, register_view_helper_arginfo, ZEND_ACC_PUBLIC)
  PHP_ME(yext_view, registerViewHelpers, register_view_helpers_arginfo, ZEND_ACC_PUBLIC)
  {NULL, NULL, NULL}
};

#ifdef YAF_HAVE_NAMESPACE
static zend_function_entry yext_view_methods_ns[] = {
  /* PHP_ME(yext_view, __construct, view_construct_arginfo, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR) */
  PHP_ME(yext_view, assign, yaf_view_assign_arginfo, ZEND_ACC_PUBLIC)
  PHP_MALIAS(yext_view, __set, assign, yaf_view_assign_arginfo, ZEND_ACC_PUBLIC)
  PHP_ME(yext_view, display, yaf_view_display_arginfo, ZEND_ACC_PUBLIC)
  PHP_ME(yext_view, render, yaf_view_render_arginfo, ZEND_ACC_PUBLIC)
  PHP_ME(yext_view, setScriptPath, yaf_view_setpath_arginfo, ZEND_ACC_PUBLIC)
  PHP_ME(yext_view, getScriptPath, yaf_view_getpath_arginfo, ZEND_ACC_PUBLIC)
  PHP_ME(yext_view, setViewModel, set_view_model_arginfo_ns, ZEND_ACC_PUBLIC)
  PHP_ME(yext_view, getViewModel, get_view_model_arginfo, ZEND_ACC_PUBLIC)
  PHP_ME(yext_view, registerViewHelper, register_view_helper_arginfo, ZEND_ACC_PUBLIC)
  PHP_ME(yext_view, registerViewHelpers, register_view_helpers_arginfo, ZEND_ACC_PUBLIC)
  {NULL, NULL, NULL}
};
#endif

static zend_function_entry yext_view_model_methods[] = {
  PHP_ME(yext_view_model, assign, yaf_view_assign_arginfo, ZEND_ACC_PUBLIC)
  PHP_MALIAS(yext_view_model, __set, assign, yaf_view_assign_arginfo, ZEND_ACC_PUBLIC)
  PHP_ME(yext_view_model, addChild, add_child_view_model_arginfo, ZEND_ACC_PUBLIC)
  {NULL, NULL, NULL}
};

#ifdef YAF_HAVE_NAMESPACE
static zend_function_entry yext_view_model_methods_ns[] = {
  PHP_ME(yext_view_model, assign, yaf_view_assign_arginfo, ZEND_ACC_PUBLIC)
  PHP_MALIAS(yext_view_model, __set, assign, yaf_view_assign_arginfo, ZEND_ACC_PUBLIC)
  PHP_ME(yext_view_model, addChild, add_child_view_model_arginfo_ns, ZEND_ACC_PUBLIC)
  {NULL, NULL, NULL}
};
#endif

void yext_register_view_class() {
  zend_class_entry ce;

  if (YAF_G(use_namespace)) {
    INIT_CLASS_ENTRY(ce, "Yext\\LayoutCapableView", yext_view_methods_ns);
    yext_view_ce = zend_register_internal_class(&ce TSRMLS_CC);

    INIT_CLASS_ENTRY(ce, VIEW_MODEL_CLASS_NS, yext_view_model_methods_ns);
    yext_view_model_ce = zend_register_internal_class(&ce TSRMLS_CC);
  } else {
    INIT_CLASS_ENTRY(ce, "Yext_LayoutCapableView", yext_view_methods);
    yext_view_ce = zend_register_internal_class(&ce TSRMLS_CC);

    INIT_CLASS_ENTRY(ce, VIEW_MODEL_CLASS, yext_view_model_methods);
    yext_view_model_ce = zend_register_internal_class(&ce TSRMLS_CC);
  }

  zend_declare_property_null(yext_view_ce, ZEND_STRL("variables"), ZEND_ACC_PROTECTED TSRMLS_CC);
  zend_declare_property_null(yext_view_ce, ZEND_STRL("viewModel"), ZEND_ACC_PROTECTED TSRMLS_CC);
  zend_declare_property_null(yext_view_ce, ZEND_STRL("helpers"), ZEND_ACC_PROTECTED TSRMLS_CC);

  zend_class_implements(yext_view_ce TSRMLS_CC, 1, yaf_view_interface_ce);

  zend_declare_property_null(yext_view_model_ce, ZEND_STRL("children"), ZEND_ACC_PROTECTED TSRMLS_CC);
}
