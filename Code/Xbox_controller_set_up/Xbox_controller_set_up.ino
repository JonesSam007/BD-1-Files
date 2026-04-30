#include <Arduino.h>
#include <BLEGamepadClient.h>

//setting up xbox controller BLE Connection
XboxController controller;
bool wasConnected = false;

void setup() {
  Serial.begin(115200);
  controller.begin();
  Serial.println("Start up");
  Serial.println();
  delay(500);
}

void loop() {

  if (controller.isConnected()){
    //reads the values coming off the controller
    XboxControlsState e;
    controller.read(&e);
    //checks if it was connected already
    if (!wasConnected){
      wasConnected = true;
    }
    //LeftStick
    Serial.printf("LX / LY: %.2f / %.2f\n", e.leftStickX, e.leftStickY);
    //RightStick
    Serial.printf("RX / RY: %.2f / %.2f\n", e.rightStickX, e.rightStickY);
    //Triggers
    Serial.printf("LT / RT: %.2f / %.2f\n", e.leftTrigger, e.rightTrigger);

    //Buttons
    Serial.print("Buttons: ");
    if(e.buttonA) Serial.print("A ");
    if(e.buttonB) Serial.print("B ");
    if(e.buttonX) Serial.print("X ");
    if(e.buttonY) Serial.print("Y ");
    Serial.println();
    
    //Bumper/StickButtons
    Serial.print("Bumpers: ");
    if (e.leftBumper)      Serial.print("LB ");
    if (e.rightBumper)     Serial.print("RB ");
    if (e.leftStickButton) Serial.print("LSB ");
    if (e.rightStickButton)Serial.print("RSB ");
    Serial.println();

    //D-pad
    Serial.print("D-pad: ");
    if (e.dpadUp)    Serial.print("Up ");
    if (e.dpadDown)  Serial.print("Down ");
    if (e.dpadLeft)  Serial.print("Left ");
    if (e.dpadRight) Serial.print("Right ");
    Serial.println();
    
    //Center
    Serial.print("Center: ");
    if (e.shareButton) Serial.print("Share ");
    if (e.menuButton)  Serial.print("Menu ");
    if (e.viewButton)  Serial.print("View ");
    if (e.xboxButton)  Serial.print("Xbox ");
    Serial.println();
    
    //Status (connected)
    Serial.print("Status: ");
    if (wasConnected) Serial.print("Connected");
    Serial.println();
    
  }else {
    if (wasConnected){
      Serial.printf("\n\n***************************************\n    Disconnected\n***************************************\n");
      wasConnected = false;
    }
  }
  delay(100);
}
