
#define LED 13  //定义LED引脚
#define POT 26  //定义电位计引脚
#define CHANNEL 0 //LEDC通道
#define RESOLUTION  12  //分辨率
#define FREQ 1000 //频率
//初始化模拟输入值
int pot_value; 


void setup() {
  analogReadResolution(RESOLUTION); //设置ADC分辨率，不写默认为12
  analogSetAttenuation(ADC_11db);  //配置输入衰减,不写默认为11db
  //建立LEDC通道，配置LEDC分辨率
  ledcSetup(CHANNEL, FREQ, RESOLUTION);  //（LEDC通道，频率，分辨率）
  //关联GPIO与LEDC通道
  ledcAttachPin(LED, CHANNEL);

  Serial.begin(9600); //串口函数，参数为波特率
  Serial.println("已执行setup");  //串口打印
}

void loop() {
  pot_value = analogRead(POT);  //获取模拟信号输入值
  ledcWrite(CHANNEL, pot_value);  //输出PWM
  Serial.println(pot_value);  //打印输出电位计值
  delay(50);
}
