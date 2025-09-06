#include <Arduino.h>
#include "InverseKinematics.h"
#include "ServoControl.h"
#include "ScreenControl.h"
#include "PID.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// -------------------- OLED Setup --------------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const int buttonPin = 2; 
int buttonState = 0;
int lastButtonState = 0;
int mode = 0; // 0=balance, 1=ellipse, 2=line, 3=figure 8, 4=triangle
int lastMode = -1;


void setup() {
  // Initialization functions
  Serial.begin(115200);
  screen_init();
  servo_init();
  pinMode(buttonPin, INPUT_PULLUP);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.println("SSD1306 allocation failed");
    for(;;);
  }
  display.clearDisplay();
}

void loop() {

  buttonState = digitalRead(buttonPin);

  //detects button transition
  if (buttonState == LOW && lastButtonState == HIGH) {
    mode = (mode + 1) % 5;
    Serial.print("Mode changed to: ");
    Serial.println(mode);
    delay(50);              
  }

  if(mode != lastMode){
    updateOLED(mode);
    lastMode = mode;
  }

  //changes pattern based on button press
  switch (mode) {
    case 0:
      balance(0, 0);
      break;
    case 1:
      ellipse(20, 20, 10);
      break;
    case 2:
      line(50, 0, 750);
      break;
    case 3:
      figure8(40, 20, 3);
      break;
    case 4:
      triangle(5); 
      break;
  }

  lastButtonState = buttonState;
}


//function to write to screen
void updateOLED(int mode) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);

  const char* text;
  switch(mode){
    case 0: text = "Balance"; break;
    case 1: text = "Ellipse"; break;
    case 2: text = "Line"; break;
    case 3: text = "Figure 8"; break;
    case 4: text = "Triangle"; break;
  }

  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);

  int16_t x = (SCREEN_WIDTH - w) / 2;
  int16_t y = (SCREEN_HEIGHT - h) / 2;

  display.setCursor(x, y);
  display.println(text);
  display.display();
}