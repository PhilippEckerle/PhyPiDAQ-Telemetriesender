from bluepy import btle
import struct
import time

class MyDelegate(btle.DefaultDelegate):
    def __init__(self, handle):
        btle.DefaultDelegate.__init__(self)
        self.handle = handle

    def handleNotification(self, cHandle, data):
        # ... perhaps check cHandle
        data = struct.unpack('fff', data)
        data = (round(data[0],3),round(data[1],3), round(data[2],3))
        print(data)
        time.sleep(0.05)


# Initialisation  -------
MAC                        = "84:cc:a8:79:15:0a"
ACCEL_SERVICE_UUID         = "2BEEF31A-B10D-271C-C9EA-35D865C1F48A"
ACCEL_CHARACTERISTIC_UUID  = "4664E7A1-5A13-BFFF-4636-7D0A4B16496C"
ONOFF_CHARACTERISTIC_UUID  = "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

p = btle.Peripheral(MAC)

# Setup to turn notifications on, e.g.
svc = p.getServiceByUUID(ACCEL_SERVICE_UUID)
#ch_Tx = svc.getCharacteristics(ONOFF_CHARACTERISTIC_UUID)[0]
ch_Rx = svc.getCharacteristics(ACCEL_CHARACTERISTIC_UUID)[0]

p.setDelegate(MyDelegate(ch_Rx.valHandle+1));

#desc = ch_Rx.getDescriptors() #ACCEL_CHARACTERISTIC_UUID???

p.writeCharacteristic(ch_Rx.valHandle+1, b"\x01\x00")


# Main loop --------

while True:
    if p.waitForNotifications(2):
        # handleNotification() was called
        #MyDelegate.handleNotification()
        continue

    print("Waiting...")

    if input() == "s":
        print("Messung starten")
        client.publish(publish_topic, "start")
    if input() == "e":
        client.publish(publish_topic, "stopp")
        print("Messung stoppen")
    else:
        pass