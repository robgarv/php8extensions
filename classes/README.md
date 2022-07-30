# Classes

A set of example classes that can be used by PHP scipts

# crudehash

This is a very stupid class. Basically, we're just
trying to see the basics of defining a class that
can be used by PHP source code, and how it can
be used to interface to C++ features. 

$myArray = array( 'This is a silly string',
  'This is another silly string',
  'This is yet another stupid string' );

$myHash = new CrudeHash( $myArray );
$hashCode = $myHash.hash();

Under the hood, CrudeHash uses vectors, strings, and the
C++ 11 hash functional. 

