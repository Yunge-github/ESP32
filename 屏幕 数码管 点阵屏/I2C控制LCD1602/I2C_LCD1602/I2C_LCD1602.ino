//驱动LCD1602

#include "LiquidCrystal_I2C.h"

//构造LCD对象，设置地址(默认0x27)，行数，列数
LiquidCrystal_I2C lcd(0x27, 16, 4);

void setup() {
  //初始化LCD对象
  lcd.init();

  //打印内容
  lcd.backlight();  //开启背光
  lcd.print("Hello world!");  //输出内容

}

void loop() {
  

}
