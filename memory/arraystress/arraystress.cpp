// An variant of dumparray that is used for basic memory
// management testing. Writes to /tmp/arraystress.log

// include the header of your extension
// the header includes php.h
#include "php_arraystress.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// GDB_BLOCK Macro
#define GDB_BLOCK \
{ \
  std::ostringstream _ssfilename; \
  _ssfilename << getenv( "HOME" ) << "/tmp/gdb.block"; \
  struct stat _gdbstat; \
  int updatepid = 1; \
  while ( stat( _ssfilename.str().c_str(), &_gdbstat ) == 0 ) \
  { \
    if ( updatepid ) \
    { \
      std::ofstream blockfile; \
      blockfile.open(_ssfilename.str().c_str() ); \
      blockfile << getpid() << "\n"; \
      blockfile.close(); \
      updatepid = 0; \
    } \
    sleep( 1 ); \
  } \
}

// Some console output support
#define _USE_FILE
#ifdef _USE_FILE
    #define _PRINTIT( __label, _x_msg_stream ) \
    do { \
        outfile << __label << "(S): " << _x_msg_stream.str() << "\n"; \
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

// Name of where the log will be written. The extension
// always appends to cleaning up the log is the responsibility
// of the run script runarraystress.sh

const char* outfileName = "/tmp/arraystress.log";

// register our function to the PHP API 
// so that PHP knows, which functions are in this module
zend_function_entry arraystress_functions[] = {
    PHP_FE(dumparray, NULL)
    PHP_FE(dumparray_new, NULL)
    PHP_FE(dumparray_new2, NULL)
    {NULL, NULL, NULL}
};

// some pieces of information about our module
zend_module_entry arraystress_module_entry = {
    STANDARD_MODULE_HEADER,
    PHP_ARRAYSTRESS_EXTNAME,
    arraystress_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    PHP_ARRAYSTRESS_VERSION,
    STANDARD_MODULE_PROPERTIES
};

// use a macro to output additional C code, to make ext dynamically loadable
ZEND_GET_MODULE(arraystress)



// Iterate an array and print its contents using the legacy API
// 
PHP_FUNCTION(dumparray)
{
  // touch $HOME/tmp/gdb.block to cause execution to loop
  // rm $HOME/gdb.block to cause execution to break out of loop
  // Gives opportunity to attach debugger
  GDB_BLOCK;
  
  std::ofstream outfile;
  outfile.open(outfileName, std::ios::app);

  zval *zArray;

  // Parse arguments into an array (a).
  if (zend_parse_parameters(ZEND_NUM_ARGS(), "a", &zArray) == FAILURE)
  {
    WARNS( "dumparray: Error parsing input params" );
    RETURN_NULL();
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

  std::ofstream outfile;
  outfile.open(outfileName, std::ios::app);

  // A note on allocation. Recommendation is now to allocate the zval
  // on the stack. But here we are declaring a zval *. That's because
  // we are working with what turns out to be an array. See dumparray_new2 
  // for an alternative way of doing this.  
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

// A variation of dumparray_new which makes explicit reference
// to the HashTable type. 
PHP_FUNCTION(dumparray_new2)
{
  GDB_BLOCK;

  std::ofstream outfile;
  outfile.open(outfileName, std::ios::app);

  // A note on allocation. Recommendation is now to allocate the zval
  // on the stack. But here we are declaring a HashTable *. That's because
  // we are working with what turns out to be an Hash Table/array. 
  HashTable *zHash;

  // Parse arguments into a hash table (h).
  if (zend_parse_parameters(ZEND_NUM_ARGS(), "h", &zHash) == FAILURE)
  {
    WARNS( "dumparray_new: Error parsing input params" );
    RETURN_NULL();
  }

  zend_string *zKey;
  zval *pVal;
  ulong numKey;

  ZEND_HASH_FOREACH_KEY_VAL(zHash, numKey, zKey, pVal) {
    STATUS( "NumKey: " << numKey << " Key: " << ZSTR_VAL(zKey) << 
      " Value: " << Z_STRVAL_P(pVal) );
  } ZEND_HASH_FOREACH_END();

}
