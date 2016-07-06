#include "php.h"

#include "yaf_ext_view.h"
#include "php_yaf.h"

zend_class_entry *yafext_view_ce;
zend_class_entry *yafext_view_model_ce;

static zend_function_entry yafext_view_methods[] = {
  {NULL, NULL, NULL}
};
static zend_function_entry yafext_view_model_methods[] = {
  {NULL, NULL, NULL}
};

void yafext_register_view_class() {
  zend_class_entry ce;

  YAF_INIT_CLASS_ENTRY(ce, "Yafext_LayoutCapableView", "Yafext\\LayoutCapableView", yafext_view_methods);
  yafext_view_ce = zend_register_internal_class(&ce, TSRMLS_CC);

  zend_class_implements(yafext_view_ce TSRMLS_CC, 1, yaf_view_interface_ce);

  YAF_INIT_CLASS_ENTRY(ce, "Yafext_ViewModel", "Yafext\\ViewModel", yafext_view_model_methods);
  yafext_view_model_ce = zend_register_internal_class(&ce, TSRMLS_CC);
}
