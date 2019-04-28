


 
// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library 
#include <SPI.h> 
#include <LiquidCrystal.h>

 
// Create Amplitude Shift Keying Object
LiquidCrystal lcd(8, 6 , 5, 4, 3, 2);  // sets the interfacing pins // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7) //
RH_ASK rf_driver;
 
char StringReceived[22];
int a,b;
void setup()
{
   
    lcd.setCursor(0,0);

    
    delay(100);

    lcd.begin(16,2);
    rf_driver.init();
    // Setup Serial Monitor
    Serial.begin(9600);
}
 
void loop()
{   
    // Set buffer to size of expected message
   
    uint8_t buf[24];
    uint8_t buflen = sizeof(buf);
    // Check if received packet is correct size
    if (rf_driver.recv(buf, &buflen))
    {
       
 int i;
        // Message with a good checksum received, dump it. 
        for (i = 0; i < buflen; i++)
 {            
          // Fill Sensor1CharMsg Char array with corresponding 
        
                   
          // chars from buffer.   
          StringReceived[i] = char(buf[i]);
 }
 
      sscanf(StringReceived, "%d,%d",&a,&b); // Converts a string to an array
         
        // Turn off light to and await next message 
      Serial.println(StringReceived);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("HeartRate=");
      
      lcd.print(a);
        lcd.print("_BPM");
      lcd.setCursor(0,1);
      lcd.print("Temp=");
      lcd.print(b);
      lcd.print(" *C");
      
 
    }
     
 memset( StringReceived, 0, sizeof( StringReceived));// This line is for reset the StringReceived

    

}
