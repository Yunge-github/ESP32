
//通过PS2摇杆，调用库控制舵机

#include <ESP32Servo.h> //舵机库

#define PS2_X 15
#define PS2_Y 2
#define SW 4

#define SERVO 13
#define RESOLUTION 12 //LEDC默认分辨率为12，所以将舵机LEDC分辨率同步
#define FREQ 50

//定义Servo对象
Servo my_servo;

int value;


void setup() {
  pinMode(PS2_X, INPUT);
  pinMode(PS2_Y, INPUT);
  pinMode(SW, INPUT_PULLUP);

  Serial.begin(115200); //约定串口波特率

  //分配硬件定时器
  ESP32PWM::allocateTimer(0);
  //设置频率
  my_servo.setPeriodHertz(FREQ);
  //关联servo对象与GPIO引脚，设置脉宽范围
  my_servo.attach(SERVO, 500, 2500);  //500脉宽对应0度，2500对应180度

}

void loop() {
  //map(需映射参数，参数最小值，参数最大值，映射范围最小值，映射范围最大值);
  value = map(analogRead(PS2_Y), 0, 4095, 0, 180);  //数值范围映射函数
  //读取数值
  Serial.printf("x：%d，y：%d，z：%d，映射后的y：%d\n", 
                analogRead(PS2_X), analogRead(PS2_Y), digitalRead(SW),value);
  //输出PWM
  my_servo.write(value);
  delay(100);
  
}
