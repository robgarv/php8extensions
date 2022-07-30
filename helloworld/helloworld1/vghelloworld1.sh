#!/bin/bash
echo $0
#php -d extension=$PWD/modules/php_helloworld.so -r '{ helloworld_php(); }'


thisdir=$PWD
myrootdir=${thisdir%/*/*}
PATH=$PATH:$myrootdir/bin
etcdir=$myrootdir/etc
logdir=$myrootdir/log

if [ ! -d "$logdir" ]; then
  echo "Creating log directory $myrootdir/log"
  mkdir -p $myrootdir/log
fi

RunValgrind.sh -o $logdir/helloworld1.vg -f xml -c $etcdir/php.ini -s $etcdir/suppressions.txt -d extension=$PWD/modules/php_helloworld.so -x hello1.php

echo "The log files are written to $logdir"
echo "To examine using valkyrie:"
echo "cd $logdir"
echo "valkyrie -l helloworld1.vg.xml"
