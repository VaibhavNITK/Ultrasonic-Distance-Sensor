#include <ThingSpeak.h> // Include the ThingSpeak library
#include <WiFi.h> // Include the WiFi library

const char *ssid = "Wokwi-GUEST"; // Replace "YOUR_WIFI_SSID" with your WiFi SSID
const char *password = ""; // Replace "YOUR_WIFI_PASSWORD" with your WiFi password

WiFiClient client;

unsigned long myChannelNumber = 2482793; // Replace "YOUR_CHANNEL_NUMBER" with your ThingSpeak channel number
const char * myWriteAPIKey = "MB38NCR7SD2KBCJ2"; // Replace "YOUR_API_KEY" with your ThingSpeak write API key

int Trig_pin = 5;
int Echo_pin = 18;
long duration;
float Speed_of_sound = 0.034;
float dist_in_cm;

void setup() {
  Serial.begin(115200);
  pinMode(Trig_pin, OUTPUT);
  pinMode(Echo_pin, INPUT);

  WiFi.begin(ssid, password); // Connect to WiFi

  ThingSpeak.begin(client); // Initialize ThingSpeak
}

void loop() {
  digitalWrite(Trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig_pin, LOW);

  duration = pulseIn(Echo_pin, HIGH);

  dist_in_cm = duration * Speed_of_sound / 2;
  Serial.print("Distance in cm: ");
  Serial.println(dist_in_cm);

  // Update ThingSpeak channel with the measured distance
  ThingSpeak.writeField(myChannelNumber, 1, dist_in_cm, myWriteAPIKey);

  delay(1500); // Wait for 15 seconds before sending the next update
}

