// Header file for the "main extension" source file

#ifndef _PHP_CRUDEHASH_H
#define _PHP_CRUDEHASH_H

#ifdef __cplusplus
extern "C" {
#endif

#include "php.h"

#ifdef __cplusplus
}
#endif

// Module entry
extern zend_module_entry crudehash_module_entry;
#define phpext_crudehash_ptr &crudehash_module_entry;


// Define Module constants
#define PHP_CRUDEHASH_EXTNAME "crudehash"
#define PHP_CRUDEHASH_VERSION "0.0.1"

#ifdef ZTS
#include "TSRM.h"
#endif
#if defined(ZTS) && defined(COMPILE_DL_INDEXED)
ZEND_TSRMLS_CACHE_EXTERN();

#endif

#endif
