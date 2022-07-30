#ifndef _PHPSUPPORT_H
#define _PHPSUPPORT_H
#ifdef __cplusplus
extern "C" {
#endif

#include "php.h"
#include "Zend/zend_exceptions.h"
#ifdef __cplusplus
}
#endif


// A structure to contain the data to be hashed, 
// and implement the CrudeHash PHP object. 
typedef struct _php_crudehash_t {
  HashTable *data;      // The data to be hashed
  zend_long size;       // Number of elements
  zend_object std;      // Standard object 
} php_crudehash_t;

// Helper macros to calculate the pointer to the php_crudehash_t 
// structure based on a pointer to the zend object. 
#define PHP_CRUDEHASH_FETCH_FROM(o) ((php_crudehash_t*) (((char*)o) - XtOffsetOf(php_crudehash_t, std)))
#define PHP_CRUDEHASH_FETCH(z)    PHP_CRUDEHASH_FETCH_FROM(Z_OBJ_P(z)) /* }}} */

// For exporting methods to other extensions
extern zend_class_entry *CrudeHash_ce;

// Called from module init. Remember zend engine will call
// module init, then request init. It will then execute the
// script, and on completion of the script calls request shutdown
// followed by module shutdown.

void php_crudehash_init(void);

#endif
