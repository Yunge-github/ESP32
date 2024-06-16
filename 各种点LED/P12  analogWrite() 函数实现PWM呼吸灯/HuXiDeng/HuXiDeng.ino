#define led_pin 2 //宏定义LED引脚

void setup() {
  // put your setup code here, to run once:
  pinMode(led_pin, OUTPUT);
}

void loop() {
  //渐亮
  for(int i=0; i<256; i++){
    analogWrite(led_pin, i);
    delay(6);
  }
  //渐灭
  for(int i=255; i>=0; i--){
    analogWrite(led_pin, i);
    delay(6);
  }
}
