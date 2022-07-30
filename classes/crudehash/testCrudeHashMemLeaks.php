<?php

// This leaks memory
// $myArray = array( "String 1", "String 2", "String 3" );
// $myHash = new CrudeHash($myArray);
// $myCode = $myHash->hashIt();
// print "Hash Code: $myCode \n";

// And this leaks memory ... same amount
for ($j = 0; $j<100; $j++)
{
  print "Memory Leaks ... why??\n";
  $myArray = array();
  for ($i = 1; $i < 4; $i++)
  {
    $myArray[] = "String $j-$i";
  }
  $myHash = new CrudeHash($myArray);
  $youHash = $myHash;
  $myCode = $myHash->hashIt();
  $yourCode = $myHash->hashIt();
  print "Hash Code: $myCode \n";
}

// Uncomment the exit to make memory leaks go away
// exit(0);