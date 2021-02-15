/* WITH LIVE READING FROM DHT11 - SZS
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-esp8266-mysql-database-php/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

*/

#ifdef ESP32
  // this will compile for ESP32 board
  #include <WiFi.h>
  #include <HTTPClient.h>
#else
  // this will compile for ESP8266, NodeMCU boards
  #include <ESP8266WiFi.h>
  #include <ESP8266HTTPClient.h>
  #include <WiFiClient.h>
#endif

#include <dht11.h>
dht11 DHT;
#define DHT11_PIN 4

// Replace with your network credentials
const char* ssid     = "air24";//REPLACE_WITH_YOUR_SSID";
const char* password = "polis12345";//REPLACE_WITH_YOUR_PASSWORD";

// REPLACE with your Domain name and URL path or server's IP address with path
const char* serverName = "http://192.168.1.102/a-my/esptodb.php";

// Keep this API Key value to be compatible with the PHP code provided in the project page. 
// If you change the apiKeyValue value, the PHP file "/esptodb.php" also needs to have the same key 
String apiKeyValue = "tPmAT5Ab3j7F9";

String sensorID = "a1";
//// latihan
////String sensorLocation = "Office";


void setup() {
  Serial.begin(115200);
  
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  //Read humid & temp
  int chk = DHT.read(DHT11_PIN);    // READ DATA
  
  //Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
    
    // Your Domain name with URL path or IP address with path
    http.begin(serverName);
    
    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    // Prepare your HTTP POST request data
    String httpRequestData = "api_key=" + apiKeyValue + "&rID=" + sensorID + "&temp=" + DHT.temperature  + "&humid=" + DHT.humidity + "&currentStat=" + "norMALis";                      
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
    
    // You can comment the httpRequestData variable above
    // then, use the httpRequestData variable below (for testing purposes without the DHT11 sensor) -->Similar with Line#66
    //String httpRequestData = "api_key=tPmAT5Ab3j7F9&rID=abc&temp=123&humid=24.75&currentStat=norMALis";

    // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);
     
    // If you need an HTTP request with a content type: text/plain
    //http.addHeader("Content-Type", "text/plain");
    //int httpResponseCode = http.POST("Hello, World!");
        
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  //Send an HTTP POST request every 30 seconds
  delay(30000);  
}
