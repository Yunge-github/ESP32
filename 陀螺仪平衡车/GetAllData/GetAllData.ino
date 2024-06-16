
#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

long timer = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
}

void loop() {
  mpu6050.update();

  // if(millis() - timer > 100){ //millis()为连续运转时长，timer存储上一时刻时间，单位mS
    
    // Serial.println("=======================================================");
    // Serial.print("temp : ");Serial.println(mpu6050.getTemp());
    // //加速度
    // Serial.print("accX : ");Serial.print(mpu6050.getAccX());
    // Serial.print("\t accY : ");Serial.print(mpu6050.getAccY());
    // Serial.print("\t accZ : ");Serial.println(mpu6050.getAccZ());
  
    //角速度
    // /*Serial.print("gyroX : ");*/Serial.print(mpu6050.getGyroX());
    // Serial.print(","); //串口绘图仪切换下一数据值使用
    // /*Serial.print("\t gyroY : ");*/Serial.print(mpu6050.getGyroY());
    // Serial.print(","); //串口绘图仪切换下一数据值使用
    // /*Serial.print("\t gyroZ : ");*/Serial.println(mpu6050.getGyroZ());
  
    // //加速度角
    // Serial.print("accAngleX : ");Serial.print(mpu6050.getAccAngleX());
    // Serial.print("\t accAngleY : ");Serial.println(mpu6050.getAccAngleY());
  
    // //陀螺仪角
    // // Serial.print("gyroAngleX : ");
    // Serial.print( int(mpu6050.getGyroAngleX()) );
    // Serial.print(","); //串口绘图仪切换下一数据值使用
    // // Serial.print("\t gyroAngleY : ");
    // Serial.print( int(mpu6050.getGyroAngleY()) );
    // Serial.print(","); //串口绘图仪切换下一数据值使用
    // // Serial.print("\t gyroAngleZ : ");
    // Serial.print( mpu6050.getGyroAngleZ() );

    //角度值
    // Serial.print("angleX : ");
    Serial.print(mpu6050.getAngleX());
    // Serial.print(","); //串口绘图仪切换下一数据值使用
    // // Serial.print("\t angleY : ");
    // Serial.print(mpu6050.getAngleY());
    // Serial.print(","); //串口绘图仪切换下一数据值使用
    // // Serial.print("\t angleZ : ");
    // Serial.print( mpu6050.getAngleZ() );
    // Serial.println("=======================================================\n");
    
    Serial.print("\n"); //串口绘图仪切换下一列数据点使用
  //   timer = millis();
  // }

}
