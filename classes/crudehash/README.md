# CrudeHash class

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

This is an adaptation of Joe Watkins' "indexed" extension example. 
Scaled down a little and corrupted because I wanted to focus on the 
aspect of managing standard C++ facilitates from an extension. 

The indexed extension can be accessed on github here

https://github.com/krakjoe/indexed

A lengthy video walkthrough of the indexed extension

https://youtu.be/AloIn2t7bWc

# Build Instructions

## Build notes 

This extension uses the std::hash functional, which is available
on Ubuntu 16.04 only for gnu C++ 11. config.m4 includes the following directive:

    CXXFLAGS="-std=gnu++11 $CXXFLAGS"

This may not be required (and may be even detrimental) in some
environments. I should probably write a configuration test or something but
I'm not that intrigued by autoconf arcana. 

## Build Procedure

phpize
./configure
make

# To Run 

./runtestcrudehash.sh <number of strings> 

e.g.

./runtestcrudehash.sh 100

## Interesting Note on Memory Leaks

runtestcrudehash.sh just sets up calling php to run the script testCrudeHash.php. This script performs an exit(0) at termination. 

The script runtestmemleaks.sh runs php scripts testCrudeHashMemLeaks.php. 
This script does not issue an exit call ... and we get memory leak reports
out of PHP. (You need to have built PHP from source with debugging options
to see that.)

One would think that RSHUTDOWN and MSHUTDOWN would be called in either case.
I don't understand this difference in behavior yet, but included 
testCrudeHashMemLeaks.php just to demonstrate the issue. 



