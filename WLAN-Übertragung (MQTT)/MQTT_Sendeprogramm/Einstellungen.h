
// Adapt this for your own WiFi-Network
const char* ssid        = "raspinet";
const char* password    = "pi=4atan1";
const char* BrokerIP    = "192.168.0.100"; 

// set time between two samples in milliseconds
unsigned long Abtastrate = 10;

// set different ClientID if you use more than one sender
const char* ClientID = "Arduino1";

const char* Publish_Topic = "ms2";
const char* Subscribe_Topic = "Steuerung";