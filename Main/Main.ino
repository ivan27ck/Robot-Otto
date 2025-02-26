#include <Arduino.h>
#include "librerias/ServoControl.h"
#include "librerias/WiFiWebServer.h"

const char* ssid = "iCUCEI";
const char* password = "";
IPAddress local_IP(10, 214, 106, 120);
IPAddress gateway(10, 214, 127, 254);
IPAddress subnet(255, 255, 192, 0);

void setup() {
    Serial.begin(115200);

    attachServos(); // Configurar servos
    setupWiFi(ssid, password, local_IP, gateway, subnet); // Configurar WiFi
    setupWebServer(); // Configurar servidor web
}

void loop() {
    server.handleClient();

    //movimiento de baile
    if (baile) {
        
    moveServo(servoMotorSup1, 90, 0, 3);
    moveServo(servoMotorSup1, 0, 90, 3);
    moveServo(servoMotorSup2, 90, 180, 3);
    moveServo(servoMotorSup2, 180, 90, 3);

    // Movimiento alternado de los servos inferiores
    for (int j = 0; j <= 2; j++) {
      moveServo(servoMotorInf1, 0, 60, 1);
      moveServo(servoMotorInf1, 0, 60, 10);

      moveServo(servoMotorInf2, 60, 120, 1);
      moveServo(servoMotorInf2, 60, 120, 10);
    }

    }

    if (caminar) {
        
      
      servoMotorInf1.write(60);
      servoMotorInf2.write(120);
      servoMotorSup1.write(90);
      servoMotorSup2.write(90);
      
    
      for (int j = 0; j <= 2; j++) {
        moveServo(servoMotorInf1, 60, 120, 4);
        moveServo(servoMotorSup1, 90, 180, 4);
        moveServo(servoMotorInf1, 120, 60, 4);
        moveServo(servoMotorSup1, 180, 90, 4);
        moveServo(servoMotorInf2, 120, 60, 4);
        moveServo(servoMotorSup2, 90, 30, 4);
        moveServo(servoMotorInf2, 60, 120, 4);
        moveServo(servoMotorSup2, 30, 90, 4);
    }

    }
}
