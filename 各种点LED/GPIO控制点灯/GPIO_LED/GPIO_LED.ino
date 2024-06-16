// int led1_pin = 12; //定义LED引脚

//定义GPIO引脚数组
int pin_list[4] = {13,12,14,27};
int num = sizeof(pin_list)/sizeof(pin_list[0]); //获取数组长度,总字节长度/单个自己长度=数组个数

void setup() {
  // put your setup code here, to run once:
  /* pinMode(led1_pin, OUTPUT); //设定led_pin引脚为输出引脚
  pinMode(led2_pin, OUTPUT);
  pinMode(led3_pin, OUTPUT);
  pinMode(led4_pin, OUTPUT);*/
  for(int i=0; i<4; i++){ pinMode(pin_list[i], OUTPUT); } //设置使用的GPIO引脚为输出模式
}

void loop() {
  // put your main code here, to run repeatedly:
  /* digitalWrite(led1_pin, HIGH); //点亮LED
  delay(500);
  digitalWrite(led1_pin, LOW); //灭灯
  delay(500); */
 
  for(int i=0; i<num; i++){
    digitalWrite(pin_list[i], HIGH);
    delay(100);
    }
    delay(100);
    for(int i=num-1; i>=0; i--){
    digitalWrite(pin_list[i], LOW);
    delay(100);
    }
    delay(100);
}
