/*******************************************************************************
* Copyright 2016 ROBOTIS CO., LTD.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include <DynamixelShield.h>

#if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_MEGA2560)
  #include <SoftwareSerial.h>
  SoftwareSerial soft_serial(7, 8); // DYNAMIXELShield UART RX/TX
  #define DEBUG_SERIAL soft_serial
#elif defined(ARDUINO_SAM_DUE) || defined(ARDUINO_SAM_ZERO)
  #define DEBUG_SERIAL SerialUSB
#else

  #define DEBUG_SERIAL Serial
#endif


#define DEBUG True    //debug mode
#define CONTROL_FREQUENCY 100  //unit: ms
#define STUCK_SPEED

const uint8_t DXL_ID = 3;
const float DXL_PROTOCOL_VERSION = 2.0;

DynamixelShield dxl;

int rotateMotor1 = 45;
int rotateMotor2 = 45;

int robotState1 = 0;
int robotState2 = 0;

int torqueNumber = 8;
int desirePosition1 = 0;
int desirePosition2 = 0;
int currentPosition1 = 0;
int currentPosition2 = 0;
int lastPosition = 0;

int liftState1 = 0; //0 is not lift, 1 is lift
int liftState2 = 0;

int duty[] = {0, 0, 0, 0};
int backoff[] = {0, 0, 0, 0};
int backoffStatus[] = {0, 0, 0, 0};
int torqueMode[] = {1, 1, 0, 0, 1, 1, 0, 0};

int desiredSpeed[] = {0, 0, 0, 0};
int currentSpeed[] = {0, 0, 0, 0};
int lastSpeed[] = {0, 0, 0, 0};
int accSpeed[] = {0, 0, 0, 0};
int outputSpeed[] = {0, 0, 0, 0};
float P = -1;
float I = 0;
float D = 0;

//This namespace is required to use Control table item names
using namespace ControlTableItem;
void reverse1(){
  dxl.setGoalVelocity(8, -95, UNIT_PERCENT);
  delay(1000);
  return;
}

void reverse2(){
  dxl.setGoalVelocity(9, 5, UNIT_PERCENT);
  delay(1000);
  return;
}

void positionControl(int id, int positionX){
  dxl.setGoalPosition(id, positionX, UNIT_DEGREE);
   DEBUG_SERIAL.println("呵额");
   DEBUG_SERIAL.println(positionX);
  return;
}

int positionDetection(int id){
  lastPosition = dxl.getPresentPosition(id, UNIT_DEGREE);
  DEBUG_SERIAL.print("Present Position(degree) : ");
  DEBUG_SERIAL.println(dxl.getPresentPosition(id, UNIT_DEGREE));
  return lastPosition;
}

void lift1(){
  if (liftState1 == 0){
    DEBUG_SERIAL.println("liftState1xx");
    for (int i = 0; i < 10; i++){
      dxl.setGoalPosition(3, (150 + 3 * i), UNIT_DEGREE);
      delay(100);
    }
    liftState1 = 1;
  }
  else{
    DEBUG_SERIAL.println("liftState1yy");
    for (int i = 0; i < 10; i++){
      dxl.setGoalPosition(3, (180 - 3 * i), UNIT_DEGREE);
      delay(100);
    }
    liftState1 = 0;
  }
  return ;
}

void lift2(){
  if (liftState2 == 0){
    DEBUG_SERIAL.println("liftState2xx");
    for (int i = 0; i < 10; i++){
      dxl.setGoalPosition(7, (150 - 3 * i), UNIT_DEGREE);
      delay(100);
    }
    liftState2 = 1;
  }
  else{
    DEBUG_SERIAL.println("liftState2yy");
    for (int i = 0; i < 10; i++){
      dxl.setGoalPosition(7, (120 + 3 * i), UNIT_DEGREE);
      delay(100);
    }
    liftState2 = 0;
  }
  return;
}

void setup() {
  // put your setup code here, to run once:
  
  // For Uno, Nano, Mini, and Mega, use UART port of DYNAMIXEL Shield to debug.
  DEBUG_SERIAL.begin(115200);
  
  // Set Port baudrate to 57600bps. This has to match with DYNAMIXEL baudrate.
  dxl.begin(1000000);
  // Set Port Protocol Version. This has to match with DYNAMIXEL protocol version.
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);

  for (int i = 1; i <= torqueNumber; i++){
  // Get DYNAMIXEL information
  dxl.ping(i);
  // Turn off torque when configuring items in EEPROM area
  dxl.torqueOff(i);
  if (torqueMode[i-1])
   dxl.setOperatingMode(i, OP_VELOCITY);
  else
    dxl.setOperatingMode(i, OP_POSITION);
  dxl.torqueOn(i);
  }
  delay(1000);

  dxl.setGoalPosition(8, 240, UNIT_DEGREE);

  delay(500);
  
  dxl.setGoalPosition(4, 60, UNIT_DEGREE);

  delay(500);
  
  //dxl.setGoalPosition(3, 150, UNIT_DEGREE);

  //delay(500);
  
  //dxl.setGoalPosition(7, 150, UNIT_DEGREE);

  delay(2000);
  
}

// movement for 1 servo
void servo1(float duty){
  if (duty > 0) duty = duty - 100;
  else if (duty < 0) duty = -duty;
  dxl.setGoalVelocity(1, duty, UNIT_PERCENT);
}

void servo2(float duty) {
  if (duty < 0) duty = -duty - 100;
  dxl.setGoalVelocity(2, duty, UNIT_PERCENT);
}

void servo3(float duty){
  if (duty > 0) duty = duty - 100;
  else if (duty < 0) duty = -duty;
  dxl.setGoalVelocity(5, duty, UNIT_PERCENT);
}

void servo4(float duty) {
  if (duty < 0) duty = -duty - 100;
  dxl.setGoalVelocity(6, duty, UNIT_PERCENT);
}


void go_1(float leftDuty, float rightDuty) {
  servo1(leftDuty);
  servo2(rightDuty);
}

void go_2(float leftDuty, float rightDuty) {
  servo3(leftDuty);
  servo4(rightDuty);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // Please refer to e-Manual(http://emanual.robotis.com) for available range of value. 
  // Set Goal Velocity using RAW unit
  //dxl.setGoalVelocity(2, 8, UNIT_PERCENT);
  //dxl.setGoalVelocity(1, -84, UNIT_PERCENT);
  //dxl.setGoalVelocity(3, 1, UNIT_PERCENT);
  //dxl.setGoalVelocity(4, 1, UNIT_PERCENT);
  
  //if (dxl.getPresentVelocity(8) < 200 )
 // reverse1();
  //if (dxl.getPresentVelocity(9) < 200 )
  //reverse2();
  //delay(2000);

   lift1();
  DEBUG_SERIAL.println("111111111111");
  delay(1000);
  while (liftState1 == 1){
    currentPosition1 = positionDetection(4);
    currentPosition2 = positionDetection(8);
    while (currentPosition1 < 65 && currentPosition1 > 55 && robotState1 == 0){
      DEBUG_SERIAL.println("5");
      robotState1 = 1;
    }
    while (currentPosition2 < 195 && robotState1 == 1){
      go_1(1, 1);
      go_2(1, 1);
      lift1();
      DEBUG_SERIAL.println("6");
      robotState1 = 0;
      
    }

    if (robotState1 == 0 && liftState1 == 1){
      go_1(-20, -10);
      DEBUG_SERIAL.println("7");
      go_2(1 ,1);
      if (currentPosition1 > 65){
        DEBUG_SERIAL.println(">65");
        desirePosition1 = currentPosition1 - 5;

        DEBUG_SERIAL.println(desirePosition1);}
      else if (currentPosition1 < 55){
        DEBUG_SERIAL.println("<55");
        desirePosition1 = currentPosition1 + 5;
        positionControl(4,desirePosition1);

        }
     
     positionControl(4,desirePosition1);
      
    }

    else if (robotState1 == 1){
      go_1(40, 20);
      go_2(1, 1);
      DEBUG_SERIAL.println("8");
      //desireposition1 = currentposition1 + 5;
      desirePosition2 = currentPosition2 - 5;
      //positioncontrol(4,desireposition1);
      positionControl(8,desirePosition2);
    }
  }

  lift2();
  DEBUG_SERIAL.println("22222222222222");
  delay(1000);
  while (liftState2 == 1){
    currentPosition1 = positionDetection(4);
    currentPosition2 = positionDetection(8);
    while (currentPosition2 < 245 && currentPosition2 > 235 && robotState2 == 0){
      robotState2 = 1;
      DEBUG_SERIAL.println("1");
    }
    while (currentPosition1 > 105 && robotState2 == 1 ){
      go_1(1, 1);
      go_2(1, 1);
      lift2();
      DEBUG_SERIAL.println("2");
      robotState2 = 0;
    }

    if (robotState2 == 0 && liftState2 == 1){
      DEBUG_SERIAL.println("3");
      go_1(1, 1);
      go_2(-10 ,-30);
      if (currentPosition2 > 245)
        desirePosition2 = currentPosition2 - 5;
      else if (currentPosition2 < 235)
        desirePosition2 = currentPosition2 + 5;
     positionControl(8,desirePosition2);
    }

    else if (robotState2 == 1){
      go_1(1, 1);
      go_2(20, 40);
      DEBUG_SERIAL.println("4");
      desirePosition1 = currentPosition1 + 5;
      if 
     
      positionControl(4,desirePosition1);
    
    }
  }



  while (rotateMotor2 < 135){
    duty[0] = 16;
    duty[1] = 8;
    duty[2] = 1;
    duty[3] = 1;
    desiredSpeed[0] = 400;
    desiredSpeed[1] = 200;
    desiredSpeed[2] = 1;
    desiredSpeed[3] = 1;

    for (int i = 0; i < 3; i ++){

      // speed PID control
      outputSpeed[i] = desiredSpeed[i];
      outputSpeed[i] += -1 * (currentSpeed[i] - desiredSpeed[i]);   // P
      outputSpeed[i] += 0 * (currentSpeed[i] - lastSpeed[i]);       // D
      accSpeed += (currentSpeed[i] - desiredSpeed[i]);              // I
      outputSpeed[i] += 0 * accSpeed[i];


      // backoff determine
      if (speed[i] < 100){
        backoff[i] ++;
        if (backoff[i] > 10) backoffStatus[i] = 1;
      }
      else backoff[i] = 0;

      // backoff strategy
      if (backoffStatus[i] == 1) {
        outputSpeed[i] = -200;
        backoff[i] --;
        if (backoff[i] == 0){
          backoffStatus[i] = 0;
          accSpeed[i] = 0;
        }
      }
      lastSpeed[i] = currentSpeed[i];

    }
    
    
    go_1(outputSpeed[1]/20, outputSpeed[2]/20);
    go_2(outputSpeed[3]/20, outputSpeed[4]/20);

    rotateMotor2 += 5;

    delay(CONTROL_FREQUENCY);

  }

  //dxl.setGoalVelocity(2, -95, UNIT_PERCENT);
  //dxl.setGoalVelocity(1, 15, UNIT_PERCENT);
  //dxl.setGoalVelocity(3, 1, UNIT_PERCENT);
  //dxl.setGoalVelocity(4, 1, UNIT_PERCENT);
  go_1(5, 15);
  go_2(1, 1);


  // Print present velocity
 // DEBUG_SERIAL.print("Present Velocity(raw8) : ");
  //DEBUG_SERIAL.println(dxl.getPresentVelocity(8));
   //DEBUG_SERIAL.print("Present Velocity(raw9) : ");
  //DEBUG_SERIAL.println(dxl.getPresentVelocity(9));
  delay(1000);

  //dxl.setGoalVelocity(4, 16, UNIT_PERCENT);
  //dxl.setGoalVelocity(3, -92, UNIT_PERCENT);
  //dxl.setGoalVelocity(1, 1, UNIT_PERCENT);
  //dxl.setGoalVelocity(2, 1, UNIT_PERCENT);
  go_1(16, 8);
  go_2(1, 1);

  delay(2000);

  dxl.setGoalVelocity(4, -85, UNIT_PERCENT);
  dxl.setGoalVelocity(3, 5, UNIT_PERCENT);
  dxl.setGoalVelocity(1, 1, UNIT_PERCENT);
  dxl.setGoalVelocity(2, 1, UNIT_PERCENT);
  go_1(5, 15);
  go_2(1, 1);
 
  delay(1000);
  
}









/*******************************************************************************
* Copyright 2016 ROBOTIS CO., LTD.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

#include <DynamixelShield.h>

#if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_MEGA2560)
  #include <SoftwareSerial.h>
  SoftwareSerial soft_serial(7, 8); // DYNAMIXELShield UART RX/TX
  #define DEBUG_SERIAL soft_serial
#elif defined(ARDUINO_SAM_DUE) || defined(ARDUINO_SAM_ZERO)
  #define DEBUG_SERIAL SerialUSB
#else

  #define DEBUG_SERIAL Serial
#endif


#define DEBUG True    //debug mode
#define CONTROL_FREQUENCY 100  //unit: ms
#define STUCK_SPEED

const uint8_t DXL_ID = 3;
const float DXL_PROTOCOL_VERSION = 2.0;

DynamixelShield dxl;

int rotateMotor1 = 45;
int rotateMotor2 = 45;

int robotState1 = 0;
int robotState2 = 0;

int torqueNumber = 8;
int desirePosition1 = 0;
int desirePosition2 = 0;
int lastPosition1 = 0;
int lastPosition2 = 0;
int currentPosition1 = 0;
int currentPosition2 = 0;
int lastPosition = 0;

int liftState1 = 0; //0 is not lift, 1 is lift
int liftState2 = 0;

int duty[] = {0, 0, 0, 0};
int backoff[] = {0, 0, 0, 0};
int backoffStatus[] = {0, 0, 0, 0};
int torqueMode[] = {1, 1, 0, 0, 1, 1, 0, 0};

int desiredSpeed = 0;
int currentSpeed = 0;
int lastSpeed = 10;
int accSpeed = 0;
int outputSpeed = 0;
float P = -1;
float I = 0;
float D = 0;

//This namespace is required to use Control table item names
using namespace ControlTableItem;
void reverse1(){
  dxl.setGoalVelocity(8, -95, UNIT_PERCENT);
  delay(1000);
  return;
}

void reverse2(){
  dxl.setGoalVelocity(9, 5, UNIT_PERCENT);
  delay(1000);
  return;
}

void positionControl(int id, int positionX){
  dxl.setGoalPosition(id, positionX, UNIT_DEGREE);
  return;
}

int speedDetection(int id){
  lastSpeed = dxl.getPresentVelocity(id, UNIT_DEGREE);
  DEBUG_SERIAL.print("Present Velovity(degree) : ");
  DEBUG_SERIAL.println(id);
  delay(100);
  DEBUG_SERIAL.println(dxl.getPresentVelocity(id, UNIT_DEGREE));
  return lastSpeed;
}

int positionDetection(int id){
  lastPosition = dxl.getPresentPosition(id, UNIT_DEGREE);
  DEBUG_SERIAL.print("Present Position(degree) : ");
  DEBUG_SERIAL.println(dxl.getPresentPosition(id, UNIT_DEGREE));
  return lastPosition;
}

int pid(int id, int desiredSpeed){
  currentSpeed = speedDetection(id);
  if (currentSpeed - desiredSpeed < 30 && currentSpeed - desiredSpeed > -30){
    outputSpeed = desiredSpeed;
    outputSpeed += -1 * (currentSpeed - desiredSpeed);  //P
    outputSpeed += 0 * (currentSpeed - lastSpeed);  //D
    accSpeed += (currentSpeed - desiredSpeed); //I
    outputSpeed += 0 * accSpeed;
    lastSpeed = currentSpeed;
    DEBUG_SERIAL.println("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx");
    DEBUG_SERIAL.println(desiredSpeed);
    DEBUG_SERIAL.println(outputSpeed);
  }
  else
    outputSpeed = desiredSpeed;
  return outputSpeed;
}
void lift1(){
  if (liftState1 == 0){
    DEBUG_SERIAL.println("liftState1xx");
    for (int i = 0; i < 10; i++){
      dxl.setGoalPosition(3, (150 + 3 * i), UNIT_DEGREE);
      delay(100);
    }
    liftState1 = 1;
  }
  else{
    DEBUG_SERIAL.println("liftState1yy");
    for (int i = 0; i < 10; i++){
      dxl.setGoalPosition(3, (180 - 3 * i), UNIT_DEGREE);
      delay(100);
    }
    liftState1 = 0;
  }
  return ;
}

void lift2(){
  if (liftState2 == 0){
    DEBUG_SERIAL.println("liftState2xx");
    for (int i = 0; i < 10; i++){
      dxl.setGoalPosition(7, (150 - 3 * i), UNIT_DEGREE);
      delay(100);
    }
    liftState2 = 1;
  }
  else{
    DEBUG_SERIAL.println("liftState2yy");
    for (int i = 0; i < 10; i++){
      dxl.setGoalPosition(7, (120 + 3 * i), UNIT_DEGREE);
      delay(100);
    }
    liftState2 = 0;
  }
  return;
}

void setup() {
  // put your setup code here, to run once:
  
  // For Uno, Nano, Mini, and Mega, use UART port of DYNAMIXEL Shield to debug.
  DEBUG_SERIAL.begin(115200);
  
  // Set Port baudrate to 57600bps. This has to match with DYNAMIXEL baudrate.
  dxl.begin(1000000);
  // Set Port Protocol Version. This has to match with DYNAMIXEL protocol version.
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);

  for (int i = 1; i <= torqueNumber; i++){
  // Get DYNAMIXEL information
  dxl.ping(i);
  // Turn off torque when configuring items in EEPROM area
  dxl.torqueOff(i);
  if (torqueMode[i-1])
   dxl.setOperatingMode(i, OP_VELOCITY);
  else
    dxl.setOperatingMode(i, OP_POSITION);
  dxl.torqueOn(i);
  }
  delay(1000);

  dxl.setGoalPosition(8, 240, UNIT_DEGREE);

  delay(500);
  
  dxl.setGoalPosition(4, 60, UNIT_DEGREE);

  delay(500);
  
  //dxl.setGoalPosition(3, 150, UNIT_DEGREE);

  //delay(500);
  
  //dxl.setGoalPosition(7, 150, UNIT_DEGREE);

  delay(2000);
  
}

// movement for 1 servo
void servo1(float duty){
  if (duty > 0) duty = duty - 100;
  else if (duty < 0) duty = -duty;
  dxl.setGoalVelocity(1, duty, UNIT_PERCENT);
}

void servo2(float duty) {
  if (duty < 0) duty = -duty - 100;
  dxl.setGoalVelocity(2, duty, UNIT_PERCENT);
}

void servo3(float duty){
  if (duty > 0) duty = duty - 100;
  else if (duty < 0) duty = -duty;
  dxl.setGoalVelocity(5, duty, UNIT_PERCENT);
}

void servo4(float duty) {
  if (duty < 0) duty = -duty - 100;
  dxl.setGoalVelocity(6, duty, UNIT_PERCENT);
}


void go_1(float leftDuty, float rightDuty) {
  servo1(leftDuty);
  servo2(rightDuty);
}

void go_2(float leftDuty, float rightDuty) {
  servo3(leftDuty);
  servo4(rightDuty);
}

void servo1_pid(float duty){
  if (duty > 0) duty = duty - 100;
  else if (duty < 0) duty = -duty;
  duty = pid(1, duty);
  DEBUG_SERIAL.println(dxl.getPresentVelocity(1, UNIT_DEGREE));
  dxl.setGoalVelocity(1, duty, UNIT_PERCENT);
}

void servo2_pid(float duty) {
  if (duty < 0) duty = -duty - 100;
  duty = pid(2, duty);
  dxl.setGoalVelocity(2, duty, UNIT_PERCENT);
}

void servo3_pid(float duty){
  if (duty > 0) duty = duty - 100;
  else if (duty < 0) duty = -duty;
  duty = pid(5, duty);
  dxl.setGoalVelocity(5, duty, UNIT_PERCENT);
}

void servo4_pid(float duty) {
  if (duty < 0) duty = -duty - 100;
  duty = pid(6, duty);
  dxl.setGoalVelocity(6, duty, UNIT_PERCENT);
}

void go_1_pid(float leftDuty, float rightDuty) {
  servo1_pid(leftDuty);
  servo2_pid(rightDuty);
}

void go_2_pid(float leftDuty, float rightDuty) {
  servo3_pid(leftDuty);
  servo4_pid(rightDuty);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  // Please refer to e-Manual(http://emanual.robotis.com) for available range of value. 
  // Set Goal Velocity using RAW unit
  //dxl.setGoalVelocity(2, 8, UNIT_PERCENT);
  //dxl.setGoalVelocity(1, -84, UNIT_PERCENT);
  //dxl.setGoalVelocity(3, 1, UNIT_PERCENT);
  //dxl.setGoalVelocity(4, 1, UNIT_PERCENT);
  
  //if (dxl.getPresentVelocity(8) < 200 )
 // reverse1();
  //if (dxl.getPresentVelocity(9) < 200 )
  //reverse2();
  //delay(2000);

  lift1();
  DEBUG_SERIAL.println("111111111111");
  delay(1000);
  desirePosition1 = positionDetection(4);
  while (liftState1 == 1){
    currentPosition1 = positionDetection(4);
    currentPosition2 = positionDetection(8);

    if (currentPosition1 < 75 && currentPosition1 > 55 && robotState1 == 0){
      DEBUG_SERIAL.println("5");
      robotState1 = 1;
      desirePosition2 = 225;
    }
    
    if (robotState1 == 0 && liftState1 == 1){
      go_1(-40, -20);
      DEBUG_SERIAL.println("7");
      DEBUG_SERIAL.println(dxl.getPresentVelocity(1, UNIT_DEGREE));
      go_2(1 ,1);
      if (currentPosition1 > 75){
        DEBUG_SERIAL.println(">65");
        desirePosition1 = desirePosition1 - 5;

        DEBUG_SERIAL.println(desirePosition1);}
      else if (currentPosition1 < 55){
        DEBUG_SERIAL.println("<55");
        desirePosition1 = desirePosition1 + 5;
      }
     positionControl(4,desirePosition1);
    }

    if (robotState1 == 1){
      go_1(40, 20);
      DEBUG_SERIAL.println(dxl.getPresentVelocity(1, UNIT_DEGREE));
      go_2(1, 1);
      DEBUG_SERIAL.println("8");
      
      desirePosition2 = desirePosition2 - 3;
     // if (desirePosition2 < 195)
       // desirePosition2 = 195;

      positionControl(8,desirePosition2);
    }

    if (currentPosition2 <= 195 && robotState1 == 1){
      go_1(1, 1);
      go_2(1, 1);
      lift1();
      DEBUG_SERIAL.println("6");
      robotState1 = 0;
    }
    delay(100);
  }

  lift2();
  DEBUG_SERIAL.println("22222222222222");
  delay(1000);
  
  desirePosition2 = positionDetection(8);
  
  while (liftState2 == 1){
    currentPosition1 = positionDetection(4);
    currentPosition2 = positionDetection(8);
    
    if (currentPosition2 < 245 && currentPosition2 > 225 && robotState2 == 0){
      robotState2 = 1;
      DEBUG_SERIAL.println("1");
      desirePosition1 = 75;
    }

    if (robotState2 == 0 && liftState2 == 1){
      DEBUG_SERIAL.println("3");
      go_1(1, 1);
      go_2(-20 ,-40);
      if (currentPosition2 > 245)
        desirePosition2 = desirePosition2 - 5;
      else if (currentPosition2 < 225)
        desirePosition2 = desirePosition2 + 5;
     positionControl(8,desirePosition2);
    }

    else if (robotState2 == 1){
      go_1(1, 1);
      go_2(20, 40);
      DEBUG_SERIAL.println("4");
      desirePosition1 = desirePosition1 + 3;
     
      positionControl(4,desirePosition1);
    
    }

    if (currentPosition1 > 115 && robotState2 == 1 ){
      go_1(1, 1);
      go_2(1, 1);
      lift2();
      DEBUG_SERIAL.println("2");
      robotState2 = 0;
    }

    delay(100);
  }
  
}