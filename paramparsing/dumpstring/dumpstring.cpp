// include the header of your extension
// the header includes php.h
#include "php_dumpstring.h"
#include <iostream>
#include <sstream>

using namespace std;

// GDB_BLOCK Macro
#define GDB_BLOCK \
{ \
  std::ostringstream _ssfilename; \
  _ssfilename << getenv( "HOME" ) << "/tmp/gdb.block"; \
  struct stat _gdbstat; \
  while ( stat( _ssfilename.str().c_str(), &_gdbstat ) == 0 ) \
  { \
    sleep( 1 ); \
  } \
}

// Some console output support
#define _USE_STDOUT
#ifdef _USE_STDOUT
    #define _PRINTIT( __label, _x_msg_stream ) \
    do { \
        std::cout << __label << "(S): " << _x_msg_stream.str() << std::endl; \
    } while( 0 )
#else
    #define _PRINTIT( __label, _x_msg_stream ) \
    do { \
        php_printf( __label << "(P): %s", _x_msg_stream.str().c_str()); \
    } while( 0 )
#endif

#define WARNS( _Expression ) \
do { \
  std::ostringstream __x_Msg; \
  __x_Msg << _Expression; \
  _PRINTIT( "WARNING", __x_Msg ); \
} while( 0 )


#define STATUS( _Expression ) \
do { \
  std::ostringstream __x_Msg; \
  __x_Msg << _Expression; \
  _PRINTIT( "STATUS", __x_Msg ); \
} while( 0 )


// register our function to the PHP API 
// so that PHP knows, which functions are in this module
zend_function_entry dumpstring_functions[] = {
    PHP_FE(dumpstring, NULL)
    PHP_FE(dumpinput, NULL)
    PHP_FE(dumparrayval, NULL)
    {NULL, NULL, NULL}
};

// some pieces of information about our module
zend_module_entry dumpstring_module_entry = {
    STANDARD_MODULE_HEADER,
    PHP_DUMPSTRING_EXTNAME,
    dumpstring_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    PHP_DUMPSTRING_VERSION,
    STANDARD_MODULE_PROPERTIES
};

// use a macro to output additional C code, to make ext dynamically loadable
ZEND_GET_MODULE(dumpstring)

// Finally, we implement our "Hello World" function
// this function will be made available to PHP
// and prints to PHP stdout using printf
PHP_FUNCTION(dumpstring)
{
    // php_printf("Hello World! (from our dumpstring extension)\n");
    RETURN_STRING( "Dumpstring test" );
}

// Dump the input string using the "old API"
PHP_FUNCTION(dumpinput)
{
    // touch $HOME/tmp/gdb.block to cause execution to loop
    // rm $HOME/tmp/gdb.block to cause execution to break out of loop
    // Gives opportunity to attach debugger
    GDB_BLOCK;
    char* input;
    size_t len;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &input, &len) == FAILURE)
    {
        std::cout << "dumpinput: Error parsing input params" << std::endl;
        RETURN_NULL();
    }
    STATUS( "dumpinput received: " << input );
    RETURN_STRING(input);
}

// Given a key and an array (hash), return the value
PHP_FUNCTION(dumparrayval)
{
    // touch $HOME/tmp/gdb.block to cause execution to loop
    // rm $HOME/gdb.block to cause execution to break out of loop
    // Gives opportunity to attach debugger
    GDB_BLOCK;
    
    zend_string *zKey;
    zval *zArray;

    // Parse arguments into a zend_string (S) and an array (a).
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "Sa", &zKey, &zArray) == FAILURE)
    {
        WARNS( "dumparrayval: Error parsing input params" );
    }

    char* szKey = ZSTR_VAL(zKey);
    std::cout << "dumparrayval fetching key: " << szKey << std::endl;

    zval *Val = zend_hash_find(Z_ARRVAL_P(zArray), zKey);
    if ( Val == NULL )
    {
        WARNS("dumparrayval could not find key ");
        RETURN_NULL();
    }
    char* szVal = Z_STRVAL_P(Val);
    RETURN_STRING(szVal);
}



