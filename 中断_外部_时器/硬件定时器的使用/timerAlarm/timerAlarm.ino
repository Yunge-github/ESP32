//此函数功能为运用硬件定时器每1秒钟打印一次当前迭代数及时间
#include <Arduino.h>

//用在中断函数内时使用volatile表明参数易失
volatile int count = 0; //迭代计数
volatile unsigned long tim = 0; //当前时间
volatile SemaphoreHandle_t timerSemaphore; //二值信号量定义

hw_timer_t * timer1 = NULL; //定义定时器指针
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

//ISR中断函数
void IRAM_ATTR onTimer1(){
  portENTER_CRITICAL_ISR(&timerMux); //进入临界区
  count++;
  tim = micros();
  portEXIT_CRITICAL_ISR(&timerMux); //退出临界区

  xSemaphoreGiveFromISR(timerSemaphore, NULL);  //将信号量设为有信号状态
}


void setup() {
  Serial.begin(115200);
  timerSemaphore = xSemaphoreCreateBinary(); //创建二值信号量(常用于检测中断是否触发)

  //ESP32共有4个硬件定时器，80分频对应时钟周期1us，40000分频对应时钟周期500us，true表示向上计数(累加)
  //timerBegin(定时器编号，分频数，计数方式)；若返回值timer为NULL则表明初始化失败
  timer1 = timerBegin(0, 80, true); //定时器初始化
  //将ISR中断函数绑定到定时器，true边沿触发，false电平触发
  //timerAttachInterrupt(定时器, 中断函数名, true/false);
  timerAttachInterrupt(timer1, onTimer1, true); //函数绑定
  //timerAlarmWrite(定时器指针, 计数器报警阈值, 是否重加载定时器); true为重复触发，false为仅触发一次
  timerAlarmWrite(timer1, 1000000, true); //设定报警阈值，定时器分频为1us，计数器到达1000000时为1s触发中断
  timerAlarmEnable(timer1); //开启定时器
}

void loop() {
  //xSemaphoreGive(timerSemaphore); //将信号量设为有信号状态
  
  //xSemaphoreTake(信号量句柄, 等待的节拍数); //一般传0立即返回不等待，ESP32默认1拍是1ms，传portMAX_DELAY则一直等待信号到来
  //在普通任务loop中获取信号量，获取过后信号量将清零。【返回值：pdTRUE获取成功，pdFALSE获取失败】
  if(xSemaphoreTake(timerSemaphore, 0) == pdTRUE){  //检测二值信号是否已触发
    portENTER_CRITICAL(&timerMux); //进入临界区，原址性访问，范围内将阻止一切中断
    auto c = count; //auto类型变量在函数被调用时创建，函数返回时自动销毁
    auto t = tim;
    portEXIT_CRITICAL(&timerMux); //退出临界区

    Serial.println(c);
    Serial.println(t);
  }
}
