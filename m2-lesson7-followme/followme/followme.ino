/*  ___   ___  ___  _   _  ___   ___   ____ ___  ____  
 * / _ \ /___)/ _ \| | | |/ _ \ / _ \ / ___) _ \|    \ 
 *| |_| |___ | |_| | |_| | |_| | |_| ( (__| |_| | | | |
 * \___/(___/ \___/ \__  |\___/ \___(_)____)___/|_|_|_|
 *                  (____/ 
 * Arduino Mecanum Omni Direction Wheel Robot Car
 * Tutorial URL http://osoyoo.com/?p=30022
 * CopyRight www.osoyoo.com

 * After running the code, smart car will 
 * go forward and go backward for 2 seconds, 
 * left turn and right turn for 2 seconds, 
 * right shift and left shift for 2 seconds,
 * left diagonal back and right diagonal forward for 2 seconds,
 * left diagonal forward and right diagonal back for 2 seconds,
 * then stop. 
 * 
 */
#define SPEED 100    
#define TURN_SPEED 100    
#define speedPinR 9   //  Front Wheel PWM pin connect Right MODEL-X ENA 
#define RightMotorDirPin1  22    //Front Right Motor direction pin 1 to Right MODEL-X IN1  (K1)
#define RightMotorDirPin2  24   //Front Right Motor direction pin 2 to Right MODEL-X IN2   (K1)                                 
#define LeftMotorDirPin1  26    //Front Left Motor direction pin 1 to Right MODEL-X IN3 (K3)
#define LeftMotorDirPin2  28   //Front Left Motor direction pin 2 to Right MODEL-X IN4 (K3)
#define speedPinL 10   //  Front Wheel PWM pin connect Right MODEL-X ENB

#define speedPinRB 11   //  Rear Wheel PWM pin connect Left MODEL-X ENA 
#define RightMotorDirPin1B  5    //Rear Right Motor direction pin 1 to Left  MODEL-X IN1 ( K1)
#define RightMotorDirPin2B 6    //Rear Right Motor direction pin 2 to Left  MODEL-X IN2 ( K1) 
#define LeftMotorDirPin1B 7    //Rear Left Motor direction pin 1 to Left  MODEL-X IN3  (K3)
#define LeftMotorDirPin2B 8  //Rear Left Motor direction pin 2 to Left  MODEL-X IN4 (K3)
#define speedPinLB 12    //  Rear Wheel PWM pin connect Left MODEL-X ENB
#define LeftSensor 53    // left IR sensor in D53
#define RightSensor 52    // right IR sensor in D52
/*motor control*/
void go_advance(int speed){
   RL_fwd(speed);
   RR_fwd(speed);
   FR_fwd(speed);
   FL_fwd(speed); 
}
void go_back(int speed){
   RL_bck(speed);
   RR_bck(speed);
   FR_bck(speed);
   FL_bck(speed); 
}
 

void left_turn(int speed){
   RL_bck(0);
   RR_fwd(speed);
   FR_fwd(speed);
   FL_bck(0); 
}
void right_turn(int speed){
   RL_fwd(speed);
   RR_bck(0);
   FR_bck(0);
   FL_fwd(speed); 
}
void left_back(int speed){
   RL_fwd(0);
   RR_bck(speed);
   FR_bck(speed);
   FL_fwd(0); 
}
void right_back(int speed){
   RL_bck(speed);
   RR_fwd(0);
   FR_fwd(0);
   FL_bck(speed); 
}
 

void FR_fwd(int speed)  //front-right wheel forward turn
{
  digitalWrite(RightMotorDirPin1,LOW);
  digitalWrite(RightMotorDirPin2,HIGH); 
  analogWrite(speedPinR,speed);
}
void FR_bck(int speed) // front-right wheel backward turn
{
  digitalWrite(RightMotorDirPin1,HIGH);
  digitalWrite(RightMotorDirPin2,LOW); 
  analogWrite(speedPinR,speed);
}
void FL_fwd(int speed) // front-left wheel forward turn
{
  digitalWrite(LeftMotorDirPin1,LOW);
  digitalWrite(LeftMotorDirPin2,HIGH);
  analogWrite(speedPinL,speed);
}
void FL_bck(int speed) // front-left wheel backward turn
{
  digitalWrite(LeftMotorDirPin1,HIGH);
  digitalWrite(LeftMotorDirPin2,LOW);
  analogWrite(speedPinL,speed);
}

void RR_fwd(int speed)  //rear-right wheel forward turn
{
  digitalWrite(RightMotorDirPin1B, LOW);
  digitalWrite(RightMotorDirPin2B,HIGH); 
  analogWrite(speedPinRB,speed);
}
void RR_bck(int speed)  //rear-right wheel backward turn
{
  digitalWrite(RightMotorDirPin1B, HIGH);
  digitalWrite(RightMotorDirPin2B,LOW); 
  analogWrite(speedPinRB,speed);
}
void RL_fwd(int speed)  //rear-left wheel forward turn
{
  digitalWrite(LeftMotorDirPin1B,LOW);
  digitalWrite(LeftMotorDirPin2B,HIGH);
  analogWrite(speedPinLB,speed);
}
void RL_bck(int speed)    //rear-left wheel backward turn
{
  digitalWrite(LeftMotorDirPin1B,HIGH);
  digitalWrite(LeftMotorDirPin2B,LOW);
  analogWrite(speedPinLB,speed);
}
 
void stop_Stop()    //Stop
{
  analogWrite(speedPinLB,0);
  analogWrite(speedPinRB,0);
  analogWrite(speedPinL,0);
  analogWrite(speedPinR,0);
}


//Pins initialize
void init_GPIO()
{
  pinMode(RightMotorDirPin1, OUTPUT); 
  pinMode(RightMotorDirPin2, OUTPUT); 
  pinMode(speedPinL, OUTPUT);  
 
  pinMode(LeftMotorDirPin1, OUTPUT);
  pinMode(LeftMotorDirPin2, OUTPUT); 
  pinMode(speedPinR, OUTPUT);
  pinMode(RightMotorDirPin1B, OUTPUT); 
  pinMode(RightMotorDirPin2B, OUTPUT); 
  pinMode(speedPinLB, OUTPUT);  
 
  pinMode(LeftMotorDirPin1B, OUTPUT);
  pinMode(LeftMotorDirPin2B, OUTPUT); 
  pinMode(speedPinRB, OUTPUT);
  pinMode(LeftSensor,INPUT);
  pinMode(RightSensor,INPUT);
  
  stop_Stop();
}
void auto_following(){
 int IRvalueLeft= digitalRead(RightSensor);
  int IRvalueRight=digitalRead(LeftSensor);
 if (IRvalueLeft==LOW && IRvalueRight==LOW)
 { 
  //both sensor detected obstacle, go ahead
      go_advance(SPEED);  //Turn left
 }
 else  if (IRvalueLeft==HIGH && IRvalueRight==HIGH)
     stop_Stop();   //no obstacle, stop
 
 else if (IRvalueLeft==LOW && IRvalueRight==HIGH)
 { 
  //only right sensor detect obstacle
      right_turn(SPEED);  //Turn lrighteft
 }
  else if (IRvalueLeft==HIGH && IRvalueRight==LOW)
 { 
   //only left sensor detect obstacle
      left_turn(SPEED);  //Turn left
 }
}
void setup()
{
  init_GPIO();
}

void loop(){
  auto_following();
}
