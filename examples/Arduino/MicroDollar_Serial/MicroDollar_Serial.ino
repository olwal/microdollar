/*
  
  MicroDollar: $1 Gesture Recognizer C++ port with optimizations for embedded hardware

  This sketch demonstrates how to run the template-based $1 gesture recognizer on
  resource-constrained microcontrollers, such as the ESP8266, Arduino Uno, and others.

  This sketch sets up a serial connection to a host PC, and receives a sequence of <x, y> coordinates,
  which are matched against a set of templates loaded into program memory.

  The start of the coordinate sequence is indicated by a START packet, followed by multiple DATA packets, and
  the recognition is triggered after a final END packet.

  The number of templates that can be loaded depend on available memory, as they are loaded into dynamic memory.
  If dynamic memory is almost full (e.g., >80%), memory can get corrupted by use of local variables. 

  The microcontroller waits for 5 bytes as part of the protocol.

  Protocol
    byte 1 = command [ START | DATA | END ]
    byte 2|3 = x (16-bit)
    byte 3|4 = y (16-but)

  If the echo flag is set, then there will be a string response (ends with newline) for each incoming
  packet, with additional data to help development and tuning.

  Initially developed for:
  SpeckleSense/SpeckleEye (http://specklesense.media.mit.edu, http://specklesense.org)
  - SpeckleSense: Fast, Precise, Low-cost and Compact Motion Sensing using Laser Speckle (https://doi.org/10.1145/2047196.2047261)
  - SpeckleEye: Gestural Interaction for Embedded Electronics in Ubiquitous Computing (https://doi.org/10.1145/2212776.2223782)
        
  Based on:
  $1 Unistroke Recognizer (http://depts.washington.edu/madlab/proj/dollar/)
  - Gestures without libraries, toolkits or training: a $1 recognizer for user interface prototypes (https://doi.org/10.1145/1294211.1294238)
    
  Author: Alex Olwal (www.olwal.com)

*/

//#include "data/DataTemplates.h"

#include "data/template_data_int_normalized_64_2.h"
using namespace TemplateDataIntNormalized64_2;

#include <MicroDollar.h>
#include <DebugPrint.h>
#include <GestureProcessing.h>
#include <Recognizer.h>
#include <Templates.h>

MicroDollar dollar;

bool echo = true; //specifies if there should be a string response to each packet

const char START = '<'; //indicates START of coordinate sequence
const char DATA = '#';  //indicates DATA packet
const char END = '>';   //indicates END of of coordinate sequence

const int PACKET_LENGTH = 5; //protocol expects 5 bytes in each packet

void setup()
{
  Serial.begin(115200);
  dollar.init(samplePoints, nSamplePoints, samplesNormalized, sampleNames, nTemplates);
}

void loop()
{

}

void serialEvent()
{
  if (Serial.available() < PACKET_LENGTH)
    return;

  // Process packet
  char command = (char)Serial.read();

  byte high = (byte)Serial.read();
  byte low = (byte)Serial.read();
  int x = high << 8 | low;

  high = (byte)Serial.read();
  low = (byte)Serial.read();
  int y = high << 8 | low;

  // Send the new coordinate to engine and check if it was added (based on timing and distance from previous)
  boolean added = dollar.update(x, y, false);

  if (command == END)
  {
    long t0 = millis();

    // Trigger the recognizer with the accumulated coordinates.
    dollar.recognize();

    if (echo)
    {
      Serial.print("template: ");
      Serial.print(dollar.getIndex());

      Serial.print(" (");
      Serial.print(dollar.getName());
      Serial.print(")");

      Serial.print(", score: ");
      Serial.print(dollar.getScore());
      Serial.print(", # samples: ");
      Serial.print(dollar.gesture.nSamples);
      Serial.print(", # overflow: ");
      Serial.print(dollar.gesture.overflow);
      Serial.print(", processing time: ");
      Serial.print(millis() - t0);
      Serial.print(" ms");
      Serial.println(" ");
    }

    // Trigger the recognizer with the accumulated coordinates.
    dollar.recognize();

    Serial.write(dollar.getIndex());
    Serial.write(dollar.getScore());
  }
  else if (echo)
  {
    Serial.print(command);
    Serial.print(' ');
    Serial.print(x);
    Serial.print(' ');
    Serial.print(y);
    Serial.print(' ');
    Serial.print(added);
    Serial.print(' ');
    Serial.print(dollar.recognizer.nValues);
    Serial.print(' ');
    Serial.print(dollar.recognizer.nTemplates);

    //end string response with newline
    Serial.println();
  }


}
