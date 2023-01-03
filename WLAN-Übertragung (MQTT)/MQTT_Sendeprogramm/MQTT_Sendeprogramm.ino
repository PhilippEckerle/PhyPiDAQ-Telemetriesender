// Sendeprogramm für Arduino-Nano-RP2040-Connect. Für die Verbindung mit dem WLAN
// müssen in der Datei "Einstellungen.h" ssid und Passwort des WLAN's eingegeben 
// werden.

// Author: Philipp Eckerle

#include <WiFiNINA.h>
#include <Arduino_LSM6DSOX.h>
#include <PubSubClient.h>
#include "Einstellungen.h"

float x, y, z;
bool flag;
String message = "stopp";
unsigned long lastMsg = 0;

WiFiClient RP2040Client;
PubSubClient client(RP2040Client);

void setup_wifi() {
  pinMode(LEDG, OUTPUT);
  
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LEDG, HIGH);
    WiFi.begin(ssid, password);
    digitalWrite(LEDG, LOW);
    delay(100);
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("Message arrived on topic: " + String(topic));
  Serial.print("payload:  ");
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println(message);

  if (topic = "Steuerung"){
    if (message == "start"){flag = true;}
    if (message == "stopp"){flag = false;}
    message = "";
  }
}

void reconnect() {
  pinMode(LEDB, OUTPUT);

  while (!client.connected()) {
    digitalWrite(LEDB, HIGH);
    if (client.connect(ClientID,"NULL","NULL",{},{},{},{},0)) {
      digitalWrite(LEDB, LOW);
    } else {
      Serial.print("Connection to broker failed, rc=");
      Serial.println(client.state());
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  // connect to WiFi
  setup_wifi();
  
  // set broker and callback
  client.setServer(BrokerIP, 1883);
  client.setCallback(callback);
  
  // connect to broker and subscribe
  reconnect();
  client.subscribe(Subscribe_Topic, 1);

  // initialize IMU
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  if(flag == true){
    unsigned long now = millis();
    if (now - lastMsg > Abtastrate) {
      lastMsg = now;

      IMU.readAcceleration(x, y, z);

      client.publish(Publish_Topic, (String(x) + " " + 
                                     String(y) + " " + 
                                     String(z)).c_str());
    }
  }
}
