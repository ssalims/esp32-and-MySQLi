/*16feb-- not this - szs
  * ESP32 Web Server - STATION Mode
*/
//===============================================================
// Load Libraries
//===============================================================

#include <WiFi.h> 
#include <WebServer.h>
#include <ESPmDNS.h>
  #include <HTTPClient.h>
    //#include <WiFiClient.h>


#include <dht11.h>
dht11 DHT;
#define DHT11_PIN 4

//===============================================================
// Initialization
//===============================================================

// enter your network credentials
const char* ssid = "air24";
const char* password = "polis12345";

// port 80 is default website port
///WebServer server(80);  

// REPLACE with your Domain name and URL path or IP address with path
const char* serverName = "http://192.168.1.102/a-my/esptodb.php?";

// Keep this API Key value to be compatible with the PHP code provided in the project page. 
// If you change the apiKeyValue value, the PHP file /post-esp-data.php also needs to have the same key 
String apiKeyValue = "tPmAT5Ab3j7F9"; //test data

String sensorID = "1a"; // test data
//api_key,rID,temp,humid,currentStat
//===============================================================
// Setup Function
//===============================================================

void setup() {
  Serial.begin(115200);
  Serial.print("Connecting to: ");
  Serial.println(ssid);

  // set ESP32 mode
  // WiFi.mode(mode);   
  
  // ESP32 will connect to your WiFi modem with SSID & PASSWORD
  WiFi.begin(ssid, password);  

  // wait until ESP32 connect to WiFi
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected successfully");
  Serial.print("Your ESP32 IP: ");
  
  // display "ESP32 IP Address" at Serial Monitor
  Serial.println(WiFi.localIP());  

  // set up mDNS responder:
  // "http://esp32.local" instead of "http://IPaddress"
  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }
 
  // attach handles
////  server.on("/", handle_root); 
  
  // "http://ipaddress/inline" OR "htpp://esp32.local/inline"
////  server.on("/inline", []() { 
////    server.send(200, "text/plain", "this works as well");
////  });
 
  // start web server
////  server.begin();
////  Serial.println("HTTP server started");
  delay(100); 

  // print key WiFi diagnostic information
////  WiFi.printDiag(Serial);
 
 // print the received signal strength:
////  long rssi = WiFi.RSSI();
////  Serial.print("RSSI:");
////  Serial.println(rssi);
    
} // end of void setup( ) function

//===============================================================
// Loop Function
//===============================================================

void loop() {
  // monitors the presence of a client 
  // and delivers the requested HTML page
  server.handleClient();
} //end of loop function

//===============================================================
// Other Functions
//===============================================================

// Handle root url (/)
void handle_root() {
  server.send(200, "text/html", SendHTML()); 
}

// HTML & CSS contents which display on web server
// park your GPIO activities in "SendHtml( )" function
String SendHTML( ){
  // returns the number of milliseconds that 
  // your ESP32 board since powered up, 
  // & become zero when reset or unplugged
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;
  int chk = DHT.read(DHT11_PIN);    // READ DATA
HTTPClient http;
http.begin(serverName);
  //
  //api_key,rID,temp,humid,currentStat


  // Prepare your HTTP POST request data
    String httpRequestData = "api_key=" + apiKeyValue + "&rID=" + sensorID
                      + "&temp=" + DHT.temperature  + "&humid=" + DHT.humidity
                          + "&currentStat=" + "norMAL";

  // Send HTTP POST request
    int httpResponseCode = http.POST(httpRequestData);
     Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
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
