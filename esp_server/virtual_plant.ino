#include <WiFi.h>

const char* ssid = "yale wireless";  // Replace with your Wi-Fi network name
const char* password = "";  // Replace with your Wi-Fi network password

WiFiServer server(80);  // Start a server on port 80

int photoresistorPin = 34;  // Analog pin for photoresistor
int touchPin = 4;

void setup() {
  Serial.begin(115200);
  pinMode(photoresistorPin, INPUT);
  pinMode(touchPin, INPUT);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  
  Serial.println("Connected to Wi-Fi");
  server.begin();  // Start the server
  Serial.print("Server started at: ");
  Serial.println(WiFi.localIP());  // Show the IP address
}

void loop() {
  WiFiClient client = server.available();  // Listen for incoming clients

  if (client) {
    Serial.println("Client connected");
    String data1 = String(analogRead(photoresistorPin));  // Read photoresistor value
    String data2 = String(touchRead(touchPin));  // Read touch value
    Serial.println("Sending photoresistor value: " + data1);
    Serial.println("Sending touch value: " + data2);
    client.println(data1 + " | " + data2);  // Send the data to the client (Raspberry Pi)
    client.stop();  // Close the connection
    delay(100);  // Send every second
  }
}