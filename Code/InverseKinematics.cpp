#include "InverseKinematics.h"
#include <Arduino.h>
#include <math.h>


const double d = 56.0; //dist form limb to center
const double L1 = 60.0; //dist lower limb
const double L2 = 101.45; //dsit upper limb

//prevents NAN values
double safe_acos(double x) {
    if (x > 1.0) x = 1.0;
    if (x < -1.0) x = -1.0;
    return acos(x);
}

// finds servo angles based on PID output
ThetaAngles IK(double theta, double phi, double h) {

  //offset angles so that platform is flat on intitalization
  theta += 4;
  phi += -3;

  //convert to radians
  float phiRad = phi * (PI / 180.0);
  float thetaRad = -theta * (PI / 180.0);

  //find height of each leg
  float Za = (cos(phiRad)*sin(thetaRad)*d) + h;
  float Zb = (sin(phiRad) * (d*sqrt(3))/2) - (cos(phiRad)*sin(thetaRad)*(d/2)) + h;
  float Zc = -(sin(phiRad) * (d*sqrt(3))/2) - (cos(phiRad)*sin(thetaRad)*(d/2)) + h;

  //find angle beta (inside angle)
  float BetaA = safe_acos((L1*L1 + Za*Za - L2*L2) / (2*L1*Za));
  float BetaB = safe_acos((L1*L1 + Zb*Zb - L2*L2) / (2*L1*Zb));
  float BetaC = safe_acos((L1*L1 + Zc*Zc - L2*L2) / (2*L1*Zc));

  //find angle theta (outside angle)
  int ThetaA = 90 - (BetaA * (180 / PI));
  int ThetaB = 90 - (BetaB * (180 / PI));
  int ThetaC = 90 - (BetaC * (180 / PI));

  //create result
  ThetaAngles result;
  result.thetaA = ThetaA;
  result.thetaB = ThetaB;
  result.thetaC = ThetaC;

  /******************DEBUG STATEMENTS******************/
  // Serial.print("Angles -> A: ");
  // Serial.print(result.thetaA);
  // Serial.print("  B: ");
  // Serial.print(result.thetaB);
  // Serial.print("  C: ");
  // Serial.println(result.thetaC);

  return result;
}
