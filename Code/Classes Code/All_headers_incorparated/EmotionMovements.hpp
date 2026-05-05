#include "class/cdc/cdc.h"
#include "Arduino.h"
#include "HardwareSerial.h"


class EmotionsMovements{
private:
int PrevRSL = 0b0000;
int movementDelay = 10;
bool PrevEmote = false;
public:

  //Adafruit_PWMServoDriver& servoDriver;
  double sideParallelPos = 0;
  double ForwardParallelPos = 0;
  double LookUP = 0;
  double LookSide = 0;
  double Tilt = 0;
  double Ear = 0;

  double RRH = 0; //Right Roll Hip
  double RTH = 0; //Right Turn Hip
  double RTL = 0; //Right Thigh Leg
  double RKL = 0; //Right Knee Leg
  double RAL = 0; //Right Ankle Leg

  double LRH = 0; //Left Roll Hip
  double LTH = 0; //Left Turn Hip
  double LTL = 0; //Left Thigh Leg
  double LKL = 0; //Left Knee Leg
  double LAL = 0; //Left Ankle Leg

  int Yes;
public:

//Head = classBD1.
//.SetMotorAngle(double sideParallelPos, double ForwardParallelPos, double LookUP, double LookSide, double Tilt, double Ear)

//Legs
//legRight
//legLeft
  EmotionsMovements(int _yes){
    Yes = _yes;
    sideParallelPos = 0;
    ForwardParallelPos = 0;
    LookUP = 0;
    LookSide = 0;
    Tilt = 0;
    Ear = 0;

    RRH = 0; //Right Roll Hip
    RTH = 0; //Right Turn Hip
    RTL = 0; //Right Thigh Leg
    RKL = 0; //Right Knee Leg
    RAL = 0; //Right Ankle Leg

    LRH = 0; //Left Roll Hip
    LTH = 0; //Left Turn Hip
    LTL = 0; //Left Thigh Leg
    LKL = 0; //Left Knee Leg
    LAL = 0; //Left Ankle Leg
  }

///////////////////////////////////////////////////////////////////////////////////////////////
//Head movements
///////////////////////////////////////////////////////////////////////////////////////////////

  void HeadNod(){
    //int i = 0;
    int highestPoint = 15;
    int lowestPoint = -15;
    for (double i = 0; i <= 15; i++) {
      classBD1.LookUP = i;
      classBD1.SetMotorAngle();
      delay(movementDelay);
    } 
    for (double i = highestPoint; i >= lowestPoint; i--) {
      classBD1.LookUP = i;
      classBD1.SetMotorAngle();
      delay(movementDelay);
    } 
    for (double i = lowestPoint; i <= 0; i++) {
      classBD1.LookUP = i;
      classBD1.SetMotorAngle();
      delay(movementDelay);
    } 
    classBD1.SetMotorZeroAngle();
  }

  void HeadShake(){
    //LS B
    Serial.printf("Shake Head No\n");

    double highestPoint = 40;
    double lowestPoint = -40;
    int LoopSpeed = 3;
    for (int j = 0; j <=1; j++){
    for (double i = 0; i <= highestPoint; i= i+LoopSpeed) {
      classBD1.LookSide = i;
      classBD1.SetMotorAngle();
      delay(movementDelay);
    } 
    for (double i = highestPoint; i >= lowestPoint; i= i-LoopSpeed) {
      classBD1.LookSide = i;
      classBD1.SetMotorAngle();
      delay(movementDelay);
    } 
    for (double i = lowestPoint; i <= 0; i= i+LoopSpeed) {
      classBD1.LookSide = i;
      classBD1.SetMotorAngle();
      delay(movementDelay);
    } 
    }
    classBD1.SetMotorZeroAngle();

  }

  void HeadTilt(){
    //LS X
    Serial.printf("Shake Head No\n");

    double highestPoint = 15;
    double lowestPoint = -15;
    int LoopSpeed = 2;
    for (int j = 0; j <=1; j++){
      for (double i = 0; i <= highestPoint; i= i+LoopSpeed) {
        classBD1.Tilt = i;
        classBD1.SetMotorAngle();
        delay(movementDelay);
      } 
      for (double i = highestPoint; i >= lowestPoint; i= i-LoopSpeed) {
        classBD1.Tilt = i;
        classBD1.SetMotorAngle();
        delay(movementDelay);
      } 
      for (double i = lowestPoint; i <= 0; i= i+LoopSpeed) {
        classBD1.Tilt = i;
        classBD1.SetMotorAngle();
        delay(movementDelay);
      } 
    }
    classBD1.SetMotorZeroAngle();

  }

  void AntenaWag(){
    //LS Y
    Serial.printf("Shake Head No\n");

    double highestPoint = 10;
    double lowestPoint = -10;
    int LoopSpeed = 2;
    for (int j = 0; j <=3; j++){
      for (double i = 0; i <= highestPoint; i= i+LoopSpeed) {
        classBD1.Ear = i;
        classBD1.SetMotorAngle();
        delay(movementDelay);
      } 
      for (double i = highestPoint; i >= lowestPoint; i= i-LoopSpeed) {
        classBD1.Ear = i;
        classBD1.SetMotorAngle();
        delay(movementDelay);
      } 
      for (double i = lowestPoint; i <= 0; i= i+LoopSpeed) {
        classBD1.Ear = i;
        classBD1.SetMotorAngle();
        delay(movementDelay);
      } 
    }
    classBD1.SetMotorZeroAngle();

  }


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Hook
///////////////////////////////////////////////////////////////////////////////////////////////
  void Hooks(){
    XController.CenterButton = XController.CenterButton & 0b1110; //Ensure Xbox button has no effet
    legLeft.HookOut();
    
  }

  void LegsUpForBack(){

    legLeft.theta1 = 0;
    legLeft.theta2 = 0;
    legLeft.theta3 = 0;
    legLeft.theta4 = 90;
    legLeft.theta5 = 0;
    legLeft.LeftLeg(0);
    legLeft.LeftHip(legLeft.theta1,legLeft.theta2);

    legRight.theta1 = 0;
    legRight.theta2 = 0;
    legRight.theta3 = 0;
    legRight.theta4 = 90;
    legRight.theta5 = 0;
    legRight.RightLeg(0);
    legRight.RightHip(legRight.theta1,legRight.theta2);
  }

///////////////////////////////////////////////////////////////////////////////////////////////

  

//Only noise making
  void Noises(){
    //Serial.printf("Right Stick\n");
    switch (XController.LetterButton){
      case 1: //Y
        if (!bitRead(PrevRSL, 0)){
          Emote.Randomised();
        }
      break;
      case 2: //X
        if (!bitRead(PrevRSL, 1)){
          Emote.backChat();
        }
      break;
      case 4: //B
        if (!bitRead(PrevRSL, 2)){
          Emote.muttering();
        }
      break;
      case 8: //A
        //Happy
        if (!bitRead(PrevRSL, 3)){
          Emote.happySound();
        }
        //XController.LetterButton = XController.LetterButton & 0b0111;
        
      break;
    }
  }

  void Movements(){

    //Serial.printf("Left Stick\n");
    switch (XController.LetterButton){
      case 1: //Y
      AntenaWag();
      break;
      case 2: //X
       HeadTilt();
      break;
      case 4: //B
      HeadShake();
      break;
      case 8: //A
        HeadNod();
      break;
    }

  }







//||

  bool CheckButtons(){
    //if the stick buttons are pressed then check for emotes 
    //, Left Stick, Right Stick
    bool StickPressed = 0;
    if ((XController.BumperButton > 0) && (XController.BumperButton <= 3)){
      legLeft.HookIn();
      
      switch (XController.BumperButton){
        case 1:
        //RS
          
          Noises();
        break;
        case 2:
        //LS
          Movements();
        break;
        case 3:
        //LS RS
          Movements();
          Noises();
        //legRight.Sit();
        //Serial.printf("Right Stick and Left\n");
        break;

      }
      Emote.Quiet();
      StickPressed = 1;
      //PrevEmote = true;
      
      PrevRSL = XController.LetterButton;
      XController.LetterButton = 0b0000;
      XController.CenterButton = XController.CenterButton & 0b1110;
      PrevEmote = true;
      
    }else if (XController.BumperButton > 3) {
      Hooks();
      LegsUpForBack();
      //Left Bumper, Right Bumper, Left Stick, Right Stick
      switch (XController.BumperButton){
        case 4:
        case 8: //RB
          Serial.printf("Bumpers\n");

        break;
        case 5: //RG,RS
        Noises();
        break;
        case 6: //RB,LS
        Movements();
        break;
        case 7: //RB,LS,RS

        break;
        //case 8: //LB
        
        //break;
        case 9: //LB,RS
        break;
        case 10: //LB,LS
        break;
        case 11: //LB,LS,RS
        break;
        case 12: //LB,RB
        break;
        case 13: //LB,RB,RS
        break;
        case 14: //LB,RB,LS
        break;
        case 15: //LB,RB,LS,RS
        break;



      }
      PrevEmote = false;
      XController.CenterButton = XController.CenterButton & 0b1110;

    }else{
      legLeft.HookIn();
      if (PrevEmote = true){
        //legLeft.Sit();
      }
      PrevEmote = false;
      StickPressed = 0;

    } //if none are pressed then normal motions 

    return StickPressed;
  }



};