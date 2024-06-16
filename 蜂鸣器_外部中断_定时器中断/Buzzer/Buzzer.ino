

//有源蜂鸣器通过外部中断，定时器中断控制响铃

#define BUTTON 13
#define BUZZER 22

hw_timer_t * timer = NULL;

int second = 3; //定义闹钟触发时长


//定时器中断函数
void timer_interrupt(){
  digitalWrite(BUZZER, LOW);
}


//外部中断函数
void handle_interrupt(){
  digitalWrite(BUZZER, HIGH);
}


void setup() {
  pinMode(BUTTON, INPUT_PULLUP); //引脚配置上拉电阻
  pinMode(BUZZER, OUTPUT);

  //初始化定时器
  timer = timerBegin(0, 80, true);
  //配置定时器
  timerAttachInterrupt(timer, timer_interrupt, true);
  //定时模式
  timerAlarmWrite(timer, second*1000*1000, false);
  //启动定时器
  timerAlarmEnable(timer);

  //配置外部中断
  //attachInterrupt(digitalPinToInterrupt(触发引脚), 中断函数名, FALLING下降沿触发);
  attachInterrupt(digitalPinToInterrupt(BUTTON), handle_interrupt, FALLING);

}

void loop() {
  // put your main code here, to run repeatedly:

}
