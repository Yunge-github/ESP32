

#define IN_1  13
#define IN_2  12
#define IN_3  14
#define IN_4  27

//单四拍模式，四拍11.25度，减速比1/64，输出轴0.703125度，2048步也就是512拍输出轴转动360度
int degree = 180;
int count = 2048/4 * degree/360;


void setup() {
  //设置引脚输出模式
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);

  //单四拍模式
  for(int i=0; i<count; i++){ //单四拍，易丢步，扭矩小
    //A向
    digitalWrite(IN_1, 1);
    digitalWrite(IN_2, 0);
    digitalWrite(IN_3, 0);
    digitalWrite(IN_4, 0);
    delay(2);
    //B向
    digitalWrite(IN_1, 0);
    digitalWrite(IN_2, 1);
    digitalWrite(IN_3, 0);
    digitalWrite(IN_4, 0);
    delay(2);
    //C向
    digitalWrite(IN_1, 0);
    digitalWrite(IN_2, 0);
    digitalWrite(IN_3, 1);
    digitalWrite(IN_4, 0);
    delay(2);
    //D向
    digitalWrite(IN_1, 0);
    digitalWrite(IN_2, 0);
    digitalWrite(IN_3, 0);
    digitalWrite(IN_4, 1);
    delay(2);
  }
  //停转复位
  digitalWrite(IN_1, 0);
  digitalWrite(IN_2, 0);
  digitalWrite(IN_3, 0);
  digitalWrite(IN_4, 0);

  delay(1000);
  //双四拍模式，逆时针旋转
  for(int i=0; i<count; i++){ //扭矩较大
    //BA向
    digitalWrite(IN_1, 1);
    digitalWrite(IN_2, 1);
    digitalWrite(IN_3, 0);
    digitalWrite(IN_4, 0);
    delay(2);
    //AD向
    digitalWrite(IN_1, 1);
    digitalWrite(IN_2, 0);
    digitalWrite(IN_3, 0);
    digitalWrite(IN_4, 1);
    delay(2);
    //CD向
    digitalWrite(IN_1, 0);
    digitalWrite(IN_2, 0);
    digitalWrite(IN_3, 1);
    digitalWrite(IN_4, 1);
    delay(2);
    //BC向
    digitalWrite(IN_1, 0);
    digitalWrite(IN_2, 1);
    digitalWrite(IN_3, 1);
    digitalWrite(IN_4, 0);
    delay(2);    
  }
  //停转复位
  digitalWrite(IN_1, 0);
  digitalWrite(IN_2, 0);
  digitalWrite(IN_3, 0);
  digitalWrite(IN_4, 0);

  delay(1000);
  //八拍模式，八拍5.625度，减速比1/64，4096步输出轴转360度
  for(int i=0; i<count; i++){ //八拍循环，最常用，扭矩最大
    //A向，1
    digitalWrite(IN_1, 1);
    digitalWrite(IN_2, 0);
    digitalWrite(IN_3, 0);
    digitalWrite(IN_4, 0);
    delay(2);
    //AB向，2
    digitalWrite(IN_1, 1);
    digitalWrite(IN_2, 1);
    digitalWrite(IN_3, 0);
    digitalWrite(IN_4, 0);
    delay(2);
    //B向，3
    digitalWrite(IN_1, 0);
    digitalWrite(IN_2, 1);
    digitalWrite(IN_3, 0);
    digitalWrite(IN_4, 0);
    delay(2);
    //BC向，4
    digitalWrite(IN_1, 0);
    digitalWrite(IN_2, 1);
    digitalWrite(IN_3, 1);
    digitalWrite(IN_4, 0);
    delay(2);
    //C向，5
    digitalWrite(IN_1, 0);
    digitalWrite(IN_2, 0);
    digitalWrite(IN_3, 1);
    digitalWrite(IN_4, 0);
    delay(2);
    //CD向，6
    digitalWrite(IN_1, 0);
    digitalWrite(IN_2, 0);
    digitalWrite(IN_3, 1);
    digitalWrite(IN_4, 1);
    delay(2);
    //D向，7
    digitalWrite(IN_1, 0);
    digitalWrite(IN_2, 0);
    digitalWrite(IN_3, 0);
    digitalWrite(IN_4, 1);
    delay(2);
    //DA向，8
    digitalWrite(IN_1, 1);
    digitalWrite(IN_2, 0);
    digitalWrite(IN_3, 0);
    digitalWrite(IN_4, 1);
    delay(2);
  }
  //停转复位
  digitalWrite(IN_1, 0);
  digitalWrite(IN_2, 0);
  digitalWrite(IN_3, 0);
  digitalWrite(IN_4, 0);

}

void loop() {


}
