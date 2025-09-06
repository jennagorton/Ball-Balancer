#include <Arduino.h>
#include <math.h>
#include "PID.h"

// PID Constants
#define kp_far_x 0.8
#define ki_far_x 0.15 
#define kd_far_x 0.27

#define kp_far_y 0.6
#define ki_far_y 0.15
#define kd_far_y 0.26

#define kp_close_x .18
#define ki_close_x 0.15
#define kd_close_x 0.23

#define kp_close_y .12
#define ki_close_y 0.15
#define kd_close_y 0.235

#define max_output 83.5  // max X distance away from the center
#define max_angle 12.5   // max tilt angle
const double height = 85; // height of platform

//Array definition
double error[2] = { 0, 0 };
double error_prev[2];
double integral[2] = { 0, 0 };
double derivative[2] = { 0, 0 };
double output[2];
double angles[2];
long time_pattern = 0;

//PID algorithm for x and y
void balance(double target_x, double target_y) {

  // Serial.print("X: ");
  // Serial.print(target_x);
  // Serial.print(", Y: ");
  // Serial.println(target_y);

  static unsigned long t_prev = 0; //previous time
  static unsigned long last_time = 0; //when ball was last detected
  unsigned long t = millis(); //current time
  double dt = (t - t_prev) / 1000.0; //calculated dt

  //inital & time gaps
  if (t_prev == 0 || dt > .075) {
    t_prev = t;
    return; 
  }

  /*************PID CONTROL****************/
  if (dt >= 0.01) {
    
    calibrated_coords p = find_position(); 

    if (detection()) { //only run if ball on plate
      last_time = t;

      double error_current;
      for (int i = 0; i < 2; i++) { // Y:0,   X:1

        error_prev[i] = error[i]; //store error before updating

        //calculating current error
        if (i == 0) {
            error_current = p.y - target_y;
        } else {
            error_current = p.x - target_x;
        }

        error[i] = error_current; //updating with current error

        integral[i] += error[i] * dt; //calculating integral
        integral[i] = constrain(integral[i], -50, 50);  //preventing windup

        derivative[i] = (error[i] - error_prev[i]) / dt; //calculating derivative
        
        if (isnan(derivative[i]) || isinf(derivative[i])) { //checking if valid
          derivative[i] = 0;
        }

        //debug
        //Serial.println(error[0]);
      }

      /*****************PID EQUAIONS******************/ 
      if (abs(error[0]) < 15) { // Y
        output[0] = kp_close_y * error[0] + ki_close_y * integral[0] + kd_close_y * derivative[0]; // differnet gain constants when close and far
      }else{
        output[0] = kp_far_y * error[0] + ki_far_y * integral[0] + kd_far_y * derivative[0];
      }
      if (abs(error[1]) < 25){ // X
        output[1] = kp_close_x * error[1] + ki_close_x * integral[1] + kd_close_x * derivative[1]; 
      }else{
        output[1] = kp_far_x * error[1] + ki_far_x * integral[1] + kd_far_x * derivative[1];
      }
        
      angles[0] = constrain(output[0], -max_output, max_output) * (max_angle / max_output);  // mapping raw output to serov angle
      angles[1] = constrain(output[1], -max_output, max_output) * (max_angle / max_output);  
    
      unsigned long start = millis();
      while (millis() - start < 20) { // run for long enough that motion seems smooth
        move(angles[0], -angles[1], height); //phi negative because of screen orientation
      }
    }

    else {
      // if no input for 3 sec reset
      if (t - last_time >= 3000) {
        integral[0] = integral[1] = 0;
        move(0, 0, height);
      }
    }
    t_prev = t;
  }
}

/***************** LINE *******************/
int direction = 0;                 // 0 = forward, 1 = backward
unsigned long lastSwitch = 0;      

void line(double rx, double ry, unsigned long interval) {
  unsigned long now = millis();

  // Only switch direction after the interval
  if (now - lastSwitch >= interval) {
    direction = !direction;   // flip 0 ↔ 1
    lastSwitch = now;
  }

  // Apply current direction
  if (direction == 0) {
    balance(rx, ry);
  } else {
    balance(-rx, -ry);
  }
}

/***************** TRIANGLE *******************/
void triangle(int scale) {
  unsigned long now = millis();

  if (now - lastSwitch >= 900) {
    direction = (direction + 1) % 3; 
    lastSwitch = now;
  }

  // Apply current direction
  if (direction == 0) {
    balance(0, scale * 10);
  } else if (direction == 1) {
    balance(scale * -10, -20);
  } else if (direction == 2) {
    balance(scale * 10, -20);
  }

}

/***************** FIGURE 8 *******************/
double theta = 0;
unsigned long lastStep = 0;

void figure8(double r, int wait, int num) {
  unsigned long now = millis();

  if (now - lastStep < wait) return; //controls speed
  lastStep = now;

 
  double scale = r * (2 / (3 - cos(2 * theta)));
  double x = scale * cos(theta);
  double y = scale * sin(2 * theta) / 1.5;

  
  balance(x, y); //move

  theta += 0.05;
  if (theta >= 2 * PI) theta = 0;  // wrap around
}

/***************** ELLIPSE *********************/
void ellipse(double rx, double ry, int interval) {
  unsigned long now = millis();

  if (now - lastStep >= interval) {
    lastStep = now;

    balance(rx * cos(theta), ry * sin(theta)); //moves one step
    theta += 0.1;
    if (theta >= 2 * PI) {
      theta = 0; // wrap around
    }
  }
}





