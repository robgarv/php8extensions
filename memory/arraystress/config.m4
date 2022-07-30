PHP_ARG_ENABLE(arraystress, Whether to enable the arraystress test extension, [ --enable-arraystress Enable arraystress])

if test "$PHP_ARRAYSTRESS" != "no"; then
    PHP_REQUIRE_CXX()
    PHP_SUBST(ARRAYSTRESS_SHARED_LIBADD)
    PHP_ADD_LIBRARY(stdc++, 1, ARRAYSTRESS_SHARED_LIBADD)
    AC_DEFINE(HAVE_ARRAYSTRESS, 1, [Whether you have Dump Array To File])
    PHP_NEW_EXTENSION(arraystress, arraystress.cpp, $ext_shared)
fi
