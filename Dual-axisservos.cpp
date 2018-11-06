#include <Servo.h> // include Servo library 

// MAKE: 240 horizontal MAX
Servo yaw; // horizontal servo
int servoy = 90;   // 90;     // stand horizontal servo

int servoyLimitHigh = 180;
int servoyLimitLow = 65;

// 65 degrees MAX
Servo pitch;   // vertical servo 
int servop = 90;    //   90;     // stand vertical servo

int servopLimitHigh = 120;
int servopLimitLow = 15;


// LDR pin connections
//  name  = analogpin;
int ldrlt = 2; //LDR top left - BOTTOM LEFT    <--- BDG
int ldrrt = 3; //LDR top rigt - BOTTOM RIGHT 
int ldrld = 0; //LDR down left - TOP LEFT
int ldrrd = 1; //ldr down rigt - TOP RIGHT

void setup()
{
  Serial.begin(9600);
// servo connections
// name.attacht(pin);
  yaw.attach(9); //Is connected to pin 9
  pitch.attach(10); // Is connected to pin 10
  horizontal.write(180);
  vertical.write(45);
  delay(3000);
}

void loop() 
{
    //Reads input from our photoresistors and stores it in a variable
  int lt = analogRead(ldrlt); // top left
  int rt = analogRead(ldrrt); // top right
  int ld = analogRead(ldrld); // down left
  int rd = analogRead(ldrrd); // down rigt
  
  // int dtime = analogRead(4)/20; // read potentiometers  
  // int tol = analogRead(5)/4;
  int dtime = 10;
  int tol = 50;
  
  int avu = (lt + rt) / 2; // average value up
  int avd = (ld + rd) / 2; // average value down
  int avl = (lt + ld) / 2; // average value left
  int avr = (rt + rd) / 2; // average value right

  int dvert = avu - avd; // check the diffirence of up and down
  int dhoriz = avl - avr;// check the diffirence og left and rigt
  
  
  Serial.print(avu);
  Serial.print(" ");
  Serial.print(avd);
  Serial.print(" ");
  Serial.print(avl);
  Serial.print(" ");
  Serial.print(avr);
  Serial.print("   ");
  Serial.print(dtime);
  Serial.print("   ");
  Serial.print(tol);
  Serial.println(" ");
  
    
  if (-1*tol > dvert || dvert > tol) // check if the diffirence is in the tolerance else change vertical angle
  {
  if (avu > avd)
  {
    servov = ++servov;
     if (servov > servovLimitHigh) 
     { 
      servov = servovLimitHigh;
     }
  }
  else if (avu < avd)
  {
    servov= --servov;
    if (servov < servovLimitLow)
  {
    servov = servovLimitLow;
  }
  }
  vertical.write(servov);
  }
  
  if (-1*tol > dhoriz || dhoriz > tol) // check if the diffirence is in the tolerance else change horizontal angle
  {
  if (avl > avr)
  {
    servoh = --servoh;
    if (servoh < servohLimitLow)
    {
    servoh = servohLimitLow;
    }
  }
  else if (avl < avr)
  {
    servoh = ++servoh;
     if (servoh > servohLimitHigh)
     {
     servoh = servohLimitHigh;
     }
  }
  else if (avl = avr)
  {
    // nothing
  }
  horizontal.write(servoh);
  }
   delay(dtime);

}