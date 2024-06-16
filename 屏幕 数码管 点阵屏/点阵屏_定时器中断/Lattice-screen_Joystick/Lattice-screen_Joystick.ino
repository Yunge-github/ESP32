
//摇杆操控点阵屏图案
#include <Arduino.h>


#define PS2_X 15
#define PS2_Y 35

//初始化LED开始位置
int led_pos[2]={1,2};
//初始化摇杆信号变量
int x_value;
int y_value;

//定义行引脚
int row_array[]={13,25,2,27,23,4,22,18};
//定义列引脚
int col_array[]={26,21,19,12,5,14,33,32};



void setup() {
  //初始化PS2引脚
  pinMode(PS2_X, OUTPUT);
  pinMode(PS2_Y, OUTPUT);

  //配置行引脚，初始化为高电平
  for(int i=0; i<8; i++){
    pinMode(row_array[i], OUTPUT);
    digitalWrite(row_array[i], HIGH);
  }
  //配置列引脚，初始化为低电平
  for(int i=0; i<8; i++){
    pinMode(col_array[i], OUTPUT);
    digitalWrite(col_array[i], LOW);
  }

}

void loop() {
  //读取摇杆信号
  x_value = analogRead(PS2_X);
  y_value = analogRead(PS2_Y);

  //清除之前位置的LED
  digitalWrite( row_array[ led_pos[0] ], HIGH);
  digitalWrite( col_array[ led_pos[1] ], LOW);


  //检测X轴是否移动
  if(x_value>4095/2+300 && led_pos[0]<7){
    led_pos[0] += 1;
  }else if(x_value<4095/2-300 && led_pos[0]>0){
    led_pos[0] -= 1;
  }

  //检测Y轴是否移动
  if(y_value>4095/2+300 && led_pos[1]>0){
    led_pos[1] -= 1;
  }else if(y_value<4095/2-300 && led_pos[1]<7){
    led_pos[1] += 1;
  }

  //显示LED位置
  digitalWrite( row_array[ led_pos[0] ], LOW);
  digitalWrite( col_array[ led_pos[1] ], HIGH);
  delay(50);

}
