#ifndef YAF_EXT_VIEW
#define YAF_EXT_VIEW

#define VIEW_MODEL_CLASS "Yafext_ViewModel"
#define VIEW_MODEL_CLASS_NS "Yafext\\ViewModel"

extern zend_class_entry *yafex_view_ce;
extern zend_class_entry *yafext_view_model_ce;

void yafext_register_view_class();

#endif
