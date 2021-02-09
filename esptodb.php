<?php

/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-esp8266-mysql-database-php/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

$servername = "localhost";

// REPLACE with your Database name
$dbname = "REPLACE_WITH_YOUR_DATABASE_NAME";

// REPLACE with table name
$tablename = "REPLACE_WITH_YOUR_TABLE_NAME";

// REPLACE with Database user
$username = "REPLACE_WITH_YOUR_USERNAME";

// REPLACE with Database user password
$password = "REPLACE_WITH_YOUR_PASSWORD";

// Keep this API Key value to be compatible with the ESP32 code provided in the project page. 
// If you change this value, the ESP32 sketch needs to match
$api_key_value = "tPmAT5Ab3j7F9";

// empty the variables
$api_key= $rackID = $tempVal = $humidVal = $rackStat = ""; 

// use GET if you want to inject to database @ for test purpose
// use POST for production
if ($_SERVER["REQUEST_METHOD"] == "GET") {				//GET or POST
	//echo "test";
    $api_key = test_input($_GET["api_key"]); 			//$_GET or $_POST
    if($api_key == $api_key_value) {
        $rackID   = test_input($_GET["rID"]); 			//$_GET or $_POST
        $tempVal  = test_input($_GET["temp"]); 		  	//$_GET or $_POST
        $humidVal = test_input($_GET["humid"]); 	  	//$_GET or $_POST
        $rackStat = test_input($_GET["currentStat"]); 	//$_GET or $_POST
        
        // Create connection
        $conn = new mysqli($servername, $username, $password, $dbname);
        // Check connection
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        } 
        
        $sql = "INSERT INTO $tablename (rackID, tempValue, humidValue, rackStatus)
        VALUES ('" . $rackID . "', '" . $tempVal . "', '" . $humidVal . "', '" . $rackStat . "')";
        
        if ($conn->query($sql) === TRUE) {
            echo "New record created successfully";
        } 
        else {
            echo "Error: " . $sql . "<br>" . $conn->error;
        }
    
        $conn->close();
    }
    else {
        echo "Wrong API Key provided.";
    }

}
else {
    echo "No data posted with HTTP POST.";
}

function test_input($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}