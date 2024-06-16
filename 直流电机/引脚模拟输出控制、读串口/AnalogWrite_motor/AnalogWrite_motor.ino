
//引脚模拟量直接输出PWM控制电机，串口读输入改变PWM

#include "BluetoothSerial.h" //蓝牙串口文件
#include <Wire.h> // Wire串口传输


#define IN1 4
#define IN2 16
#define IN3 17
#define IN4 18

int PWM=0;

/////////////// 蓝牙设参START //////////////////////////////////
const char *pin = "254163"; //将其更改为更安全的PIN
String device_name = "ESP32_Car";
BluetoothSerial SerialBT; //实例化蓝牙对象
/////////////// 蓝牙设参END //////////////////////////////////



//电机控制函数
void motor(int left_EN, int right_EN){
  //左轮，analogWrite默认分辨率为8，也就是0~255的模拟信号输出
  if( left_EN == 0 ){ analogWrite(IN1, 0); analogWrite(IN2, 0); } //停转
  else if( left_EN < -255 ) { left_EN = -255; analogWrite(IN1, 0); analogWrite(IN2, 0-left_EN); } //反转
  else if( left_EN > 0 ){ if( left_EN >255 ){ left_EN = 255;} analogWrite(IN1, left_EN); analogWrite(IN2, 0); } //正转
  //右轮
  if( right_EN == 0 ){ analogWrite(IN3, 0); analogWrite(IN4, 0); } //停转
  else if( right_EN < -255 ) { right_EN = -255; analogWrite(IN3, 0); analogWrite(IN4, 0-right_EN); } //反转
  else if( right_EN > 0 ){ if( right_EN >255 ){ right_EN = 255;} analogWrite(IN3, right_EN); analogWrite(IN4, 0); } //正转
}

//串口函数
void BLE_debug(){
  if( SerialBT.available() > 0 ){
    delay(5);
    char DATA = SerialBT.read(); //串口读数据
    switch (DATA){
      case '1': PWM++; SerialBT.printf("PWM:%d\n", PWM); break;
      case '0': PWM--; SerialBT.printf("PWM:%d\n", PWM); break;
    }
  }
}


void setup() {
/////////////// 蓝牙初始化START //////////////////////////////////
  SerialBT.begin( device_name ); //蓝牙设备名设定
  // Serial.printf( "设备 \"%s\" 已启动.\n 现已可进行蓝牙配对！\n", device_name.c_str() );
/////////////// 蓝牙初始化END //////////////////////////////////
  motor(0, 0); //启动时马达停止
  delay(10);
}

void loop() {
  BLE_debug(); //串口输入‘1’增加PWM值，‘0’减PWM值
  motor(PWM, PWM);
  
}
