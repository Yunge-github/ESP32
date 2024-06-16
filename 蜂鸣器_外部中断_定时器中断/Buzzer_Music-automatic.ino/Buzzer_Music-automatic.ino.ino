
//有源蜂鸣器,播放音乐

#define BUZZER 22
#define BUTTON 13

#define CHANNEL 0 //通道号
#define RESOLUTION 8 //分辨率
#define FREQ 20000 //频率


//定义音符频率数组
int tone_array[]={20000, 262, 294, 330, 350, 393, 441, 495};
//乐谱
int music[]= {1, 1, 5, 5, 6, 6, 5, 0, 4, 4, 3, 3,
               2, 2, 1, 0, 5, 5, 4, 4, 3, 3, 2, 0, 
               5, 5, 4, 4, 3, 3, 2, 0, 1, 1, 5, 5, 
               6, 6, 5, 0, 4, 4, 3, 3, 2, 2, 1, 0};

 
void setup() {
  pinMode(BUZZER, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  //LEDC外设初始化
  ledcSetup(CHANNEL, FREQ, RESOLUTION);
  ledcAttachPin(BUZZER, CHANNEL); //通道绑定
}


void loop() {
  if(!digitalRead(BUTTON)){
    for(int i=0; i<sizeof(music)/sizeof(music[0]); i++){
      ledcWriteTone(CHANNEL, tone_array[ music[i] ] );
      delay(500);
    }
    delay(1000);
  }
  ledcWriteTone(CHANNEL, 20000);
}
