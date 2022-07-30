
extern "C" {
  #include "php.h"
  #include "Zend/zend_exceptions.h"
}
#include "php_crudehash.h"
#include "phpsupport.h"
#include "hashobject.h"

extern zend_function_entry CrudeHash_methods[];
static zend_object_handlers php_crudehash_handlers;
zend_class_entry *CrudeHash_ce;

// Create a new CrudeHash php object. Once this has
// been done, the constructor method in crudehash.cpp runs.
zend_object* php_crudehash_create(zend_class_entry *ce) {
  php_crudehash_t *pc = 
    (php_crudehash_t*) ecalloc(1, sizeof(php_crudehash_t));

  zend_object_std_init(&pc->std, ce);

  // Set our class' handlers
  pc->std.handlers = &php_crudehash_handlers; 

  return &pc->std;
}


// Destroy/free a CrudeHash object
static void php_crudehash_free(zend_object *o) 
{
  zend_object_std_dtor(o);
}

// Garbage collection handling
static HashTable* php_crudehash_gc(zval *crudehash, zval **table, int *n) 
{
  php_crudehash_t *pc = PHP_CRUDEHASH_FETCH(crudehash);

  ZVAL_ARR(*table, pc->data);
  *n = sizeof(HashTable);

  return NULL;
}

static HashTable* php_crudehash_dump(zval *crudehash, int *is_temp) {
  php_crudehash_t *pc = PHP_CRUDEHASH_FETCH(crudehash);
  HashTable *ht;
  zend_long it;

  ALLOC_HASHTABLE(ht);
  zend_hash_init(ht, pc->size, NULL, ZVAL_PTR_DTOR, 0);
  *is_temp = 1;

  zval *item;
  ZEND_HASH_FOREACH_VAL(pc->data, item) {
    zend_hash_next_index_insert( ht, item);
  } ZEND_HASH_FOREACH_END();

  return ht;
}

static zend_object* php_crudehash_clone(zval *object) {
  php_crudehash_t *pc = PHP_CRUDEHASH_FETCH(object);
  php_crudehash_t *cl = (php_crudehash_t*) ecalloc(1, sizeof(php_crudehash_t));
  zend_long it;

  zend_object_std_init(&cl->std, pc->std.ce);

  cl->std.handlers = &php_crudehash_handlers; 

  HashTable *ht;
  ALLOC_HASHTABLE(ht);
  zend_hash_init(ht, pc->size, NULL, ZVAL_PTR_DTOR, 0);

  zval *item;
  ZEND_HASH_FOREACH_VAL(pc->data, item) {
    zend_hash_next_index_insert( ht, item);
  } ZEND_HASH_FOREACH_END();

  cl->size = pc->size;

  return &cl->std;
}


static int php_crudehash_cast(zval *indexed, zval *retval, int type) {
  php_crudehash_t *pc = PHP_CRUDEHASH_FETCH(indexed);
  zend_long it;

  if (type != IS_ARRAY) {
    return FAILURE;
  }

  array_init(retval);

  zval *item;
  ZEND_HASH_FOREACH_VAL(pc->data, item) {
        add_next_index_zval(retval, item);
  } ZEND_HASH_FOREACH_END(); 

  return SUCCESS;
}

#define PHP_CRUDEHASH_NO_PROPERTIES() do { \
  zend_throw_exception_ex(NULL, 0, \
    "properties on Indexed objects are not allowed"); \
} while(0)

static zval* php_crudehash_property_read(zval *object, zval *member, int type, void **cache_slot, zval *rv) {
  PHP_CRUDEHASH_NO_PROPERTIES();
  return &EG(uninitialized_zval);
}

static void php_crudehash_property_write(zval *object, zval *member, zval *value, void **cache_slot) {
  PHP_CRUDEHASH_NO_PROPERTIES();
}

static int php_crudehash_property_exists(zval *object, zval *member, int has_set_exists, void **cache_slot) {
  PHP_CRUDEHASH_NO_PROPERTIES();
  return 0;
}

static void php_crudehash_property_unset(zval *object, zval *member, void **cache_slot) {
  PHP_CRUDEHASH_NO_PROPERTIES();
} /* }}} */


void php_crudehash_init(void) {
  zend_class_entry ce;
  
  INIT_CLASS_ENTRY(ce, "CrudeHash", CrudeHash_methods);
  CrudeHash_ce = zend_register_internal_class(&ce);
  CrudeHash_ce->create_object = php_crudehash_create;
  CrudeHash_ce->get_iterator = NULL;
  CrudeHash_ce->ce_flags |= ZEND_ACC_FINAL;

  const zend_object_handlers *zh = zend_get_std_object_handlers();  

  memcpy(&php_crudehash_handlers, zh, sizeof(zend_object_handlers));
  
  php_crudehash_handlers.free_obj = php_crudehash_free;
  // php_crudehash_handlers.get_gc   = php_crudehash_gc;
  php_crudehash_handlers.get_debug_info = php_crudehash_dump;
  php_crudehash_handlers.clone_obj = php_crudehash_clone;
  // php_crudehash_handlers.cast_object = php_crudehash_cast;

  php_crudehash_handlers.read_property = php_crudehash_property_read;
  php_crudehash_handlers.write_property = php_crudehash_property_write;
  php_crudehash_handlers.has_property = php_crudehash_property_exists;
  php_crudehash_handlers.unset_property = php_crudehash_property_unset;

  php_crudehash_handlers.get_properties = NULL;

  php_crudehash_handlers.offset = XtOffsetOf(php_crudehash_t, std);

}
