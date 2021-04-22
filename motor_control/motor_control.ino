
#include <ModbusMaster.h>
#include <Wire.h> 
#include "Adafruit_TCS34725.h"


ModbusMaster motordrive_left;
ModbusMaster motordrive_right;

Adafruit_TCS34725 TCS = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup()
{
  

  Serial.begin(115200);
  Serial1.begin(115200);
  Serial3.begin(115200);

  motordrive_right.begin(5,Serial1); 
  motordrive_right.writeSingleRegister(0x0078,0x0001);
  
  motordrive_left.begin(3,Serial3);
  motordrive_left.writeSingleRegister(0x0078,0x0001);
     

//   if (!TCS.begin()) 
//   {
//    Serial.println("No TCS34725 found ... check your connections"); 
//    while (1);       
//    }
//     else 
//     {             
//       Serial.println("Found sensor");
//     } 
     
}

  void loop()
  { 
    uint8_t result_Right;
    uint8_t result_Left;            
    char InChar;
    
    InChar = Serial.read();

    result_Left = motordrive_left.readInputRegisters(0x0078, 16);
    result_Right = motordrive_right.readInputRegisters(0x0078, 16);

    uint16_t clear, red, green, blue;
    TCS.getRawData(&red, &green, &blue, &clear);
    
    int r = map(red, 0, 21504, 0, 1025);    // 빨간색 데이터 값
    int g = map(green, 0, 21504, 0, 1025);  // 초록색 데이터 값
    int b = map(blue, 0, 21504, 0, 1025); 

     Serial.print("   R: "); 
     Serial.print(r);        // 시리얼 모니터에 빨간색 값 출력 
     Serial.print("   G: "); 
     Serial.print(g);        // 시리얼 모니터에 초록색 값 출력 
     Serial.print("   B: "); 
     Serial.println(b);      // 시리얼 모니터에 파란색 값 출력     
    
     readSpeed();

      //드라이버 2개중 1 또는 0개 켜졌을 경우 예외처리 
//    if (if (result_Left == motordrive_left.ku8MBSuccess || result_Right == motordrive_right.ku8MBSuccess)
//    {
//      motordrive_left.writeSingleRegister(0x0078,0x0001);
//      motordrive_right.writeSingleRegister(0x0078,0x0001);  
//    }
    
    if (result_Left == motordrive_left.ku8MBSuccess || result_Right == motordrive_right.ku8MBSuccess)
    { 
      Serial.print("motor_on\n");
    
  switch(InChar)      
      {    
        
         case 'w':
           goLow();
           Serial.print("golow\n");
           
         break;
         
         case '1':
           goMid();
           Serial.print("gomid\n");
         break;
         
         case '2':
           goHigh();
           Serial.print("gohigh\n"); 
         break;
                 
         case 's':
           stopMotor();
           Serial.print("stop\n");
         break;
         
         default:
         //stopMotor();  
        break;
      }
      
//      
//      if(r>b && r>g)
//      {
//        stopMotor();
//        Serial.print("motor_stop\n");
//        
//      }
//    
//      else if (b>r && b>g)
//      {
//        goHigh();
//        Serial.print("golow\n");
//        
//      }
//
//      else if (g>r && g>b)
//      {
//        goLow();
//        Serial.print("High\n");
//        
//      }
//
//      else 
//      {
//        stopMotor();
//        Serial.print("motor_stop\n");
//        
//      }
    }
  }

  void goLow()
  {
    //go_1000rpm     
     motordrive_right.writeSingleRegister(0x0079,0xFC18);    
     motordrive_left.writeSingleRegister(0x0079,0x03E8);
  }
  
    void goMid()
    {
      //go_2000rpm       
       motordrive_right.writeSingleRegister(0x0079,0xF81B);     
       motordrive_left.writeSingleRegister(0x0079,0x07D0);  
    }
    
    void goHigh()
    {
        //go_3000rpm        
        motordrive_right.writeSingleRegister(0x00079,0xF448);
        motordrive_left.writeSingleRegister(0x0079,0x0BB8);
    }
  
    void stopMotor()
    {
      //go_1000rpm     
       motordrive_right.writeSingleRegister(0x0079,0x0000);    
       motordrive_left.writeSingleRegister(0x0079,0x0000);
    }      

    void readSpeed()
    {      
      uint16_t leftmotorspeed;
      uint16_t rightmotorspeed;
      
      motordrive_left.readInputRegisters(0x0003,0x0004);
      motordrive_right.readInputRegisters(0x0003,0x0004);
      leftmotorspeed = motordrive_left.getResponseBuffer(0);
      rightmotorspeed = motordrive_right.getResponseBuffer(0);

      Serial.print("leftmotorspeed : ");
      Serial.print(leftmotorspeed);
      Serial.print("\n");

      Serial.print("rightmotorspeed : ");
      Serial.print(rightmotorspeed);
      Serial.print("\n");
     
     
     
      motordrive_right.clearResponseBuffer();
      motordrive_left.clearResponseBuffer();
                     
    }
  
