//定义LED和按键引脚
int led_pin = 13;
int button_pin = 14;

bool led_logic = false; //定义LED逻辑值，按下亮，再按灭
bool status = false;  //定义记录LED状态是否更改的值


void setup() {
  //配置引脚模式
  pinMode(led_pin, OUTPUT);
  pinMode(button_pin, INPUT_PULLDOWN );
}

void loop() {
  //按键消抖
  if(digitalRead(button_pin)){ //检测按钮到按下
    delay(100);  //休眠10毫秒，后如果依然是高电平说明是按键按下并非抖动
    if(digitalRead(button_pin) && !status ){
      led_logic = !led_logic ;
      status = !status;
      digitalWrite(led_pin, led_logic);
    }else if(!digitalRead(button_pin)) {
      status = false;
    }
  }
}
