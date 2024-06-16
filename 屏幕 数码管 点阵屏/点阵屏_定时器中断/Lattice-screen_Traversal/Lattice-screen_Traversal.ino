
//直连点阵屏行列引脚，遍历点阵屏

#include <Arduino.h>

//定义行引脚
int row_array[]={13,25,2,27,23,4,22,18};
//定义列引脚
int col_array[]={26,21,19,12,5,14,33,32};


void setup() {
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
  //遍历LED
  for(int i=0; i<8; i++){
    digitalWrite(row_array[i], LOW);
    for(int j=0; j<8; j++){
      digitalWrite(col_array[j], HIGH);
      delay(100);
      digitalWrite(col_array[j], LOW);
    }
    digitalWrite(row_array[i], HIGH);
  }
}
