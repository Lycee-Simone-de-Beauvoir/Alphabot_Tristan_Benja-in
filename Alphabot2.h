#ifndef ALPHABOT2_H
#define ALPHABOT2_H

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <SoftwareSerial.h> // Include SoftwareSerial library

#define PWMA 6           // Left Motor Speed pin (ENA)
#define AIN2 A0          // Motor-L forward (IN2)
#define AIN1 A1          // Motor-L backward (IN1)
#define PWMB 5           // Right Motor Speed pin (ENB)
#define BIN1 A2          // Motor-R forward (IN3)
#define BIN2 A3          // Motor-R backward (IN4)
#define PIN 7            // LED pin
#define BT_RX_PIN 3      // Bluetooth RX pin (D2)
#define BT_TX_PIN 2      // Bluetooth TX pin (D3)

class Alphabot2 {
  private:
    Adafruit_NeoPixel RGB;
    SoftwareSerial btSerial;

  public:
    Alphabot2() : RGB(4, PIN, NEO_GRB + NEO_KHZ800), btSerial(BT_RX_PIN, BT_TX_PIN) {
      // Initialisation des composants
      Serial.begin(9600);
      btSerial.begin(9600); // Initialiser la communication Bluetooth
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
      RGB.show(); // Initialiser les pixels LED (tout éteint)
    }

    void avancer(int vitesse) {
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, HIGH);
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, HIGH);
      analogWrite(PWMA, vitesse);
      analogWrite(PWMB, vitesse);
      setLEDColor(0x00FF00); // Vert pour avancer
    }

    void reculer(int vitesse) {
      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
      analogWrite(PWMA, vitesse);
      analogWrite(PWMB, vitesse);
      setLEDColor(0xFF0000); // Rouge pour reculer
    }

    void droite(int vitesse) {
      digitalWrite(AIN1, LOW);
      digitalWrite(AIN2, HIGH);
      digitalWrite(BIN1, HIGH);
      digitalWrite(BIN2, LOW);
      analogWrite(PWMA, vitesse);
      analogWrite(PWMB, vitesse);
      setLEDColor(0x0000FF); // Bleu pour droite
    }
	
    void gauche(int vitesse) {
      digitalWrite(AIN1, HIGH);
      digitalWrite(AIN2, LOW);
      digitalWrite(BIN1, LOW);
      digitalWrite(BIN2, HIGH);
      analogWrite(PWMA, vitesse);
      analogWrite(PWMB, vitesse);
      setLEDColor(0xFFFF00); // Jaune pour gauche
    }

    void stop() {
      analogWrite(PWMA, 0);
      analogWrite(PWMB, 0);
      setLEDColor(0xFFFFFF); // Blanc pour stop
    }

  private:
    void setLEDColor(uint32_t color) {
      for (int i = 0; i < 4; i++) {
        RGB.setPixelColor(i, color);
      }
      RGB.show();
    }
};

#endif
