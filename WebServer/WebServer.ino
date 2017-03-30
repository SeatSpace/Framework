#include <SPI.h>
#include <WiFi.h>
const int LDR = A0;
const int LED = 11;
int value;

char ssid[] = "Manav's iPhone";
char pass[] = "manavgupta1";

int status = WL_IDLE_STATUS;
char server[] = "www.kkmonlee.com/launchpad";

WiFiClient client;

void setup() {
  
  pinMode(LDR, INPUT);
  pinMode(LED, OUTPUT);
  
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi not present");
    while(true);
  }

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    // delay(5000);
  }
  Serial.println("Connected!");
  printWiFiStatus();
  Serial.println("Starting connection to server...");

}

void loop() {
  value = analogRead(LDR);
  while (client.av
}

void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

