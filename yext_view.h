#ifndef YEXT_VIEW
#define YEXT_VIEW

#define VIEW_MODEL_CLASS "Yext_ViewModel"
#define VIEW_MODEL_CLASS_NS "Yext\\ViewModel"

extern zend_class_entry *yext_view_ce;
extern zend_class_entry *yext_view_model_ce;

void yext_register_view_class();

#endif
