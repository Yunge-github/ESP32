//串口显示屏输出 

#include "LiquidCrystal_I2C.h"
LiquidCrystal_I2C lcd(0x27, 16, 4);

//Serial.available(); //串口缓冲区数据量，常用于判断串口是否收到数据
//Serial.read();  //从串口缓冲区读取1个字节的数据，读一次缓冲区内容少一个

void setup() {
  lcd.init(); //初始化lcd对象
  lcd.backlight();  //开启背光
  Serial.begin(9600); //设置串口波特率
}

void loop() {
  //检测是否有串口输入
    if(Serial.available() > 0){
      delay(100); //等待所有数据传输完成
      lcd.clear();  //清屏
      //反复读取串口缓冲区的数据，显示在屏幕上
      while(Serial.available() > 0){
        lcd.write(Serial.read());
      }
      
    }
}
