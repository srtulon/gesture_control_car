#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();
int enA=6;
int enB=5;
int H=3;
int LmotorUp = 10;
int LmotorDn = 11; 
int RmotorUp = 8;  
int RmotorDn = 9;  
int spd;
int hstate;
int sstate;

void setup()
{
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(H,OUTPUT);
  pinMode(LmotorUp,OUTPUT);
  pinMode(LmotorDn,OUTPUT);
  pinMode(RmotorUp,OUTPUT);
  pinMode(RmotorDn,OUTPUT);
  spd=250;
  mySwitch.enableReceive(0);
 
  hstate=0;
  sstate=0;
} 
  

void loop()
{
  if(mySwitch.available())
  {
    int r = mySwitch.getReceivedValue(); 
    Serial.println(r);
    int input=5;
    int x=r/10;
    int y=r%10;
    if(y>4){
      input=4;
    }
    else if(y<2){
      input =3;
    }
    else if(x>4){
      input =1;
    }
    else if(x<2){
      input=2;
    }
      
     
    switch(input)
    {
     case 1 : MoveF();
     break;
     case 2 : MoveB(); 
     break;
     case 3 : MoveL();
     break;
     case 4 : MoveR();
     break;
     case 5 : Stop();
     break;
    
     
     default : Stop();
     break;
    }
  }
     mySwitch.resetAvailable(); 
     delay(10);
 
}

void MoveF()
{
  Serial.println("Forward");
  digitalWrite(LmotorUp,HIGH);
  digitalWrite(LmotorDn,LOW);
  analogWrite(enA, spd);
  digitalWrite(RmotorUp,HIGH);
  digitalWrite(RmotorDn,LOW);
  analogWrite(enB, spd);
  delay(10);
  
}

void MoveB()
{
  Serial.println("Backward");
  digitalWrite(LmotorUp,LOW);
  digitalWrite(LmotorDn,HIGH);
  analogWrite(enA, spd);
  digitalWrite(RmotorUp,LOW);
  digitalWrite(RmotorDn,HIGH);
  analogWrite(enB, spd);
  delay(10);
 
}

void MoveL()
{
  Serial.println("Left");
  if(sstate==0)
  {
    digitalWrite(LmotorUp,LOW); 
    digitalWrite(LmotorDn,LOW);
  }
  else if(sstate==1){
    digitalWrite(LmotorUp,LOW);
    digitalWrite(LmotorDn,HIGH);
    analogWrite(enA, spd);
  }
  digitalWrite(RmotorUp,HIGH);
  digitalWrite(RmotorDn,LOW);
  analogWrite(enB, spd);
  delay(10);
  
}

void MoveR()
{
  Serial.println("Right");
  digitalWrite(LmotorUp,HIGH);
  digitalWrite(LmotorDn,LOW);
  analogWrite(enA, spd);
  if(sstate==0)
  {
    digitalWrite(RmotorUp,LOW);
    digitalWrite(RmotorDn,LOW);
  }
  else if(sstate==1)
  {
    digitalWrite(RmotorUp,LOW);
    digitalWrite(RmotorDn,HIGH);
    analogWrite(enB, spd);
  }
  delay(10);
 
}

void Stop()
{
  Serial.println("Stop");
  digitalWrite(LmotorUp,LOW);
  digitalWrite(LmotorDn,LOW);
  digitalWrite(RmotorUp,LOW);
  digitalWrite(RmotorDn,LOW);
}

void Speed()
{
  spd=spd+75;
  if(spd>250)
  {
    spd=100;
  }
  if(spd<175)
  {
    Serial.println("Speed LOW");
  }
  else if(spd<250)
  {
    Serial.println("Speed MEDIUM");
  }
  else
  {
    Serial.println("Speed High");
  }
}

void Horn()
{ 
  if(hstate==0)
  {
    digitalWrite(H,HIGH); 
    Serial.println("Horn on");
    hstate=1;
    delay(100);
  }
  else if(hstate==1)
  {
    digitalWrite(H,LOW); 
    Serial.println("Horn off");
    hstate=0;
    delay(10);
  }
}

void Sturn()
{
 if(sstate==0)
  {
    sstate=1;
  }
 else if(sstate==1)
  {
    sstate=0;
  } 
}

