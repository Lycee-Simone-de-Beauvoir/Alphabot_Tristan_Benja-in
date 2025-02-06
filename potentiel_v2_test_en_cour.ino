#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <SoftwareSerial.h> // Include SoftwareSerial library

#define NUM_SENSORS 5
unsigned int sensorValues[NUM_SENSORS];
unsigned int last_proportional = 0;
long integral = 0;

#define PWMA 6           // Left Motor Speed pin (ENA)
#define AIN2 A0          // Motor-L forward (IN2)
#define AIN1 A1          // Motor-L backward (IN1)
#define PWMB 5           // Right Motor Speed pin (ENB)
#define BIN1 A2          // Motor-R forward (IN3)
#define BIN2 A3          // Motor-R backward (IN4)
#define PIN 7            // LED pin
#define BT_RX_PIN 3      // Bluetooth RX pin (D2)
#define BT_TX_PIN 2      // Bluetooth TX pin (D3)

int Speed = 150;
Adafruit_NeoPixel RGB = Adafruit_NeoPixel(4, PIN, NEO_GRB + NEO_KHZ800);
SoftwareSerial btSerial(BT_RX_PIN, BT_TX_PIN); // Define SoftwareSerial object for Bluetooth

void setup() {
  Serial.begin(9600);
  btSerial.begin(9600); // Initialize Bluetooth serial communication
  Serial.println("TRSensor example!!");
  pinMode(PWMA, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  
  RGB.begin();
  RGB.show(); // Initialize all pixels to 'off'
}

void loop() {
  if (btSerial.available()) {
    String command = btSerial.readStringUntil(';');     //Essayer lecture lettre par lettre + mettre tempo de 2ms après la lecture
    //command.trim(); // Remove any trailing newline characters
    Serial.println("Received command: " + command); // Print the received command for debugging
    
    // if (command == "Avance") {
    //   moveForward();
    // } else if (command == "Recule") {
    //   moveBackward();
    // } else if (command == "Gauche") {
    //   turnLeft();
    // } else if (command == "Droite") {
    //   turnRight();
    // } else if (command == "Stop") {
    //   stopMovement();
    // }
  }
}

void moveForward() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMA, Speed);
  analogWrite(PWMB, Speed);
  setLEDColor(0x00FF00); // Green for forward
}


void turnLeft() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, LOW);
  digitalWrite(BIN2, HIGH);
  analogWrite(PWMA, Speed);
  analogWrite(PWMB, Speed);
  setLEDColor(0xFFFF00); // Yellow for left
}

void turnRight() {
  digitalWrite(AIN1, LOW);
  digitalWrite(AIN2, HIGH);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMA, Speed);
  analogWrite(PWMB, Speed);
  setLEDColor(0x0000FF); // Blue for right
}

void moveBackward() {
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);
  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);
  analogWrite(PWMA, Speed);
  analogWrite(PWMB, Speed);
  setLEDColor(0xFF0000); // Red for backward
}

void stopMovement() {
  analogWrite(PWMA, 0);
  analogWrite(PWMB, 0);
  setLEDColor(0xFFFFFF); // White for stop
}

void setLEDColor(uint32_t color) {
  for (int i = 0; i < 4; i++) {
    RGB.setPixelColor(i, color);
  }
  RGB.show();
}
