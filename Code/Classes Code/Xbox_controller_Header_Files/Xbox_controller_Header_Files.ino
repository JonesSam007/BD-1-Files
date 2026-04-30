#include <Arduino.h>
#include <BLEGamepadClient.h>

#include <Controller.hpp>
XboxController controller;
ControllerClass XController(controller);


void setup() {
  Serial.begin(115200);
  controller.begin();
  Serial.println("Start up");
  Serial.println();
  delay(500);
  if (!XController.CheckConnected()){Serial.printf("\n\n         Not Connected\n\n\n");}
}

void loop() {
  if (XController.CheckConnected()){ //this calls the check connected function and returns a +ive if connected and a -ive if not connected

    XController.ReadValues(); //reads the values from the controller
    XController.PrintValues(); //prints them to the serial
    
  }else {
    if (XController.wasConnected){
      Serial.printf("\n\n***************************************\n    Disconnected\n***************************************\n");
      XController.wasConnected = false;
    }
  }
  delay(100);

}

