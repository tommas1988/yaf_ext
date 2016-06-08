PHP_ARG_ENABLE(yaf_ext, whether to enable yaf_ext support,
[  --enable-yaf_ext           Enable yaf_ext support])

if test "$PHP_YAF_EXT" != "no"; then
  PHP_NEW_EXTENSION(yaf_ext, yaf_ext.c, $ext_shared,,-I[$abs_srcdir/ext])

  PHP_ADD_EXTENSION_DEP(yaf_ext, yaf)
fi
