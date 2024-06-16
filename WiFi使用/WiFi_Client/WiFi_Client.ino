
//使开发板连接Wifi

#include <WiFi.h>

const char * ssid="Yg";
const char * password="q2541639095";

#define LED 2

void setup() {
  Serial.begin(115200); //约定串口波特率
  
  //连接Wifi
  WiFi.begin(ssid, password);
  //检测Wifi连接
  Serial.print("正在连接Wifi");
  while( WiFi.status() != WL_CONNECTED ){
    delay(500);
    Serial.print('.');
  }
  Serial.println("连接成功！");
  Serial.print("IP地址");
  Serial.print( WiFi.localIP() );
  //提供板载LED反馈Wifi连接状态
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  delay(200);
  digitalWrite(LED, LOW);
  delay(200);
  digitalWrite(LED, HIGH);
  delay(1500);
  digitalWrite(LED, LOW);
}

void loop() {
  Serial.print("LOOP！\n");
  delay(1000);
}
