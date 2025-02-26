#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H

#include <ESP32Servo.h>

// Declaraci�n de los servos
extern Servo servoMotorInf1;
extern Servo servoMotorInf2;
extern Servo servoMotorSup1;
extern Servo servoMotorSup2;

// Declaraci�n de funciones
void attachServos();
void moveServo(Servo &servo, int start, int end, int delayTime);

#endif
