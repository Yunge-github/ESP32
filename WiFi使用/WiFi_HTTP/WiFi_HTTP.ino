
//WiFi功能HTTP请求获取天气JSON网络数据

#include <WiFi.h> 
#include <HTTPClient.h>
#include <ArduinoJson.h>  //需下载库
#include <U8g2lib.h>

#define SCL 22  //定义I2C时钟引脚
#define SDA 21  //定义I2C数据引脚

//I2C构造对象 对象名(旋转角度,时钟引脚，数据引脚，U8X8_PIN_NONE)
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, SCL, SDA, U8X8_PIN_NONE);

const char * ssid = "Yg";
const char * password = "q2541639095";

String url="http://apis.juhe.cn/simpleWeather/query";
String city="共青城";
String key="de8ce667fe779d9caf405bce3afdfb57";


void setup() {
  Serial.begin(115200);
  //连接Wifi
  WiFi.begin(ssid, password);
  Serial.println("正在连接Wifi");
  //检测是否连接成功
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("Wifi连接成功！");

  //创建HTTPClient对象
  HTTPClient http;
  //指定需访问的URL
  http.begin(url+"?city="+city+"&key="+key);
  //接收HTTP响应状态码
  int http_code = http.GET();
  Serial.printf("HTTP 状态码：%d \n",http_code); // int型%d，char型%s
  //获取响应正文
  String response = http.getString();
  Serial.print("响应数据：");
  Serial.print(response);
  //关闭连接
  http.end();

  //创建 DynamicJsonDocument 对象
  DynamicJsonDocument doc(1024);
  //解析JSON数据
  deserializeJson(doc, response);
  //从解析的JSON数据中获取值
  unsigned int temp = doc["result"]["realtime"]["temperature"].as<unsigned int>(); //温度，无符号，避免零下温度显示异常
  String info = doc["result"]["realtime"]["info"].as<String>(); //天气
  int aqi = doc["result"]["realtime"]["aqi"].as<int>(); //空气指数
  Serial.printf("\n城市：%s, 温度：%d， 天气：%s， 空气指数：%d \n", city, temp, info, aqi); //将解析的值打印


  //OLED显示屏I2C输出
  u8g2.begin(); //初始化OLED对象
  u8g2.enableUTF8Print(); //开启中文字符集支持
  u8g2.setFont(u8g2_font_wqy12_t_gb2312); //设置字体,文泉驿字体库u8g2_font_wqy12_t_gb2312a
  u8g2.clearBuffer(); //清空缓存区

  u8g2.setCursor(2, 12);
  u8g2.print(city);
  u8g2.drawHLine(0, 15, 128); //绘制水平线,(横线最左端x，y，长度，颜色)

  u8g2.setCursor(6, 32); 
  u8g2.print(temp); //温度
  u8g2.drawUTF8(24, 32, "C°");

  u8g2.setCursor(46, 32);
  u8g2.print(info); //天气

  u8g2.drawUTF8(6, 52, "空气指数：");
  u8g2.setCursor(65, 52);
  u8g2.print(aqi);

  u8g2.sendBuffer();  //发送缓存区内容到OLED显示
}

void loop() {
  // put your main code here, to run repeatedly:

}
