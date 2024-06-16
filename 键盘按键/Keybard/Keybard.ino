
//矩阵键盘扫描并显示在1602显示屏上
#include <Arduino.h>

//定义行引脚数组
int row_pins[4]={26, 25, 33, 32};
//列引脚
int col_pins[4]={27, 14, 12, 13};


char key; //按键函数返回值

//按键值获取函数
char read_keypad(){
  //定义键盘按键布局二维数组
  char keys[4][4]={ {'1', '2', '3', 'A'},
                    {'4', '5', '6', 'B'},
                    {'7', '8', '9', 'C'},
                    {'*', '0', '#', 'D'},
                  };
  //行列扫描
  for(int j=0; j<4; j++){ //列循环输出低电平
    digitalWrite(col_pins[j], LOW);
    for(int i=0; i<4; i++){ //行循环接收
      if( !digitalRead(row_pins[i]) ){ //检测到低电平，则返回该值
        digitalWrite(col_pins[j], HIGH); //还原成高电平
        return keys[i][j];
      }
    }
    digitalWrite(col_pins[j], HIGH); //还原成高电平
  }
  return NULL;
}


void setup() {
  Serial.begin(115200);
  for(int i=0; i<4; i++){
    pinMode(row_pins[i], INPUT_PULLUP); //行引脚设置为上拉输入(默认高电平)
    pinMode(col_pins[i], OUTPUT); //列引脚输出
    digitalWrite(col_pins[i], HIGH); //将列引脚初始化为高电平
  }
}

void loop() {
  //key=0;
  key = read_keypad();
  if(key){ Serial.printf("检测到按键：%c\n", key); }
  delay(150);
}
