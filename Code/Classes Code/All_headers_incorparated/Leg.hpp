#include <ArduinoEigenDense.h>
#include <Adafruit_PWMServoDriver.h>


using namespace Eigen;

class Leg {
public:
  #define SERVOMINPWM 80  // Minimum pulse length count for 996
  #define SERVOMAXPWM 560  // Maximum pulse length count for 996

  int SERVOMINDEG = 0;  // Minimum degree
  int SERVOMAXDEG = 210;  // Maximum degree
  int OffsetDeg = 15;

  int SERVOMINWORK = SERVOMINDEG + OffsetDeg; //Set min degree to ensure all motors have a working range of 180 degrees
  int SERVOMAXWORK = SERVOMAXDEG - OffsetDeg; //Set max degree to ensure all motors have a working range of 180 degrees

  int SERVOMINPWMWORK = map(SERVOMINWORK,SERVOMINDEG,SERVOMAXDEG,SERVOMINPWM,SERVOMAXPWM);
  int SERVOMAXPWMWORK = map(SERVOMAXWORK,SERVOMINDEG,SERVOMAXDEG,SERVOMINPWM,SERVOMAXPWM);

  double theta1 = 0;
  double theta2 = 0;
  double theta3 = 0;
  double theta4 = 0;
  double theta5 = 0;

  int ZeroPositionsLeg0 = 115;
  int ZeroPositionsLeg1 = 111;
  int ZeroPositionsLeg2 = 130;
  int ZeroPositionsLeg3 = 115;
  int ZeroPositionsLeg4 = 105; //112;
  int ZeroPositionsLeg5 = 110; //105;
  int ZeroPositionsLeg6 = 190; //175
  int ZeroPositionsLeg7 = 26; //30;
  int ZeroPositionsLeg8 = 160; //155;
  int ZeroPositionsLeg9 = 60; //55;
  // {115,111,130,115,105,110,190,26,160,60};

  double L1 = 0;
  double L2 = 0;
  double L3 = 0;

  double targetX=0;
  double targetY=0;
  double targetZ=0;

  double stepHeight = 20;
  double stepMidYPoint = 190;

  double stepMidXPoint = 0;
  double stepXOffset = 25;

  double ZInstepMaxAdd = 15;
  double ZInstepoffset = ZInstepMaxAdd;

  Adafruit_PWMServoDriver& servoDriver;

public:
  Leg(Adafruit_PWMServoDriver& _servoDriver, double _t1, double _t2, double _t3, double _t4, double _t5, double _L1, double _L2, double _L3)
    : servoDriver(_servoDriver){
    
    theta1 = _t1;
    theta2 = _t2;
    theta3 = _t3;
    theta4 = _t4;
    theta5 = _t5;

    L1 = _L1;
    L2 = _L2;
    L3 = _L3;
  }


  //Calc invers kine of xy of leg with end potioning established
  void XYCalc(int x, int y){
    //Serial.printf("\nX = %d, Y = %d \n", x, y);
    //Calc for the planar leg (just for motors 4 to 9)
    float A = y - L3;
    float G = sqrt(sq(x) + sq(A)); //assuming y is from joint

    theta4 = acos((sq(G)-sq(L1)-sq(L2)) / ((-2) * L1 * L2));


    float alpha = atan(x/A);
    float beta = asin((L2 * sin(theta4)) / G);

    theta3 = alpha + beta;


    theta3 = theta3 *180/ PI;
    theta4 = theta4 *180/ PI;

    theta5 = 180 - theta3 - theta4;
    
    // Serial.print("Theta1 = ");
    // Serial.println(theta1);
    // Serial.print("Theta2 = ");
    // Serial.println(theta2);
    // Serial.print("Theta3 = ");
    // Serial.println(theta3);
    // Serial.println();
    
   }

  void RightLeg(int ThighOffset){
  
    //Thigh
    pwm.setPWM(4, 0, map(ZeroPositionsLeg4 - (theta3 + ThighOffset),SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
    //delay(20);
    //Knee
    pwm.setPWM(6, 0, map(ZeroPositionsLeg6 - (180 - theta4),SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
    //delay(20);
    //Ankle
    pwm.setPWM(8, 0, map(ZeroPositionsLeg8 - theta5,SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
    //delay(20);
   }

  void LeftLeg(int ThighOffset){
    
    //Thigh
    pwm.setPWM(5, 0, map(ZeroPositionsLeg5 + (theta3 + ThighOffset),SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
    //delay(20);
    //Knee
    pwm.setPWM(7, 0, map(ZeroPositionsLeg7 + (180 - theta4),SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
    //delay(20);
    //Ankle
    pwm.setPWM(9, 0, map(ZeroPositionsLeg9 + theta5,SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
    //delay(20);
   }

  void RightHip(int M0, int M2){
    //Right side
    //M0 +ive then leg lift
    pwm.setPWM(0, 0, map(ZeroPositionsLeg0 - M0,SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
    //delay(20);
    //Hip2
    //M2 +ive then leg swing forward
    pwm.setPWM(2, 0, map(ZeroPositionsLeg2 + M2,SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
    //delay(20);
   }
  void LeftHip(int M1, int M3){
      //Left Side
    //M1 +ive then leg lift
    pwm.setPWM(1, 0, map(ZeroPositionsLeg1 + M1,SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
    //delay(20);
    //Hip2
    //M3 +ive then leg swing forward
    pwm.setPWM(3, 0, map(ZeroPositionsLeg3 - M3,SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
    //delay(20);
   }

  
  void setGaitposStomp(Leg& leg, double phaseOffset, double t, double Speed) {
    targetX = 0; 
    targetY = stepMidYPoint + ((stepHeight * sin(Speed * PI * t + phaseOffset))); 
    targetZ = 0;
  }


  void setGaitposStepforward(Leg& leg, double phaseOffset, double t, double Speed) {
    targetX = stepMidXPoint - ((stepXOffset * cos(Speed * PI * t + phaseOffset))); 
    targetY = stepMidYPoint + ((stepHeight * sin(Speed * PI * t + phaseOffset)));  
    targetZ = 0; 
  }

private:
  //MatrixXd computeJacobian(double t1, double t2, double t3, double L1, double L2, double L3);
};

