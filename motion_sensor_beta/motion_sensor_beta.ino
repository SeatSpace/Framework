/*Darryl's drunk code*/
#include <SPI.h>
#include <WiFi.h>

WiFiClient client;

int ledPin = 13;
int motionPin[] = {3,4,5,6};
int id[] = {1,2,3,4};
int timeSpan = 10;
int elements = 4;
int motionValue;
int prev[] = {2,2,2,2};
int status = WL_IDLE_STATUS;
int current[] = {0,0,0,0};
char ssid[]= "OnePlus3";
char password[] = "82718271";

char server[] = "www.kkmonlee.com";

void setup(){
  Serial.begin(9600);
  for(int i=0; i<elements; i++) {
    digitalWrite(motionPin[i], LOW);
    pinMode(motionPin[i], INPUT);
  }
  connectWiFi();
  printWiFiStatus();
}

void loop() {
  checkPresence();
  
  for(int i = 0; i < elements; i++) {
    Serial.print(current[i] + ",");

    if (prev[i] != current[i]) {
      postData(current[i], i);
    } else {
      Serial.println("Same value");
    }
    
    prev[i] = current[i];
  }
}

void checkPresence() {
  int previous[] = {0, 0, 0, 0};
  int changed[] = {0, 0, 0, 0};
  int i = 0;
  int j = 0;
  for(j = 0; j < timeSpan; j++) {
    for (i = 0; i < elements; i++) {
      current[i] = digitalRead(motionPin[i]);
      if(previous[i] != current[i] && changed[i] == 0) {
        changed[i]=1;
       }
      previous[i] = current[i];
    }
    delay(1000);
  }
}

void connectWiFi() {
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, password);
    delay(500);
  }
}


void printWiFiStatus() {
  // Print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // Print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // Print the received signal strength
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}

void postData(int val, int i) {
  if (!client.connected()) {
    client.flush();
    if (client.connect(server, 80)) {
      client.flush();
      Serial.println("SENDING => " + String(val));
      String data = "taken=" + String(val) + "&id=" + String(id[i]);
      client.print("GET /launchpad/server/add_data.php?");
      client.print(data);
      client.println(" HTTP/1.1");
      client.println("Host: www.kkmonlee.com");
      client.println("Connection: close");
      client.println();
      delay(10);

       // testing timeouts
        unsigned long timeout = millis();
        while (client.available() == 0) {
          if (millis() - timeout > 5000) {
            Serial.println("Client timeout!");
            client.stop();
            return;
          }
        }
    } else {
      Serial.println("Connection failed");
      client.stop();
    }
  } else {
    client.stop();
    delay(1000);
  }

  while (client.available()) {
    client.stop();
  }
}
