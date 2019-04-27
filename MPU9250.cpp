#include <Wire.h>
#include "MPU9250.h"
#include "MPU9250_MAPPING.h"


MPU9250::MPU9250(){
  Wire.begin();
}
void MPU9250::begin(){

}

void MPU9250::getAccXYZ(int16_t*ax, int16_t*ay, int16_t*az){
  Wire.beginTransmission(MPU9250_DEFAULT_ADDRESS);
  Wire.write(ACCEL_XOUT_H);
  Wire.endTransmission();

  Wire.requestFrom(MPU9250_DEFAULT_ADDRESS, 6);
  while(Wire.available()){
    *ax = (Wire.read() << 8 | Wire.read());
    *ay = (Wire.read() << 8 | Wire.read());
    *az = (Wire.read() << 8 | Wire.read());
  }
}

void MPU9250::getGyrXYZ(int16_t*gx, int16_t*gy, int16_t*gz){
  Wire.beginTransmission(MPU9250_DEFAULT_ADDRESS);
  Wire.write(GYRO_XOUT_H);
  Wire.endTransmission();

  Wire.requestFrom(MPU9250_DEFAULT_ADDRESS, 6);
  while(Wire.available()){
    *gx = (Wire.read() << 8 | Wire.read());
    *gy = (Wire.read() << 8 | Wire.read());
    *gz = (Wire.read() << 8 | Wire.read());
  }
}

void MPU9250::getTemp(int16_t* t){
  Wire.beginTransmission(MPU9250_DEFAULT_ADDRESS);
  Wire.write(TEMP_OUT_H);
  Wire.endTransmission();

  Wire.requestFrom(MPU9250_DEFAULT_ADDRESS, 2);
  while(Wire.available()){
    *t = (Wire.read() << 8 | Wire.read());
  }
}

uint8_t MPU9250::readRegister(const uint8_t host, const uint8_t addr){
  Wire.beginTransmission(host);
  Wire.write(addr);
  Wire.endTransmission();

  Wire.requestFrom(host, 1);
  if(Wire.available()){
    return Wire.read();
  }
}
uint8_t MPU9250::writeRegister(const uint8_t host, const uint8_t addr, const uint8_t value){
    Wire.beginTransmission(host);
    Wire.write(addr);
    Wire.write(value);
    return Wire.endTransmission();
    /*
    0:success
    1:data too long to fit in transmit buffer
    2:received NACK on transmit of address
    3:received NACK on transmit of data
    4:other error
    */
}

/****************************************************************
*****************************************************************
* Magnetometer
*/
void MPU9250::getMagXYZ(int16_t*mx, int16_t*my, int16_t*mz){
  uint8_t ST1, ST2;
  do{
    Wire.beginTransmission(MPU9250_MAG_ADDRESS);
    Wire.write(MAG_ST1);
    Wire.endTransmission();
    Wire.requestFrom(MPU9250_MAG_ADDRESS, 1);
    while(Wire.available()){
    /*
    * 0x00 = DRDY: Data Ready  ? 0 : 1
    * 0x01 = DOR: Data Overrun ? 0 : 1
    */
      ST1 = Wire.read();
    }
  }
  while (!(ST1 & 0x01)); // 0x01 = ready | 0x00 = not ready.

  Wire.beginTransmission(MPU9250_MAG_ADDRESS);
  Wire.write(MAG_XOUT_L);
  Wire.endTransmission();
  Wire.requestFrom(MPU9250_MAG_ADDRESS, 7);
    while(Wire.available()){
      *mx= (Wire.read()<<8) | Wire.read();
      *my= (Wire.read()<<8) | Wire.read();
      *mz= (Wire.read()<<8) | Wire.read();
      ST2 = Wire.read();
    }
}
