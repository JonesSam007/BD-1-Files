///////////////////////////////////////////////////////////////////
//Aim to control neck with xbox controller button inputs 
//////////////////////////////////////////////////////////////////

#include <Arduino.h>
#include <BLEGamepadClient.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Timing Variables
double elapsed = 0;
double start = 0;
double dt = 0;
double t = 0;

#include <Controller.hpp>
XboxController controller;
ControllerClass XController(controller);


Adafruit_PWMServoDriver neck = Adafruit_PWMServoDriver(0x41);
#include <HeadViaInput.hpp>
HeadClass classBD1(neck, 0,0,0,0,0);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  classBD1.startUP();


  Serial.println("Start up");
  Serial.println();
  delay(500);

  controller.begin();

  //Controller check
  if (!XController.CheckConnected()){Serial.printf("\n\n         Not Connected\n\n\n");}
}

void loop() {

  // Keep track of the amount of time past
  elapsed = millis() - start;
  dt = elapsed / 1000.0;
  start = millis();
  t += dt;

  if (XController.ControllerFetchReadings()) {
    classBD1.NeckCalc();
  }
  //delay(10);
  while (millis() - start < 10) {}  // 100Hz Main Loop
}



