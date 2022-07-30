PHP_ARG_ENABLE(populate1, Whether to enable the populate1 extension, [ --enable-populate1 Enable populate1])

if test "$PHP_POPULATE1" != "no"; then
    PHP_REQUIRE_CXX()
    PHP_SUBST(POPULATE1_SHARED_LIBADD)
    PHP_ADD_LIBRARY(stdc++, 1, POPULATE1_SHARED_LIBADD)
    PHP_ADD_INCLUDE(../../include)
    AC_DEFINE(HAVE_POPULATE1, 1, [Whether you have populate1])
    PHP_NEW_EXTENSION(populate1, populate1.cpp HoldStructure.cpp, $ext_shared)
fi
