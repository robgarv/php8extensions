#!/bin/bash
stringcount=""
case "$#" in
  "0") stringcount="3";;
  "1") stringcount="$1";;
  "*") echo "Invalid argument count"; exit 1;;
esac;

php -d extension=$PWD/modules/crudehash.so -f testCrudeHash.php -- -n $1
