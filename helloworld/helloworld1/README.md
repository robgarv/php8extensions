# helloworld1

Very simple hello world extension. No parameter parsing
or anything. 


To build

cd helloworld1
phpize
./configure
make


## To run the example

./runhelloworld1.sh


## To compile so as to play with gdb and/or valgrind:

cd helloworld1
phpize
CXXFLAGS="-g -O0" ./configure
make

## To run valgrind,

./vghelloworld1.sh

This script will cause valgrind to write its logs to a log
directory immediately under the repository root.  
(See the script for details.)


(I find the valgrind output for this simple example terrifying.)