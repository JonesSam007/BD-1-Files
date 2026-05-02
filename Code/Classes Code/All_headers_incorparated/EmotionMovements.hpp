#include "HardwareSerial.h"


class EmotionsMovements{
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

  void Happy(){
    Emote.happySound();

  }
















  bool CheckButtons(){
    //if the stick buttons are pressed then check for emotes 
    //, Left Stick, Right Stick
    bool StickPressed = 0;
    if ((XController.BumperButton > 0)&& (XController.BumperButton <= 3)){
      //
      
      switch (XController.BumperButton){
        case 1:
        Serial.printf("Right Stick\n");
          switch (XController.LetterButton){
            case 1: //Y

            break;
            case 2: //X
            break;
            case 4: //B
            break;
            case 8: //A
              //Happy
              Happy();
            break;
          }
        break;
        case 2:
        Serial.printf("Left Stick\n");
        switch (XController.LetterButton){
          case 1: //Y

          break;
          case 2: //X
          break;
          case 4: //B
          break;
          case 8: //A
          break;
        }
        break;
        case 3:
        legRight.Sit();
        Serial.printf("Right Stick and Left\n");
        switch (XController.LetterButton){
          case 1: //Y

          break;
          case 2: //X
          break;
          case 4: //B
          break;
          case 8: //A
          break;
        }
        break;

      }
      Emote.Quiet();
      StickPressed = 1;
      
    }else{StickPressed = 0;} //if none are pressed then normal motions 

    return StickPressed;
  }



};