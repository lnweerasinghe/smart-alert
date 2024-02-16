#include "EmonLib.h"             
#define VOLT_CAL 592
#include <SoftwareSerial.h>


SoftwareSerial mySerial(7,8); 


int offset =20;


EnergyMonitor emon1;             
bool flag = 0;

void setup()
{  
  Serial.begin(9600);
  mySerial.begin(9600);
  

  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(11,OUTPUT);
  emon1.voltage(1, VOLT_CAL, 1.7);  
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
}

void loop()
{

  int volt = analogRead(A0);// read the input
  double voltage = map(volt,0,1023, 0, 2500) + offset;
  
  voltage /=100;
  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.println("V");


//partition3
 /*emon1.calcVI(25,1000);         
  
  float supplyVoltage   = emon1.Vrms;            
  if(supplyVoltage >= 100)
  {
    flag = 0;
 Serial.print("Voltage : ");  
 Serial.println(supplyVoltage);
 
  }
  else if((supplyVoltage < 100) && (flag == 0))
 {
  flag = 1;
    led3();
   Serial.println("Power OFF ac");
  }*/
  emon1.calcVI(25,1000);         
  
  float supplyVoltage   = emon1.Vrms;            
  //relay 5/1=dc,6/2=ac
    if(supplyVoltage >= 100){
       digitalWrite(6, LOW);// turn relay 2 ON
       digitalWrite(5, HIGH);// turn relay 1 OFF
      }
    else if((supplyVoltage < 100) && (voltage >= 11.5)){
       digitalWrite(5, LOW);// turn relay 1 ON
       digitalWrite(6, HIGH);// turn relay 2 OFF
      }
    else if((supplyVoltage < 100) && (voltage < 11.5)){
      digitalWrite(5, HIGH);// turn relay 1 off
      digitalWrite(6, HIGH);// turn relay 2 OFF
      }
  //relay
  
  if((supplyVoltage >= 100)  && (flag == 0))
  {
    flag = 1;
    //led1();
    sendSMS1();
    
 Serial.print("Voltage : ");  
 Serial.println(supplyVoltage);
 
  }
  else if((supplyVoltage < 100))
 {
  flag = 0;
  Serial.println("Power OFF"); 
  led3();
  sendSMS3();
//partition3
  
  /*if((voltage >= 2) && (flag == 0))//it's garbage
  {
    //flag = 1;
    //led1();
    
   /*do {
    led1();
    
    } while (voltage < 2);*/
 
 //}*/
  if(voltage >= 11.5)//it's garbage
  {
    //flag = 1;
    //led1();
    //new code

     
      if((voltage >= 11.5) && (j == 0)){
         Serial.println("hello");
         
        }
       else if((voltage >= 11.5) && (j > 0)){
        Serial.println("inf");
        delay(500);

        int volt = analogRead(A0);// read the input
  double voltage = map(volt,0,1023, 0, 2500) + offset;
  
  voltage /=100;// divide by 100 to get the decimal values
  Serial.print("Voltage: ");
  Serial.print(voltage);//print the voltge
  Serial.println("V");

//partition2
  emon1.calcVI(25,1000);         
  
  float supplyVoltage   = emon1.Vrms;             
  if(supplyVoltage >= 100)
  {
 Serial.print("Voltage : ");  
 Serial.println(supplyVoltage);
 
  }
  else
 {
   Serial.println("Power OFF ac");
  }
//partition2  

        if((voltage >= 11.5) && (supplyVoltage >= 100)){
         // int i =-2;
        break;
        }

       else if(/*(*/voltage < 11.5) /*&& (supplyVoltage >= 100))*/{
         // int i =-2;
        break;
        }
        
        }
        
        // else if((voltage >= 2)){
         // int i =-2;
        //break;
        //}
        
        
      }
   Serial.println("Power OFF");
    
    //new code
   /*do {
    led1();
    
    } while (voltage < 2);*/
 
 }
 
  else if(voltage < 11.5)
 {
    //flag = 0;

    
         led2();
         sendSMS2();
        
       else if((voltage < 11.5) && (i > 0)){
        Serial.println("inf");
        delay(500);

        int volt = analogRead(A0);
  double voltage = map(volt,0,1023, 0, 2500) + offset;
  
  voltage /=100;
  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.println("V");

//partition2
  emon1.calcVI(25,1000);         
  float supplyVoltage   = emon1.Vrms;            
  if(supplyVoltage >= 100)
  {
 Serial.print("Voltage : ");  
 Serial.println(supplyVoltage);
 
  }
  else
 {
   Serial.println("Power OFF ac");
  }
//partition2  

        if((voltage >= 11.5) && (supplyVoltage >= 100)){
         // int i =-2;
        break;
        }

       else if((voltage < 11.5) && (supplyVoltage >= 100)){
         // int i =-2;
        break;
        }
        
        }
        
        // else if((voltage >= 2)){
         // int i =-2;
        //break;
        //}
        
        
      }
   Serial.println("Power OFF");
       

  }

 
  }
  delay(500);
  //partition
  
 /* emon1.calcVI(25,1000);        
  
  float supplyVoltage   = emon1.Vrms;             
  if(supplyVoltage >= 100)
  {
 Serial.print("Voltage : ");  
 Serial.println(supplyVoltage);
 
  }
  else
 {
   Serial.println("Power OFF");
  }*/
 }

 void led1(){
    digitalWrite(13,HIGH);
    delay(2000);
    digitalWrite(13,LOW);
    delay(2000);    
  }
void led2(){
    digitalWrite(12,HIGH);
    delay(2000);
    digitalWrite(12,LOW);
    delay(2000);    
  }
void led3(){
    digitalWrite(11,HIGH);
    delay(2000);
    digitalWrite(11,LOW);
    delay(2000);    
  }
void sendSMS1() {
  Serial.println("Initializing..."); 
  delay(1000);

  mySerial.println("AT"); 
  updateSerial();

  mySerial.println("AT+CMGF=1");
  updateSerial();
  mySerial.println("AT+CMGS=\"+94702002122\"");
  updateSerial();
  mySerial.println("Duwa road madam's pond | MAIN CURRENT ON"); 
  updateSerial();
  mySerial.write(26);
  
  
}
void sendSMS2() {
  Serial.println("Initializing..."); 
  delay(1000);

  mySerial.println("AT"); 
  updateSerial();

  mySerial.println("AT+CMGF=1"); 
  updateSerial();
  mySerial.println("AT+CMGS=\"+94702002122\"");
  updateSerial();
  mySerial.println("Duwa road madam's pond | BATTERY PACK CUT OFF"); 
  updateSerial();
  mySerial.write(26);
  
  
}
void sendSMS3() {
  Serial.println("Initializing..."); 
  delay(1000);

  mySerial.println("AT");

  mySerial.println("AT+CMGF=1"); 
  
  mySerial.println("AT+CMGS=\"+94702002122\"");
  mySerial.println("Duwa road madam's pond | MAIN CURRENT OFF"); 

  mySerial.write(26);
  
  
}



 
