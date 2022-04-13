
//Pin connected to pin 1 of MAX7219 Orange
#define dataPin A2
//Pin connected to pin 12 of MAX7219 White
#define latchPin A1
//Pin connected to pin 13 of MAX7219 Yellow
#define clockPin A0

#include "MAX7219.h"
#include <Wire.h>
#include <SparkFun_Alphanumeric_Display.h> //Click here to get the library: http://librarymanager/All#SparkFun_Qwiic_Alphanumeric_Display by SparkFun
  HT16K33 display;
#include <SparkFun_Qwiic_Keypad_Arduino_Library.h>
KEYPAD keypad1; //Create instance of this object

void displayTEST(){
  display.print("88:8.8");
  delay(1000);
  display.clear();     
}


char button = ' '; //Button '0' to '9' and '*' and '#'
char button1 = ' '; //Button '0' to '9' and '*' and '#'
char button2 = ' '; //Button '0' to '9' and '*' and '#'
char button3 = ' '; //Button '0' to '9' and '*' and '#'
char button0 = ' '; //Button '0' to '9' and '*' and '#'
void setup() {
  // put your setup code here, to run once:
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  
  Serial.begin(9600);//Start Serial UART at 115200 Baud
  
  Wire.begin(); //Join I2C bus
  if (display.begin() == false){
    Serial.println("Device did not acknowledge! Freezing.");
    while (1){
      digitalWrite(LED_BUILTIN,HIGH);
      delay(200);
      digitalWrite(LED_BUILTIN,LOW);
      delay(200);
    }
  }
  Serial.println("Display acknowledged.");
  if (keypad1.begin() == false)
  {
    Serial.println("Keypad does not appear to be connected. Please check wiring. Freezing...");
    while (1);
  }
  Serial.print("Initialized. Firmware Version: ");
  Serial.println(keypad1.getVersion());
  Serial.println("Press a button: * to do a space. # to go to next line.");

  
  //writeMAX7219(latchPin,clockPin,dataPin,address,data)
  DisplayTest();
  displayTEST();//Test the alpha numeric display display
  DisplayINIT();
  display.clear();
//  Serial.println("Welcome to the Arduino Map System.\n The builtin key pad is not yet installed.\nPlease Use the Serial Console to communicate.");
//  Serial.println("Commands:\nMAXNumber to Print a number to the MAX right aligned.\n")
}

void loop() {
  // put your main code here, to run repeatedly:
  keypad1.updateFIFO();  // necessary for keypad to pull button from stack to readable register
  button = keypad1.getButton();
  if(button == 0)
  {
    Serial.println("No button has been pressed.");
  }
  else if(button == '#')
  {
//    writeMAX7219(latchPin,clockPin,dataPin,address,data)
    writeMAX7219(latchPin,clockPin,dataPin,0x04,button0);//Write BLANK to digit 3
    writeMAX7219(latchPin,clockPin,dataPin,0x03,button1);//Write BLANK to digit 2
    writeMAX7219(latchPin,clockPin,dataPin,0x02,button2);//Write BLANK to digit 1
    writeMAX7219(latchPin,clockPin,dataPin,0x01,button3);//Write BLANK to digit 0
  }
  else if(button == '*')
  {
//    writeMAX7219(latchPin,clockPin,dataPin,address,data)
    writeMAX7219(latchPin,clockPin,dataPin,0x04,0x0f);//Write BLANK to digit 3
    writeMAX7219(latchPin,clockPin,dataPin,0x03,0x0f);//Write BLANK to digit 2
    writeMAX7219(latchPin,clockPin,dataPin,0x02,0x0f);//Write BLANK to digit 1
    writeMAX7219(latchPin,clockPin,dataPin,0x01,0x0f);//Write BLANK to digit 0
    display.clear();
    button = ' '; button1 = ' '; button2 = ' ';button3 = ' ';button0 = ' ';
  }
  else 
  {
    button3=button2;
    button2=button1;
    button1=button0;
    button0=button;
    display.print(String(button3)+String(button2)+String(button1)+String(button0));
    //Serial.println("Button '" + String(button) + "' was pressed " + String(timeSincePressed) + " milliseconds ago.");
  }
  
  
}
