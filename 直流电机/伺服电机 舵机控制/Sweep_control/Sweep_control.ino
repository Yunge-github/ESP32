/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.
 =此示例代码位于公共域中。

 modified 8 Nov 2013
 =2013年11月8日修订
 by Scott Fitzgerald
 =由Scott Fitzgerald修改
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep

*/


#include <Servo.h>

Servo myservo1;  // 创建伺服对象以控制伺服 create servo object to control a servo
Servo myservo2;
// 在大多数板上可以创建12个伺服对象 twelve servo objects can be created on most boards

int pos = 0;    // 存储伺服位置的变量 variable to store the servo position
int posf = 180;

void setup() {
  myservo1.attach(4);  // 将引脚9上的伺服连接到伺服对象 attaches the servo on pin 9 to the servo object
  myservo2.attach(8);
  /*
  Serial.begin(9600); //约定串口传输波特率为9600，需要使用串口输出内容时
  serial.println(servo.read()); //将获取到的舵机角度信息串口输出
  */
}

void loop() {
  for (pos = 0; pos <= 180; pos += 5) { // 从0度到180度 goes from 0 degrees to 180 degrees
    // 以1度为步长 in steps of 1 degree
    myservo1.write(pos);
    posf -= 5;
    myservo2.write(posf);              // 告诉伺服机构转到变量“pos”中的位置 tell servo to go to position in variable 'pos'
    delay(8);                       // 等待15毫秒，等待伺服到达位置 waits 15 ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 5) { // 从180度到0度 goes from 180 degrees to 0 degrees
    myservo1.write(pos);              // 告诉伺服机构转到变量“pos”中的位置 tell servo to go to position in variable 'pos'
    posf += 5;
    myservo2.write(posf);
    delay(8);                       // 等待15毫秒，等待伺服到达位置 waits 15 ms for the servo to reach the position
  }
  //x=servo.read();  //获取舵机角度给x
  /*
  pinMode(A0,INPUT);  /定义A0引脚为输入引脚【需放于setup函数中】
  y=map(analogRead(A0),0,1023,0,180);  //将电位器引脚A0中获取到的从0到1023的值映射到0-180后赋给y
  */
}
