#include <HCSR04.h>

//本例使用DS18B20 1线温度传感器 
//当然，你可以使用其他东西，比如DHT22、LM35或你周围的任何东西。
#include <OneWire.h>
#include <DallasTemperature.h> //超声波测距库
#include <DHT11.h>

UltraSonicDistanceSensor distanceSensor0(26, 25); //(trig,echo)初始化使用数字引脚13和12的超声波传感器
UltraSonicDistanceSensor distanceSensor1(14, 27);
DHT11 dht11(5); //创建DHT11温湿度计实例对象

void setup () {
    Serial.begin(9600);
    dht11.setDelay(500); //设置温湿度传感器读数之间的自定义延迟(毫秒),默认值500ms
}
 
void loop () {
  int temperature=0, humidity=0;
  //使用传感器进行一次测量，并打印出以厘米为单位的距离。
  dht11.readTemperatureHumidity(temperature, humidity);
  double distance0 = distanceSensor0.measureDistanceCm(temperature);
  double distance1 = distanceSensor1.measureDistanceCm(temperature);
  Serial.print(F("温度: ")); //print(F"")中F语句可节省sram空间，字符串存在外部flash中
  Serial.print(temperature);

  Serial.print(F("°C\t\tD0: "));
  Serial.print(distance0);
  Serial.print(F("cm"));
  Serial.print(F("\tD1: "));
  Serial.print(distance1);
  Serial.println(F("cm"));
  
  //******** 温湿度一起获取 ***********
  //读取DHT11传感器的温度和湿度值,返回0表无误，返回1表报错
  // int result = dht11.readTemperatureHumidity(temperature, humidity);
// if (result == 0) {
//   Serial.print("温度: ");
//   Serial.print(temperature);
//   Serial.print(" °C\湿度: ");
//   Serial.print(humidity);
//   Serial.println(" %");
// } else { Serial.println(DHT11::getErrorString(result)); } //根据错误代码打印错误信息
  delay(500);
}
