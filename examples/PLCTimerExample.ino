/*
This is an example of the PLC Timer library. 

This library aims to make timing simple for people used to PLC's that are now using an Arduino. 
You create a PLCTimer variable with the type (TON or TOF) and it will react as a normal Siemens PLC 
timer would do.

The TOF timer will keep the output of the run method high for the preset time after the In signal resets. 
The TON timer will keep the output of the run method low for the preset time after the In signal sets
*/

#include <PLCTimer.h>

PLCTimer Delay(PLCTimer::TOF); //or PLCTimer::TON


//create buttons and led's to test this function.
const int button1 = 4; 
const int led1 = 13;

void setup() {
  //start Serial port
  Serial.begin(19200);
  //configure pins for in and out.
  pinMode(button1, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  delay(1000);
  
}

void loop() {
  uint32_t elapsed;
  uint8_t timing;
  
  /*
   * read button state.
   * buttons are wired as normally set to 1 (INPUT_PULLUP). 
   * So we should negate the input to have them perform as "normal" PLC buttons.
  */

  uint8_t but1 = !digitalRead(button1);
  //simple test
  digitalWrite(led1, Delay.run(but1, 5000, &elapsed, &timing));
  
  Serial.print("Timer is ");
  Serial.print (but1); 
  Serial.print(" elapsed time = ");
  Serial.print(elapsed);
  Serial.print(" and timing is ");
  Serial.println(timing);
}
