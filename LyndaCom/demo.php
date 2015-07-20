<?php



/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

function __autoload($class_name){
    include 'class.' . $class_name . '.inc';
}
    

echo '<h2>Instantiating a residence address</h2>';
$add = new Address;
$add->street_address_1 = '3098, du Finistere';
$add->city_name = 'Ste-Foy';
$add->subdivision_name = 'Quebec';
$add->country_name = 'Canada';
$add->address_type_id = '1';

echo $add;

echo '<h2>Testing address __contsruct function</h2>';
$add2 = new Address(array(
    'street_address_1' => '3098, Finest',
    'street_address_2' => 'app.#3',
    'city_name' => 'Rockwood City',
    'subdivision_name' => 'California',
    'country_name' => 'USA',
));
echo $add2;


echo '<h2>Creating an AddressBusiness instance</h2>';
$address_bus_data = array(
        'address_type_id' => 2,
        'street_address_1' => '18 Bay Street',
        'city_name' => 'Toronto',
        'country_name' => 'Canada'
        );
$address_bus = new AddressBusiness($address_bus_data);
echo '<tt><pre>'. var_export($address_bus, TRUE) . '</pre></tt>';        
        
echo '<h2>Loading from database and creating an instance of an Address subclass';
echo ' based on the value of the _address_type_id</h2>';
$address_sub = Address::load(2);
echo '<tt><pre>'. var_export($address_sub, TRUE) . '</pre></tt>';

echo '<h2>Now adding address_bus in database passing data array</h2>';
Address::populateDatabase($address_bus_data);

echo '<h2>Now adding another address in database by calling the Address constructor</h2>';
$addnew = new Address;
$addnew->street_address_1 = '337 Ernie Els';
$addnew->city_name = 'Jackman';
$addnew->subdivision_name = 'Maine';
$addnew->country_name = 'USA';
$addnew->address_type_id = '3';
$addnew->populateDBFromAddress();
    






