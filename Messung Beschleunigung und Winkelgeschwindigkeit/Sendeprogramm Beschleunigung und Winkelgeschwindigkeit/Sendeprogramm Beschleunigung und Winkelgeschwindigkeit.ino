// Programm zum Messen und Senden von Beschleunigung und Winkelgeschwindigkeit 
// in einem rotierenden System mit einem Arduino Nano RP2040 über ein WLAN-Netz 
// mit dem MQTT-Protokoll. die angegebenen Dreh- und Beschleunigungsachsen müssen
// je nach Lage des Boards eingestellt werden.

// Author: Philipp Eckerle

#include <WiFiNINA.h>
#include <PubSubClient.h>
#include <Arduino_LSM6DSOX.h>


// Adapt this for your own WiFi-Network
const char* ssid        = "ssid_of_your_WiFi";
const char* password    = "password_of_your_WiFi";
const char* BrokerIP    = "xxx.xxx.x.xxx"; 

// set different ClientID if you use more than one sender
const char* ClientID = "Arduino1";

const char* Publish_Topic = "ms2";
const char* Subscribe_Topic = "Steuerung";

float ax,ay,az;
float gx,gy,gz;

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
  delay(700);

  // connect to WiFi
  setup_wifi();
  
  // set broker and callback
  client.setServer(BrokerIP, 1883);
  
  // connect to broker and subscribe
  reconnect();

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
  //client.loop();
  
  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(ax, ay, az);
  }
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(gx, gy, gz);

    gx = (2*3.141*gx)/360;
    gy = (2*3.141*gy)/360;
    gz = (2*3.141*gz)/360;
  }

  // adapt axes according to the position of the board in the rotating system
  // a: acceleration axis
  // g: rotation axis
  client.publish(Publish_Topic, (String(ax) + " " + 
                                 String(gz)).c_str());

}
