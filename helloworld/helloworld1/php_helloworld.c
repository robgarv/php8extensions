// include the PHP API itself
#include <php.h>
// then include the header of your extension
#include "php_helloworld.h"

// register our function to the PHP API 
// so that PHP knows, which functions are in this module
zend_function_entry helloworld_php_functions[] = {
    PHP_FE(helloworld_php, NULL)
    {NULL, NULL, NULL}
};

// some pieces of information about our module
zend_module_entry helloworld_php_module_entry = {
    STANDARD_MODULE_HEADER,
    PHP_HELLOWORLD_EXTNAME,
    helloworld_php_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    PHP_HELLOWORLD_VERSION,
    STANDARD_MODULE_PROPERTIES
};

// use a macro to output additional C code, to make ext dynamically loadable
ZEND_GET_MODULE(helloworld_php)

// Finally, we implement our "Hello World" function
// this function will be made available to PHP
// and prints to PHP stdout using printf
PHP_FUNCTION(helloworld_php) {
    php_printf("Hello World! (from our extension)\n");
}
