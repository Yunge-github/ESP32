//attachInterrupt( digitalPinToInterrupt(pin引脚号), ISR中断服务程序, mode中断触发方式);
/*
  mode:
    //【LOW-低电平触发】
    //【HIGH-高电平触发】
    //【RISING-上升沿触发】（按下立刻触发）
    //【FALLING-下降沿触发】（松开后触发）
    //【CHANGE-电平变化触发】
*/

#define BUTTON 14 //中断按键
#define LED 2

//定义一个可在外部中断函数内部使用的变量
volatile bool flag = false;


void handle_interrup(){
  flag = true;  //通过变量控制loop函数if语句执行

}

void setup() {
  Serial.begin(9600); //串口初始化
  pinMode(BUTTON, INPUT_PULLDOWN);  //配置输入引脚
  pinMode(LED, OUTPUT);

  //配置中断引脚
  attachInterrupt(digitalPinToInterrupt(BUTTON), //当转向到位则正常前进//当转向到位则正常前进, FALLING);
}

void loop() {
  if(flag){
    Serial.println("中断已触发");

    digitalWrite(LED,HIGH);
    delay(2000);  //delay函数执行期间无法触发中断，使用中断时应避免
    digitalWrite(LED, LOW);

    flag = false;  //重置中断标志位
  }

}