#include <ros.h>
#include <sensor_msgs/Joy.h>
#include <PWM.h>

ros::NodeHandle  nh;

int32_t frequency_shoulder = 10000;
int32_t frequency_elbow = 10000;
int32_t frequency_wristy = 10;

//pin definitions
int const basePwm = 10; 
int const baseDir = 51;

int const shoulderPwm = 11;
int const shoulderDir = 3;

int const elbowPwm = 12;
int const elbowDir = 2;

int const wristPwmy = 4;
int const wristDiry = 53;

int const wristPwmx = 8;
int const wristDirx = 52;

int const gripperPwm = 13; 
int const gripperDir1 = 6;
int const gripperDir2 = 7;

int gripperFlag = 0;


void messageCb( const sensor_msgs::Joy& joystick){

//  frequency_shoulder = abs(map(joystick.axes[1]*10, -10, 10, -130, 130));
//  frequency_elbow = abs(map(joystick.axes[5]*10, -10, 10, -100, 100));

//  SetPinFrequencySafe(shoulderPwm, frequency_shoulder);
//  SetPinFrequencySafe(elbowPwm, frequency_elbow);
//  SetPinFrequencySafe(wristPwmy, 490);
  //SetPinFrequencySafe(wristPwmx, 490);

  SetPinFrequencySafe(shoulderPwm, 120);
  SetPinFrequencySafe(elbowPwm, 120);

  // light up when sending signal
  if (joystick.buttons[2] > 0) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }

    digitalWrite(LED_BUILTIN, LOW);

// BASE
//  we found that sending pwm of 5 works the best for the base stepper motor
 analogWrite(basePwm,0);

 if(joystick.axes[0] > 0.5 ){
   digitalWrite(baseDir,1);
   analogWrite(basePwm, 5);
 }

 if(joystick.axes[0] < -0.5){
   digitalWrite(baseDir,0);
   analogWrite(basePwm, 5);
 }

 
 // SHOULDER
  pwmWrite(shoulderPwm, 0);

 if (joystick.axes[1] > 0.25) {
    digitalWrite(shoulderDir, 1);
    pwmWrite(shoulderPwm, 155);
 }
 if (joystick.axes[1] < -0.25) {
    digitalWrite(shoulderDir, 0);
    pwmWrite(shoulderPwm, 155);
 }

  // ELBOW
    pwmWrite(elbowPwm,0);

 if(joystick.axes[5] > 0.5 ){
   digitalWrite(elbowDir,1);
   pwmWrite(elbowPwm, 155);
 }
 if(joystick.axes[5] < -0.5){
   digitalWrite(elbowDir,0);
   pwmWrite(elbowPwm, 155);
 }

//
  // WRIST Y
 analogWrite(wristPwmy,0);
 if(joystick.buttons[2] == 1 ){
   digitalWrite(wristDiry,0);
   analogWrite(wristPwmy, 20); //set pwm
   //analogWrite(gripperPwm,0); // temp solution
 }
 if(joystick.buttons[4] == 1){
   digitalWrite(wristDiry,1);
   analogWrite(wristPwmy, 20);
   //analogWrite(gripperPwm,0);
 }


  // WRIST X
   analogWrite(wristPwmx,0);
 if(joystick.buttons[5] == 1 ){
   digitalWrite(wristDirx,1);
   analogWrite(wristPwmx, 150);
   digitalWrite(LED_BUILTIN, HIGH);


 }else if(joystick.buttons[3] == 1){
   digitalWrite(wristDirx,0);
   analogWrite(wristPwmx, 150);
   digitalWrite(LED_BUILTIN, HIGH);


 }
 

//GRIPPER
  //squeeze 

 analogWrite(gripperPwm,0);
 digitalWrite(gripperDir1,LOW);
 digitalWrite(gripperDir2,LOW);
 
 if(joystick.buttons[0] == 1){
    analogWrite(gripperPwm, 240);
   digitalWrite(gripperDir1,HIGH);
   digitalWrite(gripperDir2,LOW);

 }else if(joystick.buttons[1] == 1){
    analogWrite(gripperPwm, 240);
  digitalWrite(gripperDir1,LOW);
  digitalWrite(gripperDir2,HIGH);
 }
//   analogWrite(gripperPwm,0);
// digitalWrite(gripperDir1,LOW);
// digitalWrite(gripperDir2,LOW);
// 

// if(joystick.buttons[11] == 1){
//  if(gripperFlag == 1){
//    gripperFlag = 0;
//  }else if(gripperFlag == 0){
//    gripperFlag = 1;
//  }
//  while(joystick.buttons[11] == 1){}
  
// }
// Serial.println(gripperFlag);

//  //un-squeeze
// if(joystick.buttons[1] == 1){
//  analogWrite(gripperPwm, 240);
//  digitalWrite(gripperDir1,LOW);
//  digitalWrite(gripperDir2,HIGH);
//  
//  }
// 
}


ros::Subscriber<sensor_msgs::Joy> sub("joy", &messageCb );

void setup() {
  // put your setup code here, to run once:
  pinMode(basePwm, OUTPUT);
  pinMode(baseDir, OUTPUT);
  pinMode(shoulderPwm, OUTPUT);
  pinMode(shoulderDir, OUTPUT);
  pinMode(elbowPwm, OUTPUT);
  pinMode(elbowDir, OUTPUT);
  pinMode(wristPwmy, OUTPUT);
  pinMode(wristDiry, OUTPUT);
  pinMode(wristPwmx, OUTPUT);
  pinMode(wristDirx, OUTPUT);
  pinMode(gripperPwm, OUTPUT);
  pinMode(gripperDir1, OUTPUT);
  pinMode(gripperDir2, OUTPUT);

//  Serial.begin(57600);
  
  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{  
  nh.spinOnce();
  delay(1);
}