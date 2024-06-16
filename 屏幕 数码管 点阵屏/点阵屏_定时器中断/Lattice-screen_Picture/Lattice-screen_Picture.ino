
//借助PCtoLCD2002实现点阵屏图案显示
#include <Arduino.h>


//定义图案逻辑数组
int hex_array[]={0x00,0x66,0xFF,0xFF,0xFF,0x7E,0x3C,0x18};

//定义行引脚
int row_array[]={13,25,2,27,23,4,22,18};
//定义列引脚
int col_array[]={26,21,19,12,5,14,33,32};


void setup() {
  Serial.begin(115200);

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
    for(int j=0; j<8; j++){
      //bitRead(读取值，读取的位置); 将值转换为二进制
      //Serial.print( bitRead(hex_array[i], j) );
      digitalWrite(col_array[j], bitRead(hex_array[i], j))
    }
    digitalWrite(row_array[i], LOW);  //行低电平，亮
    delay(1);
    digitalWrite(row_array[i], HIGH); //行状态清除
    //Serial.println(); //换行
    //delay(1000);
  }
  Serial.println();
}

