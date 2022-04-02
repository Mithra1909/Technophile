//Include ESP8266WiFi.h
#include <ESP8266WiFi.h>

//Include Firebase ESP8266 library (this library)
#include <FirebaseESP8266.h>
#include<TinyGPS++.h>

//Define the Firebase Data object
FirebaseData fbdo;

// Define the FirebaseAuth data for authentication data
FirebaseAuth auth;
TinyGPSPlus gps;

// Define the FirebaseConfig data for config data
FirebaseConfig config;

// Assign the project host and api key (required)
config.host = "https://locate-rec-default-rtdb.firebaseio.com/";

config.api_key = "AIzaSyDWiKX80He02l-kzUYyqIxyhiiz8ftTtWI";

// Assign the user sign in credentials
auth.user.email = "shalini.m.2019.cse@rajalakshmi.edu.in";

auth.user.password = "espdemo";

//Initialize the library with the Firebase authen and config.
Firebase.begin(&config, &auth);

//Optional, set AP reconnection in setup()
Firebase.reconnectWiFi(true);

//Optional, set number of error retry
Firebase.setMaxRetry(fbdo, 3);

//Optional, set number of error resumable queues
Firebase.setMaxErrorQueue(fbdo, 30);

//Optional, use classic HTTP GET and POST requests. 
//This option allows get and delete functions (PUT and DELETE HTTP requests) works for 
//device connected behind the Firewall that allows only GET and POST requests.   
Firebase.enableClassicRequest(fbdo, true);

//Optional, set the size of BearSSL WiFi to receive and transmit buffers
//Firebase may not support the data transfer fragmentation, you may need to reserve the buffer to match
//the data to be transported.
fbdo.setBSSLBufferSize(1024, 1024); //minimum size is 512 bytes, maximum size is 16384 bytes

//Optional, set the size of HTTP response buffer
//Prevent out of memory for large payload but data may be truncated and can't determine its type.
fbdo.setResponseSize(1024); //minimum size is 1024 bytes




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  while(Serial.available()>0)
  {
    if(gps.encode(Serial.read()))
    {
      displayInfo();
    }
  }

}
void displayInfo()
{
  Serial.print(F("Location:"));
  if(gps.location.isValid())
  {
    Serial.print(gps.location.lat(),8);
    Serial.print(F(","));
    Serial.print(gps.location.lng(),8);
  }
  else
  {
     Serial.print(F("INVALID"));
    
  }
  Serial.println();
}
