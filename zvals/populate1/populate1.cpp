#include "php_populate1.h"
#include "pextcommon.h"
#include "HoldStructure.h"
#include <iostream>
#include <sstream>

using namespace std;


// register our functions to the PHP API 
// so that PHP knows, which functions are in this module
zend_function_entry populate1_functions[] = {
    PHP_FE(populatefromarray, NULL)
    PHP_FE(populatearray, arginfo_populatearray)
    {NULL, NULL, NULL}
};

// some pieces of information about our module
zend_module_entry populate1_module_entry = {
    STANDARD_MODULE_HEADER,
    PHP_POPULATE1_EXTNAME,
    populate1_functions,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    PHP_POPULATE1_VERSION,
    STANDARD_MODULE_PROPERTIES
};

// use a macro to output additional C code, to make ext dynamically loadable
ZEND_GET_MODULE(populate1)


// populatefromarray
//
// We're going to accept an associative array as input and store the values
// in a HoldStructure object. This function will return true for success, 
// false otherwise.
PHP_FUNCTION(populatefromarray)
{
    // touch $HOME/tmp/gdb.block to cause execution to loop
    // rm $HOME/gdb.block to cause execution to break out of loop
    // Gives opportunity to attach debugger
    GDB_BLOCK;

    HashTable *zHash;

    // Parse arguments into an array (a).
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "h", &zHash) == FAILURE)
    {
        WARNS( "populatefromarray: Error parsing input params" );
        RETURN_BOOL(0);
    }

    zend_string *zKey;
    zval *pVal;
    ulong numKey;
    HoldStructure hs;
    try
    {
        ZEND_HASH_FOREACH_KEY_VAL(zHash, numKey, zKey, pVal) {
            switch (Z_TYPE_P(pVal))
            {
                case IS_LONG:
                    {
                        long longVal = Z_LVAL_P(pVal);
                         hs.mSetField(ZSTR_VAL(zKey), longVal);
                    }
                    break;

                case IS_STRING:
                    hs.mSetField(ZSTR_VAL(zKey), Z_STRVAL_P(pVal));
                    break;
            }
        } ZEND_HASH_FOREACH_END();
        STATUS( "Populated: " << std::endl << hs.mToString());
    }
    catch (HoldStructureException &hx)
    {
        WARNS("populatefromarray caught holdstructure exception! : " << hx.mFormat());
        RETURN_BOOL(0);
    }
    RETURN_BOOL(1);
}

// Given a HoldStructure, populate a PHP associative array.
// In this simple example, the HoldStructure is built locally
// and written to an array passed by reference.
PHP_FUNCTION(populatearray)
{

    zval *table;    // The input array
    int argc;       // Number of arguments to be pushed

    // ZEND_PARSE_PARAMETERS_START( min params, max params)
    // Z_PARAM_ARRAY_EX( zval, check null, seperate)
    ZEND_PARSE_PARAMETERS_START(1, -1)
        Z_PARAM_ARRAY_EX(table, 0, 1)
    ZEND_PARSE_PARAMETERS_END();


    zend_string *zKey;
    zval *pVal;
    ulong numKey;

    // Fill out a hold structure
    HoldStructure hs;
    hs.mValueA = 98765;
    hs.mValueB = "OutputValueB";
    hs.mValueC = "OutputValueC";

    for (std::map<std::string,HoldFieldDef>::iterator it = hs.mFieldDefs.begin();
        it != hs.mFieldDefs.end(); ++it)
    {
        std::string fieldName = it->second.mFieldName;
        HoldStructureFieldType type = it->second.mType;
        switch (type)
        {
            case stringfield:
                {
                    STATUS("Start stringfield");
                    std::string* pValue = it->second.mFieldPointer.stringValue;
                    const char* szValue = pValue->c_str();
                    zend_string* zStrValue = zend_string_init(szValue, strlen(szValue), 0);
                    zval zValue;
                    ZVAL_STR(&zValue, zStrValue);
                    zend_hash_str_add(Z_ARRVAL_P(table), fieldName.c_str(), fieldName.length(), &zValue);
                    STATUS("Done with stringfield");
                }
                break;
            case longfield:
                {
                    STATUS("start with longfield");
                    long* plValue = it->second.mFieldPointer.longValue;
                    zend_string* zStrKey = zend_string_init(fieldName.c_str(), fieldName.length(), 0);
                    zval zValue;
                    ZVAL_LONG(&zValue, *plValue);
                    zend_hash_add_new(Z_ARRVAL_P(table), zStrKey, &zValue);
                    zend_string_release(zStrKey);
                    STATUS( "Done with longfield");
                }
                break;
        }
    }

#ifdef _POPULATE1_INTERNAL_DUMP
    {
        ulong numKey;
        zend_string* zKey;
        zval* pVal;
        ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(table), numKey, zKey, pVal) {
            switch (Z_TYPE_P(pVal))
            {
                case IS_LONG:
                    STATUS( "LONG VALUE: " << ZSTR_VAL(zKey) << " => " << Z_LVAL_P(pVal) );
                    break;

                case IS_STRING:
                    STATUS( "STRING VALUE: " << ZSTR_VAL(zKey) << " => " << Z_STRVAL_P(pVal));
                    break;
            }
        } ZEND_HASH_FOREACH_END();
    }
#endif
    RETVAL_LONG(zend_hash_num_elements(Z_ARRVAL_P(table)))
}

PHP_FUNCTION(dumpzval)
{

}




