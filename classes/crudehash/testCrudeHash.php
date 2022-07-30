<?php

// This code snippet produces memory leaks but the
// larger script does not!!!! 
// $myArray = array( "String 1", "String 2", "String 3" );
// $myHash = new CrudeHash($myArray);
// $myCode = $myHash->hashIt();
// print "Hash Code: $myCode \n";

$options = array();

function readOptionValue( $opt )
{
  global $options;
  
  $optKeys = $opt; 
  if ( ! is_array($opt ) )
  { $optKeys = array( $opt ); }
  
  foreach ( $optKeys as $key )
  {
      
    if ( array_key_exists( $key, $options ) )
    {
      if ( $options[$key] === false )
      { return true; }      // indicate the flag was set in cmd line
      else
      { return $options[$key]; }
    }
  }
  return NULL;
}

function Main()
{
  global $argc;
  global $argv;
  global $options;

  $shortopts = "n:";
  $longopts = array( "NumberStrings");

  $optind = 1;
  $options = getopt($shortopts,$longopts, $optind);
  $stringCount = 3;
  if (! empty($options))
  {
    $stringCount = readOptionValue( array('n', 'NumberStrings') );
  }

  print "String Count = $stringCount\n";
  $strArray = array();
  for ($i = 0; $i < $stringCount; $i++)
  {
    $strArray[] = "String $i";
  }
  $myHash = new CrudeHash($strArray);
  $myCode = $myHash->hashIt();
  print "Hash Code: $myCode \n";
}

Main();
exit(0);
