
// Adapt this for your own WiFi-Network
const char* ssid        = "ssid_of_your_WiFi";
const char* password    = "password_of_your_WiFi";
const char* BrokerIP    = "xxx.xxx.x.xxx"; 

// set time between two samples in milliseconds
unsigned long Abtastrate = 10;

// set different ClientID if you use more than one sender
const char* ClientID = "Arduino1";

const char* Publish_Topic = "ms2";
const char* Subscribe_Topic = "Steuerung";
