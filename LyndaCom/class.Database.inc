<?php

class Database{
  
    private $_connection;
    private static $_instance;
    
    public static function getInstance(){
        if (!self::$_instance){
            self::$_instance = new self();   
        }
        return self::$_instance;
    }
    
    public function __construct(){
        $this->_connection = new mysqli('localhost', 'root', 'Stop!123...', 'mabase');
        if (mysqli_connect_error()){
            trigger_error('Failed to connect to database'. mysqli_connect_error(),E_USER_ERROR);
        }
    }
    
    
    /* empty clone method to prevent connection from being cloned
     * 
     */
    private function __clone(){}
    
    public function getConnection(){
        return $this->_connection;
    }
    
    
}


