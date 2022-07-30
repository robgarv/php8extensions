PHP_ARG_ENABLE(dumpstring, Whether to enable the dumpstring extension, [ --enable-dumpstring Enable dumpstring])

if test "$PHP_DUMPSTRING" != "no"; then
    PHP_REQUIRE_CXX()
    PHP_SUBST(DUMPSTRING_SHARED_LIBADD)
    PHP_ADD_LIBRARY(stdc++, 1, DUMPSTRING_SHARED_LIBADD)
    AC_DEFINE(HAVE_DUMPSTRING, 1, [Whether you have Hello World])
    PHP_NEW_EXTENSION(dumpstring, dumpstring.cpp, $ext_shared)
fi
