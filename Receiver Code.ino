


 
// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library 
#include <SPI.h> 
#include <LiquidCrystal.h>

 
// Create Amplitude Shift Keying Object
LiquidCrystal lcd(8, 6 , 5, 4, 3, 2);  // sets the interfacing pins // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7) //
RH_ASK rf_driver;
 
char StringReceived[22];   //setting maximum string length
int a,b;
void setup()
{
   
    lcd.setCursor(0,0);    
    delay(100);

    lcd.begin(16,2);    //initializing LCD 16*2 display
    rf_driver.init();      //calling class driver initialization function
    
    Serial.begin(9600);    // Setup Serial Monitor
}
 
void loop()
{   
    
   
    uint8_t buf[24];    // Set buffer to size of expected message
    uint8_t buflen = sizeof(buf);
   
    if (rf_driver.recv(buf, &buflen))    // Check if received packet is correct size
    {
       
 int i;
        // Message with a good checksum received, dump it. 
        for (i = 0; i < buflen; i++)
 {            
              
          StringReceived[i] = char(buf[i]);  // chars from buffer. 
 }
 
      sscanf(StringReceived, "%d,%d",&a,&b); // Converts a string to an array
         
        // Turn off light to and await next message 
      Serial.println(StringReceived);  //printing received string to serial monitor
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("HeartRate=");
      
      lcd.print(a);          //printing the value of heart beat to LCD
        lcd.print("_BPM");
      lcd.setCursor(0,1);
      lcd.print("Temp=");
      lcd.print(b);           //printing the value temperature to the lcd
      lcd.print(" *C");
      
 
    }
     
 memset( StringReceived, 0, sizeof( StringReceived));// This line is for reset the StringReceived

    

}
