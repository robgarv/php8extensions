// include the header of your extension
// the header includes php.h
#include "php_dumparray.h"
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
zend_function_entry dumparray_functions[] = {
    PHP_FE(dumparray, NULL)
    PHP_FE(dumparray_new, NULL)
    {NULL, NULL, NULL}
};

// some pieces of information about our module
zend_module_entry dumparray_module_entry = {
    STANDARD_MODULE_HEADER,
    PHP_DUMPARRAY_EXTNAME,
    dumparray_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    PHP_DUMPARRAY_VERSION,
    STANDARD_MODULE_PROPERTIES
};

// use a macro to output additional C code, to make ext dynamically loadable
ZEND_GET_MODULE(dumparray)



// Iterate an array and print its contents using the legacy API
PHP_FUNCTION(dumparray)
{
  // touch $HOME/tmp/gdb.block to cause execution to loop
  // rm $HOME/gdb.block to cause execution to break out of loop
  // Gives opportunity to attach debugger
  GDB_BLOCK;
  
  zval *zArray;

  // Parse arguments into an array (a).
  if (zend_parse_parameters(ZEND_NUM_ARGS(), "a", &zArray) == FAILURE)
  {
    WARNS( "dumparray: Error parsing input params" );
  }


  HashPosition i = 0;
  zval *Data;
  HashTable *Table = Z_ARRVAL_P( zArray );
  for( zend_hash_internal_pointer_reset_ex( Table, &i );
   ( Data = zend_hash_get_current_data_ex( Table, &i ) ) != NULL;
   zend_hash_move_forward_ex( Table, &i ) )
  {
    zend_string *zStrKey;
    zend_ulong numIndex;

    if (zend_hash_get_current_key_ex(Table, &zStrKey, &numIndex, &i) == FAILURE)
    {
      WARNS( "Call to zend_hash_get_current_key_ex fails!");
      RETURN_NULL();
    }
    char* szVal = Z_STRVAL_P(Data);
    STATUS( "HashPosition: " << i << " Key: " << ZSTR_VAL(zStrKey) << " Value: " << szVal );
  }
  RETURN_NULL();
}

// Iterate an array using the updated PHP7 Hash API
PHP_FUNCTION(dumparray_new)
{
  GDB_BLOCK

  zval* zArray;

  // Parse arguments into an array (a).
  if (zend_parse_parameters(ZEND_NUM_ARGS(), "a", &zArray) == FAILURE)
  {
    WARNS( "dumparray_new: Error parsing input params" );
    RETURN_NULL();
  }


  zend_string *zKey;
  zval *pVal;
  ulong numKey;

  ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(zArray), numKey, zKey, pVal) {
    STATUS( "NumKey: " << numKey << " Key: " << ZSTR_VAL(zKey) << 
      " Value: " << Z_STRVAL_P(pVal) );
  } ZEND_HASH_FOREACH_END();
}

