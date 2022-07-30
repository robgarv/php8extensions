<?php


$x1 = array(
  "ValueA" => 12345,
  "ValueB" => "ThisIsValueB",
  "ValueC" => "ThisIsValueC"
);

print "Populate structure from zval\n";
populatefromarray( $x1 );


print "Populate zval from structure\n";
$x2 = array();
$itemCount = populatearray( $x2 );

print "Back from populatearray. Item count = $itemCount\n";
print_r($x2);
foreach ($x2 as $key => $val)
{
  print "[$key] => $val\n";
}
?>
