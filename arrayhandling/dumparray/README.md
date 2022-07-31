# dumparray

Examples of basic parameter parsing and array (hash) access. This is written
in C++ just to provide an example. (See config.m4 for necessary details.)

This example uses "traditional" parameter parsing APIs to parse parameters
and perform basic array access. The GDB_BLOCK macro is used to block
execution of the extension to facilitate attaching a debugger. 

## To build


cd dumparray
phpize
./configure
make

You can build for debugging with gdb by configuring and making as follows

CXXFLAGS="-g -O0" ./configure
make


## To run the example

./rundumparray.sh

## Debugging

See the GDB_BLOCK macro in dumparray.cpp. If it finds a file at $HOME/tmp/gdb.block, it begins looping. This blocks execution of the code until you can attach the gdb debugger. Typical use case:

cd <this directory>
touch $HOME/tmp/gdb.block
./rundumparray.sh

From a second terminal window:

ps -afe | grep testDumpArray
gdb -p <pid obtained by ps command>

Set break points. From third terminal window, 

rm $HOME/tmp/gdb.block

GDB_BLOCK will exit the loop


