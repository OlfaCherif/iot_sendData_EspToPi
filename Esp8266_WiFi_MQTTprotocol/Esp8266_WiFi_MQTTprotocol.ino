#include <ESP8266WiFi.h>
#include <PubSubClient.h>


const char* ssid = "ORANGE_7F78";
const char* password = "123456789";


const char* mqtt_server = ""; // Change the variable to the Raspberry Pi IP address, so it connects to your MQTT broker
const char *topic = "esp8266/test";

// Initializes the espClient
WiFiClient espClient;
PubSubClient client(espClient);


// Timers auxiliar variables
long now = millis();

//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701
//ultrasound sensor variables
const int trigPin = 12;
const int echoPin = 14;
long duration;
float distanceCm;
float distanceInch;

// This function connect the ESP8266 To WiFi
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected - ESP IP address: ");
  Serial.println(WiFi.localIP());
}


//a pointer to a message callback function called when a message arrives for a subscription created by this client.
void callback(String topic, byte* message, unsigned int length) {
  String messageTemp; // messageTemp is the message that receives the esp as a subscriber 
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

}


// This function connect the client and be sure that he is subscribed to the topic of MQTT protocol
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) { // if return false then the client is still connecting 
    Serial.print("Attempting MQTT connection...");
    
    if (client.connect("ESP8266Client")) { // this function returns a bolean variable if the client is connected successfully or not and ESP8266Client is the client ID
      Serial.println("connected");  
      client.subscribe("esp8266/4"); //esp8266/4 is a topic
      client.subscribe("esp8266/5"); //esp8266/5 is a topic
    } else { 
      Serial.print("failed, rc=");
      delay(15000);
    }
  }
}

double UltrasonicValue()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  distanceCm = duration * SOUND_VELOCITY/2;
 
 
  // Prints the distance on the Serial Monitor
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  delay(1000);
  return (distanceCm);
} 



void setup() {
 
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}


void loop() {

  if (!client.connected()) { //if the client is not connected 
    reconnect(); 
  }
  client.loop() //This should be called regularly to allow the client to process incoming messages and maintain its connection to the server.

    
 value=UltrasonicValue();
    
    // Publishvalues
    client.publish("esp8266/test", value);
    Serial.print("Value of the sensor ");
    Serial.print(value);
    

  }
}
