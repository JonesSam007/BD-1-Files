///////////////////////////////////////////////////////////////////////////////////////////////////
// Walking gait V1 D style cycle (rotated 90 degrees anticlockwise)
///////////////////////////////////////////////////////////////////////////////////////////////////
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);


#define SERVO_FREQ 50 // Analog servos run at ~50 Hz
#define SERVOMINPWM 80  // Minimum pulse length count for 996
#define SERVOMAXPWM 560  // Maximum pulse length count for 996



int SERVOMINDEG = 0;  // Minimum degree
int SERVOMAXDEG = 210;  // Maximum degree
int OffsetDeg = 15;

int SERVOMINWORK = SERVOMINDEG + OffsetDeg; //Set min degree to ensure all motors have a working range of 180 degrees
int SERVOMAXWORK = SERVOMAXDEG - OffsetDeg; //Set max degree to ensure all motors have a working range of 180 degrees

int SERVOMINPWMWORK = map(SERVOMINWORK,SERVOMINDEG,SERVOMAXDEG,SERVOMINPWM,SERVOMAXPWM);
int SERVOMAXPWMWORK = map(SERVOMAXWORK,SERVOMINDEG,SERVOMAXDEG,SERVOMINPWM,SERVOMAXPWM);

int MidPoint = (SERVOMAXWORK + SERVOMINWORK)/2;

float L1 = 70.85; //M0/1 to M2/3 link length
float theta1 = 0;

float L2 = 77; //M2/3 to M4/5 Link length
float theta2 = 0;

float L3 = 79.35; //M4/5 to Floor Link Length
float theta3 = 0;

double stepHeight = 15;
double stepMidYPoint = 190;

double stepMidXPoint = 0;
double stepXOffset = 15;

int ZeroPotions[] = {112,105,175,30,155,55};


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
}
//Sat
void Sat(){

  //Thigh
  pwm.setPWM(0, 0, map(70,SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
  pwm.setPWM(1, 0, map(150,SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
  delay(10);
  //Knee
  pwm.setPWM(2, 0, map(40,SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK)); //36/37
  pwm.setPWM(3, 0, map(165,SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));//175
  delay(10);
  //Ankle
  pwm.setPWM(4, 0, map(61,SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK)); //61
  pwm.setPWM(5, 0, map(147,SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
  delay(10);

}

//Calc invers kine of xy of leg with end potioning established
void XYCalc(int x, int y){
  //Serial.printf("\nX = %d, Y = %d \n", x, y);
  //Calc for the planar leg (just for motors 4 to 9)
  float A = y - L3;
  float G = sqrt(sq(x) + sq(y-L3)); //assuming y is from joint

  theta2 = acos((sq(G)-sq(L1)-sq(L2)) / ((-2) * L1 * L2));


  float alpha = atan(x/A);
  float beta = asin((L2 * sin(theta2)) / G);

  theta1 = alpha + beta;


  theta1 = theta1 *180/ PI;
  theta2 = theta2 *180/ PI;

  theta3 = 180 - theta1 - theta2;
  
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
  pwm.setPWM(0, 0, map(ZeroPotions[0] - (theta1 + ThighOffset),SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
  //delay(20);
  //Knee
  pwm.setPWM(2, 0, map(ZeroPotions[2] - (180 - theta2),SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
  //delay(20);
  //Ankle
  pwm.setPWM(4, 0, map(ZeroPotions[4] - theta3,SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
  //delay(20);
}

void LeftLeg(int ThighOffset){
  
  //Thigh
  pwm.setPWM(1, 0, map(ZeroPotions[1] + (theta1 + ThighOffset),SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
  //delay(20);
  //Knee
  pwm.setPWM(3, 0, map(ZeroPotions[3] + (180 - theta2),SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
  //delay(20);
  //Ankle
  pwm.setPWM(5, 0, map(ZeroPotions[5] + theta3,SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
  //delay(20);
}


//Use for seting XY posiont of the legs
void MotorSet(int ThighOffset){

  //Thigh
  pwm.setPWM(0, 0, map(ZeroPotions[0] - (theta1 + ThighOffset),SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
  pwm.setPWM(1, 0, map(ZeroPotions[1] + (theta1 + ThighOffset),SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
  delay(20);
  //Knee
  pwm.setPWM(2, 0, map(ZeroPotions[2] - (180 - theta2),SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
  pwm.setPWM(3, 0, map(ZeroPotions[3] + (180 - theta2),SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
  delay(20);
  //Ankle
  pwm.setPWM(4, 0, map(ZeroPotions[4] - abs(theta3),SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
  pwm.setPWM(5, 0, map(ZeroPotions[5] + abs(theta3),SERVOMINWORK,SERVOMAXWORK, SERVOMINPWMWORK, SERVOMAXPWMWORK));
  delay(20);

  
}

void StandPos(){
  int x = 0;
  int y = 200;
  int offset = 0;
  XYCalc(x,y);
  MotorSet(offset);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ); // Set PWM frequency to 50 Hz
  pwm.setOscillatorFrequency(27000000);

  Sat();
  delay(2000);
  StandPos();
  delay(1000);

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loop() {
  

  
  //delay(200);
  int SweepDelay = 25;
  int MinX = -20; //forward, can be either -ive or +ive
  int MaxX = 30; //back Has to always be positive
  int DiffX = abs(MaxX) + abs(MinX);
  int MidRangeX = DiffX / 2;
  int MidX = MaxX - MidRangeX;
  int QuaterRangeX = MidRangeX/2;
  int LowerQuaterX = MidX - QuaterRangeX;
  int UpperQuaterX = MidX + QuaterRangeX;

  int yStand = 200;
  int yUp = 170;

  int y = yStand;

  //Left leg
  int step = 0;
  int Lx;
  int Ly = yStand;

  int Thigh = 15;


  //Sweeping x axis
  //Right Leg slides back while left lifts
  Serial.printf("if 1\n");
  for (int x = MinX; x <= MaxX; x=x+2){
    
    /*Serial.print("X = ");
    Serial.println(x);
    Serial.print("Y = ");
    Serial.println(y);*/

    //calc position of right Leg
    XYCalc(x,y);
    RightLeg(Thigh);

    Lx = MaxX - (step*2);  
   /* Serial.print("LX = ");
    Serial.println(Lx);
    Serial.print("LY = ");
    Serial.println(Ly);*/

    //Calc position of left leg
    XYCalc(Lx,Ly);
    LeftLeg(Thigh);
    delay(SweepDelay);
    step++;
    //Serial.printf("Lx = %d\n", Lx);
    //Serial.printf("Ly = %d\n", Ly);
    
    //changing the hight of the left leg
    if (Lx >= UpperQuaterX){
      Ly = Ly - 3;
      //Serial.printf("Ly, UpperQuaterX = %d\n", Ly);
    }else if((MidX < Lx) && (Lx <= UpperQuaterX)){
      Ly= Ly -1;
      //Serial.printf("Ly, MidX, UpperQuaterX = %d\n", Ly);

    }else if((MidX >= Lx) && (Lx > LowerQuaterX)){
      Ly = Ly +1;
      //Serial.printf("Ly, MidX, LowerQuaterX = %d\n", Ly);
    }
    else if(Lx <= LowerQuaterX){
      Ly = Ly + 3;
      //Serial.printf("Ly, LowerQuaterX = %d\n", Ly);
    }

    if(Ly > yStand){Ly = yStand;}
    else if (Ly < yUp){Ly = yUp;}

  }
  delay(50);

  //////////////////////////////

  //Reset variables
  Ly = yStand;
  step = 0;
  

  //////////////////////////////

  Serial.printf("if 2\n");
  //Right leg lifts as left slides back
  for (int x = MaxX; x >= MinX; x = x-2){

    //Calc Right leg
    XYCalc(x,y);
    /*Serial.print("X = ");
    Serial.println(x);
    Serial.print("Y = ");
    Serial.println(y);*/
    RightLeg(Thigh);

    
    //change the height of the right leg for next iteration
    if (x >= UpperQuaterX){
      y = y - 3;
    }else if((MidX < x) && (x <= UpperQuaterX)){
      y = y - 1;
    }else if((MidX >= x) && (x > LowerQuaterX)){
      y = y +1;
    }else if(x <= LowerQuaterX){
      y = y + 3;
    }

    if(y > yStand){y = yStand;}
    else if (y < yUp){y = yUp;}

    Lx = MinX + (step*2);
    /*Serial.print("LX = ");
    Serial.println(Lx);
    Serial.print("LY = ");
    Serial.println(Ly);*/

    //Calc Left Leg
    XYCalc(Lx,Ly);
    LeftLeg(Thigh);
    delay(SweepDelay);
    step++;

  }
  delay(50);


}
