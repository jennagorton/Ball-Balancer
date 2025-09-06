#include "ServoControl.h"
#include "InverseKinematics.h"
#include <Arduino.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

#define SERVOMIN 125
#define SERVOMAX 525
#define SERVO_FREQ 60

double step[3] = {0.0, 0.0, 0.0};  // array for step sizes
double currentAngles[3];
const double height = 90; // height of platform

// initalizes serovs to make platform level
void servo_init() {
  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);
  delay(10);

  ThetaAngles angle = IK(0, 0, height); // calculate angles
  currentAngles[0] = angle.thetaA;
  currentAngles[1] = angle.thetaB;
  currentAngles[2] = angle.thetaC;

    for (int i = 0; i < 3; i++) { //set angles
      pwm.setPWM(i, 0, map(currentAngles[i], 0, 180, SERVOMIN, SERVOMAX));
    }
}

// moves servo to desired position using output from PID and IK
void move(double theta_deg, double phi_deg, double height) {
  
  ThetaAngles result = IK(theta_deg, phi_deg, height); //gets the desired angle
  double target_angle[3] = {result.thetaA, result.thetaB, result.thetaC};

  //calculates a step size for smooth movement
  for (int i = 0; i < 3; i++) {
    step[i] = constrain(abs(target_angle[i] - currentAngles[i]) * 0.05, 0.5, 3.0);
  }

  for (int i = 0; i < 3; i++) {
    if (fabs(target_angle[i] - currentAngles[i]) > step[i]) { // checks if difference is less than stepsize

      //gradual angel change
      if (target_angle[i] > currentAngles[i]) currentAngles[i] += step[i];
      else currentAngles[i] -= step[i];
    } 
    else { 
      currentAngles[i] = target_angle[i]; // no change if at the correct angle
    }

    pwm.setPWM(i, 0, map(currentAngles[i], 0, 180, SERVOMIN, SERVOMAX)); //update servo
  }
}



