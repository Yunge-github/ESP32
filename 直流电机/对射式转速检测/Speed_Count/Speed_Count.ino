
#include <RBD_Timer.h> //按键消抖相关库
#include <RBD_Button.h> //按键消抖相关库
// #include <U8g2lib.h>  //U8G2_SSD1306_128X64


// #define SCL 22  //定义时钟引脚
// #define SDA 21  //定义数据引脚
// //I2C构造对象 对象名(旋转角度,时钟引脚，数据引脚，U8X8_PIN_NONE)
// U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, SCL, SDA, U8X8_PIN_NONE);

#define SPEED_COUNT 26  
bool Run_Bool=1;
unsigned int count=0;
unsigned int count_g=0;

hw_timer_t * timer1 = NULL; //定义定时器指针
volatile SemaphoreHandle_t timerSemaphore; //二值信号量定义
//创建一个可以消除拉动的按键对象
RBD::Button button(SPEED_COUNT, INPUT); //此语句已将按键设置为输入上拉，无需再初始化


void IRAM_ATTR onTimer1(){
  xSemaphoreGiveFromISR(timerSemaphore, NULL);  //将信号量设为有信号状态
}


void setup() {
  Serial.begin(9600);
  pinMode(SPEED_COUNT, INPUT);
  timerSemaphore = xSemaphoreCreateBinary(); //创建二值信号量
  timer1 = timerBegin(0, 80, true); //定时器初始化
  timerAttachInterrupt(timer1, onTimer1, true); //函数绑定
  timerAlarmWrite(timer1, 1000000, true); //设定报警阈值，定时器分频为1us，计数器到达1000000时为1s触发中断
  timerAlarmEnable(timer1); //开启定时器

  // u8g2.begin(); //初始化OLED对象
  // u8g2.enableUTF8Print(); //开启中文字符集支持
  // u8g2.setFont(u8g2_font_wqy15_t_gb2312); //设置字体

  //button.setDebounceTimeout(10); //消抖时长
}


void loop() {
  if( button.onPressed() ){
    count++;
    // count_g++;
  }
  if(xSemaphoreTake(timerSemaphore, 0) == pdTRUE){
    // u8g2.clearBuffer(); //清空缓存区
    // u8g2.firstPage(); //进入第一页（清空缓存区）
    // u8g2.setCursor(0,15); //设置光标位置(x,y); 0~20行为黄色，字模高10行
    // u8g2.print("半秒圈速: ");
    // u8g2.setCursor(75,15);
    // u8g2.print(count/4 );
    // u8g2.setCursor(0,40); //设置光标位置(x,y); 0~20行为黄色，字模高10行
    // u8g2.print("半秒转速: ");
    // u8g2.setCursor(75,40);
    // u8g2.print(count);
    // u8g2.setCursor(0,60);
    // u8g2.print(count_g);
    // u8g2.sendBuffer();  //发送缓存区内容到OLED显示

    Serial.printf("秒速：%d\n", count);
    count=0;
  }
}
