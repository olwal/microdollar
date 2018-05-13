/*

  MicroDollar: $1 Gesture Recognizer C++ port with optimizations for embedded hardware

  This sketch demonstrates how to run the template-based $1 gesture recognizer on
  resource-constrained microcontrollers, such as the ESP8266, Arduino Uno, and others.

  The number of templates that can be loaded depend on available memory, as they are loaded into dynamic memory.
  If dynamic memory is almost full (e.g., >80%), memory can get corrupted by use of local variables.

  Initially developed for:
  SpeckleSense/SpeckleEye (http://specklesense.media.mit.edu, http://specklesense.org)
  - SpeckleSense: Fast, Precise, Low-cost and Compact Motion Sensing using Laser Speckle (https://doi.org/10.1145/2047196.2047261)
  - SpeckleEye: Gestural Interaction for Embedded Electronics in Ubiquitous Computing (https://doi.org/10.1145/2212776.2223782)

  Based on:
  $1 Unistroke Recognizer (http://depts.washington.edu/madlab/proj/dollar/)
  - Gestures without libraries, toolkits or training: a $1 recognizer for user interface prototypes (https://doi.org/10.1145/1294211.1294238)

  Author: Alex Olwal (www.olwal.com)

*/

#include "data/template_data_int_normalized_64_4.h"
using namespace TemplateDataIntNormalized64_4;

#include <DebugPrint.h>
#include <GestureProcessing.h>
#include <MicroDollar.h>
#include <Recognizer.h>
#include <Templates.h>

MicroDollar dollar;

int addedPoints = 0;
int gesture;
int downSample;

void setup()
{
  Serial.begin(115200);

  dollar.init(samplePoints, nSamplePoints, samplesNormalized, sampleNames, nTemplates);
}

void recognizePoints(int * points, int nPoints, int downSample)
{
  addedPoints = 0;
  int increment = 1;

  for (int i = 0; i < nPoints; i = i += 2 * downSample)
  {
    int x = points[i];
    int y = points[i + 1];

    bool added = dollar.update(x, y);

    if (added)
      addedPoints++;
  }

  dollar.recognize();
}

void printResult()
{
  Serial.print("Using ");
  Serial.print(addedPoints);
  Serial.print(" of ");
  Serial.print(nSamplePoints[gesture] / 2);
  Serial.print(" points, ");

  Serial.print("template: ");
  Serial.print(dollar.getIndex());

  Serial.print(" (");
  Serial.print(dollar.getName());
  Serial.print(")");

  Serial.print(", score: ");
  Serial.print(dollar.getScore());
  Serial.println("%");
}

void loop()
{
  for (gesture = 0; gesture < nTemplates; gesture++)
  {
    Serial.println();
    Serial.print("Gesture: ");
    Serial.println(gesture);
    
    for (downSample = 1; downSample < 4; downSample++)
    {
      recognizePoints(samplePoints[gesture], nSamplePoints[gesture], downSample);
      printResult();
      delay(1000);
    }
  }
}
