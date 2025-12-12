# distance_controller.py
import paho.mqtt.client as mqtt

BROKER = "172.16.114.108"
PORT = 1883
DIST_THRESHOLD = 10.0  # cm

T_DIST = "iot/esp32/distance"
T_LED  = "iot/esp8266/led"

def on_connect(client, userdata, flags, rc):
    print("Connected rc=", rc)
    client.subscribe(T_DIST)

def on_message(client, userdata, msg):
    try:
        d = float(msg.payload.decode().strip())
    except:
        print("bad payload:", msg.payload)
        return
    print("Distance:", d)
    if d != 9999 and d < DIST_THRESHOLD:
        client.publish(T_LED, "ON")
        print("-> LED ON")
    else:
        client.publish(T_LED, "OFF")
        print("-> LED OFF")

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect(BROKER, PORT, 60)
client.loop_forever()
