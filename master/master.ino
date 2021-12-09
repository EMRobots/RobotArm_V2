#include <Wire.h>
#include <Ps3Controller.h>

volatile signed char x = 0;

bool flag,flag_Button,flag_Viereck,old_flag_Viereck = false; 
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
 if (Ps3.event.button_down.cross ){
  flag_Button = true;  Serial.println("x");} else flag_Button = false;
    

 if (Ps3.event.button_down.right){
  flag_Viereck = true; 
  Serial.println("Viereck");}else flag_Viereck = false;   
}

void sendTicker()
{
  if (flag == true)
  {
    Wire.beginTransmission(4); // transmit to device #4
    Wire.write(Ps3.data.analog.stick.lx);
    Wire.write(Ps3.data.analog.stick.ly);
    Wire.write((int)flag_Button);
    Wire.write((int)flag_Viereck); 
    Wire.endTransmission();    // stop transmitting
    flag = false; 
    flag_Button = false;
  }
}
