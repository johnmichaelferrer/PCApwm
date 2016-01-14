/*****************
 * Built off PCA9685 base library pulled off GitHub by K
 * Attempt to establish basic functionality for LED control via PWM.
 * For test rig purposes, only channels LED0, LED1, and LED are available.
 * 
 * Channel Guide
 * 0 = Red (R)
 * 1 = Blue (B) --not green as I would have thought in RGB...this is noted on schematic though.
 * 2 = Green (G) --yeah that's just going to annoy me
 * 
 * SDA (A4) and SCL (A5) as appropriate
 * ground OE.
 */

#include <Wire.h>
#include <PCA9685.h>

PCA9685 ledDriver;
unsigned long delayTimer;
unsigned long delayTime;
unsigned long delayCheck;
bool ALL_LED_STATE;
bool ON = true;
bool OFF = false;
bool BLINKING = false;
int currentBrightness;

void setup()
{
  Serial.begin(9600);
  Serial.setTimeout(20000);
  Serial.println("Serial Started");

  Wire.begin();              // Wire must be started!
  ledDriver.begin(B110001);  // Address pins A5-A0 set to B110001
  ledDriver.init();
  ALL_LED_STATE = ON;
  ledDriver.setLEDDimmed(0,10);
  ledDriver.setLEDDimmed(1,67);     //--general fx check (have you pulled up SDA/SCL with 4k7, grounded OE)
  ledDriver.setLEDDimmed(2,33);
}

//LED toggle command
void globalToggleLED(bool turnOn) {
  if (turnOn == true) {
    for (int i=0; i<16; i++){
      ledDriver.setLEDOn(i);
      ALL_LED_STATE = ON;
    }
  } else if (turnOn == false) {
    for (int f=0; f<16; f++){
      ledDriver.setLEDOff(f);
      ALL_LED_STATE = OFF;
    }
  } else return;
}

//LED on with LUMINOSITY, brightness values 0-100
void globalSetLED(int brightness) {
  ledDriver.setLEDDimmed(0,brightness);
  ledDriver.setLEDDimmed(1,brightness);
  ledDriver.setLEDDimmed(2,brightness);
}

void globalBlinkLED (int brightness, unsigned long interval) {
  globalSetLED(brightness);
  currentBrightness = brightness;
  delayTime = interval; //blink frequency
  resetTimers();
  BLINKING = true;
  ALL_LED_STATE = ON;
}

void checkBlink() {
  if (BLINKING = true && millis()>= delayCheck + delayTimer) {
    if (ALL_LED_STATE == ON) {
      globalToggleLED(OFF);
      resetTimers();
      ALL_LED_STATE = OFF;
    } else if (ALL_LED_STATE == OFF) {
      for(int i=0;i<16;i++){
        ledDriver.setLEDDimmed(i,currentBrightness);
      }
    } else return;
  }
}

void resetTimers(){
  delayCheck = millis();
  delayTimer = delayTime;
}

void loop(){
  checkBlink();
  if (Serial.available() > 0) {
    char mode = Serial.read();
    switch (mode) {
      default:
        break;
      case 'o':                               //an on-off button.
        if (ALL_LED_STATE == ON) {
          globalToggleLED(OFF);
          ALL_LED_STATE = OFF;
          Serial.println("toggledOff");
        } else {
          globalToggleLED(ON);
          ALL_LED_STATE = ON;
          Serial.println("toggledOn");
        }
        break;
      case 'b':
        Serial.println("blinkAll mode initiate");
        Serial.println("enter brightness 1-100");
        int bright = Serial.parseInt();
        Serial.println("brightness set");
        Serial.println(bright);
        Serial.println("enter blink interval ms");
        unsigned long freq = Serial.parseInt();
        Serial.println("interval set");
        Serial.println(freq);
        globalBlinkLED(bright,freq);
      }
  }
} 
