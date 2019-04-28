#include <RH_ASK.h>
#include<LiquidCrystal.h>
// sets the interfacing pins // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7) //
LiquidCrystal lcd(8, 6, 5, 4, 3, 2);  // sets the interfacing pins // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7) //

RH_ASK driver;
char buffer[24];
int temp;
int in = 9;
int i=0,k=0,rate=0;

unsigned long time2,time1;
unsigned long time;


void setup()
{ pinMode(in, INPUT);
 
 lcd.begin(16,2);
 
  delay(500);
  Serial.begin(9600);   // Debugging only
  if (!driver.init())
    Serial.println("init failed");
}

void loop()
{

    k=0;
    while(k<7)
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
      rate=60000/rate;  


     temp = analogRead(A2);
    int mv=(temp/1024.0)*5000;
    int cel=mv/10;

      

      lcd.setCursor(0,0);
      lcd.print("HeartRate=");
      
      lcd.print(rate);
        lcd.print("_BPM");
      lcd.setCursor(0,1);
      lcd.print("Temp=");
      lcd.print(cel);
      lcd.print(" *C");
      delay(1000);
   
  sprintf(buffer, "%d,%d", rate,cel);
  
    lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("HeartRate=");
      
      lcd.print(rate);
        lcd.print("_BPM");
      lcd.setCursor(0,1);
      lcd.print("Temp=");
      lcd.print(cel);
      lcd.print(" *C");
      delay(1000);
  driver.send((uint8_t *)buffer, strlen(buffer)); 
  driver.waitPacketSent();
  delay(500);
   
      Serial.println((char*)buffer);



}
