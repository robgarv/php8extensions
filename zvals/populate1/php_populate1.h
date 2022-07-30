#ifndef _PHP_POPULATE1_H
#define _PHP_POPULATE1_H

#ifdef __cplusplus
extern "C" {
#endif
  #include "php.h"
#ifdef __cplusplus
}
#endif

// we define Module constants
#define PHP_POPULATE1_EXTNAME "populate1"
#define PHP_POPULATE1_VERSION "0.0.1"

// then we declare the function to be exported
PHP_FUNCTION(populatefromarray);
PHP_FUNCTION(populatearray);


// Note: Because the array passed to populatearray must be 
// passed by reference, we need to declare our arguments
// If first arg to ZEND_ARG_INFO is 1 then the argument
// is to be passed by reference.
ZEND_BEGIN_ARG_INFO_EX(arginfo_populatearray, 0, 0, 1)
  ZEND_ARG_INFO(1, table) /* ARRAY_INFO(1, stack, 0) */
ZEND_END_ARG_INFO()


extern zend_module_entry populate1_module_entry;
#define phpext_populate1_ptr &populate1_module_entry

#endif
