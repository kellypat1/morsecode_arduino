#include <AltSoftSerial.h>
AltSoftSerial BTserial; 
boolean DEBUG = true;
const byte maxDataLength = 20;
char receivedChars[21] ;
// MorsceTable from Achindra Bhatnagar for create.arduino.cc
const char* MorseTable[] = {
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
        // space, !, ", #, $, %, &, '
        NULL, "-.-.--", ".-..-.", NULL, NULL, NULL, NULL, ".----.",
        // ( ) * + , - . /
        "-.--.", "-.--.-", NULL, ".-.-.", "--..--", "-....-", ".-.-.-", "-..-.",
        // 0 1 2 3 4 5 6 7
        "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...",
        // 8 9 : ; < = > ?
        "---..", "----.", "---...", "-.-.-.", NULL, "-...-", NULL, "..--..",
        // @ A B C D E F G
        ".--.-.", ".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
        // H I J K L M N O
        "....", "..", ".---", "-.-", ".-..", "--", "-.", "---",
        // P Q R S T U V W
        ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--",
        // X Y Z [ \ ] ^ _
        "-..-", "-.--", "--..", NULL, NULL, NULL, NULL, "..--.-",
        // ' a b c d e f g
        NULL, ".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
        // h i j k l m n o
        "....", "..", ".---", "-.-", ".-..", "--", "-.", "---",
        // p q r s t u v w
        ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--",
        // x y z { | } ~ DEL
        "-..-", "-.--", "--..", NULL, NULL, NULL, NULL, NULL,
        };
// Variables used 
int dotLength = 50;                  //lenght for "." is 50ms
int dashLength = dotLength*3;       // lenght for "-" is 150ms
boolean newData = false;            // newData is used to determine if there is a new command
void setup() { 
  if (DEBUG)
    {
        // open serial communication for debugging and show 
        // the sketch filename and the date compiled
        Serial.begin(9600);
        Serial.println(__FILE__);
        Serial.println(__DATE__);
        Serial.println(" ");
    }
 
    //  open software serial connection to the Bluetooth module.
    BTserial.begin(9600); 
    if (DEBUG)  {   Serial.println("BTserial started at 9600");     }
    newData = false;
}

void loop() {
  char ch;
  if(Serial.available()){
    ch = Serial.read();             //if characters have been sent
    BTserial.print("<");  BTserial.print( ch ); BTserial.print(">");
  }
    flashDashDot(MorseTable[ch]);
    delay(dotLength*2);
}

void flashDashDot(const char * morseCode)
{
  int i = 0;
  while(morseCode[i] != 0)
  {
    if(morseCode[i] == '.'){        
      dot();                   //go to the dot function
    } else if (morseCode[i] == '-'){
      dash();                 //go to the dash function
    }
    i++;                      //go to the next character
  }
}

void dot()
{
  BTserial.println("<MORSEON>");              //sent "MORSEON" to Arduino in slave mode
  if (DEBUG) {Serial.println("MORSEON command sent");}   
  delay(dotLength);
  BTserial.println("<MORSEOFF>");            //sent "MORSEOFF" to Arduino in slave mode
  if (DEBUG) {Serial.println("MORSEOFF command sent");}  
  delay(dotLength);
}

void dash()
{
  BTserial.println("<MORSEON>");            //sent "MORSEON" to Arduino in slave mode
  if (DEBUG) {Serial.println("MORSEON command sent");}  
  delay(dashLength);
  BTserial.println("<MORSEOFF>");           //sent "MORSEOFF" to Arduino in slave mode
  if (DEBUG) {Serial.println("MORSEOFF command sent");}  
  delay(dotLength);
}
