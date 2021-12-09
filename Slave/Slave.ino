#include <Wire.h>
#include <AccelStepper.h>
volatile signed char x,xalt,y,yalt,SavePos,SavePosalt,DrivePos = 0;
int Pos = 0;  
bool dataWasReceived = 0; 
 AccelStepper stepper(1,5,4);
 AccelStepper stepper2(1,8,7);
void setup()
{
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(115200);           // start serial for output
  pinMode(9, OUTPUT);
  pinMode(9, LOW);
  pinMode(6,OUTPUT);
  digitalWrite(6, HIGH);
  stepper.setAcceleration(500); 
  stepper.setMaxSpeed(10000); 
  stepper2.setAcceleration(500); 
  stepper2.setMaxSpeed(10000);
 
  stepper.setMaxSpeed(1000);
  stepper.setAcceleration(200);
  stepper.moveTo(1000);

}

void GetData()
{
  pinMode(9, HIGH);
  pinMode(9,LOW);
}

void loop()
{ 
  if(dataWasReceived == 0)
  {
    GetData(); 
  }

  programmingmode(); 
  
 //if(SavePos == 1)
 // {
 //   SavePos = 0; 
 //   stepper.setCurrentPosition(0); 
 //   
 // }
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  xalt = x;
  yalt = y;
  x = Wire.read();
  y = Wire.read();
  SavePos = Wire.read();
  DrivePos = Wire.read(); 
  dataWasReceived = 0;
  if(SavePos)
    Serial.println("X"); 
  if(DrivePos)
    Serial.println("Viereck");

}

void programmingmode()
{
  
   if(x>10 || x<-10){
    if(x!= xalt){
  stepper.setSpeed(x*5);} //Test
  stepper.runSpeed();
  }
  
  if(y>10 || y<-10){
    if(y!= yalt){  
  stepper2.setSpeed(y*10);} 
  stepper2.runSpeed();
    }
}
