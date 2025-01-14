#include "librerias/ServoControl.h"


// Definición de los servos
Servo servoMotorInf1;
Servo servoMotorInf2;
Servo servoMotorSup1;
Servo servoMotorSup2;

// Conexión de los servos a los pines del ESP32
void attachServos() {
    servoMotorInf1.attach(21);
    servoMotorInf2.attach(22);
    servoMotorSup1.attach(23);
    servoMotorSup2.attach(19);
}

// Movimiento de los servos
void moveServo(Servo &servo, int start, int end, int delayTime) {
    if (start < end) {
        for (int pos = start; pos <= end; pos++) {
            servo.write(pos);
            delay(delayTime);
        }
    } else {
        for (int pos = start; pos >= end; pos--) {
            servo.write(pos);
            delay(delayTime);
        }
    }
}
