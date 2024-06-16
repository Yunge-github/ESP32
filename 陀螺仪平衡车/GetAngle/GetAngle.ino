
#include <MPU6050_tockn.h>
#include <Wire.h>

#define sda_pin 21
#define scl_pin 22
float erro_angleZ=0.0f; //存储温漂误差值补偿

MPU6050 mpu6050(Wire);

void setup() {
  Serial.begin(9600);
  // Wire.begin(/*sda_pin, scl_pin*/); //无传参则保持默认IIC引脚21.22，也可自定义IIC引脚
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
}

void loop() {
  mpu6050.update();
  // Serial.print("angleX : ");
  // Serial.print( mpu6050.getAngleX() ); //输出X轴旋转角度
  // Serial.print(","); //串口绘图仪切换下一数据值使用
  // Serial.print("\t angleY : ");
  // Serial.print( mpu6050.getAngleY() );
  // Serial.print(",");
  // Serial.print("\t angleZ : ");
  erro_angleZ = 0.00039*micros()/1000000-0.61;
  Serial.print( mpu6050.getAngleZ()-erro_angleZ );
  Serial.print(",");
  Serial.print( micros()/10000 );
  Serial.print("\n"); //串口绘图仪切换下一列数据点使用
  delay(100);
}
