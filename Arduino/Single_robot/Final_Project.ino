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

int duty[] = {0, 0, 0, 0};
int backoff[] = {0, 0, 0, 0};
int backoffStatus[] = {0, 0, 0, 0};

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

void setup() {
  // put your setup code here, to run once:
  
  // For Uno, Nano, Mini, and Mega, use UART port of DYNAMIXEL Shield to debug.
  DEBUG_SERIAL.begin(115200);
  
  // Set Port baudrate to 57600bps. This has to match with DYNAMIXEL baudrate.
  dxl.begin(1000000);
  // Set Port Protocol Version. This has to match with DYNAMIXEL protocol version.
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
  // Get DYNAMIXEL information
  dxl.ping(8);
  dxl.ping(9);
  // Turn off torque when configuring items in EEPROM area
  dxl.torqueOff(8);
  dxl.setOperatingMode(8, OP_VELOCITY);
  dxl.torqueOn(8);
  dxl.torqueOff(9);
  dxl.setOperatingMode(9, OP_VELOCITY);
  dxl.torqueOn(9);

  delay(2000);
}

// movement for 1 servo
servo1(float duty){
  if (duty > 0) duty = duty - 100;
  else if (duty < 0) duty = -duty;
  dxl.setGoalVelocity(1, duty, UNIT_PERCENT);
}

servo2(float duty) {
  dxl.setGoalVelocity(2, duty, UNIT_PERCENT);
}

servo3(float duty){
  if (duty > 0) duty = duty - 100;
  else if (duty < 0) duty = -duty;
  dxl.setGoalVelocity(3, duty, UNIT_PERCENT);
}

servo4(float duty) {
  dxl.setGoalVelocity(4, duty, UNIT_PERCENT);
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
  dxl.setGoalVelocity(2, 8, UNIT_PERCENT);
  dxl.setGoalVelocity(1, -84, UNIT_PERCENT);
  dxl.setGoalVelocity(3, 1, UNIT_PERCENT);
  dxl.setGoalVelocity(4, 1, UNIT_PERCENT);
  
  //if (dxl.getPresentVelocity(8) < 200 )
 // reverse1();
  //if (dxl.getPresentVelocity(9) < 200 )
  //reverse2();
  delay(2000);

  currentSpeed[0] =  dxl.getPresentVelocity(1);
  currentSpeed[1] =  dxl.getPresentVelocity(2);
  currentSpeed[2] =  dxl.getPresentVelocity(3);
  currentSpeed[3] =  dxl.getPresentVelocity(4);

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

  dxl.setGoalVelocity(2, -95, UNIT_PERCENT);
  dxl.setGoalVelocity(1, 15, UNIT_PERCENT);
  dxl.setGoalVelocity(3, 1, UNIT_PERCENT);
  dxl.setGoalVelocity(4, 1, UNIT_PERCENT);
  go_1(5, 15);
  go_2(1, 1);


  // Print present velocity
 // DEBUG_SERIAL.print("Present Velocity(raw8) : ");
  //DEBUG_SERIAL.println(dxl.getPresentVelocity(8));
   //DEBUG_SERIAL.print("Present Velocity(raw9) : ");
  //DEBUG_SERIAL.println(dxl.getPresentVelocity(9));
  delay(1000);

  dxl.setGoalVelocity(4, 16, UNIT_PERCENT);
  dxl.setGoalVelocity(3, -92, UNIT_PERCENT);
  dxl.setGoalVelocity(1, 1, UNIT_PERCENT);
  dxl.setGoalVelocity(2, 1, UNIT_PERCENT);
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