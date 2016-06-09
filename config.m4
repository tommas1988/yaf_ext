PHP_ARG_WITH(yaf_ext, for yaf_ext support,
[  --with-yaf_ext           Include yaf_ext support])

if test "$PHP_YAF_EXT" != "no"; then
  if test -r $PHP_YAF_EXT/php_yaf.h; then
    YAF_DIR=$PHP_YAF_EXT
  fi

  if test -z "$YAF_DIR"; then
    AC_MSG_RESULT([not found yaf directory])
    AC_MSG_ERROR([Please make sure the right yaf directory path])
  fi

  PHP_ADD_INCLUDE($YAF_DIR)

  PHP_NEW_EXTENSION(yaf_ext, yaf_ext.c, $ext_shared)
  PHP_ADD_EXTENSION_DEP(yaf_ext, yaf)
fi
