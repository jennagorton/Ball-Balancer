#include "ScreenControl.h"
#include <Arduino.h>

#define YP A1
#define XM A2
#define YM 7
#define XP 6


// Touch Screen usable values
#define MIN_X 60
#define MAX_X 970
#define MIN_Y 95
#define MAX_Y 940

// Screen dimensions
#define WIDTH 187.0
#define HEIGHT 140.0

// Pressure thresholds (adjust if needed)
#define MINPRESSURE 10
#define MAXPRESSURE 500

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);  // 300 = ohms of touchscreen
TSPoint raw_val;


/***********************ARDUINO MAP FUNCTION**************************/
// long map(long x, long in_min, long in_max, long out_min, long out_max) {
//   return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
// }

//Recreating map function to avoid integer math, need more exact results
double map_double(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}


void screen_init() {
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
}

//checks if theres an object on touchscreen
bool detection() {
  raw_val = ts.getPoint();
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  
  // if x in range then ball on plate
  return (raw_val.x > 0 && raw_val.x < 1023);
}

// calculating usable coordinates of balls positon
calibrated_coords find_position() {
  static double last_x = 0;
  static double last_y = 0;
  calibrated_coords cali_p;

  raw_val = ts.getPoint();
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  //mapping the raw values to the usable range
  double x_coords = map_double(raw_val.x, MIN_X, MAX_X, WIDTH / 2, -WIDTH / 2);
  double y_coords = map_double(raw_val.y, MIN_Y, MAX_Y, HEIGHT / 2, -HEIGHT / 2);

 
  

  // All good — save and return
  last_x = x_coords;
  last_y = y_coords;
  cali_p.x = x_coords;
  cali_p.y = y_coords;
  cali_p.z = raw_val.z;

  return cali_p;
}
