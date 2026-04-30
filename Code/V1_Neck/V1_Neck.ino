///////////////////////////////////////////////////////////////////////
//Ran on arduino Nano with 1 joystick and 3 potoentiomiters
///////////////////////////////////////////////////////////////////////
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMINPWM 100  // Minimum pulse length count
#define SERVOMAXPWM 600  // Maximum pulse length count
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz
//#define potPin1 A0
int potPin1 = A0; //Joystick x
int AnglePot1 = 0;
int PrevAnglePot1 = 0;
int DEGPot1 = 0;

int potPin2 = A1; //Joystick y
int AnglePot2 = 0;
int PrevAnglePot2 = 0;
int DEGPot2 = 0;

int TILT = A2;
int TILTRead = 0;
int PrevTILTRead = 0;
int TILTDEG = 0;
int TILTDif = 0;

int PAN = A3;
int PANRead = 0;
int PrevPANRead = 0;
int PANDEG = 0;
int PANDif = 0;
int PrevPANDif = 0;

int ROTATE = A6;
int ROTATERead = 0;
int PrevROTATERead = 0;
int ROTATEDEG = 0;
int ROTATEDif = 0;

int SERVOMINDEG = 0;  // Minimum degree
int SERVOMAXDEG = 180;  // Maximum degree

//servo definitions
int SERVOArrayMINDEG[5] = {70, 65, 40, 55, 70};
int SERVOArrayMAXDEG[5] = {110, 120, 140, 125, 110};



int x = 15; //Sensativity value


int HeadM0 = 90;
double HeadM1 = 90;
double HeadM2 = 90;
int HeadM3 = 90;
int HeadM4 = 90;


//zero motors
void StartingPosition(){
  for (int i = 0; i<=4; i++){
    pwm.setPWM(i, 0, map(90, SERVOMINDEG,SERVOMAXDEG, SERVOMINPWM,SERVOMAXPWM));
    delay(100);
  }
}


void setup() {

  Serial.begin(9600);
  //Set up Servo driver board
  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ); // Set PWM frequency to 50 Hz
  //pinMode(potPin1, INPUT);

  StartingPosition();

  delay(2000);
  

}


void loop(){
  //control head forward
  AnglePot1 = analogRead(potPin1);
  PANRead = analogRead(PAN);

  if (AnglePot1 >= (PrevAnglePot1 + x) || AnglePot1 <= (PrevAnglePot1 - x)||PANRead >= (PrevPANRead + x) || PANRead <= (PrevPANRead - x)){

    DEGPot1 = map(AnglePot1, 0, 1023, SERVOArrayMINDEG[1], SERVOArrayMAXDEG[1]);
  
    HeadM1 = DEGPot1;
  
    HeadM2 = SERVOArrayMAXDEG[1] - (DEGPot1 - SERVOArrayMINDEG[1]);

    PrevAnglePot1 = AnglePot1;

    if (PANRead >= (PrevPANRead + x) || PANRead <= (PrevPANRead - x)){
    
      PANDEG = map(PANRead, 0, 1023, SERVOArrayMINDEG[2], SERVOArrayMAXDEG[2]);
      PANDif = PANDEG - 90;
      HeadM2 = HeadM2 + PANDif; //pan
      PrevPANDif = PANDif;
      PrevPANRead = PANRead;
      
    }else {
      HeadM2 = HeadM2 + PrevPANDif; //pan
    }
  }

//////////////////////////////////////////////////////////////////////////////////////////////
  
  //side leveling
  //base all angles off the smaller range 
  
  AnglePot2 = analogRead(potPin2);

  if (AnglePot2 >= (PrevAnglePot2 + x) || AnglePot2 <= (PrevAnglePot2 - x)){

    DEGPot2 = map(AnglePot2, 0, 1023, SERVOArrayMINDEG[0], SERVOArrayMAXDEG[0]);
  
    HeadM0 = DEGPot2;
  
    HeadM3 = HeadM0;

    PrevAnglePot2 = AnglePot2;
  }
///////////////////////////////////////////////////////////////////////////////////////////////

  //Head tilt side to side
  TILTRead = analogRead(TILT);

  if (TILTRead >= (PrevTILTRead + x) || TILTRead <= (PrevTILTRead - x)){

    TILTDEG = map(TILTRead, 0, 1023, SERVOArrayMINDEG[3], SERVOArrayMAXDEG[3]);
    TILTDif = TILTDEG - 90;
    HeadM3 = HeadM3 + TILTDif; //tilt
    PrevTILTRead = TILTRead;
  }

///////////////////////////////////////////////////////////////////////////////////////////////
  
  //Looking left and right
  ROTATERead = analogRead(ROTATE);

  if (ROTATERead >= (PrevROTATERead + x) || ROTATERead <= (PrevROTATERead - x)){
    
    ROTATEDEG = map(ROTATERead, 0, 1023, SERVOArrayMINDEG[4], SERVOArrayMAXDEG[4]);
    HeadM4 = ROTATEDEG;
    PrevROTATERead = ROTATERead;
    
  }
  //ROTATEDif = ROTATEDEG - 90;


  
  if (HeadM3 > SERVOArrayMAXDEG[3]){
    HeadM3 = SERVOArrayMAXDEG[3];
  } else if(HeadM3 < SERVOArrayMINDEG[3]){
    HeadM3 = SERVOArrayMINDEG[3];
  }

  if (HeadM2 > SERVOArrayMAXDEG[2]){
    HeadM2 = SERVOArrayMAXDEG[2];
  } else if(HeadM2 < SERVOArrayMINDEG[2]){
    HeadM2 = SERVOArrayMINDEG[2];
  }

  

///////////////////////////////////////////////////////////
  //Move motors

  pwm.setPWM(0, 0, map(HeadM0,SERVOMINDEG,SERVOMAXDEG, SERVOMINPWM,SERVOMAXPWM));
  pwm.setPWM(1, 0, map(HeadM1,SERVOMINDEG,SERVOMAXDEG, SERVOMINPWM,SERVOMAXPWM));
  pwm.setPWM(2, 0, map(HeadM2,SERVOMINDEG,SERVOMAXDEG, SERVOMINPWM,SERVOMAXPWM));
  pwm.setPWM(3, 0, map(HeadM3,SERVOMINDEG,SERVOMAXDEG, SERVOMINPWM,SERVOMAXPWM));
  pwm.setPWM(4, 0, map(HeadM4,SERVOMINDEG,SERVOMAXDEG, SERVOMINPWM,SERVOMAXPWM));
  delay(200);
}


