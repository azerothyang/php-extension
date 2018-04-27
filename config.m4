dnl $Id$
dnl config.m4 for extension sample

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(sample, for sample support,
dnl Make sure that the comment is aligned:
dnl [  --with-sample             Include sample support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(sample, whether to enable sample support,
dnl Make sure that the comment is aligned:
[  --enable-sample           Enable sample support])

if test "$PHP_SAMPLE" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-sample -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/sample.h"  # you most likely want to change this
  dnl if test -r $PHP_SAMPLE/$SEARCH_FOR; then # path given as parameter
  dnl   SAMPLE_DIR=$PHP_SAMPLE
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for sample files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       SAMPLE_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$SAMPLE_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the sample distribution])
  dnl fi

  dnl # --with-sample -> add include path
  dnl PHP_ADD_INCLUDE($SAMPLE_DIR/include)

  dnl # --with-sample -> check for lib and symbol presence
  dnl LIBNAME=sample # you may want to change this
  dnl LIBSYMBOL=sample # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $SAMPLE_DIR/$PHP_LIBDIR, SAMPLE_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_SAMPLELIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong sample lib version or lib not found])
  dnl ],[
  dnl   -L$SAMPLE_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  PHP_SUBST(SAMPLE_SHARED_LIBADD)

  PHP_NEW_EXTENSION(sample, sample.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
