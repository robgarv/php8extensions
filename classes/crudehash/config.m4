PHP_ARG_ENABLE(crudehash, Whether to enable the crudehash extension, [ --enable-crudehash Enable crudehash])

if test "$PHP_CRUDEHASH" != "no"; then
    PHP_REQUIRE_CXX()
    CXXFLAGS="-std=gnu++11 $CXXFLAGS"
    PHP_SUBST(CRUDEHASH_SHARED_LIBADD)
    PHP_ADD_LIBRARY(stdc++, 1, CRUDEHASH_SHARED_LIBADD)
    PHP_ADD_INCLUDE(../../include)
    AC_DEFINE(HAVE_CRUDEHASH, 1, [Whether you have crudehash])
    PHP_NEW_EXTENSION(crudehash, crudehash.cpp phpsupport.cpp hashobject.cpp, $ext_shared)
fi
