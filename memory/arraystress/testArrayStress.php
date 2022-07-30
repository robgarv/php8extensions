<?php

function runTest()
{
  $myTable = array(
    'key1' => 'val1',
    'key2' => 'val2',
    'key3' => 'val3'
  );

  dumparray($myTable);  

  $newTable = array();
  for ($i = 0; $i < 10; ++$i)
  {
    $newTable["NKey$i"] = "NVal$i";
  }
  dumparray_new($newTable);

  $newTable2 = array();
  for ($i = 0; $i < 10; ++$i)
  {
    $newTable2["NKey2_$i"] = "NVal2_$i";
  }
  dumparray_new2($newTable2);
}

$InitMemUsage = memory_get_usage();
$InitMemPeak = memory_get_peak_usage();
print "Init Usage: $InitMemUsage Init Peak: $InitMemPeak\n" ;
$testCount = 100;

$PrevUsage = $InitMemUsage;
$PrevPeak = $InitMemPeak;

for ($i = 0; $i < $testCount; ++$i)
{
  // If the extensions called by runTest leak, we should see
  // usage and peak usage grow
  runTest();
  $Usage = memory_get_usage();
  $Peak = memory_get_peak_usage();
  print "Prev: $PrevUsage PrevPeak: $PrevPeak Usage: $Usage Peak: $Peak\n";
  $PrevUsage = $Usage;
  $PrevPeak = $Peak;
}
?>
