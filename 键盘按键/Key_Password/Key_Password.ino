
//矩阵键盘扫描并显示在1602显示屏上
#include <Arduino.h>
#include <U8g2lib.h>  //U8G2_SSD1306_128X64

#define SCL 22  //定义时钟引脚
#define SDA 21  //定义数据引脚
//I2C构造对象 对象名(旋转角度,时钟引脚，数据引脚，U8X8_PIN_NONE)
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, SCL, SDA, U8X8_PIN_NONE);

int row_pins[4]={26, 25, 33, 32}; //定义行引脚数组
int col_pins[4]={27, 14, 12, 13}; //列引脚
char key; //按键函数返回值
const char password[5]="1234"; //定义密码与输入密码变量
char entered_password[5]="";  //存放键盘输入的密码

//按键值获取函数
char read_keypad(){
  //定义键盘按键布局二维数组
  char keys[4][4]={ {'1', '2', '3', 'A'},
                    {'4', '5', '6', 'B'},
                    {'7', '8', '9', 'C'},
                    {'*', '0', '#', 'D'},
                  };
  //行列扫描
  for(int j=0; j<4; j++){ //列循环输出低电平
    digitalWrite(col_pins[j], LOW);
    for(int i=0; i<4; i++){ //行循环接收
      if( !digitalRead(row_pins[i]) ){ //检测到低电平，则返回该值
        digitalWrite(col_pins[j], HIGH); //还原成高电平
        return keys[i][j];
      }
    }
    digitalWrite(col_pins[j], HIGH); //还原成高电平
  }
  return NULL;
}


//校验并显示密码
void check_password(char enter_key){
  if(enter_key){
    if(enter_key=='#'){
      //密码校验函数，strcmp( 校验字符串, password)，为0则校验通过
      if( strcmp(entered_password, password)==0 ){ //若相等则进入
        u8g2.clearBuffer(); //清空缓存区、
        u8g2.firstPage(); //进入第一页（清空缓存区）
        u8g2.setCursor(0, 14); //设置光标位置
        u8g2.print("访问已授权！");
        u8g2.sendBuffer();  //发送缓存区内容到OLED显示
      }else{
        u8g2.clearBuffer(); //清空缓存区
        u8g2.firstPage(); //进入第一页（清空缓存区）
        u8g2.setCursor(0, 14); //设置光标位置
        u8g2.print("错误，拒绝访问！");
        u8g2.sendBuffer();  //发送缓存区内容到OLED显示
      }
      delay(2000);
      //回到输入密码页面
      u8g2.clearBuffer(); //清空缓存区
      u8g2.firstPage(); //进入第一页（清空缓存区）
      u8g2.setCursor(0, 14); //设置光标位置
      u8g2.print("请输入密码：");
      u8g2.sendBuffer();  //发送缓存区内容到OLED显示
      //清空已输入的密码，memset(操作数组名, 填充内容, 字节大小)
      memset( entered_password, 0, sizeof(entered_password) );
    }else{
      //输入密码，添加输入的字符到密码字符串中
      if( strlen(entered_password)<4 ){
        u8g2.setCursor( strlen(entered_password)*15, 34); //设置光标位置
        //u8g2.print('*');
        u8g2.print(key);
        u8g2.sendBuffer();  //发送缓存区内容到OLED显示
        entered_password[ strlen(entered_password) ] = enter_key; //输入值存入数组
      }
    }
  }

  delay(120);
}



void setup() {
  //Serial.begin(115200);

  u8g2.begin(); //初始化OLED对象
  u8g2.enableUTF8Print(); //开启中文字符集支持
  u8g2.setFont(u8g2_font_wqy14_t_gb2312); //设置字体
    u8g2.clearBuffer(); //清空缓存区、
  u8g2.firstPage(); //进入第一页（清空缓存区）
  u8g2.setCursor(0, 14); //设置光标位置
  u8g2.print("请输入密码：");
  u8g2.sendBuffer();  //发送缓存区内容到OLED显示


  pinMode(2,OUTPUT);
  digitalWrite(2, LOW);
  for(int i=0; i<4; i++){
    pinMode(row_pins[i], INPUT_PULLUP); //行引脚设置为上拉输入(默认高电平)
    pinMode(col_pins[i], OUTPUT); //列引脚输出
    digitalWrite(col_pins[i], HIGH); //将列引脚初始化为高电平
  }
}

void loop() {
  key = read_keypad();
  check_password(key);
  /*
  if(key){
    Serial.printf("检测到按键：%c\n", key);

    u8g2.clearBuffer(); //清空缓存区、
    u8g2.firstPage(); //进入第一页（清空缓存区）
    u8g2.setCursor(0, 14); //设置光标位置
    u8g2.print("检测到按键：");
    u8g2.setCursor(75,14); //设置光标位置
    u8g2.print(key);
    u8g2.sendBuffer();  //发送缓存区内容到OLED显示
  }*/
}

