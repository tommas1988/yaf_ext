#include "php.h"

#include "yaf_ext_view.h"
#include "php_yaf.h"

zend_class_entry *yafext_view_ce;
zend_class_entry *yafext_view_model_ce;

YAF_BEGIN_ARG_INFO_EX(view_construct_arginfo, 0, 0, 0)
ZEND_ARG_ARRAY_INFO(0, options, 1)
ZEND_END_ARG_INFO()

YAF_BEGIN_ARG_INFO_EX(get_view_model_arginfo, 0, 0, 0)
ZEND_END_ARG_INFO()

YAF_BEGIN_ARG_INFO_EX(set_view_model_arginfo, 0, 0, 1)
ZEND_ARG_OBJ_INFO(0, viewModel, VIEW_MODEL_CLASS, 0)
ZEND_END_ARG_INFO()

YAF_BEGIN_ARG_INFO_EX(register_view_helper_arginfo, 0, 0, 2)
ZEND_ARG_INFO(0, name)
ZEND_ARG_INFO(0, callback)
ZEND_END_ARG_INFO()

YAF_BEGIN_ARG_INFO_EX(register_view_helpers_arginfo, 0, 0, 1)
ZEND_ARG_ARRAY_INFO(0, callbacks, 0)
ZEND_END_ARG_INFO()

YAF_BEGIN_ARG_INFO_EX(add_child_view_model_arginfo, 0, 0, 2)
ZEND_ARG_INFO(0, name)
ZEND_ARG_OBJ_INFO(0, viewModel, VIEW_MODEL_CLASS, 0)
ZEND_END_ARG_INFO()

#ifdef YAF_HAVE_NAMESPACE
YAF_BEGIN_ARG_INFO_EX(set_view_model_arginfo_ns, 0, 0, 1)
ZEND_ARG_OBJ_INFO(0, viewModel, VIEW_MODEL_CLASS_NS, 0)
ZEND_END_ARG_INFO()

YAF_BEGIN_ARG_INFO_EX(add_child_view_model_arginfo_ns, 0, 0, 2)
ZEND_ARG_INFO(0, name)
ZEND_ARG_OBJ_INFO(0, viewModel, VIEW_MODEL_CLASS_NS, 0)
ZEND_END_ARG_INFO()
#endif

PHP_METHOD(yafext_view, assign) {
  RETURN_TRUE;
}

PHP_METHOD(yafext_view, display) {
  RETURN_TRUE;
}

PHP_METHOD(yafext_view, render) {
  RETURN_TRUE;
}

PHP_METHOD(yafext_view, setScriptPath) {
  RETURN_TRUE;
}

PHP_METHOD(yafext_view, getScriptPath) {
  RETURN_TRUE;
}

PHP_METHOD(yafext_view, setViewModel) {
  RETURN_TRUE;
}

PHP_METHOD(yafext_view, registerViewHelper) {
  RETURN_TRUE;
}

PHP_METHOD(yafext_view, registerViewHelpers) {
  RETURN_TRUE;
}

PHP_METHOD(yafext_view, getViewModel) {
  RETURN_TRUE;
}

PHP_METHOD(yafext_view_model, assign) {
  RETURN_TRUE;
}

PHP_METHOD(yafext_view_model, addChild) {
  RETURN_TRUE;
}

static zend_function_entry yafext_view_methods[] = {
  /* PHP_ME(yafext_view, __construct, view_construct_arginfo, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR) */
  PHP_ME(yafext_view, assign, yaf_view_assign_arginfo, ZEND_ACC_PUBLIC)
  PHP_MALIAS(yafext_view, __set, assign, yaf_view_assign_arginfo, ZEND_ACC_PUBLIC)
  PHP_ME(yafext_view, display, yaf_view_display_arginfo, ZEND_ACC_PUBLIC)
  PHP_ME(yafext_view, render, yaf_view_render_arginfo, ZEND_ACC_PUBLIC)
  PHP_ME(yafext_view, setScriptPath, yaf_view_setpath_arginfo, ZEND_ACC_PUBLIC)
  PHP_ME(yafext_view, getScriptPath, yaf_view_getpath_arginfo, ZEND_ACC_PUBLIC)
  PHP_ME(yafext_view, setViewModel, set_view_model_arginfo, ZEND_ACC_PUBLIC)
  PHP_ME(yafext_view, getViewModel, get_view_model_arginfo, ZEND_ACC_PUBLIC)
  PHP_ME(yafext_view, registerViewHelper, register_view_helper_arginfo, ZEND_ACC_PUBLIC)
  PHP_ME(yafext_view, registerViewHelpers, register_view_helpers_arginfo, ZEND_ACC_PUBLIC)
  {NULL, NULL, NULL}
};

#ifdef YAF_HAVE_NAMESPACE
static zend_function_entry yafext_view_methods_ns[] = {
  /* PHP_ME(yafext_view, __construct, view_construct_arginfo, ZEND_ACC_PUBLIC|ZEND_ACC_CTOR) */
  PHP_ME(yafext_view, assign, yaf_view_assign_arginfo, ZEND_ACC_PUBLIC)
  PHP_MALIAS(yafext_view, __set, assign, yaf_view_assign_arginfo, ZEND_ACC_PUBLIC)
  PHP_ME(yafext_view, display, yaf_view_display_arginfo, ZEND_ACC_PUBLIC)
  PHP_ME(yafext_view, render, yaf_view_render_arginfo, ZEND_ACC_PUBLIC)
  PHP_ME(yafext_view, setScriptPath, yaf_view_setpath_arginfo, ZEND_ACC_PUBLIC)
  PHP_ME(yafext_view, getScriptPath, yaf_view_getpath_arginfo, ZEND_ACC_PUBLIC)
  PHP_ME(yafext_view, setViewModel, set_view_model_arginfo_ns, ZEND_ACC_PUBLIC)
  PHP_ME(yafext_view, getViewModel, get_view_model_arginfo, ZEND_ACC_PUBLIC)
  PHP_ME(yafext_view, registerViewHelper, register_view_helper_arginfo, ZEND_ACC_PUBLIC)
  PHP_ME(yafext_view, registerViewHelpers, register_view_helpers_arginfo, ZEND_ACC_PUBLIC)
  {NULL, NULL, NULL}
};
#endif

static zend_function_entry yafext_view_model_methods[] = {
  PHP_ME(yafext_view_model, assign, yaf_view_assign_arginfo, ZEND_ACC_PUBLIC)
  PHP_MALIAS(yafext_view_model, __set, yaf_view_assign_arginfo, ZEND_ACC_PUBLIC)
  PHP_ME(yafext_view_model, addChild, add_child_view_model, ZEND_ACC_PUBLIC)
  {NULL, NULL, NULL}
};

#ifdef YAF_HAVE_NAMESPACE
static zend_function_entry yafext_view_model_methods_ns[] = {
  PHP_ME(yafext_view_model, assign, yaf_view_assign_arginfo, ZEND_ACC_PUBLIC)
  PHP_MALIAS(yafext_view_model, __set, yaf_view_assign_arginfo, ZEND_ACC_PUBLIC)
  PHP_ME(yafext_view_model, addChild, add_child_view_model_ns, ZEND_ACC_PUBLIC)
  {NULL, NULL, NULL}
};
#endif

void yafext_register_view_class() {
  zend_class_entry ce;

  if (YAF_G(use_namespace)) {
    INIT_CLASS_ENTRY(ce, "Yafext\\LayoutCapableView", yafext_view_methods_ns);
    yafext_view_ce = zend_register_internal_class(&ce, TSRMLS_CC);

    INIT_CLASS_ENTRY(ce, VIEW_MODEL_CLASS_NS, yafext_view_model_methods_ns);
    yafext_view_model_ce = zend_register_internal_class(&ce, TSRMLS_CC);
  } else {
    INIT_CLASS_ENTRY(ce, "Yafext_LayoutCapableView", yafext_view_methods);
    yafext_view_model_ce = zend_register_internal_class(&ce, TSRMLS_CC);

    INIT_CLASS_ENTRY(ce, VIEW_MODEL_CLASS, yafext_view_model_methods);
    yafext_view_model_ce = zend_register_internal_class(&ce, TSRMLS_CC);
  }

  zend_declare_property_null(yafext_view_ce, ZEND_STRL("variables"), ZEND_ACC_PROTECTED, TSRMLS_CC);
  zend_declare_property_null(yafext_view_ce, ZEND_STRL("viewModel"), ZEND_ACC_PROTECTED, TSRMLS_CC);
  zend_declare_property_null(yafext_view_ce, ZEND_STRL("helpers"), ZEND_ACC_PROTECTED, TSRMLS_CC);

  zend_class_implements(yafext_view_ce TSRMLS_CC, 1, yaf_view_interface_ce);

  zend_declare_property_null(yafext_view_model_ce, ZEND_STRL("children"), ZEND_ACC_PROTECTED, TSRMLS_CC);
}
