#include <SPI.h>
#include <WiFi.h>
WiFiClient client;
int LDR1 = A0;
int LDR2 = A1;
char ssid[] = "OnePlus3";
char password[] = "82718271";
int status = WL_IDLE_STATUS;


char server[] = "www.kkmonlee.com";
int value1, value2;

void setup() {
  Serial.begin(9600);
  pinMode(LDR1, INPUT);
  pinMode(LDR2, INPUT);
  connectWifi();
  printWifiStatus();
  // postData();
}

void loop() {
  value1 = analogRead(LDR1);
  value2 = analogRead(LDR2);
  postData();

  delay(10000);
}

void connectWifi() {
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, password);
    delay(500);
  }
}

void printWifiStatus() {
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

void postData() {
  if (!client.connected()) {
    client.flush();
    if (client.connect(server, 80)) {
      client.flush();
      Serial.println("Connecting...");
      Serial.println("Value 1: " + String(value1));
      Serial.println("Value 2: " + String(value2));
      if (value1 > 350 && value2 > 350) {
        Serial.println("0,0");
        String data = "value=0,0";
        client.print("GET /launchpad/client.php?");
        client.print(data);
        client.println(" HTTP/1.1");
        client.println("Host: www.kkmonlee.com");
        client.println("Connection: close");
        client.println(); client.println();
        delay(1);

        // testing timeouts
        unsigned long timeout = millis();
        while (client.available() == 0) {
          if (millis() - timeout > 5000) {
            Serial.println("Client timeout!");
            client.stop();
            return;
          }
        }
      } else if (value1 <= 350 && value2 > 350) {
        Serial.println("1,0");
        String data = "value=1,0";
        client.print("GET /launchpad/client.php?");
        client.print(data);
        client.println(" HTTP/1.1");
        client.println("Host: www.kkmonlee.com");
        client.println("Connection: close");
        client.println(); client.println();
        delay(1);

        // testing timeouts
        unsigned long timeout = millis();
        while (client.available() == 0) {
          if (millis() - timeout > 5000) {
            Serial.println("Client timeout!");
            client.stop();
            return;
          }
        }
      } else if (value1 > 350 && value2 <= 350) {
        Serial.println("0,1");
        String data = "value=0,1";
        client.print("GET /launchpad/client.php?");
        client.print(data);
        client.println(" HTTP/1.1");
        client.println("Host: www.kkmonlee.com");
        client.println("Connection: close");
        client.println(); client.println();
        delay(1);

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
        Serial.println("1,1");
        String data = "value=1,1";
        client.print("GET /launchpad/client.php?");
        client.print(data);
        client.println(" HTTP/1.1");
        client.println("Host: www.kkmonlee.com");
        client.println("Connection: close");
        client.println(); client.println();
        delay(1);

        // testing timeouts
        unsigned long timeout = millis();
        while (client.available() == 0) {
          if (millis() - timeout > 5000) {
            Serial.println("Client timeout!");
            client.stop();
            return;
          }
        }
      }
      Serial.println("LOL");
      WiFi.disconnect();
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
