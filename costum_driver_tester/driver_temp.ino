
#include <DebugPrint.h>
#include <GestureProcessing.h>
#include <MicroDollar.h>
#include <Recognizer.h>
#include <Templates.h>
#include <CircularBuffer.h>
#include <TouchScreen.h>
#include "data/template_data_int_normalized_64_2.h"
#include "data/secrets.h"

// Pin connection definitions
#define x_p  4 
#define x_n  33   // X_N Must be analog
#define y_p  32   // Y_P Must be analog
#define y_n  15 

using namespace TemplateDataIntNormalized64_2;

MicroDollar* dollar;
TouchScreen ts = TouchScreen(x_p, y_p, x_n, y_n, 600);

int addedPoints = 0;
int gesture;
int downSample;

const uint16_t num_of_elements = 64;
CircularBuffer<int, num_of_elements> inputGesture; 

/* Internal methods*/
void Capture_new_gesture(void);

void setup() {
  Serial.begin(115200);
  dollar = new MicroDollar();
  dollar->init(samplePoints, nSamplePoints, samplesNormalized, sampleNames, nTemplates);
}

void recognizePoints() {
  addedPoints = 0;
  int increment = 1;

  while (inputGesture.available() > 0){ // pad the remaining with the last x,y coordinate
    int first = inputGesture[inputGesture.size() - 2];
    int second = inputGesture.last();

    inputGesture.push(first);
    inputGesture.push(second);
  }

  for (int i = 0; i < num_of_elements; i = i += 2)
  {
    int x = inputGesture[i];
    int y = inputGesture[i + 1];

    bool added = dollar->update(x, y);

    if (added)
      addedPoints++;
  }

  dollar->recognize();
}

void loop() {
  uint16_t pressure = ts.pressure();
  if (pressure > 200 && pressure < 2500 ) { // is pressed -> collect points
    uint16_t x = ts.readTouchX();
    uint16_t y = ts.readTouchY();

    Serial.print(x); Serial.print(","); Serial.print(y); Serial.print("\n");

    inputGesture.push(x);
    inputGesture.push(y);
  } else if (!inputGesture.isEmpty()) { // unpressed and contains values to classify -> classify
      recognizePoints();
      String classification = dollar->getName();      
      Serial.print(classification); Serial.print("\n");
      if(classification.equals("o")) {

      } else if(classification.equals("s")) {
        Capture_new_gesture();
      } else if(classification.equals("c")) {
        
      }
      inputGesture.clear();
  }

  delay(50);
}

//
/* Reads new gesture and adds to classification*/
void Capture_new_gesture(void) {
 int i = 0;
 while(i < 64) {
   uint16_t pressure = ts.pressure();
   if(pressure < 5000) {
     Serial.println("----");
     Serial.print(custom[i]);
     Serial.print(",");
     Serial.println(custom[i+1]);
     Serial.print(i);
     Serial.print(". ");
     uint16_t x = ts.readTouchX();
     uint16_t y = ts.readTouchY();
     Serial.print(x); Serial.print(","); Serial.print(y); Serial.print("\n");
     custom[i] = x;
     custom[i+1] = y;
     Serial.print(custom[i]);
     Serial.print(",");
     Serial.println(custom[i+1]);
     i += 2;
   }
   delay(50);
 }
 Serial.println("Finishe+d custom");

 /* Reinit recognition to upload custom gesture */
 
 /*Wait for user to lift finger */
 while(ts.pressure() < 2500);
 inputGesture.clear();
 Serial.println("Reinit");
 delete dollar;
 dollar = new MicroDollar();
 dollar->init(samplePoints, nSamplePoints, samplesNormalized, sampleNames, nTemplates);
}
