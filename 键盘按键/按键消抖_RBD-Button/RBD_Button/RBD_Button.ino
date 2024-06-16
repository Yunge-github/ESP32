
//软件消除按键抖动，RBD_Button库方法
#include <RBD_Timer.h>
#include <RBD_Button.h>

int switchPin = 25; //按键引脚
int ledPin = 2; //LED引脚
int ledStatus = 0; //LED当前状态

//创建一个可以消除拉动的按键对象
RBD::Button button(switchPin, INPUT_PULLUP); //此语句已将按键设置为输入上拉，无需再初始化


void setup() {
  pinMode(ledPin, OUTPUT);
  button.setDebounceTimeout(20); //消抖时长设为20ms
}

void loop() {
  //检测按键按下触发(下降沿)
  if( button.onPressed() ){ //button.onPressed()返回，True已按下/False未按下
    ledStatus = !ledStatus;
    digitalWrite(ledPin, ledStatus);
  }
}
