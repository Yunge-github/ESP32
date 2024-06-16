//DHT11温湿度计 

#include <DHT11.h>

DHT11 dht11(15); //创建DHT11类的一个实例

void setup() {
  Serial.begin(9600);
  dht11.setDelay(500); //设置温湿度传感器读数之间的自定义延迟(毫秒),默认值500ms。
}

void loop() {
  int temperature=0, humidity=0;

// //******** 温湿度一起获取 ***********
//   //读取DHT11传感器的温度和湿度值,返回0表无误，返回1表报错
//   int result = dht11.readTemperatureHumidity(temperature, humidity);
//   if (result == 0) {
//     Serial.print("温度: ");
//     Serial.print(temperature);
//     Serial.print(" °C\湿度: ");
//     Serial.print(humidity);
//     Serial.println(" %");
//   } else { Serial.println(DHT11::getErrorString(result)); } //根据错误代码打印错误信息
  

//******** 单独获取温湿度 ***********
  int temperature1 = dht11.readTemperature(); //读取温度值
  int humidity1 = dht11.readHumidity(); //读取湿度值
  //当humidity值不为“校验错误”和“超时错误”
  if (temperature != DHT11::ERROR_CHECKSUM && temperature != DHT11::ERROR_TIMEOUT) {
    Serial.print("温度: ");
    Serial.print(temperature1);
    Serial.println(" °C");
  } else { Serial.println(DHT11::getErrorString(humidity)); } //根据错误代码打印错误消息。

  if (humidity != DHT11::ERROR_CHECKSUM && humidity != DHT11::ERROR_TIMEOUT) {
    Serial.print("湿度: ");
    Serial.print(humidity1);
    Serial.println(" %\n");
  } else { Serial.println(DHT11::getErrorString(humidity)); }
}
