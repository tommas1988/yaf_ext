PHP_ARG_WITH(yext, for yext support,
[  --with-yext           Include yext support])

if test "$PHP_YEXT" != "no"; then
  if test -r $PHP_YEXT/php_yaf.h; then
    YAF_DIR=$PHP_YEXT
  fi

  if test -z "$YAF_DIR"; then
    AC_MSG_RESULT([not found yaf directory])
    AC_MSG_ERROR([Please make sure the right yaf directory path])
  fi

  PHP_ADD_INCLUDE($YAF_DIR)

  PHP_NEW_EXTENSION(yext,
        yext.c          \
        yext_view.c,
        $ext_shared)
  PHP_ADD_EXTENSION_DEP(yext, yaf)
fi
