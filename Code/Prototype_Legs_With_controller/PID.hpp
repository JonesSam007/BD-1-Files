

class PID{
private:
  int ID; //0 Pitch, 1 Roll
  double Kp = 0;
  double Ki = 0;
  double Kd = 0;
  float LastError;

  double integral;
  double derivative;

  float ProportionalOutput;
  float IntegralOutput;
  float DerivativeOutput;

  
  float ErrorSum;

public:
  int TargetAngle;
  //float Angle;
  float Error;
  float OverallOutput;

public:

  PID(double _Kp, double _Ki, double _Kd){
    Kp = _Kp;
    Ki = _Ki;
    Kd = _Kd;
  }

  void PIDCalc(double dt, float Angle){

    Error = TargetAngle - Angle;

    //Proportional
    ProportionalOutput = Kp * Error;

    //Integral
    integral += Error * dt;
    IntegralOutput = Ki * integral;

    //Derivative
    derivative = (dt > 0) ? (Error - LastError) / dt : 0.0;
    DerivativeOutput = Kd * derivative;

    //Summing all parts together
    OverallOutput = ProportionalOutput + IntegralOutput + DerivativeOutput;

    //Updates the last error used to the one just used
    LastError = Error;

    Serial.printf("OverallOutput: %f.2\n", OverallOutput);
  }


};













