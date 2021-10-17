# iot_sendData_EspToPi
This project is about sending Data of an ultrasonic sensor connected to an Esp8266 Node MCU to the Raspberry pi3.
The Esp8266 and the raspberry pi are connected to a MQTT protocol via WiFi

Command on raspberry pi :

UPDATE THE RASPBERRY:
sudo apt-get update
sudo apt-get upgrade

sudo apt install -y mosquitto-clients : This command install the mosquitto
mosquitto -v
moosquitto -d : This command start the process

mosquitto_sub -d -t testing : This command subscribe to the topic testing
mosquitto_pub -d -t testing -m "HELLO" : This command publish the message "HELLO" on the topic testing 

pip install paho-mqtt :Command to install the library on python
