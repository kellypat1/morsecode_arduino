#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
#include <AltSoftSerial.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows 
AltSoftSerial BTserial; 
 
// Variables used for incoming data
String data; 
char ch;
const byte maxDataLength = 20;          // maxDataLength is the maximum length allowed for received data.
char receivedChars[maxDataLength+1] ;
boolean newData = false;               // newData is used to determine if there is a new command
const int buzzer = 2; 
const int led=3;
int motorPin = 13; 
int flag=0;
boolean DEBUG = true;               // Change DEBUG to true to output debug information to the serial monitor
void setup()  
{
   
    pinMode(led, OUTPUT); 
    pinMode(buzzer, OUTPUT);
    pinMode(motorPin,OUTPUT);
    digitalWrite(led,LOW);
    lcd.init();                
    lcd.backlight();
    lcd.begin(16,2); 
    lcd.setCursor(0,0);    lcd.print("Morse code"); 
    lcd.setCursor(0,1);    lcd.print("Starting..."); 
    delay(10000);
    lcd.clear();
    lcd.setCursor(0, 0);   lcd.print("Morse decoder");
    
    if (DEBUG)
    {
        // open serial communication for debugging and show the sketch name and the date compiled
        Serial.begin(9600);
        Serial.println(__FILE__);
        Serial.println(__DATE__);
        Serial.println(" ");
    }
 
    //  open software serial connection to the Bluetooth module.
    BTserial.begin(9600); 
    if (DEBUG)  {   Serial.println(F("AltSoftSerial started at 9600"));     }
    //no new command
    newData = false;
 
} 
 
 
void loop()  
{
      
         lcd.setCursor(0, 1);                   
         recvWithStartEndMarkers();                // check to see if we have received any new commands
         if (newData)  {   processCommand();
         }    // if we have a new command do something
}
 
 
void processCommand()
{
    newData = false;
    if (DEBUG)  {   Serial.print("recieved data = ");  Serial.println(receivedChars);         }
    //if the new command is "MORSEON"
    if      (strcmp ("MORSEON",receivedChars) == 0)  {
      digitalWrite(led,HIGH);                 //led is turn on
      tone(buzzer,1000 );                     //passive buzzer is turn on
      digitalWrite(motorPin, HIGH);           //vibration motor is turn on
    }
    // if the new command is "MORSEOFF"
    else if (strcmp ("MORSEOFF",receivedChars) == 0) { 
      digitalWrite(3,LOW);                   //led is turn off
      noTone(buzzer);                        //passive buzzer is turn off
      digitalWrite(motorPin, LOW);           //vibration motor is turn off
    }
    // the new command is the characters 
    else  {
      data+=receivedChars;
      lcd.print(data);                      //print the characters in the second row
      flag+=1;
      if(flag==16){                         //if the received characters are 16
        lcd.clear();                        //delete the characters of the second row of lcd
        lcd.setCursor(0, 0);                // set the cursor in first row
        lcd.print("Morse decoder");
        lcd.setCursor(0, 1);                //set cursor in second row
        flag=0;                             //start again
        data="";
      }
      
      
}

}
 
// function recvWithStartEndMarkers by Robin2 of the Arduino forums
// See  http://forum.arduino.cc/index.php?topic=288234.0
void recvWithStartEndMarkers() 
{
     static boolean recvInProgress = false;
     static byte ndx = 0;
     char startMarker = '<';
     char endMarker = '>';
 
     if (BTserial.available() > 0) 
     {
          char rc = BTserial.read();
          if (recvInProgress == true) 
          {
               if (rc != endMarker) 
               {
                    if (ndx < maxDataLength) { receivedChars[ndx] = rc; ndx++;  }
               }
               else 
               {
                     receivedChars[ndx] = '\0'; // terminate the string
                     recvInProgress = false;
                     ndx = 0;
                     newData = true;
                     
               }
          }
          else if (rc == startMarker) { recvInProgress = true; }
     }
}
