
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <ArduinoEigenDense.h> // prob not use


#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver neck = Adafruit_PWMServoDriver(0x41);
Adafruit_MPU6050 mpu;

#include <Servo.hpp>
#include <Leg.hpp>
#include <MPU6050.hpp>
#include <PID.hpp>



#include <Controller.hpp>
XboxController controller;
ControllerClass XController(controller);

#include <Head.hpp>
HeadClass classBD1(neck, 0,0,0,0,0);

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

int ZeroPotions[] = {115,111,130,115,105,110,190,26,160,60};

float L1 = 70.85; 
float L2 = 77;
float L3 = 79.35;

int ZeroPotionsNeck[] = {50,180,115,60,85};

int NeckPosition[] = {50,180,115,60,85};
// Timing Variables
double elapsed = 0;
double start = 0;
double dt = 0;
double t = 0;




Leg legRight(pwm, 0, 0, 0, 0, 0, L1,L2,L3);
Leg legLeft(pwm, 0, 0, 0, 0, 0, L1,L2,L3);
MPU6050Class MPU6050(mpu);

double ProportionalGainP = 0.15;      //2
double IntegralGainP = 0.05;      //0.05
double DerivativeGainP = 0.0001; //0.001

double ProportionalGainR = 0.25;      //2
double IntegralGainR = 0.005;      //0.05
double DerivativeGainR = 0.00001; //0.001
PID PIDPitch(ProportionalGainP, IntegralGainP, DerivativeGainP);
PID PIDRoll(ProportionalGainR, IntegralGainR, DerivativeGainR);


// LED and light
const int ledTorchPin = 9; // D2 corresponds to GPIO2
const int ledSidePin = 8; // D2 corresponds to GPIO2
bool SideOfHeadState = false; //shows when the LED is on or off

int step = 0; //number of loops through the code


// Speaker
int speakerPin = 2;
#include <Emotions.h>
Emotions Emote(speakerPin);

//Emotions
#include <EmotionMovements.hpp>
EmotionsMovements EmoteMoves(0);

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
  pwm.setPWM(4, 0, map((ZeroPotions[4] - 42),SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
  pwm.setPWM(5, 0, map((ZeroPotions[5] + 45),SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
  delay(10);
  //Knee36
  pwm.setPWM(6, 0, map((ZeroPotions[6] - 135),SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK)); //40
  pwm.setPWM(7, 0, map((ZeroPotions[7] + 135),SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));//165
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

void LEDFlashRate(int CheckVal){
  if (step >= CheckVal){
    if (SideOfHeadState == false){
      digitalWrite(ledSidePin, HIGH);
      SideOfHeadState = true;
    }else{
      digitalWrite(ledSidePin, LOW);
      SideOfHeadState = false;
    }
    step = 0;
  }
}



void setup() {
  Serial.begin(9600);
  pwm.begin();
  neck.begin();

  pwm.setPWMFreq(SERVO_FREQ); // Set PWM frequency to 50 Hz
  neck.setPWMFreq(SERVO_FREQ); // Set PWM frequency to 50 Hz

  pwm.setOscillatorFrequency(27000000);
  neck.setOscillatorFrequency(27000000);

  MPU6050.startup();

  controller.begin();

  //Controller check
  //if (!XController.CheckConnected()){Serial.printf("\n\n         Not Connected\n\n\n");}
  
  pinMode(ledTorchPin, OUTPUT);
  pinMode(ledSidePin, OUTPUT);

  //StraightLeg();
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
    int _CheckFlash = 50;

    if(!EmoteMoves.CheckButtons()){
      classBD1.NeckCalc();

      if (bitRead(XController.LetterButton, 1)){
        //digitalWrite(ledTorchPin, HIGH);
        digitalWrite(ledSidePin, HIGH);
        
        //Serial.printf("\n ON\n");
      }else {
        //removed due to always turning LEDoff eeven if auto turn on happens
        //digitalWrite(ledTorchPin, LOW);
        //digitalWrite(ledSidePin, LOW);
        //Serial.printf("\n OFF\n");

      }

      if (bitRead(XController.LetterButton, 0)){
        digitalWrite(ledTorchPin, HIGH);
        //digitalWrite(ledSidePin, HIGH);
        
        //Serial.printf("\n ON\n");
      }else {
        digitalWrite(ledTorchPin, LOW);
        //digitalWrite(ledSidePin, LOW);
        
        //Serial.printf("\n OFF\n");
      }

      //bitRead(XController.LetterButton, 1)
      //Xbox button turns on legs segment
      if (bitRead(XController.CenterButton, 0)){
        _CheckFlash = 40;
        if (bitRead(XController.DPadButton, 3)){
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

        }else if(bitRead(XController.CenterButton,1)){                              ///////////test///////////////
            //PID Controller 
            legRight.XYCalc(10, 200);
            legLeft.XYCalc(-5, 200);

            legRight.XYCalc(0, 200);
            legLeft.XYCalc(0, 200);

            MPU6050.ReadValues();
            MPU6050.CalcPitRoll();
            PIDPitch.TargetAngle = 0;
            PIDRoll.TargetAngle = 0;

            PIDPitch.PIDCalc(dt, MPU6050.pitch);
            PIDRoll.PIDCalc(dt, MPU6050.roll);

            double PitchCorrection = map(PIDPitch.OverallOutput, -100, 100, -30,30);
            double RollCorrection = map(PIDRoll.OverallOutput, -100, 100, -30,30);
//////////////
            legLeft.LeftLeg(PIDPitch.OverallOutput);
            legRight.RightLeg(PIDPitch.OverallOutput);
            legLeft.LeftHip(PIDRoll.OverallOutput+10, 0);
            legRight.RightHip(PIDRoll.OverallOutput+10, 0);
            DriveMotor(PIDPitch.OverallOutput,(PIDRoll.OverallOutput+10),(PIDRoll.OverallOutput+10),0,0);
        }else{
          legRight.XYCalc(10, 200);
          legLeft.XYCalc(-10, 200);
          DriveMotor(10,10,0,0,0);
          // legLeft.LeftLeg(10);
          // legRight.RightLeg(10);
          // legLeft.LeftHip(0, 0);
          // legRight.RightHip(0, 0);
          //Sat();
        }


      }else{
        Sat();

      }
      
      LEDFlashRate(_CheckFlash);
    }
  }else{      
    Sat();

    //Every 50 loops it switches value of LED
    LEDFlashRate(25);
  }
  
  //legLeft.LeftHip(0, 0);
  //legRight.RightHip(0, 0);
  //classBD1.HeadForwards(5);
  //classBD1.SetMotorAngle(0,0,0,0,0);
  while (millis() - start < 10) {}  // 100Hz Main Loop
  step++;
}
  

  // // legRight.XYCalc(10, 180);
  // // legLeft.XYCalc(-5, 180);

  // // legRight.XYCalc(0, 200);
  // // legLeft.XYCalc(0, 200);


  // // MPU6050.ReadValues();
  // // MPU6050.CalcPitRoll();
  // // PIDPitch.TargetAngle = 0;
  // // PIDRoll.TargetAngle = 0;

  // // PIDPitch.PIDCalc(dt, MPU6050.pitch);
  // // PIDRoll.PIDCalc(dt, MPU6050.roll);

  // // double PitchCorrection = map(PIDPitch.OverallOutput, -100, 100, -30,30);
  // // double RollCorrection = map(PIDRoll.OverallOutput, -100, 100, -30,30);

  // // legLeft.LeftLeg(PIDPitch.OverallOutput);
  // // legRight.RightLeg(PIDPitch.OverallOutput);
  // // legLeft.LeftHip(PIDRoll.OverallOutput+10, 0);
  // // legRight.RightHip(PIDRoll.OverallOutput+10, 0);
////////////////////////////////////////////////////////////////////////////////////////////////

//     elapsed = millis() - start;
//   dt = elapsed / 1000.0;
//   start = millis();
//   t += dt;

//   legRight.XYCalc(0, 200);
//   legLeft.XYCalc(0, 170);

//   legLeft.LeftLeg(0);
//   legRight.RightLeg(0);
//   //legLeft.LeftHip(0, 0);
//   //legRight.RightHip(0, 0);
//   //classBD1.HeadForwards(5);
//   //classBD1.SetMotorAngle(0,0,0,0,0);
//   while (millis() - start < 10000) {}  // 100Hz Main Loop

//     Sat();
//     elapsed = millis() - start;
//   dt = elapsed / 1000.0;
//   start = millis();
//   t += dt;
//  while (millis() - start < 10000) {}  // 100Hz Main Loop


