// Basic demo for accelerometer readings from Adafruit MPU6050

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;
#include <MPU6050.hpp>

MPU6050Class MPU6050(mpu);

void setup() {
  Serial.begin(115200);
  MPU6050.startup();
}

void loop() {

  MPU6050.ReadValues();
  MPU6050.CalcPitRoll();
  
}
