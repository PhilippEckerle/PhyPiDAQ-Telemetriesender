#include <ArduinoBLE.h>
#include <Arduino_LSM6DSOX.h>

// set time between two samples in milliseconds
#define UPDATE_INTERVALL 15

#define ACCEL_SERVICE_UUID         "2ACA" 
#define ACCEL_CHARACTERISTIC_UUID  "2713"

#define NUMBER_OF_SENSORS 3
union multi_sensor_data
{
  struct __attribute__((packed))
  {
    float values[NUMBER_OF_SENSORS];
  };
  uint8_t bytes[NUMBER_OF_SENSORS * sizeof(float)];
};
multi_sensor_data IMU_Data;

BLEService sensorDataService(ACCEL_SERVICE_UUID);
BLECharacteristic sensorDataCharacteristic(ACCEL_CHARACTERISTIC_UUID, BLENotify, sizeof IMU_Data.bytes);

void setup() {
  Serial.begin(115200);
  delay(700);

  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (1);
  }

  if (!IMU.begin()){ 
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  pinMode(LED_BUILTIN, OUTPUT);
  
  BLE.setAdvertisedService(sensorDataService);
  sensorDataService.addCharacteristic(sensorDataCharacteristic);
  BLE.addService(sensorDataService);
  
  BLE.setConnectable(true);
  
  if(BLE.advertise()){
    Serial.println("Bluetooth Device Active, Waiting for Connections...");
  }
}  
  
void loop() {
  static float acc_x, acc_y, acc_z;
  static long previousMillis = 0;
  
  BLEDevice central = BLE.central();

  if(central) {
    Serial.print("Connected to Central");
    while(central.connected()) {
      unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= UPDATE_INTERVALL) {
        previousMillis = currentMillis;
      
        IMU.readAcceleration(acc_x, acc_y, acc_z);
        IMU_Data.values[0] = acc_x;
        IMU_Data.values[1] = acc_y;
        IMU_Data.values[2] = acc_z;
        sensorDataCharacteristic.writeValue(IMU_Data.bytes, sizeof  IMU_Data.bytes);
      }
    }
  }
  Serial.println("Disconnected from Central");
  Serial.print("MAC-Address of Device is: ");
  Serial.println(BLE.address());
  Serial.println();
  
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);      
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);             
  digitalWrite(LED_BUILTIN, LOW);
  delay(300); 
}
