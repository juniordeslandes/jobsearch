<?php

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


class Connect2Gmail{

//Try connecting to Gmail inbox
public static function inbox(){
    $hostname = '{imap.gmail.com:993/imap/ssl}INBOX';
    $username = 'michelj.deslandes@gmail.com';
    $password = 'Stop!123...';    
    
    try{
        $inbox = imap_open( $hostname , $username , $password );
        return $inbox;
    }
    catch (Exception $excep){
        echo 'Could not connect to GMail account: ' . $excep;
    }
}
 
}



