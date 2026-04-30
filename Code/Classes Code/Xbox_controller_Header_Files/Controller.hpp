#include <BLEGamepadClient.h>


class ControllerClass {
public:
  XboxController& controllerName;

  double LSXCorrected; //Left Stick X axis
  double LSYCorrected; //Left Stick Y axis

  double RSXCorrected; //Right Stick X axis
  double RSYCorrected; //Right Stick Y axis

  double LTCorrected; //Left Triger
  double RTCorrected; //Left Triger

  int LetterButton = 0b0000; //A,B,X,Y 
  int BumperButton = 0b0000; //Left Bumper, Right Bumper, Left Stick, Right Stick
  int DPadButton = 0b0000; //Up, Down, Left, Right
  int CenterButton = 0b0000; //Share, Menu, View, Xbox
  bool wasConnected = false;
  XboxControlsState e;

public:
  ControllerClass(XboxController& _controller)
  : controllerName(_controller){
    LSXCorrected = 0; //Left Stick X axis
    LSYCorrected = 0; //Left Stick Y axis

    RSXCorrected = 0; //Right Stick X axis
    RSYCorrected = 0; //Right Stick Y axis

    LTCorrected = 0; //Left Triger
    RTCorrected = 0; //Left Triger

    LetterButton = 0b0000; //A,B,X,Y 
    BumperButton = 0b0000; //Left Bumper, Right Bumper, Left Stick, Right Stick
    DPadButton = 0b0000; //Up, Down, Left, Right
    CenterButton = 0b0000; //Share, Menu, View, Xbox
    wasConnected = 0;

  }

  bool CheckConnected(){
    return (controllerName.isConnected());//{return 1;} else{return 0;}
  }
  void ReadValues(){

    controllerName.read(&e);
    ConvertToUseable();

  }

  void ConvertToUseable(){
  //checks if it was connected already
    if (!wasConnected){
      wasConnected = true;
    }
    //LeftStick
    LSXCorrected = e.leftStickX * 100;
    LSYCorrected = e.leftStickY * 100;

    RSXCorrected = e.rightStickX * 100;
    RSYCorrected = e.rightStickY * 100;

    LTCorrected = e.leftTrigger  * 100;
    RTCorrected = e.rightTrigger * 100;
     
  //A,B,X,Y 
    if(e.buttonA) {LetterButton = LetterButton | 0b1000;} else{LetterButton = LetterButton & 0b0111;}
    if(e.buttonB) {LetterButton = LetterButton | 0b0100;} else{LetterButton = LetterButton & 0b1011;}
    if(e.buttonX) {LetterButton = LetterButton | 0b0010;} else{LetterButton = LetterButton & 0b1101;}
    if(e.buttonY) {LetterButton = LetterButton | 0b0001;} else{LetterButton = LetterButton & 0b1110;}

  //Left Bumper, Right Bumper, Left Stick, Right Stick
    if (e.leftBumper)      {BumperButton = BumperButton | 0b1000;} else{BumperButton = BumperButton & 0b0111;}
    if (e.rightBumper)     {BumperButton = BumperButton | 0b0100;} else{BumperButton = BumperButton & 0b1011;}
    if (e.leftStickButton) {BumperButton = BumperButton | 0b0010;} else{BumperButton = BumperButton & 0b1101;}
    if (e.rightStickButton){BumperButton = BumperButton | 0b0001;} else{BumperButton = BumperButton & 0b1110;}

  //Up, Down, Left, Right
    if (e.dpadUp)    {DPadButton = DPadButton | 0b1000;} else{DPadButton = DPadButton & 0b0111;}
    if (e.dpadDown)  {DPadButton = DPadButton | 0b0100;} else{DPadButton = DPadButton & 0b1011;}
    if (e.dpadLeft)  {DPadButton = DPadButton | 0b0010;} else{DPadButton = DPadButton & 0b1101;}
    if (e.dpadRight) {DPadButton = DPadButton | 0b0001;} else{DPadButton = DPadButton & 0b1110;}

  //Share, Menu, View, Xbox
    if (e.shareButton) {CenterButton = CenterButton | 0b1000;} else{CenterButton = CenterButton & 0b0111;} 
    if (e.menuButton)  {CenterButton = CenterButton | 0b0100;} else{CenterButton = CenterButton & 0b1011;} 
    if (e.viewButton)  {CenterButton = CenterButton | 0b0010;} else{CenterButton = CenterButton & 0b1101;} 
    if (e.xboxButton)  {CenterButton = CenterButton | 0b0001;} else{CenterButton = CenterButton & 0b1110;} 



  }


  void PrintValues(){
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
    Serial.print("       ");
    Serial.print(LetterButton, BIN);
    Serial.println();
    
    //Bumper/StickButtons
    Serial.print("Bumpers: ");
    if (e.leftBumper)      Serial.print("LB ");
    if (e.rightBumper)     Serial.print("RB ");
    if (e.leftStickButton) Serial.print("LSB ");
    if (e.rightStickButton)Serial.print("RSB ");
    Serial.print("       ");
    Serial.print(BumperButton, BIN);
    Serial.println();

    //D-pad
    Serial.print("D-pad: ");
    if (e.dpadUp)    Serial.print("Up ");
    if (e.dpadDown)  Serial.print("Down ");
    if (e.dpadLeft)  Serial.print("Left ");
    if (e.dpadRight) Serial.print("Right ");
    Serial.print("       ");
    Serial.print(DPadButton, BIN);
    Serial.println();
    
    //Center
    Serial.print("Center: ");
    if (e.shareButton) Serial.print("Share ");
    if (e.menuButton)  Serial.print("Menu ");
    if (e.viewButton)  Serial.print("View ");
    if (e.xboxButton)  Serial.print("Xbox ");
    Serial.print("       ");
    Serial.print(CenterButton, BIN);
    Serial.println();
    
    //Status (connected)
    Serial.print("Status: ");
    if (wasConnected) Serial.print("Connected");
    Serial.println();
  }
};
