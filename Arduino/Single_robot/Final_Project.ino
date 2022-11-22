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
//
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

const uint8_t DXL_ID = 3;
const float DXL_PROTOCOL_VERSION = 2.0;

DynamixelShield dxl;

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
  
  dxl.setGoalVelocity(2, -95, UNIT_PERCENT);
  dxl.setGoalVelocity(1, 15, UNIT_PERCENT);
  dxl.setGoalVelocity(3, 1, UNIT_PERCENT);
  dxl.setGoalVelocity(4, 1, UNIT_PERCENT);
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
  delay(2000);

  dxl.setGoalVelocity(4, -85, UNIT_PERCENT);
  dxl.setGoalVelocity(3, 5, UNIT_PERCENT);
  dxl.setGoalVelocity(1, 1, UNIT_PERCENT);
  dxl.setGoalVelocity(2, 1, UNIT_PERCENT);
  delay(1000);
  
}
