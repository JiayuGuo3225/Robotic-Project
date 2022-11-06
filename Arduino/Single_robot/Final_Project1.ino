#include <DynamixelShield.h>
#include <stdlib.h>
#include <math.h>
#if defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_MEGA2560)
  #include <SoftwareSerial.h>
  SoftwareSerial soft_serial(7, 8); // DYNAMIXELShield UART RX/TX
  #define DEBUG_SERIAL soft_serial
#elif defined(ARDUINO_SAM_DUE) || defined(ARDUINO_SAM_ZERO)
  #define DEBUG_SERIAL SerialUSB    
#else
  #define DEBUG_SERIAL Serial
#endif
const float DXL_PROTOCOL_VERSION = 2.0;
DynamixelShield dxl;

int total_legs=3;          //total_legs
uint8_t IDs[]={4,2,3,1};   //legs id (anchor is leg 1; helper leg is leg 2; bottom is leg 3)  


float angle;               //moter's angle
float T;                   //Time, a cycle is 15s
//test
float get_desired_angle( int leg, long elapsed ) { 
    T = fmod ( T , 10 );
  
    if ( leg == 0 ) {                      //left leg
      if ( T < 2.5 )
        angle = 110 + 24 * T;
      else if ( T >= 2.5 && T < 5 )
        angle = 170;
      else if ( T >= 5 && T < 7.5 )
        angle = 170 - 24 * ( T - 5);
      else if ( T >= 7.5 )
        angle = 110 ;
        }

    else if ( leg == 1 ) {                //helper leg
      if ( T < 2.5 )
        angle = 40 + 24* ( T );
      else if ( T >= 2.5 && T < 5 )
        angle = 100;
      else if ( T >= 5 && T < 7.5 )
        angle = 100 - 24 * ( T - 5) ;
      else if ( T >= 7.5 )
        angle = 40 ;
        }
        
    else {                                //bottom leg
      if ( T < 2.5 )
        angle = 270 ;
      else if ( T >= 2.5 && T < 5 )
        angle = 270 - 24 * ( T - 2.5 );
      else if ( T >= 5 && T < 7.5 )
        angle = 210 ;
      else if ( T >= 7.5 && T < 10 )
        angle = 210 + 24 * ( T - 7.5 );
        }

    return angle; 
  }

//electric magnet
void set_pwm() {
      dxl.setGoalPWM(4, 300);
      DEBUG_SERIAL.print("HELPER CONNECT ");
      delay(5000);
      
      for(int j=0;j<2000;j++){
        dxl.setGoalPosition(2, j/20, UNIT_DEGREE);
        DEBUG_SERIAL.print(j/20);
        }
      DEBUG_SERIAL.print("HELPER MOVED ");
      delay(5000);
      
      dxl.setGoalPWM(4, 0);
      DEBUG_SERIAL.print("HELPER END ");
      delay(5000);
      
      T=10;
  return;
}


void print_position(long t, int leg, float desired_pos ){
    DEBUG_SERIAL.print("the time is ");
    DEBUG_SERIAL.println(t/1000.0);
    DEBUG_SERIAL.print("the leg is ");
    DEBUG_SERIAL.println(leg);
    DEBUG_SERIAL.print("the desired position is ");
    DEBUG_SERIAL.println(desired_pos);
        
  return ;
}



long start;

void setup() {
  
  DEBUG_SERIAL.begin(115200);

  dxl.begin(1000000);
 
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);

  for (int i=0;i<=0;i++){
    dxl.torqueOff(IDs[i]);
    dxl.setOperatingMode(IDs[i], OP_POSITION);
    dxl.torqueOn(IDs[i]);
    delay(100);

//Initializing the motor
    dxl.setGoalPosition(1, 110, UNIT_DEGREE);
    dxl.setGoalPosition(2, 40, UNIT_DEGREE);
    dxl.setGoalPosition(3, 270, UNIT_DEGREE);
    delay(500);

//Reed switch
    pinMode(4, INPUT);      //set PD4 as digital input to catch reed switch
    pinMode(7, OUTPUT);     //set PD7 as digital output, because we don't have reed switch, so use this to simiulate reed switch output
  }

  start = millis();
}


long last_time=0;
int time_step=10;


void loop() {
  
  long elapsed = millis() - start;
  
  if (elapsed-last_time>time_step){
    last_time=elapsed;
    for (int i=0;i<total_legs;i++){
      T=T+0.005;
      float desired_pos=get_desired_angle(i,elapsed);
   
      print_position(elapsed, i,desired_pos);
      
      dxl.setGoalPosition(IDs[i], desired_pos, UNIT_DEGREE);


    

     
    }
    digitalWrite(7, HIGH);
    //if(digitalRead(4)==1)
    //set_pwm();
  }
  
}
