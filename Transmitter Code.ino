#include <RH_ASK.h>  //include radiohead library
#include<LiquidCrystal.h> //include liquid crystal library

LiquidCrystal lcd(8, 6, 5, 4, 3, 2);  // sets the interfacing pins // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7) //

RH_ASK driver;   //creating object driver of class
char buffer[24];  // setting buffer size length
int temp; 
int in = 9;
int i=0,k=0,rate=0;

unsigned long time2,time1;
unsigned long time;


void setup()
{ pinMode(in, INPUT);  //make pin 9 as input pin
 
 lcd.begin(16,2);  //initialize 16*2 lcd display
 
  delay(500);
  Serial.begin(9600);   //set up serial monitor
  if (!driver.init()) // Debugging only
    Serial.println("init failed");
}

void loop()
{

    k=0;
    while(k<7)  // description given above.
    {
     if(digitalRead(in))
     {
      if(k==0)
      time1=millis();
      k++;
      while(digitalRead(in));
     }
    }
      time2=millis();
      rate=time2-time1;
      rate=rate/5;
      rate=60000/rate;  // here we are getting heart rate 


     temp = analogRead(A2);
    int mv=(temp/1024.0)*5000;
    int cel=mv/10;   // here we are getting temperature in celsius

      

      lcd.setCursor(0,0);
      lcd.print("HeartRate=");
      
      lcd.print(rate);  //printing heart rate to the lcd display
        lcd.print("_BPM");
      lcd.setCursor(0,1);
      lcd.print("Temp=");
      lcd.print(cel);   //printing temperature to lcd display
      lcd.print(" *C");
      delay(1000);
   
  sprintf(buffer, "%d,%d", rate,cel);  // converting integer to string; as we cannot transmit integer directly through network 
  
  driver.send((uint8_t *)buffer, strlen(buffer)); 
  driver.waitPacketSent();
  delay(500);
   
      Serial.println((char*)buffer);



}
