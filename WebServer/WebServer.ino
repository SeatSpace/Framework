#include <SPI.h>
#include <WiFi.h>
const int LDR = A0;
const int BUILTIN = 13;
int value;

char ssid[] = "Manav's iPhone";
char pass[] = "manavgupta1";

int status = WL_IDLE_STATUS;

WiFiServer server(80);

void setup() {
  pinMode(BUILTIN, OUTPUT);
  pinMode(LDR, INPUT);
  
  Serial.begin(9600);
  while (!Serial) {
    ;
  }

  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi module doesn't exist.");
    while (true);
  }

  while (status != WL_CONNECTED) {#include <SPI.h>
#include <WiFi.h>

const int LDR = A0;
const int LED = 11;
char ssid[] = "Manav's iPhone";      // your network SSID (name) 
char pass[] = "manavgupta1";   // your network password
int keyIndex = 0;                 // your network key Index number (needed only for WEP)

int value;

int status = WL_IDLE_STATUS;

WiFiServer server(80);

void setup() {
  pinMode(LDR, INPUT);
  pinMode(LED, OUTPUT);
  
  //Initialize serial and wait for port to open:
  Serial.begin(9600); 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present"); 
    // don't continue:
    while(true);
  } 
  
  // attempt to connect to Wifi network:
  while ( status != WL_CONNECTED) { 
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:    
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
  } 
  server.begin();
  // you're connected now, so print out the status:
  printWifiStatus();
}


void loop() {
  value = analogRead(LDR);
  // listen for incoming clients
  WiFiClient client = server.available();
  
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 2");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");

          if (value > 500) {
            digitalWrite(LED, LOW);
            client.print("0");
          } else {
            digitalWrite(LED, HIGH);
            client.print("1");
          }
          
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(100);
    
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}


void printWifiStatus() {
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
    Serial.print("Attempting to connect to ");
    Serial.println(ssid);

    status = WiFi.begin(ssid, pass);

    delay(5000);
  }
  server.begin();
  printWiFiStatus();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");

    boolean isCurrentLineBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
      }
    }
  }
}

