#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"
#include "php_hello.h"

ZEND_BEGIN_ARG_INFO_EX(arginfo_hello_world, 0, 0, 0)
ZEND_END_ARG_INFO()

static zend_function_entry hello_functions[] = {
    PHP_FE(hello_world, arginfo_hello_world)
    {NULL, NULL, NULL}
};

zend_module_entry hello_module_entry = {
    STANDARD_MODULE_HEADER,
    PHP_HELLO_WORLD_EXTNAME,
    hello_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    PHP_HELLO_WORLD_VERSION,
    STANDARD_MODULE_PROPERTIES
};


#ifdef COMPILE_DL_HELLO
ZEND_GET_MODULE(hello)
#endif

PHP_FUNCTION(hello_world)
{
    RETURN_STRING("Hello World");
}
