<?php

  $myTable = array(
    'key1' => 'val1',
    'key2' => 'val2',
    'key3' => 'val3'
  );

  print "Array Dump test: Legacy Hash Table API\n";
  dumparray($myTable);  

  $newTable = array();
  for ($i = 0; $i < 10; ++$i)
  {
    $newTable["NKey$i"] = "NVal$i";
  }
  print "Array Dump Test: New PHP 7 Hash Table API\n";
  dumparray_new($newTable);
?>
