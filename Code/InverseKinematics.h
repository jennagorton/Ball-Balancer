#ifndef INVERSEKINEMATICS_H
#define INVERSEKINEMATICS_H

#include <math.h>

//Structure to hold calculated angles for each motor. Combines calculate_triangle and ik_solver functions
struct ThetaAngles {
  double thetaA;
  double thetaB;
  double thetaC;
};

ThetaAngles IK(double theta, double phi, double h);

#endif