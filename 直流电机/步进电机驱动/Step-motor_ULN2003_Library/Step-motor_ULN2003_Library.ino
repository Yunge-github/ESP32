
#include <CheapStepper.h>

#define IN_1  13
#define IN_2  12
#define IN_3  14
#define IN_4  27
CheapStepper stepper( IN_1, IN_2, IN_3, IN_4);
bool moveClockwise = true;

void setup() {
  //设置转速
  stepper.setRpm(15);
  //根据步数旋转
  // stepper.moveTo(moveClockwise, 2048);  //180度
  
  // delay(1000);
  
  // //根据角度旋转
  // stepper.moveDegrees(moveClockwise, 90);  //90度

  // //停转复位
  // digitalWrite(IN_1, 0);
  // digitalWrite(IN_2, 0);
  // digitalWrite(IN_3, 0);
  // digitalWrite(IN_4, 0);

}

void loop() {
  //根据角度旋转
  stepper.moveDegrees(moveClockwise, 90);  //90度
  delay(500);

  //停转复位
  digitalWrite(IN_1, 0);
  digitalWrite(IN_2, 0);
  digitalWrite(IN_3, 0);
  digitalWrite(IN_4, 0);
}
