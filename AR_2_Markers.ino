#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "JioFiber-Suni";
const char* password = "3521@KiiT";

WebServer server(80);

// Define two LED pins
#define LED1_PIN 4
#define LED2_PIN 5   // Change if needed

bool led1State = false;
bool led2State = false;

// -------- LED 1 Handler --------
void toggleLED1() {
  led1State = !led1State;
  digitalWrite(LED1_PIN, led1State);
  
  Serial.print("LED 1 State: ");
  Serial.println(led1State ? "ON" : "OFF");

  server.send(200, "text/plain", led1State ? "LED1 ON" : "LED1 OFF");
  delay(500);
}

// -------- LED 2 Handler --------
void toggleLED2() {
  led2State = !led2State;
  digitalWrite(LED2_PIN, led2State);
  // delay(500);
  Serial.print("LED 2 State: ");
  Serial.println(led2State ? "ON" : "OFF");

  server.send(200, "text/plain", led2State ? "LED2 ON" : "LED2 OFF");
  delay(500);
}

void setup() {
  Serial.begin(115200);

  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);

  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nESP32 Connected");
  Serial.print("ESP32 IP: ");
  Serial.println(WiFi.localIP());

  // Define routes
  server.on("/led1", toggleLED1);
  server.on("/led2", toggleLED2);

  server.begin();
}

void loop() {
  server.handleClient();
}