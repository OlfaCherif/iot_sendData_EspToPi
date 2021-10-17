import paho.mqtt.client as mqtt

def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    #reconnect then subscriptions will be renewed
    client.subscribe("esp8266/test")
    

def on_message(client, userdata, message):
    print("Data received" + str(message.payload) + "' on topic '" + message.topic)
    

def main():
    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message

    client.connect('localhost', 1883, 60) 
    # Connect to the MQTT server and process messages in a background thread. 
    client.loop_start() 

main()