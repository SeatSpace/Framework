#include <WiFi.h>

// WiFiClient instance
WiFiClient client;

// 2 LDRs on A0 and A1
int LDR1 = A0;
int LDR2 = A1;

// WiFi details (subject to change)
char ssid[] = "OnePlus3";
char password[] = "82718271";
int status = WL_IDLE_STATUS;

// Primary server address (domain only)
char server[] = "www.kkmonlee.com";

// analogRead of LDR1 and LDR2
int value1, value2;

void setup() {
  // Start at baud 9600
  Serial.begin(9600);
  pinMode(LDR1, INPUT);
  pinMode(LDR2, INPUT);
  // Connect to WiFi
  connectWifi();
  // Print WiFi status (verbose)
  printWifiStatus();
  // postData();
}

void loop() {
  // value1 and value2 subject to being volatile type
  value1 = analogRead(LDR1);
  value2 = analogRead(LDR2);

  // HTTP GET to execute PHP script on web server
  postData();

  // Do this every 5 seconds
  delay(5000);
}

// Connects to WiFi access point
void connectWifi() {
  // Keep looping until connected
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, password);
    // Try every 0.5 seconds so as to not get rejected by the access point
    delay(500);
  }
}

// Prints WiFi connection details in verbose
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

// Executes GET request to PHP
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

  // Important to stop client after every loop since only 9 
  // instances can be connected 
  // Otherwise "No Socket available" is printed
  while (client.available()) {
    client.stop();
  }
}
