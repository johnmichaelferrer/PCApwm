/*****************
 * This example demonstrates the library assuming that LEDs are connected to the outputs
 * It will run through all 16 LEDs turning them up and down in 10 steps.
 * The PCA9685 chip is assumed to have PINS A0,A1 and A2 grounded (LOW) and A3,A4 and A5 set to VCC (5V, HIGH)
 * 
 * 
 */

#include <Wire.h>
#include <PCA9685.h>


PCA9685 ledDriver;
unsigned long delayTimer;
unsigned long delayCheck;
int currentRed;
int currentGreen;
int currentBlue;
int currentLumen;
int inputFields;
int fieldIndex;
int values[3];

void setup()
{
  Serial.begin(9600); // set up serial
  Serial.println("Serial Started");

  Wire.begin();           // Wire must be started!
  ledDriver.begin(B110001);  // Address pins A5-A0 set to B110001
  ledDriver.init();
  globalSetLED(50);
  Serial.println("LEDs default to 50% at Startup.");
  ledDriver.setLEDDimmed(0,0);
  ledDriver.setLEDDimmed(1,25);
  ledDriver.setLEDDimmed(2,75);
}

//LUMEN values 1-100
void globalSetLED(int brightness) {
  ledDriver.setLEDDimmed(0,brightness);
  ledDriver.setLEDDimmed(1,brightness);
  ledDriver.setLEDDimmed(2,brightness);
}

void globalBlinkLED(int brightness, unsigned long delayTime) {
  globalSetLED(brightness);
  delayCheck = millis();
  delayTimer = delayTime;
}

void loop()
{
//  if(Serial.available()){
//    char ch = Serial.read();
//    if (ch = 'c'){    //color change based on COLOR WORD, two input values (COLOR, LUMEN)
//      inputFields = 2;
//      fieldIndex = 0;
//      int array[inputFields];
//      values = array;
//    } else 
//    if (ch = 'V'){ //color change based on VALUE of RGB, four input valued (RGB 0-255, LUMEN 0-100);
//      inputFields = 3;
//      fieldIndex = 0;
//      Serial.println("read V");
//    } else if (ch >= '0' && ch <= '9'){
//      if (fieldIndex < inputFields){
//        values[fieldIndex] = (values[fieldIndex]*10) + (ch-'0');
//      }
//    } else if (ch = ',') {
//      fieldIndex++;
//    } else {
//      for (int i=0; i<min(inputFields, fieldIndex+1); i++) {
//        Serial.println(values[i]);
//        values[i]=0;
//      }
//      fieldIndex = 0;
//    }
//  }
} 


