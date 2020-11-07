#include <Wire.h>
#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

long accelX, accelY, accelZ;
float X, Y, Z;
int sendd;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  setupMPU();
  mySwitch.enableTransmit(10);
}


void loop() {
  if(sendd>0)
  {
    mySwitch.send(sendd, 8);
  }
  recordAccelRegisters();
  
  printData();
  delay(100);
}

void setupMPU(){
  Wire.beginTransmission(0b1101000); //This is the I2C address of the MPU (b1101000/b1101001 for AC0 low/high datasheet sec. 9.2)
  Wire.write(0x6B); //Accessing the register 6B - Power Management (Sec. 4.28)
  Wire.write(0b00000000); //Setting SLEEP register to 0. (Required; see Note on p. 9)
  Wire.endTransmission();  
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x1B); //Accessing the register 1B - Gyroscope Configuration (Sec. 4.4) 
  Wire.write(0x00000000); //Setting the gyro to full scale +/- 250deg./s 
  Wire.endTransmission(); 
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x1C); //Accessing the register 1C - Acccelerometer Configuration (Sec. 4.5) 
  Wire.write(0b00000000); //Setting the accel to +/- 2g
  Wire.endTransmission(); 
}

void recordAccelRegisters() {
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x3B); //Starting register for Accel Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6); //Request Accel Registers (3B - 40)
  while(Wire.available() < 6);
  accelX = Wire.read()<<8|Wire.read(); //Store first two bytes into accelX
  accelY = Wire.read()<<8|Wire.read(); //Store middle two bytes into accelY
  accelZ = Wire.read()<<8|Wire.read(); //Store last two bytes into accelZ
  processAccelData();
}

void processAccelData(){
  X = ((accelX / 16384.0)+2)*5;
  Y = ((accelY / 16384.0)+2)*5; 
  Z = ((accelZ / 16384.0)+2)*5;
  sendd=(int)X*10+(int)Y;
}



void printData() {
  
  Serial.print(" Accel (g)");
  Serial.print(" X=");
  Serial.print(X);
  Serial.print(" Y=");
  Serial.print(Y);
  Serial.print(" Z=");
  Serial.println(Z);
  
  
  delay(500);
}

