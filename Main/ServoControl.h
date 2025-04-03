#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H

#include <ESP32Servo.h>

extern Servo servoMotorInf1;
extern Servo servoMotorInf2;
extern Servo servoMotorSup1;
extern Servo servoMotorSup2;
extern Servo servoMotorHand;
extern Servo servoMotorHand2;

extern bool startMovement;
extern bool startMovement2;
extern bool isInitialized;
extern bool stopMovement;

void setupServos();
void moveServo(Servo &servo, int start, int end, int delayTime);
void moveBrazo(Servo &servo, int microseconds, int delayTime);
void stopServos();
void checkUltrasonicSensor();

#endif
