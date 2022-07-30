#ifndef _PHP_ARRAYSTRESS_H
#define _PHP_ARRAYSTRESS_H

#ifdef __cplusplus
extern "C" {
#endif
  #include "php.h"
#ifdef __cplusplus
}
#endif

// we define Module constants
#define PHP_ARRAYSTRESS_EXTNAME "dumparray"
#define PHP_ARRAYSTRESS_VERSION "0.0.1"

// then we declare the function to be exported
PHP_FUNCTION(dumparray);
PHP_FUNCTION(dumparray_new);
PHP_FUNCTION(dumparray_new2);

extern zend_module_entry arraystress_module_entry;
#define phpext_arraystress_ptr &arraystress_module_entry

#endif
