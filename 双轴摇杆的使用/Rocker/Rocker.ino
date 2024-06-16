
//通过PS2摇杆模块在串口监视器中打印读取到的数值，并将数值映射以控制舵机


#define PS2_X 15
#define PS2_Y 2
#define SW 4

#define SERVO 13
#define RESOLUTION 12 //LEDC默认分辨率为12，所以将舵机LEDC分辨率同步
#define CHANNEL 0
#define FREQ 50

int min_width = 0.6/20*pow(2,RESOLUTION); //最小脉宽
int max_width = 2.5/20*pow(2,RESOLUTION); //最大脉宽
int value;


void setup() {
  pinMode(PS2_X, INPUT);
  pinMode(PS2_Y, INPUT);
  pinMode(SW, INPUT_PULLUP);

  Serial.begin(115200); //约定串口波特率

  //设置LEDC通道的频率和分辨率
  ledcSetup(CHANNEL, FREQ, RESOLUTION);
  //关联通道号与GPIO引脚
  ledcAttachPin(SERVO, CHANNEL);


}

void loop() {
  //map(需映射参数，参数最小值，参数最大值，映射范围最小值，映射范围最大值);
  value = map(analogRead(PS2_Y), 0, 4095, min_width, max_width);  //数值范围映射函数

  //读取数值
  Serial.printf("x：%d，y：%d，z：%d，映射后的y：%d\n", 
                analogRead(PS2_X), analogRead(PS2_Y), digitalRead(SW),value);
  ledcWrite(CHANNEL, value);
  delay(100);

}
