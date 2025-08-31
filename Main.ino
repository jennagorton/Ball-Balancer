#include <Arduino.h>
#include "InverseKinematics.h"
#include "ServoControl.h"
#include "ScreenControl.h"
#include "PID.h"

void setup() {
  // Initialization functions
  Serial.begin(115200);
  screen_init();
  servo_init();
  delay(100);
}

void loop() {
  balance(0,0);
}