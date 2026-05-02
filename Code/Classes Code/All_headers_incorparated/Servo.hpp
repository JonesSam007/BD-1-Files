#include <Adafruit_PWMServoDriver.h>

class Servo {
private:
  int MinDeg = 0;   // 0 deg min for both MG90s and DM996
  int MaxDeg = 210;  // 210 deg Max for DM996, 180 deg Max for Mg90s
  int OffSetDeg = 15;  // 15 Offset deg for 996, 5 deg for Mg90s

  int SERVOMINPWM = 80;  // 80 Minimum pulse length count for 996, 100 min for MG90s
  int SERVOMAXPWM = 560;  // 560 Maximum pulse length count for 996, 540 Max for MG90s

  int ZeroPosistion = 0; //To be set 
  int OpperationToSetMotorAngle = 0;  // 0 means Zero + AngleIn
                                      // 1 means Zero - AngleIn
                                      // 2 means Zero - (180 - AngleIn)
                                      // 3 means Zero + (180 - AngleIn) 
  Adafruit_PWMServoDriver& servoDriver;
  int ID;


public:

  Servo(Adafruit_PWMServoDriver& _servoDriver, int _ID, int _MinDeg, 
        int _OffSetDeg, int _MaxDeg, int _SERVOMINPWM, int _SERVOMAXPWM, 
        int _ZeroPosistion, int _OpperationToSetMotorAngle)
    : servoDriver(_servoDriver) {
    ID = _ID;
    MinDeg = _MinDeg;
    MaxDeg = _MaxDeg;
    OffSetDeg = _OffSetDeg;
    SERVOMINPWM = _SERVOMINPWM;
    SERVOMAXPWM = _SERVOMAXPWM;
    ZeroPosistion = _ZeroPosistion;
    OpperationToSetMotorAngle = _OpperationToSetMotorAngle;
  }

  // Convert microseconds to PWM
  int DegToPWM(int CorrectedAngle) {
    return map(CorrectedAngle, MinDeg, MaxDeg, SERVOMINPWM, SERVOMAXPWM);
  }

  // Sets the servo target angle in radians
  void setServoAngle(float AngleOfMotor) {
    
    int CorrectedAngle = 0;
    //AngleOfMotor = map(AngleOfMotor, -PI, PI, -180, 180); 

    switch(OpperationToSetMotorAngle){
      case 0: //Zero + AngleIn
        CorrectedAngle = ZeroPosistion + AngleOfMotor;
        break;
      case 1: //Zero - AngleIn
        CorrectedAngle = ZeroPosistion - AngleOfMotor;
        break;
      case 2: //Zero - (180 - AngleIn)
        CorrectedAngle = ZeroPosistion - (180 - AngleOfMotor);
        break;
      case 3: //Zero + (180 - AngleIn)
        CorrectedAngle = ZeroPosistion + (180 - AngleOfMotor);
        break;
      default:
      break;
    }
    // keep radians in range
    if (CorrectedAngle < (MinDeg + OffSetDeg)) {
      CorrectedAngle = (MinDeg + OffSetDeg);
      //Serial.print("### ANGLE OUT OF RANGE (Lower) ###\n");
    }else if (CorrectedAngle > (MaxDeg - OffSetDeg)) {
      CorrectedAngle = (MaxDeg - OffSetDeg);
      //Serial.print("### ANGLE OUT OF RANGE (Higher) ###\n");
    }

    int pwmValue = DegToPWM((int)CorrectedAngle);

    // Drive the servo
    servoDriver.setPWM(ID, 0, pwmValue);

  }
};