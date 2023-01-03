import paho.mqtt.client as mqtt

mqtt_broker_ip  = "127.0.0.1"  #Standard "localhost"
subscribe_topic = "ms2"
publish_topic   = "Steuerung"

client = mqtt.Client()

# As soon as client is connected to broker, subscribe to Topic
def on_connect(client, userdata, flags, rc):
    print("Connected!", str(rc))
    client.subscribe(subscribe_topic)

def on_message(client, userdata, msg):
    str=msg.payload.decode("utf-8")
    list = str.split(" ")           
    print(float(list[0]), float(list[1]), float(list[2]))           

client.on_connect = on_connect
client.on_message = on_message

# Connect to the broker
client.connect(mqtt_broker_ip, 1883)

# Run continously
client.loop_start()

while True:
    if input() == "s":
        print("Messung starten")
        client.publish(publish_topic, "start")
    if input() == "e":
        client.publish(publish_topic, "stopp")
        print("Messung stoppen")
    else:
        pass