#!/bin/bash
php -d extension=$PWD/modules/hello.so -r '{ echo hello_world() . "\n"; }'
