#include <Wire.h>
#include <Ps3Controller.h>

volatile signed char x = 0;

bool flag,flag_Button,flag_Viereck,old_flag_Viereck = 0; 
void IRAM_ATTR isr() {
    flag = true; 
}

void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
  pinMode(15, INPUT_PULLUP);
  attachInterrupt(15,isr,FALLING); 
  pinMode(2,OUTPUT); 
  Serial.begin(9600); 
  Ps3.begin("60:f4:94:cb:d9:b3");
}//sdasda



void loop()
{
 sendTicker(); //GIT TEST;

 flag_Button = 0; 
 flag_Viereck = 0; 
 
 if (Ps3.event.button_down.cross)
  flag_Button = 1;
    
 if (Ps3.event.button_down.right)
  flag_Viereck = 1;

   
}

void sendTicker()
{
  if (flag == true)
  {
    Wire.beginTransmission(4); // transmit to device #4
    Wire.write(Ps3.data.analog.stick.lx);
    Wire.write(Ps3.data.analog.stick.ly);
    Wire.write(flag_Button);
    Wire.write(flag_Viereck); 
    Wire.endTransmission();    // stop transmitting
    flag = false; 
  }
}
