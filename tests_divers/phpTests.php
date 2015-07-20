<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

$cars = array("Volvo", "BMW", "Toyota");
$arrlength = count($cars);
echo 'There are ' . $arrlength . ' items in the array.';

echo '<h2>Now sorting the items in the array in alphabetical order</h2>';
sort($cars);

foreach($cars as $key=>$name) {
    echo $key . ' is a ' . $name ;
    echo "<br>";
}

echo '<h2>Now creating an associative array.</h2>';

$employes = array(
    'Michel' => 47,
    'Andre' => 28,
    'Jocelyne' => 35,
    'Louise' => 21
    );
echo 'Sorting the array by key<br>';
ksort($employes);
foreach($employes as $key => $val) {
    echo 'The name is '. $key . ' and he or she is ' . $val . ' years old.';
    echo '<br>';
}

echo '<h2>Now uses of super global $_SERVER variable which, like $_GLOBALS, is
basically an associative array of variable-value pairs.</h2><br>';
echo "This is calling <b>_SERVER['PHP_SELF']:</b> " . $_SERVER['PHP_SELF'];
echo "<br>";
echo 'This is calling _SERVER(SERVER_NAME): '.$_SERVER['SERVER_NAME'];
echo "<br>";
echo 'This is calling _SERVER(HTTP_HOST): '.$_SERVER['HTTP_HOST'];
echo "<br>";
echo 'This is calling _SERVER(HTTP_USER_AGENT): '.$_SERVER['HTTP_USER_AGENT'];
echo "<br>";
echo 'This is calling _SERVER(SCRIPT_NAME): '.$_SERVER['SCRIPT_NAME'];
echo "<br>";
echo 'This is calling _SERVER(SCRIPT_FILENAME): '. $_SERVER['SCRIPT_FILENAME'];
echo "<br>";

echo '<h2>Date() function and its formats (argument of function).</h2>';
echo "Today is date(quoteY/m/dquote)" . date("Y/m/d") . "<br>";
echo "Today is date(quoteY.m.dquote)" . date("Y.m.d") . "<br>";
echo "Today is date(quoteY-m-dquote)" . date("Y-m-d") . "<br>";
echo "Today is date(quotelquote)" . date("l"). "<br>";
echo "Today is date(quoteh:i:saquote)" . date("h:i:sa"). "<br>";

