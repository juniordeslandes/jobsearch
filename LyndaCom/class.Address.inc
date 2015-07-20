<?php

class Address {
    const ADDRESS_TYPE_RESIDENCE = 1;
    const ADDRESS_TYPE_BUSINESS = 2;
    const ADDRESS_TYPE_PARK = 3;
    
    static public $valid_address_types = array(
        Address::ADDRESS_TYPE_RESIDENCE=> 'Residence',
        Address::ADDRESS_TYPE_BUSINESS=> 'Business',
        Address::ADDRESS_TYPE_PARK=> 'Park',
    );
    public $street_address_1;
    public $street_address_2;
    public $city_name;
    public $subdivision_name;
    protected $_postal_code;
    public $country_name;
    
    protected $_address_id;
    protected $_time_created;
    protected $_time_updated;
    protected $_address_type_id;
    
    
    function __construct($data = array()){
        $this->_time_created = time();
        
        if (!is_array($data)){
            trigger_error('Impossible to construct address with '. $data);
        }
        
        if (count($data)>0){
            foreach ($data as $name => $value){
//                special case for protected properties
                if (in_array($name, array('time_created','time_updated',
                    'address_type_id', 'address_id')))
                {
                    $name = '_'.$name;
                }
                $this->$name = $value;
            }
           //now add address to database
           Address::populateDatabase($data); 
        }
        
        
        
    }
    
    /**
     * 
     * @param string $name
     * @return mixed
     */
    function __get($name) {
        if (!$this->_postal_code){
            $this->_postal_code = $this->_postal_code_guess();
        }
      
        $protected_property_name = '_' . $name;
        if (property_exists($this, $protected_property_name)){
        return $this->$protected_property_name;
        }
    
        trigger_error('Undefined property ' . $name);
        return NULL;
        } 
    
    /**
     * 
     * @param string $name
     * @param mixed $value
     */
    public function __set($name, $value) {
        if ($name == 'postal_code'){
        $this->$name = $value;
        return;
        }
        
        if ($name == 'address_type_id'){
            $this->_address_type_id = $value;
            return;
        }
        
        trigger_error('Undefined or unallowed access to '. $name . 'via set method');
        return NULL;
    }
    
    protected function _setAddressTypeID($address_type_id){
       if (self::isValidAddressTypeID($address_type_id)){
           $this->_address_type_id = $address_type_id;
            
        } 
    }
    protected function _postal_code_guess(){
        $db = Database::getInstance();
        $mysqli = $db->getConnection();
        $sql_query = 'SELECT postal_code ';
        $sql_query .= 'FROM location';
        
        $city_name = $mysqli->real_escape_string($this->city_name);
        $sql_query .= ' WHERE city_name = "' . $city_name . '"';
        
        $subdivision_name = $mysqli->real_escape_string($this->subdivision_name);
        $sql_query .= ' AND subdivision_name = "' . $subdivision_name . '"';
        
        $result = $mysqli->query($sql_query);
        
        if ($row = $result->fetch_assoc()){
            return $row["postal_code"];
        }
    }  
        
            
    public function display()
    {
        $output = '';
        $output .= $this->street_address_1;
        $output .= '<br/>';
        if (isset($this->street_address_2)){ 
            $output .= $this->street_address_2;
            $output .= '<br/>';
        }
        $output .= $this->city_name . ', ' . $this->subdivision_name;
        $output .= '<br/>';
        $output .= $this->country_name . '<br/>';
        $output .= $this->postal_code;
        return $output;
    }
    
    /**
     * magic __toString
     * returns string
     */
    public function __toString(){    
        return $this->display();
    }

    /**
     * checks whether the address_type_id provided as argument is valid
     * @param type $address_type_id
     * @return boolean 
     */
    static public function isValidAddressTypeID($address_type_id){
        return array_key_exists($address_type_id, self::$valid_address_types);
    }
   
    /*
     * load a record from address table given an address_id
     * @param address_id
     * @return void
     */
    public final static function load($address_id){
        $db = Database::getInstance();
        $mysqli = $db->getConnection();
        $query = 'SELECT address.* FROM address ';  //address.* est plus securitaire que * surtout avec des joins dans la requete
        $query .= 'WHERE address_id = "' . (int) $address_id . '"';
        $result = $mysqli->query($query);
        $row = $result->fetch_assoc(); //on met le resultat de la requete dans un array
        var_dump($row['address_type_id']);
        if ($row){
            return self::getInstance($row['address_type_id'], $row);
        }    
    }
    
    /* given an address_type_id, determine the corresponding subclass...
     * and create an instance of that subclass.
     * @param string address_type_id
     * @param array data
     */
    final public static function getInstance($address_type_id, $data = array() ){
        $class_name = 'Address' . self::$valid_address_types[$address_type_id];
        var_dump($class_name);
        return new $class_name($data);
    }
    
    /* insert a record in the address table of the database
     * @param array $data
     * return void
     */
    public static function populateDatabase($data = array()){
        $db = Database::getInstance();
        $mysqli = $db->getConnection();
        $arrlength = count($data);
        $counter = 1;
        $ins_fields = 'INSERT INTO address (';
        $ins_values = ' VALUES (';
        foreach ($data as $key => $value)
            {
            $key = ltrim ($key, "_");  // remove leading underscore to match db field names
            
            
            if (is_string($value) && ($key !=="address_type_id")){ //only string key values will be wrapped in ""
                $ins_values .= '"';
            }
            
            if (isset($value)){   //append current key and its value to the query only if value is not null
                $ins_fields .= $key ;
                $ins_values .= $value ;
            }
            
            if (is_string($value) && ($key !=="address_type_id")){  //add closing " for strings in VALUES section of query
                $ins_values .= '"';
            }
            
            if ($counter == $arrlength){  //close parentheses in the query when last key/value pair of the array has been reached
                $ins_fields .= ')';
                $ins_values .= ')';
                }
            elseif (isset($value)){  //only append "," to the query if key value isn't null
                $ins_fields .= ',';
                $ins_values .= ',';
                }
            $counter++;       
            }
            $query = $ins_fields . $ins_values;
          
        $mysqli->query($query);
        }
    
    /* 
     * This function gets the data array from an Address object and then 
     * calls the populateDatabase function.
     * @param Address $address 
     * @return array $data
     */    
    public function populateDBFromAddress(){
        $data = get_object_vars($this);
        Address::populateDatabase($data);
        
    }    
}
        

