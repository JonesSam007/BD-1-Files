#include <Adafruit_PWMServoDriver.h>
//#include <Controller.hpp>


class HeadClass {
private:
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz
#define SERVOMINPWM 80  // Minimum pulse length count for 996
#define SERVOMAXPWM 560  // Maximum pulse length count for 996

#define SERVOMINPWM90 100  // Minimum pulse length count for Mg90s
#define SERVOMAXPWM90 540  // Maximum pulse length count for MG90s
int SERVOMINDEG90 = 0;  // Minimum degree
int SERVOMAXDEG90 = 180;  // Maximum degree
int OffsetDeg90 = 5;

int SERVOMINDEG = 0;  // Minimum degree
int SERVOMAXDEG = 210;  // Maximum degree
int OffsetDeg = 15;

int SERVOMINWORK = SERVOMINDEG + OffsetDeg; //Set min degree to ensure all motors have a working range of 180 degrees
int SERVOMAXWORK = SERVOMAXDEG - OffsetDeg; //Set max degree to ensure all motors have a working range of 180 degrees


int SERVOMINPWMWORK = map(SERVOMINWORK,SERVOMINDEG,SERVOMAXDEG,SERVOMINPWM,SERVOMAXPWM);
int SERVOMAXPWMWORK = map(SERVOMAXWORK,SERVOMINDEG,SERVOMAXDEG,SERVOMINPWM,SERVOMAXPWM);

int ZeroPositionDeg0 = 99;
int ZeroPositionDeg1 = 98 +40;
int ZeroPositionDeg2 = 97-35;
int ZeroPositionDeg3 = 80;
int ZeroPositionDeg4 = 100;
int ZeroPositionDeg5 = 90;
int ZeroPositionDeg6 = 90;

int LimitBaseTiltMin = 75; //towards Left
int LimitBaseTiltMax = 125; //towards Right
int BaseTiltMid = (LimitBaseTiltMin + LimitBaseTiltMax) / 2;

int LimitBasePitchMin = 40; //Forward
int LimitBasePitchMax = 160; //Backward
int BasePitchMid = (LimitBasePitchMin + LimitBasePitchMax) / 2;


int LimitHeadPitchMin = 40; //Look Down
int LimitHeadPitchMax = 160; //Look up
int HeadPitchMid = (LimitHeadPitchMin + LimitHeadPitchMax) / 2;

int LimitHeadTiltMin = 0; //tilt Right
int LimitHeadTiltMax = 0; //tilt Left

int LimitHeadRotateMin = 10; //rotate Left
int LimitHeadRotateMax = 180; //rotate Right

  Adafruit_PWMServoDriver& servoDriver;
  double sideParallelPos = 0;
  double ForwardParallelPos = 0;
  double LookUP = 0;
  double LookSide = 0;
  double Tilt = 0;
  double Ear = 0;


public:

  HeadClass(Adafruit_PWMServoDriver& _servoDriver,  double _sideParallelPos, double _ForwardParallelPos, double _LookUP, double _LookSide, double _Tilt)
    : servoDriver(_servoDriver){
    sideParallelPos = _sideParallelPos;
    ForwardParallelPos = ForwardParallelPos;
    LookUP = _LookUP;
    LookSide = _LookSide;
    Tilt = _Tilt;
  }

  void startUP(){
    neck.begin();
    //Servo Board startup
    neck.setPWMFreq(SERVO_FREQ); // Set PWM frequency to 50 Hz
    neck.setOscillatorFrequency(27000000);
  }

  void SetMotorAngle(double sideParallelPos, double ForwardParallelPos, double LookUP, double LookSide, double Tilt, double Ear){
      neck.setPWM(0,0,map(ZeroPositionDeg0 + sideParallelPos, SERVOMINWORK, SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
      neck.setPWM(1,0,map(ZeroPositionDeg1 + ForwardParallelPos, SERVOMINWORK, SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
      neck.setPWM(2,0,map(ZeroPositionDeg2 - ForwardParallelPos + LookUP, SERVOMINWORK, SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
      neck.setPWM(3,0,map(ZeroPositionDeg3 + 2*sideParallelPos + Tilt, SERVOMINDEG90, SERVOMAXDEG90, SERVOMINPWM90, SERVOMAXPWM90));
      neck.setPWM(4,0,map(ZeroPositionDeg4 + LookSide, SERVOMINDEG90, SERVOMAXDEG90, SERVOMINPWM90, SERVOMAXPWM90));
      neck.setPWM(5,0,map(ZeroPositionDeg5 + Ear, SERVOMINDEG90, SERVOMAXDEG90, SERVOMINPWM90, SERVOMAXPWM90));
      neck.setPWM(6,0,map(ZeroPositionDeg6 - Ear, SERVOMINDEG90, SERVOMAXDEG90, SERVOMINPWM90, SERVOMAXPWM90));

  }

  void NeckCalc(/*int LSXCorrected, int LSYCorrected, RSYCorrected*/){
    //Controller movements
    
    if ((XController.LSXCorrected < -10) || (XController.LSXCorrected > 10)){
      sideParallelPos = map(XController.LSXCorrected, -100, 100, LimitBaseTiltMin,LimitBaseTiltMax);
      sideParallelPos = BaseTiltMid - sideParallelPos;
      //times by 1.2 for motor [3]
    }else{sideParallelPos = 0;}

    if ((XController.LSYCorrected < -10) || (XController.LSYCorrected > 10)){
      ForwardParallelPos = map(XController.LSYCorrected, -100, 100, LimitBasePitchMin,LimitBasePitchMax);
      ForwardParallelPos = BasePitchMid - ForwardParallelPos;
    }else{ForwardParallelPos = 0;}

    if ((XController.RSYCorrected < -10) || (XController.RSYCorrected > 10)){
      LookUP = map(XController.RSYCorrected, -100, 100, LimitHeadPitchMin,LimitHeadPitchMax);   
      LookUP = HeadPitchMid - LookUP;
    }else{LookUP = 0;}

    if ((XController.RSXCorrected < -10) || (XController.RSXCorrected > 10)){
      LookSide = map(XController.RSXCorrected, -100, 100, LimitHeadRotateMin,LimitHeadRotateMax);   
      LookSide = ZeroPositionDeg4 - LookSide;
    }else{LookSide = 0;}

    if (bitRead(XController.CenterButton, 2)){
      if ((XController.LTCorrected > 10) || (XController.RTCorrected > 10)){
        double overallTrigger = XController.LTCorrected - XController.RTCorrected; //Left bias
        Tilt = map(overallTrigger, -100, 100, LimitHeadRotateMin,LimitHeadRotateMax);   
        Tilt = ZeroPositionDeg3 - Tilt;
      }else{Tilt = 0;}
    }else{
      //if ((XController.LTCorrected > 10) || (XController.RTCorrected > 10)){
        double overallTrigger = XController.LTCorrected - XController.RTCorrected; //Left bias
        Ear = map(overallTrigger, -100, 100, 0, 180);   
        Ear = 90 - Ear;
      
    }
    SetMotorAngle(sideParallelPos, ForwardParallelPos, LookUP, LookSide, Tilt, Ear);

  }

  void HeadForwards(int X){
      ForwardParallelPos = BasePitchMid - X;
      Serial.printf("\n ForwardParallelPos = %f.2\n", ForwardParallelPos);
      SetMotorAngle(sideParallelPos, ForwardParallelPos, LookUP, LookSide, Tilt, Ear);
   
  }
  void HeadWalkGateMotion(double t, double Speed) {
    if (cos(Speed * PI * t) >=0){
      sideParallelPos = BaseTiltMid - LimitBaseTiltMin;
    }else{sideParallelPos = BaseTiltMid - LimitBaseTiltMax;}
    //sideParallelPos = stepMidXPoint - (( * cos(Speed * PI * t))); 
    SetMotorAngle(sideParallelPos, ForwardParallelPos, LookUP, LookSide, Tilt,Ear);
  }

};