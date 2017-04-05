#include <SPI.h>
#include <WiFi.h>

WiFiClient client;

int ledPin = 13;
int motionPin = 3;
int id = 1;
int timeSpan=10;

int motionValue;
int prev;
int status = WL_IDLE_STATUS;

char ssid[]= "OnePlus3";
char password[] = "82718271";

char server[] = "www.kkmonlee.com";

void setup() {
  prev = 2;
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(motionPin, INPUT);
  digitalWrite(ledPin, LOW);

  connectWiFi();
  printWiFiStatus();
}

void loop() {
  int curr = checkPresence();
  
  Serial.println(curr);
  digitalWrite(ledPin, curr);
  
  if (prev != curr) {
    postData(curr);
  } else {
    Serial.println("Same value");
  }
  prev = curr;
}

int checkPresence(){
  int previous = 420;
  int current = digitalRead(motionPin);
  for(int i = 0; i < timeSpan; i++) {
    if(previous == current) {
      previous = current;
      delay(1000);
    } else {
      delay((timeSpan-i)*1000);
      return current;
    }
  }
  return current;
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

void postData(int val) {
  if (!client.connected()) {
    client.flush();
    if (client.connect(server, 80)) {
      client.flush();
      Serial.println("SENDING => " + String(val));
      String data = "taken=" + String(val) + "&id=" + String(id);
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

