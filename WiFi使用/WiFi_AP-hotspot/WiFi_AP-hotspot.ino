
//创建Wifi热点

#include <WiFi.h>

//Wifi名称及密码
const char * ssid = "Yg_AP";
const char * password = "q2541639095";


void setup() {
  Serial.begin(115200);
  //创建AP热点
  WiFi.softAP(ssid, password);
  //打印热点IP
  Serial.print("WiFi接入的IP:");
  Serial.println( WiFi.softAPIP() );
}


void loop() {


}
