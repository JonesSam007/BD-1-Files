//////////////////////////////////////////////////////
//ESP32 xiao code for head 
//////////////////////////////////////////////////////
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz
#define SERVOMINPWM 100  // Minimum pulse length count 100
#define SERVOMAXPWM 540  // Maximum pulse length count 540
int SERVOMINDEG = 0;  // Minimum degree
int SERVOMAXDEG = 180;  // Maximum degree
int OffsetDeg = 5;

int SERVOMINWORK = SERVOMINDEG + OffsetDeg; //Set min degree to ensure all motors have a working range of 180 degrees
int SERVOMAXWORK = SERVOMAXDEG - OffsetDeg; //Set max degree to ensure all motors have a working range of 180 degrees

int MidPoint = (SERVOMAXWORK + SERVOMINWORK)/2;
int pulselen;
int servonum = 0;


int Pot1 = A10;
int Pot2 = A3;
int Pot3 = A2;
int Pot4 = A1;
int Pot5 = A0;


void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ); // Set PWM frequency to 50 Hz
  pwm.setOscillatorFrequency(27000000);

}

void loop() {

  // Read values of Potentiomiters
  int ValPot1 = analogRead(Pot1);
  int ValPot2 = analogRead(Pot2);
  int ValPot3 = analogRead(Pot3);
  int ValPot4 = analogRead(Pot4);
  int ValPot5 = analogRead(Pot5);
  //Serial.println(ValPot1);
  //Serial.println(ValPot2);
  
  //Map Pot vals to a range of Dregrees
  int motorDEG1 = map(ValPot1, 0, 4095, SERVOMINDEG, SERVOMAXDEG);
  int motorDEG2 = map(ValPot2, 0, 4095, SERVOMINDEG, SERVOMAXDEG);
  int motorDEG3 = map(ValPot3, 0, 4095, -30, 30);
  int motorDEG4 = map(ValPot4, 0, 4095, SERVOMINDEG, SERVOMAXDEG);
  int motorDEG5 = map(ValPot5, 0, 4095, SERVOMINDEG, SERVOMAXDEG);

  //Print to see angles
  Serial.printf("Base Neck Tilt angle    = %d\n",motorDEG1);
  Serial.printf("Base Neck Fowards angle = %d\n",motorDEG2);
  Serial.printf("Top Neck Forwards angle = %d\n",motorDEG3);
  Serial.printf("Top Neck Tilt angle     = %d\n",motorDEG4);
  Serial.printf("Rotate angle            = %d\n",motorDEG5);
  
  //Convert to PWM values
  int motorPWM1 = map(motorDEG1,SERVOMINDEG,SERVOMAXDEG, SERVOMINPWM, SERVOMAXPWM);
  int motorPWM2 = map(motorDEG2,SERVOMINDEG,SERVOMAXDEG, SERVOMINPWM, SERVOMAXPWM);
  int motorPWM3 = map(motorDEG3,SERVOMINDEG,SERVOMAXDEG, SERVOMINPWM, SERVOMAXPWM);
  int motorPWM4 = map(motorDEG4,SERVOMINDEG,SERVOMAXDEG, SERVOMINPWM, SERVOMAXPWM);
  int motorPWM5 = map(motorDEG5,SERVOMINDEG,SERVOMAXDEG, SERVOMINPWM, SERVOMAXPWM);

  //Serial.println(motorPWM1);
  //Serial.println(motorPWM2);
  
  //Move motors
  pwm.setPWM(0, 0, motorPWM1);
  delay(10);
  pwm.setPWM(1, 0, motorPWM2);
  delay(10);
  pwm.setPWM(2, 0, map(180 - motorDEG2,SERVOMINDEG,SERVOMAXDEG, SERVOMINPWM, SERVOMAXPWM));
  delay(10);
  pwm.setPWM(3, 0, map(motorDEG2 + motorDEG3,SERVOMINDEG,SERVOMAXDEG, SERVOMINPWM, SERVOMAXPWM));
  delay(10);
  pwm.setPWM(4, 0, map(180 - motorDEG2 - motorDEG3,SERVOMINDEG,SERVOMAXDEG, SERVOMINPWM, SERVOMAXPWM));
  delay(10);
  pwm.setPWM(5, 0, motorPWM4);
  delay(10);
  pwm.setPWM(6, 0, motorPWM5);
  delay(50);
  Serial.println();

}
