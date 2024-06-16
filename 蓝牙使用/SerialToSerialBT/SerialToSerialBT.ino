//此示例代码位于公共域（或CC0许可，由您选择） 
//作者Evandro Copercini-2018 
// 
//此示例在串行蓝牙和经典蓝牙（SPP）之间创建了一个桥接器 
//并证明SerialBT具有与普通Serial相同的功能

#include "BluetoothSerial.h"

//#define USE_PIN //取消注释以在配对过程中使用PIN，PIN在下面的行中指定
const char *pin = "254163"; //将其更改为更安全的PIN

String device_name = "ESP32-Car";

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
//蓝牙未启用！请运行“make menuconfig”到并启用它
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
//串行蓝牙不可用或未启用。它仅适用于ESP32芯片。
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT; //实例化蓝牙对象

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_Car"); //蓝牙设备名称
  Serial.printf("设备 \"%s\" 已启动.\n 现已可进行蓝牙配对！\n", device_name.c_str());
  //Serial.printf("设备名: \"%s\"  MAC地址: %s  已启动.\n现已可进行蓝牙配对！\n", device_name.c_str(), SerialBT.getMacString()); //在MAC方法实现后使用
  #ifdef USE_PIN
    SerialBT.setPin(pin);
    Serial.println("Using PIN");
  #endif
}

void loop() {
  //判断电脑USB串口是否有数据
  if ( Serial.available() ) { SerialBT.write( Serial.read() ); } //Serial.read()获取USB串口数据，SerialBT.write()蓝牙串口发送
  //判断蓝牙串口是否有数据
  if ( SerialBT.available() ){ Serial.write( SerialBT.read() ); } //通过电脑串口打印蓝牙串口获取的数据
  delay(20);
}
