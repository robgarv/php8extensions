#ifndef _PHP_DUMPSTRING_H
#define _PHP_DUMPSTRING_H

#ifdef __cplusplus
extern "C" {
#endif
  #include "php.h"
#ifdef __cplusplus
}
#endif

// we define Module constants
#define PHP_DUMPSTRING_EXTNAME "dumpstring"
#define PHP_DUMPSTRING_VERSION "0.0.1"

// then we declare the function to be exported
PHP_FUNCTION(dumpstring);
PHP_FUNCTION(dumpinput);
PHP_FUNCTION(dumparrayval);

extern zend_module_entry dumpstring_module_entry;
#define phpext_dumpstring_ptr &dumpstring_module_entry

#endif
