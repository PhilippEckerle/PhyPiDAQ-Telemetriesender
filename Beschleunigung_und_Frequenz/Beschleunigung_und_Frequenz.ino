// Frequenzregelung

#include <WiFiNINA.h>
#include <PubSubClient.h>
#include <Arduino_LSM6DSOX.h>

float x1 = 1.00,x2,y,z;
unsigned long sampleTime;
unsigned long time0 = 0;
unsigned long time1 = 1;
unsigned long periode;
float frequency;
float g;
bool flag = false;

// Adapt this for your own WiFi-Network
const char* ssid        = "raspinet";
const char* password    = "pi=4atan1";
const char* BrokerIP    = "192.168.0.100"; 

// set different ClientID if you use more than one sender
const char* ClientID = "Arduino1";

const char* Publish_Topic = "ms2";
const char* Subscribe_Topic = "Steuerung";

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
  client.loop();
  
  unsigned long currentMillis = millis();
  if (IMU.accelerationAvailable()){
    IMU.readAcceleration(x2,y,z);
    sampleTime = currentMillis;
  }
  //delay(10);
  //IMU.readAcceleration(x2,y,z);

  if (x1 > 0 && x2 > 0){
    if(x2 < x1 && flag == true) {
      g = x1 - 1.00;
      time1 = sampleTime;
      flag = false;
      
      periode = time1 - time0;
      frequency = 1000/periode;
      time0 = time1;

      client.publish(Publish_Topic, (String(g) + " " + 
                                 String(frequency) + " " + 
                                 String(periode)).c_str());
    }
    if(x2 > x1){
      flag = true;
    }

    x1 = x2;
  }
}
