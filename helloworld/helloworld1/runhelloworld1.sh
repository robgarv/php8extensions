#!/bin/bash
echo $0
php -d extension=$PWD/modules/php_helloworld.so -r '{ helloworld_php(); }'
