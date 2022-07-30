# populate1 Abstract

The populate1 example demontrates a simple methodology for populating 
a structure from the contents of an associative array, and populating
an array with the contents of a structure. 

## HoldStructure

This is a structure with "named" fields ... that is, members that are
described by a field definition structure. The field definition 
structure provides a logical name, the data type, and pointer to 
the physical structure field. 

So this basically allows you to relate a structure field to a logical
name (which will be used as an associative array key).

## populate1

This implements the following functions 

### populatefromarray

PHP code provides an associative array by value. The keys of the
associative array are the logical names of the HoldStructure fields.
The values will be written to the related HoldStructure member variables.

### populatearray

PHP code provides an associative array by reference, which should
be empty. The function builds a HoldStructure locally, and then
populates the associative array with the structure members using
the logical names as keys.

This example illustrates passing an array by reference, 
and the use of the "modern" parameter parsing API. 