from bluepy import btle
import struct

# Adapt the MAC-Address for your own Sending Device!
MAC                        = "84:cc:a8:79:15:0a"
ACCEL_SERVICE_UUID         = "2ACA"
ACCEL_CHARACTERISTIC_UUID  = "2719"

P = btle.Peripheral(MAC)
service = P.getServiceByUUID(ACCEL_SERVICE_UUID)
ch = service.getCharacteristics(ACCEL_CHARACTERISTIC_UUID)[0]

class MyDelegate(btle.DefaultDelegate):
    def __init__(self, handle):
        btle.DefaultDelegate.__init__(self)

    def handleNotification(self, cHandle, data):
        data = struct.unpack('fff', data)
        data = (round(data[0],2),
                round(data[1],2), 
                round(data[2],2))
        print(data)
        
P.setDelegate(MyDelegate(ch.valHandle+1));

# Enable notifications
P.writeCharacteristic(ch.valHandle+1, b"\x01\x00");

while True:
    if p.waitForNotifications(1):
        # handleNotification() was called
        continue