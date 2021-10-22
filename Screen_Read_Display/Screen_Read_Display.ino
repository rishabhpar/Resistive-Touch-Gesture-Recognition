#include "TouchScreen.h"

// Pin connection definitions
#define x_p  26 // A0
#define x_n  4 // A1
#define y_p  25 // A3
#define y_n  15 // A4

TouchScreen ts = TouchScreen(x_p, y_p, x_n, y_n, 600);

void setup(void) {
  Serial.begin(9600);
}

void loop(void) {
  // a point object holds x y and z coordinates
  TSPoint p = ts.getPoint();
  
  // we have some minimum pressure we consider 'valid'
  // pressure of 0 means no pressing!
  // ts.pressureThreshhold
  uint16_t pressure = ts.pressure();
  if (pressure > 200 && pressure < 2500) {
     //Serial.print("X = "); 
     Serial.print(ts.readTouchX());
     Serial.print(",");
     //Serial.print("\tY = "); 
     Serial.print(ts.readTouchY());
     Serial.print("\n");
     //Serial.print("\tPressure = "); Serial.println(pressure);
  }

  delay(50);
}
