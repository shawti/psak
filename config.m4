dnl $Id$
dnl config.m4 for extension psak

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(psak, for psak support,
Make sure that the comment is aligned:
[  --with-psak             Include psak support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(psak, whether to enable psak support,
dnl Make sure that the comment is aligned:
dnl [  --enable-psak           Enable psak support])

if test "$PHP_PSAK" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-psak -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/psak.h"  # you most likely want to change this
  dnl if test -r $PHP_PSAK/$SEARCH_FOR; then # path given as parameter
  dnl   PSAK_DIR=$PHP_PSAK
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for psak files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       PSAK_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$PSAK_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the psak distribution])
  dnl fi

  dnl # --with-psak -> add include path
  dnl PHP_ADD_INCLUDE($PSAK_DIR/include)

  dnl # --with-psak -> check for lib and symbol presence
  dnl LIBNAME=psak # you may want to change this
  dnl LIBSYMBOL=psak # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $PSAK_DIR/lib, PSAK_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_PSAKLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong psak lib version or lib not found])
  dnl ],[
  dnl   -L$PSAK_DIR/lib -lm
  dnl ])
  dnl
  dnl PHP_SUBST(PSAK_SHARED_LIBADD)

  PHP_NEW_EXTENSION(psak, psak.c, $ext_shared)
fi
