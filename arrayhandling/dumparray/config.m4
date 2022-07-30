PHP_ARG_ENABLE(dumparray, Whether to enable the dumparray extension, [ --enable-dumparray Enable dumparray])

if test "$PHP_DUMPSTRING" != "no"; then
    PHP_REQUIRE_CXX()
    PHP_SUBST(DUMPARRAY_SHARED_LIBADD)
    PHP_ADD_LIBRARY(stdc++, 1, DUMPARRAY_SHARED_LIBADD)
    AC_DEFINE(HAVE_DUMPARRAY, 1, [Whether you have Dump Array])
    PHP_NEW_EXTENSION(dumparray, dumparray.cpp, $ext_shared)
fi
