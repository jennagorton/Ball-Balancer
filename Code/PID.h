#ifndef PID_H
#define PID_H

#include "ServoControl.h"
#include "InverseKinematics.h"
#include <Arduino.h>
#include <math.h>
#include "ScreenControl.h"


void balance(double target_x, double target_y);
void ellipse(double rx, double ry, int interval);
void line(double rx, double ry, unsigned long interval);
void figure8(double r, int wait, int num);
void triangle(int scale);



#endif