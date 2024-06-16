
//陀螺仪小车

#include "BluetoothSerial.h" //蓝牙串口文件
#include <MPU6050_tockn.h> //陀螺仪
#include <Wire.h> // Wire串口传输


#define IN1 17 //电机控制板
#define IN2 18
#define IN3 4
//GPIO5引脚上电默认高电平
#define IN4 16

/////////////// 陀螺仪设参START //////////////////////////////////
MPU6050 mpu6050(Wire); //实例化MPU陀螺仪对象

//PID调试参数
float Balnce_Angle_raw = -9; //静态机械平衡角度
const int left_Motor_PWM_Offset = 4; //左马达PWM补偿值4
const int right_Motor_PWM_Offset = 3; //右马达PWM补偿值3
    float ENERGY = 5; //前进后退允许倾斜角度
float kp=20, ki=0, kd=3; //PID调试参数
    int z_trun = 30; //Z轴转向角速度值
    int z_turn_spd  = 0; //Z轴转向角速度
    float z_angle_kp = -2; //转向环，仅比例控制

//保持角度，角度偏差变量，角度偏差积分
float Keep_Angle, bias,integrate;
float /*AngleX,*/ AngleY, AngleZ; //角度值
float /*GyroX,*/ GyroY, GyroZ; //角速度值
//直立PWM，转向PWM，最终PWM，左马达PWM，右马达PWM
int vertical_PWM, turn_PWM, PWM, L_PWM, R_PWM;

unsigned char flag = 'S'; //状态标志

//I2C引脚定义，默认引脚为21，22
#define sda_pin 21
#define scl_pin 22
/////////////// 陀螺仪设参END //////////////////////////////////


/////////////// 蓝牙设参START //////////////////////////////////
const char *pin = "254163"; //将其更改为更安全的PIN
String device_name = "ESP32_Car";
BluetoothSerial SerialBT; //实例化蓝牙对象
/////////////// 蓝牙设参END //////////////////////////////////


//蓝牙串口输入修改PWM值
void BLE_debug(){
  if ( SerialBT.available() ){ //判断蓝牙串口是否有数据
    char DATA = SerialBT.read(); //串口读数据
    delay(5);
    switch (DATA){
      case 's': //停车
        flag = 's'; //状态反馈
        Keep_Angle = Balnce_Angle_raw; //保持角度回到机械平衡角度
        z_turn_spd = 0; //z轴转向角速度归零
        break; 
      case 'a': //前进
        flag = 'a';
        Keep_Angle = Balnce_Angle_raw + ENERGY; //保持角度=机械平衡角度+倾角
        z_turn_spd = 0;
        break; 
      case 'b': //后退
        flag = 'b';
        Keep_Angle = Balnce_Angle_raw - ENERGY; //保持角度=机械平衡角度-倾角
        z_turn_spd = 0;
        break; 
      case 'l': flag = 'l'; z_turn_spd = z_trun; break; //左转
      case 'r': flag = 'r'; z_turn_spd = -(z_trun); break; //右转

      //===参数调试==测定小车静态平衡角度值
        //调节物理平衡点
        case 'u': Keep_Angle += 0.1; break; //u前倾
        case 'd': Keep_Angle -= 0.1; break; //d后仰
        //==直立环调试==
        case '0': if( kp > 0 ){ kp-=1; }else{ kp=0; } break;   case '1': kp+=1; break; //直立环比例项
        case '2': if( ki > 0 ){ ki-=0.1; }else{ ki=0; } break;   case '3': ki+=0.1; break; //直立环积分项
        case '4': if( kd > 0 ){ kd-=0.1; }else{ kd=0; } break;   case '5': kd+=0.1; break; //直立环微分项
        //==转向环调试
        case '6': z_angle_kp-=0.2; break;  case '7': z_angle_kp+=0.2; break; //转向环比例项，取值范围由限定范围确定
      default: SerialBT.printf("Undefined!\n"); break; //未定义按键
    }
    //蓝牙参数回传
    SerialBT.printf("Keep_Angle:%f\n", Keep_Angle); //保持角
    SerialBT.printf("Kp:%f  ki:%f  kd:%f \n", kp, ki, kd); //PID参数
    SerialBT.printf("z_angle_kp:%f \n", z_angle_kp); //转向环，仅比例控制
    SerialBT.printf("z_turn_spd:%d\n", z_turn_spd); //转向Z速度
    SerialBT.printf("Keep_Angle:%f\n", Keep_Angle); //机械平衡角
    SerialBT.printf("--------------------\n");
  }
}


//电机PWM控制函数
void motor(int left_EN, int right_EN){
  left_EN = constrain( left_EN, -255, 255); //限制PWM范围
  right_EN = constrain( right_EN, -255, 255);
  //左轮，analogWrite默认分辨率为8，也就是0~255的模拟信号输出
  if( left_EN == 0 ){ analogWrite(IN1, 0); analogWrite(IN2, 0); } //停转
  else if( left_EN < 0 ) { analogWrite(IN1, 0); analogWrite(IN2, 0-left_EN); } //反转
  else if( left_EN > 0 ){ analogWrite(IN1, left_EN); analogWrite(IN2, 0); } //正转
  //右轮
  if( right_EN == 0 ){ analogWrite(IN3, 0); analogWrite(IN4, 0); } //停转
  else if( right_EN < 0 ) { analogWrite(IN3, 0); analogWrite(IN4, 0-right_EN); } //反转
  else if( right_EN > 0 ){ analogWrite(IN3, right_EN); analogWrite(IN4, 0); } //正转
}


//转向PWM计算
void turn_PWM_calculation(){
  // AngleZ = mpu6050.getAngleZ(); //获取Z轴角度
  GyroZ = mpu6050.getGyroZ(); //获取陀螺仪Z轴角速度
  turn_PWM = z_angle_kp * (GyroZ - z_turn_spd); //转向PWM=比例项*(Z轴当前角速度-目标角速度)
  turn_PWM = constrain( turn_PWM, -130, 130); //参数范围限定函数constrain，将angle_PWM值限定在-130到130之间，防止因角速度过大影响平衡
}

//直立PWM计算
void vertical_PWM_calculation(){
  AngleY = mpu6050.getAngleY(); //获取Y轴角度
  GyroY = mpu6050.getGyroY(); //获取Y轴角速度

  bias = AngleY - Keep_Angle; //计算角度偏差，bias为小车角度偏差值
  integrate += bias; //角度偏差积分，integrate为全局变量，一直积累
  integrate = constrain(integrate, -1000, 1000); //参数范围限定
  
//*******************************************************************************
  //==直立PID计算PWM==通过陀螺仪返回数据计算，前倾陀螺仪Y轴为正，后仰陀螺仪Y轴为负
    //前倾车前进，后仰车后退，保持直立。但可能为了直立车随时会移动。
  vertical_PWM = kp * bias + ki * integrate + kd * GyroY;
  //直立PWM值 = kp*角度偏差变量 + ki*角度偏差积分 + kd*Y轴角速度(倾倒速度)
  //              倾角比例项         积分项         微分项(回正时抑制kp)
//*******************************************************************************
}


//电机控制PWM换算
void motor_control(){
  //【PWM差值补偿】
  if( PWM>0 ){ L_PWM = PWM + left_Motor_PWM_Offset;  R_PWM = PWM + right_Motor_PWM_Offset; } //正补偿
  else if( PWM<0 ){ L_PWM = PWM - left_Motor_PWM_Offset;  R_PWM = PWM - right_Motor_PWM_Offset; } //负补偿
  else if( PWM==0 ){ L_PWM = 0;  R_PWM = 0; } //归零

  //【转向判断】
  if( flag=='s' ){ L_PWM = L_PWM; R_PWM = R_PWM; } //使小车保持原地直立
  else if( flag=='l' ){ L_PWM += turn_PWM;  R_PWM -= turn_PWM; } //右转，转向差速PWM值angle_PWM
  else if( flag=='r' ){ L_PWM -= turn_PWM;  R_PWM += turn_PWM; } //左转

  //【控制马达输出】
  motor(L_PWM, R_PWM); //传参输出PWM

  //【判断小车是否倒下】倒下则停止马达和编码器计数
  if( AngleY > 50 || AngleY < -50 ){  motor( 0, 0 ); } //判断Y轴角度，过大则停转马达
}



void setup() {
  // Serial.begin(115200);
/////////////// 蓝牙初始化START //////////////////////////////////
  SerialBT.begin( device_name ); //蓝牙设备名设定
  // Serial.printf( "设备 \"%s\" 已启动.\n 现已可进行蓝牙配对！\n", device_name.c_str() );
/////////////// 蓝牙初始化END //////////////////////////////////

/////////////// 陀螺仪初始化START /////////////////
  Wire.begin(/*sda_pin, scl_pin*/); //无传参则保持默认IIC引脚21.22，也可自定义IIC引脚
  mpu6050.begin(); //启动陀螺仪
  mpu6050.calcGyroOffsets(true); //计算陀螺仪偏移相关
  Keep_Angle = Balnce_Angle_raw; //平衡角度初始化为静态平衡时的陀螺仪角度
/////////////// 陀螺仪初始化END /////////////////
  motor(0, 0); //启动时马达停止
  delay(10);
}

void loop() {
  BLE_debug(); //串口PID调试与控制
  mpu6050.update(); //陀螺仪刷新
  turn_PWM_calculation(); //转向环PWM值计算
  vertical_PWM_calculation(); //直立环PWM计算
  PWM = vertical_PWM; //保持直立
  motor_control(); //马达输出
}
