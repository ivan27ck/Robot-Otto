#include <ESP32Servo.h>
#include "ServoControl.h"
#include "WiFiWebServer.h"

Servo servoMotorInf1;
Servo servoMotorInf2;
Servo servoMotorSup1;
Servo servoMotorSup2;
Servo servoMotorHand;
Servo servoMotorHand2;

const int triggerPin = 12;
const int echoPin = 13;
const int detectionDistance = 15;

void setup() {
  Serial.begin(115200);
  
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  setupServos();
  setupWiFi();
}

void loop() {
  server.handleClient();
  checkUltrasonicSensor();

  if (startMovement && !stopMovement) {
    servoMotorInf1.write(90);
    servoMotorInf2.write(90);
    
    moveServo(servoMotorSup1, 90, 0, 2);
    if (stopMovement) { stopServos(); return; }
    
    moveServo(servoMotorSup1, 0, 90, 2);
    if (stopMovement) { stopServos(); return; }
    
    moveServo(servoMotorSup2, 90, 180, 2);
    if (stopMovement) { stopServos(); return; }
    
    moveServo(servoMotorSup2, 180, 90, 2);
    if (stopMovement) { stopServos(); return; }

    for (int j = 0; j <= 3 && !stopMovement; j++) {
      servoMotorHand2.writeMicroseconds(1300);
      server.handleClient();

      servoMotorHand.writeMicroseconds(1700);
      server.handleClient();
      moveServo(servoMotorInf1, 90, 20, 1);
      if (stopMovement) break;
      
      moveServo(servoMotorInf1, 20, 90, 5);
      if (stopMovement) break;
      
      moveServo(servoMotorInf2, 90, 160, 1);
      if (stopMovement) break;
      
      moveServo(servoMotorInf2, 160, 90, 5);
      if (stopMovement) break;
      
      moveServo(servoMotorInf1, 90, 20, 1);
      if (stopMovement) break;
      
      moveServo(servoMotorInf1, 20, 90, 5);
      if (stopMovement) break;
      
      moveServo(servoMotorInf2, 90, 160, 1);
      if (stopMovement) break;
      
      moveServo(servoMotorInf2, 160, 90, 5);
      if (stopMovement) break;
    }
    
    if (stopMovement) {
      stopServos();
    }
  }

  if (startMovement2 && !stopMovement) {
    for (int j = 0; j < 50 && !stopMovement; j++) {
      servoMotorHand2.writeMicroseconds(1700);
      server.handleClient();
    
      moveServo(servoMotorInf1, 90, 30, 3);
      if (stopMovement) break;

      moveServo(servoMotorSup1, 90, 120, 5);
      if (stopMovement) break;

      servoMotorHand.writeMicroseconds(1700);
      server.handleClient();
      servoMotorHand2.writeMicroseconds(1500);
      server.handleClient();

      moveServo(servoMotorInf1, 30, 90, 3);
      if (stopMovement) break;
      
      moveServo(servoMotorSup1, 120, 90, 5);
      if (stopMovement) break;

      servoMotorHand.writeMicroseconds(1500);
      server.handleClient();
      servoMotorHand2.writeMicroseconds(1300);
      server.handleClient();

      moveServo(servoMotorInf2, 90, 150, 3);
      if (stopMovement) break;
      
      moveServo(servoMotorSup2, 90, 60, 5);
      if (stopMovement) break;

      servoMotorHand.writeMicroseconds(1300);
      server.handleClient();

      servoMotorHand2.writeMicroseconds(1500);
      server.handleClient();
      
      moveServo(servoMotorInf2, 150, 80, 3);
      if (stopMovement) break;
      
      moveServo(servoMotorSup2, 60, 90, 5);
      if (stopMovement) break;

      servoMotorHand.writeMicroseconds(1500);
      server.handleClient();
    }
    
    if (stopMovement) {
      stopServos();
    }
  }
}
