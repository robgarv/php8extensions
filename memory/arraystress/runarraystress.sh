#!/bin/bash

logfile="/tmp/arraystress.log"
if [ -f $logfile ]; then
  rm $logfile
fi

php -d extension=$PWD/modules/arraystress.so -f testArrayStress.php

