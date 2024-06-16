
#define CHANNEL 0 //通道号
#define FREQ 2000 //频率
#define RESOLUTION 8 //分辨率

#define LED 12 //LED引脚


void setup() {
  //1、设置通道
  ledcSetup(CHANNEL, FREQ, RESOLUTION);
  //2、通道号绑定引脚
  ledcAttachPin(LED, CHANNEL);
}

void loop() {
  //渐亮,pow(底数，指数)
  for(int i=0; i<pow(2,RESOLUTION); i++){
    //3、输出PWM
    ledcWrite(CHANNEL, i);
    delay(10);
  }
  //渐灭
  for(int i=pow(2,RESOLUTION); i>=0; i--){
    //输出PWM
    ledcWrite(CHANNEL, i);
    delay(10);
  }
}
