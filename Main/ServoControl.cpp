#include "ServoControl.h"
#include "WiFiWebServer.h"

bool startMovement = false;
bool startMovement2 = false;
bool isInitialized = false;
bool stopMovement = false;

const int triggerPin = 12;
const int echoPin = 13;
const int detectionDistance = 15;

void setupServos() {
  servoMotorInf1.attach(21);
  servoMotorInf2.attach(22);
  servoMotorSup1.attach(23);
  servoMotorSup2.attach(19);
  servoMotorHand.attach(18);
  servoMotorHand2.attach(5);

  servoMotorInf1.write(90);
  servoMotorInf2.write(90);
  servoMotorSup1.write(90);
  servoMotorSup2.write(90);
  servoMotorHand.writeMicroseconds(1500);
  servoMotorHand2.writeMicroseconds(1500);
}

void moveServo(Servo &servo, int start, int end, int delayTime) {
  if (start < end) {
    for (int pos = start; pos <= end; pos++) {
      servo.write(pos);
      delay(delayTime);
      if ((pos % 10 == 0) || (pos == end)) {
        server.handleClient();
        if (stopMovement) return;
      }
    }
  } else {
    for (int pos = start; pos >= end; pos--) {
      servo.write(pos);
      delay(delayTime);
      if ((pos % 10 == 0) || (pos == end)) {
        server.handleClient();
        if (stopMovement) return;
      }
    }
  }
}

void moveBrazo(Servo &servo, int microseconds, int delayTime) {
  servo.writeMicroseconds(microseconds);
  delay(delayTime);
  server.handleClient();
}

void stopServos() {
  startMovement = false;
  startMovement2 = false;
  stopMovement = false;
  
  servoMotorInf1.write(90);
  servoMotorInf2.write(90);
  servoMotorSup1.write(90);
  servoMotorSup2.write(90);
  servoMotorHand.writeMicroseconds(1500);
  servoMotorHand2.writeMicroseconds(1500);
}

void checkUltrasonicSensor() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;

  if (distance <= detectionDistance && distance > 0) {
    Serial.println("Obstáculo detectado. Deteniendo los servos.");
    stopMovement = true;
    stopServos();
  }
}