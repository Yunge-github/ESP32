//电位器ADC输入控制PWM信号

#define LED 13  //定义LED引脚
#define POT 26  //定义电位器引脚

int pot_value; //初始化电位器模拟信号
int led_value; //初始化LED模拟信号

void setup(){
  pinMode(LED, OUTPUT);
  pinMode(POT, INPUT);
  Serial.begin(9600); //串口函数，参数为波特率
  Serial.println("已执行setup");  //串口打印
}


void loop(){
  pot_value = analogRead(POT); //读取电位计模拟输入值
  //analogRead为4096位，analogWrite为256位
  led_value = pot_value/16; //把电位计模拟输入值转为LED模拟输出
  analogWrite(LED, led_value);
  Serial.println(pot_value);  //打印电位计模拟输入值
  delay(50);
}

