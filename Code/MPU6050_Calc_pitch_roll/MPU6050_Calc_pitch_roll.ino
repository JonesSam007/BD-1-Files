/////////////////////////////////////////////////////////////////////////////////////
//MPU6050 angles
/////////////////////////////////////////////////////////////////////////////////////

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  if (!mpu.begin()) {
    while (1) delay(10);
  }
  // Setup range
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
}

void loop() {
  //Read Values from Accel and Gyro and temp
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  //Calc Pitch and roll 
  float pitch = atan2(a.acceleration.z, a.acceleration.x) * 180 / PI; //offset -5.5
  float roll = atan2(-a.acceleration.y, sqrt(a.acceleration.z * a.acceleration.z + a.acceleration.x * a.acceleration.x)) * 180 / PI;

  //Serial print out
  Serial.println();
  Serial.println();
  Serial.print("Pitch: "); Serial.print(pitch);
  Serial.print(" | Roll: "); Serial.println(roll);
  Serial.println();
  Serial.println();

  delay(100);
}