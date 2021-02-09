<!DOCTYPE html>
<html>

<head><meta name="viewport" content="width=device-width, initial-scale=1.0, user-scalable=no">
  <title>ESP32 Web Page</title>
  <meta http-equiv=refresh content=5>
  <style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}
         body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}
         p {font-size: 24px;color: #444444;margin-bottom: 10px;}
  </style>
  </head>
<body>  
  <div id="webpage">
    <h1>My Portable Data Center<br>
    Temperature & Humidity Monitoring System</h1>
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

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql = "SELECT logDateTime, rackID, tempValue, humidValue, rackStatus FROM $tablename ORDER BY id DESC";

echo '<table cellspacing="5" cellpadding="5">
      <tr> 
        <td><b>Rack ID</b></td> 
        <td><b>Timestamp</b></td> 
        <td><b>Temparature (&#8451;)</b></td> 
        <td><b>Humidity (%)</b></td> 
        <td><b>Rack Status</b></td>
      </tr>';
 
if ($result = $conn->query($sql)) {
    while ($row = $result->fetch_assoc()) {
        $row_id = $row["rackID"];
        $row_log = $row["logDateTime"];
        $row_temp = $row["tempValue"];
        $row_humid = $row["humidValue"];
        $row_stats = $row["rackStatus"]; 
        // Uncomment to set timezone to - 1 hour (you can change 1 to any number)
        //$row_reading_time = date("Y-m-d H:i:s", strtotime("$row_reading_time - 1 hours"));
      
        // Uncomment to set timezone to + 4 hours (you can change 4 to any number)
        //$row_reading_time = date("Y-m-d H:i:s", strtotime("$row_reading_time + 4 hours"));
      
        echo '<tr> 
                <td>' . $row_id . '</td> 
                <td>' . $row_log . '</td> 
                <td>' . $row_temp . '</td> 
                <td>' . $row_humid . '</td> 
                <td>' . $row_stats . '</td>
              </tr>';
    }
    $result->free();
}

$conn->close();
?> 
</table>
</div>
</body>
</html>