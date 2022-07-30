#ifndef _PHP_DUMPARRAY_H
#define _PHP_DUMPARRAY_H

#ifdef __cplusplus
extern "C" {
#endif
  #include "php.h"
#ifdef __cplusplus
}
#endif

// we define Module constants
#define PHP_DUMPARRAY_EXTNAME "dumparray"
#define PHP_DUMPARRAY_VERSION "0.0.1"

// then we declare the function to be exported
PHP_FUNCTION(dumparray);
PHP_FUNCTION(dumparray_new);

extern zend_module_entry dumparray_module_entry;
#define phpext_dumparray_ptr &dumparray_module_entry

#endif
