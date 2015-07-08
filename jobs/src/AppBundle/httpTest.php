<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
require_once './../../vendor/autoload.php';

$hostfile = fopen("http://google.com", 'r');

while (!feof($hostfile)) 
{
    $output = fread($hostfile, 8192);
    echo $output;
}
    
fclose($hostfile);

