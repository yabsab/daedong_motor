
#include <ModbusMaster.h>

ModbusMaster motordrive_right;

void setup() 

{
  Serial.begin(115200);
  Serial2.begin(115200);

  motordrive_right.begin(1,Serial2);  //Serial1은 19번(Rx)과 18번(Tx)
  motordrive_right.writeSingleRegister(0x0078,0x0001);
 
//  motordrive_left.begin(3,Serial3); //Serial3는 15번(Tx)과 14번(Rx)
//  motordrive_left.writeSingleRegister(0x0078,0x0001);
//    
}

  void loop()
  { 

     motordrive_right.begin(1,Serial2);  //Serial1은 19번(Rx)과 18번(Tx)
     motordrive_right.writeSingleRegister(0x0078,0x0001);
     Serial.print("test");
//    uint8_t result_Right;
//   // uint8_t result_Left;            
//    char InChar;
//    
//    InChar = Serial.read();
//      switch(InChar)      
//      {    
//        
//         case 'w':
//           goLow();
//           Serial.print("golow\n");
//           
//         break;
//         
//         case '1':
//           goMid();
//           Serial.print("gomid\n");
//         break;
//         
//         case '2':
//           goHigh();
//           Serial.print("gohigh\n"); 
//         break;
//                 
//         case 's':
//           stopMotor();
//           Serial.print("stop\n");
//         break;
//         
//         default:
//         //stopMotor();  
//        break;
//      }
//   //delay(1000);
//  //  }
//  
   
  }

  void goLow()
  {
    //go_1000rpm     
     //motordrive_left.writeSingleRegister(0x0079,0xFC18);
     motordrive_right.writeSingleRegister(0x0079,0x03E8);    
     
  }
  
    void goMid()
    {
      //go_2000rpm       
         motordrive_right.writeSingleRegister(0x0079,0x07D0);     
       //  motordrive_left.writeSingleRegister(0x0079,0xF81B);  
    }
    
    void goHigh()
    {
        //go_3000rpm        
       motordrive_right.writeSingleRegister(0x00079,0x0BB8);
    //   motordrive_left.writeSingleRegister(0x0079,0xF448);
    }
  
    void stopMotor()
    {
      //go_1000rpm     
       motordrive_right.writeSingleRegister(0x0079,0x0000);    
      // motordrive_left.writeSingleRegister(0x0079,0x0000);
    }      

//    void readSpeed()
//    {      
//      uint16_t leftmotorspeed;
//      uint16_t rightmotorspeed;
//      
//      motordrive_left.readInputRegisters(0x0003,0x0004);
//      motordrive_right.readInputRegisters(0x0003,0x0004);
//      leftmotorspeed = motordrive_left.getResponseBuffer(0);
//      rightmotorspeed = motordrive_right.getResponseBuffer(0);
//
//      Serial.print("leftmotorspeed : ");
//      Serial.print(leftmotorspeed);
//      Serial.print("\n");
//
//      Serial.print("rightmotorspeed : ");
//      Serial.print(rightmotorspeed);
//      Serial.print("\n");
//     
//     
//     
//      motordrive_right.clearResponseBuffer();
//      motordrive_left.clearResponseBuffer();
//                     
//    }

  
