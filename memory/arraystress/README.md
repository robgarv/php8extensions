# arraystress

A variant of dumparray used to test simple memory management. Running
this test basically shows that the simple extension functions implemented
in the arraystress extension don't leak memory. 

The array dump output is written to /tmp/arraystress.log

The test script prints memory utilization stats to the console. 

Examples of basic parameter parsing and array (hash) access. This is written
in C++ just to provide an example. (See config.m4 for necessary details.)

This example uses "traditional" parameter parsing APIs to parse parameters
and perform basic array access. The GDB_BLOCK macro is used to block
execution of the extension to facilitate attaching a debugger. 

## To build


cd arraystress

phpize

./configure

make

You can build for debugging with gdb by configuring and making as follows

CXXFLAGS="-g -O0" ./configure
make


## To run the example

./runarraystress

## Debugging

See the GDB_BLOCK macro in dumparray.cpp. If it finds a file at $HOME/tmp/gdb.block, it begins looping. This blocks execution of the code until you can attach the gdb debugger. Typical use case:

cd <this directory>
touch $HOME/tmp/gdb.block
./runarraystress.sh

From a second terminal window:

ps -afe | grep testArrayStress
gdb -p <pid obtained by ps command>

Set break points. From third terminal window, 

rm $HOME/tmp/gdb.block

GDB_BLOCK will exit the loop


