// buttonthing32 - a variation of buttonthing for ESP32

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>

// put the WIFI credentials in wificreds.h, in the same directory as buttonthing.cpp (this file) with the lines:
// const char* ssid = "WIFI SSID";
// const char* password = "WIFI SECRET PASSWORD";
// (uncommented, of course)
#include "wificreds.h"

const char* host = "max.kenkl.org";

const unsigned int clienttimeout = 60000;  //ms for client timeout in the doThing* actions
const int led = 13;

const int button1 = 12;
const char* url1 = "/lights/but7.php";
int button1State = 0;

void doThing(const char* url);

void setup() {
  pinMode(button1, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  digitalWrite(led, 1);
  Serial.begin(115200);
  Serial.println();
  Serial.println("buttonthing32 - 20200205");
  Serial.println("fires /lights/but7.php on Max, in response to button on GPIO12");

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Explicitly set the ESP32 to be a WiFi-client
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Serial.println("Startup complete. Waiting for button press...");
  Serial.println();

  digitalWrite(led, 0);
}

void loop() {
  button1State = digitalRead(button1);

  if(button1State == LOW) {
    Serial.println("button 1 pressed");
    digitalWrite(led, 1);
    while(digitalRead(button1) == LOW) {
       // debounce. wait until button is released.
    }
    doThing(url1);
  }
  else {
    digitalWrite(led, 0);
  }


}

void doThing(const char* url) {

  digitalWrite(led, 1); // light up a pilot while we connect, send, and get a response.

  Serial.println("Got to doThing...");
  Serial.print("connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // We now create a URI for the request

  Serial.print("Requesting URL: ");
  Serial.println(url);

  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
             "Host: " + host + "\r\n" +
             "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > clienttimeout) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  Serial.println("closing connection");
  Serial.println();

  digitalWrite(led, 0); // turn off the pilot

}
