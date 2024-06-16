
//有源蜂鸣器,播放音乐

#define BUZZER 22

#define CHANNEL 0 //通道号
#define RESOLUTION 8 //分辨率
#define FREQ 20000 //频率

//定义按键数组
int button_array[]={25, 26, 27, 14, 12, 13};
//定义音符频率数组
int tone_array[]={262, 294, 330, 350, 393, 441, 495};
//初始化发音频率
int tone_value = pow(2,RESOLUTION);


void setup() {
  pinMode(BUZZER, OUTPUT);
  for(int i=0; i<6; i++){
    pinMode(button_array[i], INPUT_PULLUP); //按键引脚配置上拉电阻
  }

  //LEDC外设初始化
  ledcSetup(CHANNEL, FREQ, RESOLUTION);
  ledcAttachPin(BUZZER, CHANNEL); //通道绑定

}

void loop() {
  //检测按键是否按下
  for(int i=0; i<6; i++){
    if(!digitalRead(button_array[i])){
      tone_value = tone_array[i];
    }
  }
  //ledcWriteTone(通道号, 频率); 输出PWM控制蜂鸣器音调
  ledcWriteTone(CHANNEL, tone_value); //蜂鸣器发声
  tone_value = 20000; //不发声
  delay(10);
}
