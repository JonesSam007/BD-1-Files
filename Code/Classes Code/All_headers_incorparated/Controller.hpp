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

  int prevousCentre = 0b0000;
  int prevousLetter = 0b0000;
  int prevousDPad = 0b0000;
  int prevousBumper = 0b0000;
  
  XboxControlsState e;

  int ToggleSelectedButton = 0b0000;
  int TogglePrevousButtonVal = 0b0000;


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

  void ControllerStartup(){}

  bool ControllerFetchReadings(){
    bool Connected = 0;
    if (CheckConnected()){

      ReadValues();
      //controller.read(&e);
      //Checks();
      //PrintValues();
      Connected = 1;
      
      
    }else {
      if (wasConnected){
        Serial.printf("\n\n***************************************\n    Disconnected\n***************************************\n");
        wasConnected = false;
        
      }
      Connected = 0;
    }
    return Connected;

  }

  bool CheckConnected(){
    return (controllerName.isConnected());//{return 1;} else{return 0;}
  }
  void ReadValues(){

    controllerName.read(&e);
    ConvertToUseable();

  }

  void ToggleButton(int SelectedButton, int prevousButtonVal, int bitCheckNo, int BinaryValue){
      if (!bitRead(prevousButtonVal, bitCheckNo)){
        ToggleSelectedButton = SelectedButton ^ BinaryValue;
        TogglePrevousButtonVal = prevousButtonVal | BinaryValue;
      }
      
  }


  void ConvertToUseable(){
  //checks if it was connected already
    if (!wasConnected){
      wasConnected = true;
    }
      //Share, Menu, View, Xbox
    if (e.shareButton) {
      ToggleButton(CenterButton, prevousCentre, 3, 0b1000);
      CenterButton = ToggleSelectedButton;
      prevousCentre = TogglePrevousButtonVal;

    } else{prevousCentre = prevousCentre & 0b0111;} 

    if (e.menuButton)  {      
      ToggleButton(CenterButton, prevousCentre, 2, 0b0100);
      CenterButton = ToggleSelectedButton;
      prevousCentre = TogglePrevousButtonVal;

    } else{prevousCentre = prevousCentre & 0b1011;} 

    if (e.viewButton)  {      
      ToggleButton(CenterButton, prevousCentre, 1, 0b0010);
      CenterButton = ToggleSelectedButton;
      prevousCentre = TogglePrevousButtonVal;
    } else{prevousCentre = prevousCentre & 0b1101;} 

    if (e.xboxButton)  {     
      ToggleButton(CenterButton, prevousCentre, 0, 0b0001);
      CenterButton = ToggleSelectedButton;
      prevousCentre = TogglePrevousButtonVal;
    } else{prevousCentre = prevousCentre & 0b1110;} 
    //LeftStick
    LSXCorrected = e.leftStickX * 100;
    
    LSYCorrected = e.leftStickY * 100;

    RSXCorrected = e.rightStickX * 100;
    RSYCorrected = e.rightStickY * 100;

    LTCorrected = e.leftTrigger  * 100;
    RTCorrected = e.rightTrigger * 100;

    if (bitRead(CenterButton, 3)){

      if(e.buttonA) {//1000
        ToggleButton(LetterButton, prevousLetter, 3, 0b1000);
        LetterButton = ToggleSelectedButton;
        prevousLetter = TogglePrevousButtonVal;
      } else{prevousLetter = prevousLetter & 0b0111;} 

      if(e.buttonB) {       //0100 
        ToggleButton(LetterButton, prevousLetter, 2, 0b0100);
        LetterButton = ToggleSelectedButton;
        prevousLetter = TogglePrevousButtonVal;
      } else{prevousLetter = prevousLetter & 0b1011;}

      if(e.buttonX) {     //0010
        ToggleButton(LetterButton, prevousLetter, 1, 0b0010);
        LetterButton = ToggleSelectedButton;
        prevousLetter = TogglePrevousButtonVal;
      } else{prevousLetter = prevousLetter & 0b1101;}  

      if(e.buttonY) {     //0001
        ToggleButton(LetterButton, prevousLetter, 0, 0b0001);
        LetterButton = ToggleSelectedButton;
        prevousLetter = TogglePrevousButtonVal;
      } else{prevousLetter = prevousLetter & 0b1110;}   



    //Left Bumper, Right Bumper, Left Stick, Right Stick
      if (e.leftBumper)      {
        ToggleButton(BumperButton, prevousBumper, 3, 0b1000);
        BumperButton = ToggleSelectedButton;
        prevousBumper = TogglePrevousButtonVal;
      } else{prevousBumper = prevousBumper & 0b0111;} 

      if (e.rightBumper)     {
        ToggleButton(BumperButton, prevousBumper, 2, 0b0100);
        BumperButton = ToggleSelectedButton;
        prevousBumper = TogglePrevousButtonVal;
      } else{prevousBumper = prevousBumper & 0b1011;} 

      if (e.leftStickButton) {
        ToggleButton(BumperButton, prevousBumper, 1, 0b0010);
        BumperButton = ToggleSelectedButton;
        prevousBumper = TogglePrevousButtonVal;
      } else{prevousBumper = prevousBumper & 0b1101;} 

      if (e.rightStickButton){
        ToggleButton(BumperButton, prevousBumper, 0, 0b0001);
        BumperButton = ToggleSelectedButton;
        prevousBumper = TogglePrevousButtonVal;
      } else{prevousBumper = prevousBumper & 0b1110;} 



    //Up, Down, Left, Right
      if (e.dpadUp){ //1000
        if (!bitRead(prevousDPad, 3)){
          prevousDPad = prevousDPad | 0b1000;
      
          if ((!bitRead(DPadButton, 3)) && (bitRead(DPadButton, 2))){
            DPadButton = DPadButton ^ 0b1100;
          }
          else{
            DPadButton = DPadButton ^ 0b1000;
          }
        }
      }else{prevousDPad = prevousDPad & 0b0111;} 

      if (e.dpadDown)  { //0100  
        if (!bitRead(prevousDPad, 2)){
          prevousDPad = prevousDPad | 0b0100;
          if ((bitRead(DPadButton, 3)) && (!bitRead(DPadButton, 2))){
            DPadButton = DPadButton ^ 0b1100;
          }
          else{
            DPadButton = DPadButton ^ 0b0100;
          }
        } 
      }else{prevousDPad = prevousDPad & 0b1011;} 

      if (e.dpadLeft)  { //0010 
        if (!bitRead(prevousDPad, 1)){
          prevousDPad = prevousDPad | 0b0010;
          if ((!bitRead(DPadButton, 1)) && (bitRead(DPadButton, 0))){
            DPadButton = DPadButton ^ 0b0011;
          }
          else{
            DPadButton = DPadButton ^ 0b0010;
          }
        }  
      }else{prevousDPad = prevousDPad & 0b1101;} 

      if (e.dpadRight) { //0001
        if (!bitRead(prevousDPad, 0)){
          prevousDPad = prevousDPad | 0b0001;
          if ((bitRead(DPadButton, 1)) && (!bitRead(DPadButton, 0))){
            DPadButton = DPadButton ^ 0b0011;
          }
          else{
            DPadButton = DPadButton ^ 0b0001;
          }
        } 
      }else{prevousDPad = prevousDPad & 0b1110;} 

    }else{
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
    }

    //PrintValues();

  }


  void PrintValues(){
    Serial.printf("LX / LY: %.2f / %.2f\n", e.leftStickX, e.leftStickY);
    Serial.printf("LX / LY: %f / %f\n", LSXCorrected, LSYCorrected);

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
    Serial.println();
    Serial.println();
  }
};