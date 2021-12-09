#include <Wire.h>
#include <Ps3Controller.h>

volatile signed char x = 0;

bool flag,flag_Button,flag_Viereck = false; 
void IRAM_ATTR isr() {
    flag = true; 
}

void onEvent()
{
  if (Ps3.event.button_down.cross)
  { 
    flag_Button = true;
  }
  
  if (Ps3.event.button_down.square)
   { 
    flag_Viereck = true;
   }
}

void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
  pinMode(15, INPUT_PULLUP);
  attachInterrupt(15,isr,FALLING); 
  pinMode(2,OUTPUT); 
  Serial.begin(230400); 
  Ps3.begin("60:f4:94:cb:d9:b3");
  digitalWrite(2,LOW);
  Ps3.attach(onEvent); 
}



void loop()
{  
 sendTicker(); //GIT TEST
    
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
