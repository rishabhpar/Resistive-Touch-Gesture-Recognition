#include "TouchScreen.h"

#include "data/template_data_int_normalized_64_2.h"
using namespace TemplateDataIntNormalized64_2;

#include <DebugPrint.h>
#include <GestureProcessing.h>
#include <MicroDollar.h>
#include <Recognizer.h>
#include <Templates.h>
#include <CircularBuffer.h>

// Pin connection definitions
#define x_p  26 
#define x_n  4 
#define y_p  25 
#define y_n  15 

MicroDollar dollar;
TouchScreen ts = TouchScreen(x_p, y_p, x_n, y_n, 600);

int addedPoints = 0;
int gesture;
int downSample;

const uint16_t num_of_elements = 64;
CircularBuffer<int, num_of_elements> inputGesture; 

void init

void setup()
{
  Serial.begin(115200);

  dollar.init(samplePoints, nSamplePoints, samplesNormalized, sampleNames, nTemplates);
}

void recognizePoints()
{
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

    bool added = dollar.update(x, y);

    if (added)
      addedPoints++;
  }

  dollar.recognize();
}

void loop()
{
  uint16_t pressure = ts.pressure();

  if (pressure > 200 && pressure < 2000 ) { // is pressed -> collect points
    uint16_t x = ts.readTouchX();
    uint16_t y = ts.readTouchY();

    Serial.print(x); Serial.print(","); Serial.print(y); Serial.print("\n");

    inputGesture.push(x);
    inputGesture.push(y);
    // if (inputGesture.isFull()) { // if 32 points have been collected -> try classifying
    //   recognizePoints();
    //   if (dollar.getScore() > 90){
    //     Serial.print(dollar.getName()); Serial.print("\n");
    //   }
    // }
  } else if (!inputGesture.isEmpty()) { // unpressed and contains values to classify -> classify
      recognizePoints();
      Serial.print(dollar.getName()); Serial.print("\n");
      inputGesture.clear();
  }

  delay(50);
}
