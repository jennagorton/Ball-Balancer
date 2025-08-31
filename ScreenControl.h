#ifndef SCREENCONTROL_H
#define SCREENCONTROL_H

#include <Arduino.h>
#include <TouchScreen.h>

struct calibrated_coords {
  double x; //x position
  double y; //y position
  double z; //pressure
};

double map_double(double x, double in_min, double in_max, double out_min, double out_max);
void screen_init();
bool detection();
calibrated_coords find_position();

#endif