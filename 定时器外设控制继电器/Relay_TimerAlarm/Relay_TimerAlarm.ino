
//定时器中断实现继电器开关灯
#define RELAY_PIN 15

//初始化定时器
hw_timer_t * timer = NULL;

void timer_interrupt(){
  digitalWrite(RELAY_PIN, !digitalRead(RELAY_PIN) );
}

void setup() {
  pinMode(RELAY_PIN, OUTPUT);

  //初始化定时器
  timer = timerBegin(0,80,true); //timerBegin(定时器编号0-3, 分频系数, true向上计数/false向下计数false);
  //注册中断处理函数
  timerAttachInterrupt(timer, timer_interrupt, true); //绑定定时器与中断函数，true边沿触发/false电平触发
  //设置定时器模式
  timerAlarmWrite(timer, 500000, true);
  //启动定时器
  timerAlarmEnable(timer);
}

void loop() {
  

}
