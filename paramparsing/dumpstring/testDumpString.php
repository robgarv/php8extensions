<?php

  $string = dumpstring();
  echo "String received is: $string\n";

  print "Calling dumpinput\n";
  $string2 = dumpinput("This is an input string");
  if ( empty($string2) )
  {
    print "Empty string received from dumpinput\n";
  }
  else
  {
    print "Received from dumpinput: $string2\n";
  }

  $myTable = array(
    'key1' => 'val1',
    'key2' => 'val2',
    'key3' => 'val3'
  );

  print "Array fetch test\n";
  foreach ($myTable as $key => $val )
  {
    $outstring = dumparrayval($key, $myTable);
    if (empty($outstring))
    {
      print "dumparrayval fails to fetch from key: $key\n";
    }
    else
    {
      print "dumparrayval $key => $val\n";
    }
  }
  
?>
