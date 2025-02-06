#include <SoftwareSerial.h>
#include "Alphabot2.h" // Inclure le fichier de la classe

Alphabot2 robot; //on definit l'appelle de classe avec "robot"

SoftwareSerial btSerial(3, 2); // RX, TX pour la communication Bluetooth

void setup() {
  Serial.begin(9600);
  btSerial.begin(9600); // Initialiser la communication Bluetooth

  Serial.println("Robot prêt à recevoir des commandes");
}

void loop() {
  if (btSerial.available()) {
    String command = btSerial.readStringUntil(';');
    Serial.println("Commande reçue: " + command);

    if (command == "AVANCER") {
      robot.avancer(150); // Vitesse 150 pour avancer
    } else if (command == "RECULER") {
      robot.reculer(150); // Vitesse 150 pour reculer
    } else if (command == "A_GAUCHE") {
      robot.gauche(150); // Vitesse 150 pour tourner à gauche
    } else if (command == "A_DROITE") {
      robot.droite(150); // Vitesse 150 pour tourner à droite
    } else if (command == "STOP") {
      robot.stop(); // Arrêter le robot
    } else {
      btSerial.println("NOK"); // Commande incorrecte
    }
  }
}
