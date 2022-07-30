#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

extern "C" {
  #include "php.h"
  #include "ext/standard/info.h"
}

#include "php_crudehash.h"
#include "phpsupport.h"
#include "hashobject.h"

#include <iostream>

// Destructor for objects stored in our hash table.
// Setup by zend_hash_table_init call. Don't really
// use this ... but left in as example of how one
// would be declared.
// static void data_string_dtor(zval *el)
// {
//   efree(Z_PTR_P(el));
// }

// Note: ZEND_BEGIN_ARG_INFO_EX
//  name: Name of the function or method
// _unusused
// return_reference: flag meanting return a reference
// required_num: Required number of arguments

// Note: ZEND_ARG_TYPE_INFO arguments:
// ZEND_ARG_TYPE_INFO => pass by reference
// First arg: pass by reference (0)
// Second arg: name
// Third arg: type
// Fourth arg: allow NULL


// Constructor method
//
// Takes an array of strings as input.
// $myHash = new CrudeHash( $myArray )
ZEND_BEGIN_ARG_INFO_EX(CrudeHash_construct_arginfo, 0, 0, 1)
  ZEND_ARG_ARRAY_INFO(0, data, 0)
ZEND_END_ARG_INFO()

// Note that the ZEND_ARG_ARRAY_INFO macro use above is equivalent to
//  ZEND_ARG_TYPE_INFO(0, data, IS_ARRAY, 0)


PHP_METHOD(CrudeHash, __construct)
{
  HashTable *data;
  ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_ARRAY_HT_EX(data, 0, 1)
  ZEND_PARSE_PARAMETERS_END();

  // getThis returns our own standard object. The
  // macro performs the offset calculate to get the
  // start of our structure. 
  php_crudehash_t *pc = PHP_CRUDEHASH_FETCH(getThis());
  pc->size = zend_hash_num_elements(data);

  if (pc->size == 0)
  { 
    pc->data = NULL;
    return; 
  }

  // We're going to copy the strings in the input hash table to 
  // a new hash table and store that in our object. Note:
  // Zend/zend_hash.h declares the hash table API. We could
  // have used zend_hash_copy. 
  ALLOC_HASHTABLE(pc->data);
  zend_hash_init(pc->data, pc->size, NULL, ZVAL_PTR_DTOR, 0);
  zval *item;
  ZEND_HASH_FOREACH_VAL(data, item) {
    zend_hash_next_index_insert( pc->data, item);
  } ZEND_HASH_FOREACH_END();
}



// Calculates the hash of the strings in the array
// $hash = $myHash.hash();
// 
// This is where we construct the HashObject C++ class, 
// and call its mHash method. The return value is
// the hexadecimal representation of the unsigned long
// integer hash code. 
ZEND_BEGIN_ARG_INFO_EX(CrudeHash_hash_arginfo, 0, 0, 0)
ZEND_END_ARG_INFO();

PHP_METHOD(CrudeHash, hashIt)
{
  php_crudehash_t *pc = PHP_CRUDEHASH_FETCH(getThis());
  HashObject ho;    // Contructs a HashObject on the stack
  zval *item;
  ZEND_HASH_FOREACH_VAL(pc->data, item) {
    char* szString = Z_STRVAL_P(item);
    ho.mAddString(szString);
  } ZEND_HASH_FOREACH_END();
  
  char hexbuff[HashObject::HEXBUFFSIZE];
  ho.mHash(hexbuff);
  RETURN_STRING(hexbuff);
}

// Function Entry List
// PHP_ME args:
// 1) Class
// 2) Method
// 3) Arg ingo structure
// 4) Access constant. Access constants can be or'ed together:
//  ZEND_ACC_PUBLIC | ZEND_ACC_FINAL
//  makes a public method that is also final.
//
// PHP_ME => "PHP Method Entry"
// PHP_FE => "PHP (free) Function Entry"
zend_function_entry CrudeHash_methods[] = {
  PHP_ME(CrudeHash, __construct,  CrudeHash_construct_arginfo, ZEND_ACC_PUBLIC)
  PHP_ME(CrudeHash, hashIt,        CrudeHash_hash_arginfo,     ZEND_ACC_PUBLIC)
  PHP_FE_END
}; /* }}} */


// Module init function. Called before request init.
PHP_MINIT_FUNCTION(crudehash)
{
  php_crudehash_init();

  return SUCCESS;
}


// This gets called once per request
// This is where module globals would be allocated
PHP_RINIT_FUNCTION(crudehash)
{
#if defined(COMPILE_DL_INDEXED) && defined(ZTS)
  ZEND_TSRMLS_CACHE_UPDATE();
#endif
  return SUCCESS;
}



PHP_MINFO_FUNCTION(crudehash)
{
  php_info_print_table_start();
  php_info_print_table_header(2, "crudehash support", "enabled");
  php_info_print_table_end();
}

zend_module_entry crudehash_module_entry = {
  STANDARD_MODULE_HEADER,
  PHP_CRUDEHASH_EXTNAME,
  CrudeHash_methods,      // RCG NOTE: This was NULL in indexed.c example
  PHP_MINIT(crudehash),
  NULL,
  PHP_RINIT(crudehash),
  NULL,
  PHP_MINFO(crudehash),
  PHP_CRUDEHASH_VERSION,
  STANDARD_MODULE_PROPERTIES
};

ZEND_GET_MODULE(crudehash)

#ifdef COMPILE_DL_INDEXED
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE();
#endif
ZEND_GET_MODULE(indexed)
#endif

