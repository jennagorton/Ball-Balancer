#ifndef SERVOCONTROL_H
#define SERVOCONTROL_H

#include <Adafruit_PWMServoDriver.h>

void servo_init();
void move(double thetaA, double thetaB, double thetaC);

#endif