# memory

Sample PHP7 extensions that explore various aspects of memory management and access.

## arraystress

This takes the "dumparray" example and wraps it in a php script for many calls. The testArrayStress.php stress checks memory utilization after each call. This basically demonstrates PHP7 garbage collection ... the extension code makes no specific attempt to release memory. 

