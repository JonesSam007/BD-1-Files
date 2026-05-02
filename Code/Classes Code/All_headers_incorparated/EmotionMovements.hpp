#include "Arduino.h"
#include "HardwareSerial.h"


class EmotionsMovements{
private:
int PrevRSL = 0b0000;
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


  void Randomised(){
    int mood = random(10);

    switch (mood) {
      case 0:
        Serial.printf("Happy\n");
        Emote.happySound();

        break;
      case 1:
        Serial.printf("curiousSound\n");
        Emote.curiousSound();
        break;
      case 2:
        Serial.printf("sadSound\n");
        Emote.sadSound();
        break;
      case 3:
        Serial.printf("alertSound\n");
        Emote.alertSound();
        break;
      case 4:
        Serial.printf("idleSound\n");
        Emote.idleSound();
        break;
      case 5: Emote.backChat(); break;
      case 6: Emote.muttering(); break;
      case 7: Emote.nervous(); break;
      case 8: Emote.scared(); break;
      case 9: delay(100); break;
    }
  }













  bool CheckButtons(){
    //if the stick buttons are pressed then check for emotes 
    //, Left Stick, Right Stick
    bool StickPressed = 0;
    if ((XController.BumperButton > 0)&& (XController.BumperButton <= 3)){
      //
      
      switch (XController.BumperButton){
        case 1:
        //Serial.printf("Right Stick\n");
          switch (XController.LetterButton){
            case 1: //Y
              if (!bitRead(PrevRSL, 0)){
                Randomised();
              }
            break;
            case 2: //X
              if (!bitRead(PrevRSL, 1)){
                Emote.backChat();
              }
            break;
            case 4: //B
              if (!bitRead(PrevRSL, 2)){
                Emote.alertSound();
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
        break;
        case 2:
        //Serial.printf("Left Stick\n");
        switch (XController.LetterButton){
          case 1: //Y

          break;
          case 2: //X
          break;
          case 4: //B
          break;
          case 8: //A
            //HeadNod();
          break;
        }
        break;
        case 3:
        legRight.Sit();
        //Serial.printf("Right Stick and Left\n");
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
      PrevRSL = XController.LetterButton;
      XController.LetterButton = 0b0000;
      
    }else{StickPressed = 0;} //if none are pressed then normal motions 

    return StickPressed;
  }



};