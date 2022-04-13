void writeMAX7219(int LATCH,int CLOCK,int DATA,byte Address,byte Command);
void DisplayTest();
void DisplayINIT();

void writeMAX7219(int LATCH,int CLOCK,int DATA,byte Address,byte Command){
  digitalWrite(LATCH, LOW);//the chip admits data when latch is low
  digitalWrite(CLOCK, LOW);//the chip stores data on the rising clock edge
  //shiftOut(dataPin, clockPin, bitOrder, value)
  shiftOut(DATA, CLOCK, MSBFIRST, Address);
  shiftOut(DATA, CLOCK, MSBFIRST, Command);
  digitalWrite(LATCH, HIGH);//the chip stores data when latch rises
}

void DisplayTest(){
  writeMAX7219(latchPin,clockPin,dataPin,0x0F,0x01);//Display Test mode ON
  delay(1000);
  writeMAX7219(latchPin,clockPin,dataPin,0x0F,0x00);//Display Test mode OFF
}

void DisplayINIT(){ //sets the MAX7219 to recieve and display numbers
  writeMAX7219(latchPin,clockPin,dataPin,0x0C,0x00);//Shutdown mode
  writeMAX7219(latchPin,clockPin,dataPin,0x0A,0x07);//Midrange Brightness Mode
  writeMAX7219(latchPin,clockPin,dataPin,0x0B,0x03);//scan digits 0-3
  writeMAX7219(latchPin,clockPin,dataPin,0x09,0x0F);//Decode BCD for digits 0,1,2,3
  writeMAX7219(latchPin,clockPin,dataPin,0x04,0x0F);//Write BLANK to digit 3
  writeMAX7219(latchPin,clockPin,dataPin,0x03,0x0F);//Write BLANK to digit 2
  writeMAX7219(latchPin,clockPin,dataPin,0x02,0x0F);//Write BLANK to digit 1
  writeMAX7219(latchPin,clockPin,dataPin,0x01,0x0F);//Write BLANK to digit 0
  writeMAX7219(latchPin,clockPin,dataPin,0x0C,0x01);//Normal mode
}


//void startupFullTest();
//void Test1_LoadingBars();
//void Test2_Characters();
//void Test3_Segments();
//void Test4_HELP();
//void Test5_Brightness();
//void Test6_Pass();
//
//
//
//void startupFullTest(){
//  Test1_LoadingBars();
//  Test2_Characters();
//  Test3_Segments();
//  Test4_HELP();
//  Test5_Brightness();
//  Test6_PASS();
//}
//
////Part 1 "Loading Bars"
//void Test1_LoadingBars(){
//  DisplayINIT();
//  for(byte Address = 0x01;Address<=0x04;Address+=0x01){//loop from address 1 to address 4, digits 0 through 3
//    writeMAX7219(latchPin,clockPin,dataPin,Address,0x0A);//Write - to digit
//    delay(500);//stop for 0.5 seconds
//  }
//  for(byte Address = 0x01;Address<=0x04;Address+=0x01){//loop from address 1 to address 4, digits 0 through 3
//    writeMAX7219(latchPin,clockPin,dataPin,Address,0x0F);//Write BLANK to digit
//    delay(500);//stop for 0.5 seconds
//  }
//}
//
////Part 2 "Character Sweep"
//void Test2_Characters(){
//  DisplayINIT();
//  for(byte Address = 0x01;Address<=0x04;Address+=0x01){//loop from address 1 to address 4, digits 0 through 3
//    for(word value = 0x00;value<=0x0F;value+=0x01){//loop through all decodeable values
//      writeMAX7219(latchPin,clockPin,dataPin,Address,value|0x80);
//      delay(250);//stop for 1 seconds
//    }
//    writeMAX7219(latchPin,clockPin,dataPin,Address,0x0A);//Write - to digit
//    delay(250);//stop for 1 seconds
//   }
//}
//
////Part 3 "Segment Sweep"
//void Test3_Segments(){
//  DisplayINIT();
//  writeMAX7219(latchPin,clockPin,dataPin,0x09,0x00);//Decode BCD for digits none
//  writeMAX7219(latchPin,clockPin,dataPin,0x04,0x00);//Write BLANK to digit 3
//  writeMAX7219(latchPin,clockPin,dataPin,0x03,0x00);//Write BLANK to digit 2
//  writeMAX7219(latchPin,clockPin,dataPin,0x02,0x00);//Write BLANK to digit 1
//  writeMAX7219(latchPin,clockPin,dataPin,0x01,0x00);//Write BLANK to digit 0
//  
//  for(byte Address = 0x01;Address<=0x04;Address+=0x01){//loop from address 1 to address 4, digits 0 through 3
//    for(byte itter = 0x00;itter<=0x07;itter+=0x01){//loop through all decodeable values
//      byte value=0x00;
//      bitSet(value, 0x07-itter);
//      writeMAX7219(latchPin,clockPin,dataPin,Address,value);
//      delay(250);//stop for 0.5 seconds
//      bitClear(value, 0x07-itter);
//      writeMAX7219(latchPin,clockPin,dataPin,Address,value);
//      delay(125);//stop for 0.005 seconds
//    }
//  }
//}
//
////Part 4 spell HELP
//void Test4_HELP(){
//  DisplayINIT();
//  writeMAX7219(latchPin,clockPin,dataPin,0x01,0x0C);//Write H to digit 0
//  writeMAX7219(latchPin,clockPin,dataPin,0x02,0x0B);//Write E to digit 1
//  writeMAX7219(latchPin,clockPin,dataPin,0x03,0x0D);//Write L to digit 2
//  writeMAX7219(latchPin,clockPin,dataPin,0x04,0x0E);//Write P to digit 3
//  writeMAX7219(latchPin,clockPin,dataPin,0x0C,0x01);//Normal mode
//  delay(1000);
//}
//
////Part 5 Sweep the brightness
//void Test5_Brightness(){
//  DisplayINIT();
//  writeMAX7219(latchPin,clockPin,dataPin,0x01,0x88);//Write 8. to digit 0
//  writeMAX7219(latchPin,clockPin,dataPin,0x02,0x88);//Write 8. to digit 1
//  writeMAX7219(latchPin,clockPin,dataPin,0x03,0x88);//Write 8. to digit 2
//  writeMAX7219(latchPin,clockPin,dataPin,0x04,0x88);//Write 8. to digit 3
//  delay(500);
//  writeMAX7219(latchPin,clockPin,dataPin,0x0A,0x00);
//  delay(500);
//  writeMAX7219(latchPin,clockPin,dataPin,0x0A,0x03);
//  delay(500);
//  writeMAX7219(latchPin,clockPin,dataPin,0x0A,0x06);
//  delay(500);
//  writeMAX7219(latchPin,clockPin,dataPin,0x0A,0x09);
//  delay(500);
//  writeMAX7219(latchPin,clockPin,dataPin,0x0A,0x0C);
//  delay(500);
//  writeMAX7219(latchPin,clockPin,dataPin,0x0A,0x0F);
//  delay(500);
//}
//
////Part 6 spell PASS
//void Test6_PASS(){
//  DisplayINIT();
//  writeMAX7219(latchPin,clockPin,dataPin,0x09,0x00);//Decode BCD for digits none
//  writeMAX7219(latchPin,clockPin,dataPin,0x01,B01100111);//Write P to digit 0
//  writeMAX7219(latchPin,clockPin,dataPin,0x02,B01110111);//Write A to digit 1
//  writeMAX7219(latchPin,clockPin,dataPin,0x03,B01011011);//Write S to digit 2
//  writeMAX7219(latchPin,clockPin,dataPin,0x04,B01011011);//Write S to digit 3
//  writeMAX7219(latchPin,clockPin,dataPin,0x0C,0x01);//Normal mode
//  delay(1000);
//}
