
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <ArduinoEigenDense.h> // prob not use




Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);


#include <Leg.hpp>




#include <Controller.hpp>
XboxController controller;
ControllerClass XController(controller);


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

int MidPoint = (SERVOMAXWORK + SERVOMINWORK)/2;

double stepHeight = 15;
double stepMidYPoint = 190;

double stepMidXPoint = 0;
double stepXOffset = 15;

int ZeroPotions[] = {115,111,130,115,90,100,165,25,165,55};

float L1 = 70.85; 
float L2 = 77;
float L3 = 79.35;


// Timing Variables
double elapsed = 0;
double start = 0;
double dt = 0;
double t = 0;




Leg legRight(pwm, 0, 0, 0, 0, 0, L1,L2,L3);
Leg legLeft(pwm, 0, 0, 0, 0, 0, L1,L2,L3);


int step = 0; //number of loops through the code

//Uses Zero Potions
void StraightLeg(){

  pwm.setPWM(0, 0, map(ZeroPotions[0],SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
  pwm.setPWM(1, 0, map(ZeroPotions[1],SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
  delay(10);
  pwm.setPWM(2, 0, map(ZeroPotions[2],SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
  pwm.setPWM(3, 0, map(ZeroPotions[3],SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
  delay(10);
  pwm.setPWM(4, 0, map(ZeroPotions[4],SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
  pwm.setPWM(5, 0, map(ZeroPotions[5],SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
  delay(10);
  pwm.setPWM(6, 0, map(ZeroPotions[6],SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
  pwm.setPWM(7, 0, map(ZeroPotions[7],SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
  delay(10);
  pwm.setPWM(8, 0, map(ZeroPotions[8],SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
  pwm.setPWM(9, 0, map(ZeroPotions[9],SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
  delay(10);
}
//Sat
void Sat(){
//ZeroPotions[] = {115,111,130,115,105,110,190,26,160,60};
  //Hip1
  pwm.setPWM(0, 0, map(ZeroPotions[0],SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
  pwm.setPWM(1, 0, map(ZeroPotions[1],SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
  delay(10);
  //Hip2
  pwm.setPWM(2, 0, map(ZeroPotions[2],SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
  pwm.setPWM(3, 0, map(ZeroPotions[3],SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
  delay(10);
  //Thigh
  pwm.setPWM(4, 0, map((ZeroPotions[4] - 25),SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
  pwm.setPWM(5, 0, map((ZeroPotions[5] + 25),SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
  delay(10);
  //Knee36
  pwm.setPWM(6, 0, map((ZeroPotions[6] - 120),SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK)); //40
  pwm.setPWM(7, 0, map((ZeroPotions[7] + 120),SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));//165
  delay(10);
  //Ankle
  pwm.setPWM(8, 0, map((ZeroPotions[8] - 94),SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK)); //61
  pwm.setPWM(9, 0, map((ZeroPotions[9] + 92),SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
  delay(10);

}


void DriveMotor(int thighOffset, int RollHipR, int RollHipL, int SwivelR, int SwivelL){
  legLeft.LeftLeg(thighOffset);
  legRight.RightLeg(thighOffset);
  legLeft.LeftHip(RollHipL, SwivelL);
  legRight.RightHip(RollHipR, SwivelR);
}





void setup() {
  Serial.begin(9600);
  pwm.begin();

  pwm.setPWMFreq(SERVO_FREQ); // Set PWM frequency to 50 Hz
  pwm.setOscillatorFrequency(27000000);


  controller.begin();

  //Controller check
  if (!XController.CheckConnected()){Serial.printf("\n\n         Not Connected\n\n\n");}

  StraightLeg();
  delay(2000);
  Sat();
  delay(500);
  // StandPos();
  // delay(1000);
}

void loop() {
  double Speed = 1;
  elapsed = millis() - start;
  dt = elapsed / 1000.0;
  start = millis();
  t += dt;




  //Serial.printf("\n\n\ndt = %f.2\n\n\n",dt);


  if(XController.ControllerFetchReadings()){
    

    //Xbox button turns on legs segment
    if (bitRead(XController.CenterButton, 0)){
      
      if (bitRead(XController.DPadButton, 3)){
        int MappedVal = map(XController.LSYCorrected, -100, 100, -25, 25);
        Speed = 0.1 + (MappedVal/10);
        //Walk Forward
        legRight.setGaitposStepforward(legRight, 0, t, Speed);
        legRight.XYCalc(legRight.targetX, legRight.targetY);

        legLeft.setGaitposStepforward(legLeft, M_PI, t, Speed);
        legLeft.XYCalc(legLeft.targetX, legLeft.targetY);

        DriveMotor(0,0,0,0,0);

      }else if(bitRead(XController.DPadButton, 2)){                              ///////////test///////////////
        //Walk backwards
        legRight.setGaitposStepforward(legRight, 0, t, -Speed);
        legRight.XYCalc(legRight.targetX, legRight.targetY);

        legLeft.setGaitposStepforward(legLeft, M_PI, t, -Speed);
        legLeft.XYCalc(legLeft.targetX, legLeft.targetY);
        DriveMotor(0,0,0,0,0);

      }else{
        legRight.XYCalc(0, 200);
        legLeft.XYCalc(0, 200);
        DriveMotor(0,0,0,0,0);
        // legLeft.LeftLeg(10);
        // legRight.RightLeg(10);
        // legLeft.LeftHip(0, 0);
        // legRight.RightHip(0, 0);
        //Sat();
      }


    }else{
      Sat();

    }

  }else{      
    Sat();


  }
  //legLeft.LeftHip(0, 0);
  //legRight.RightHip(0, 0);
  //classBD1.HeadForwards(5);
  //classBD1.SetMotorAngle(0,0,0,0,0);
  while (millis() - start < 10) {}  // 100Hz Main Loop
  step++;
}
  


