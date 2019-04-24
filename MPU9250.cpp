#include <Wire.h>
#include "MPU9250.h"
#include "MPU9250_MAPPING.h"


MPU9250::MPU9250(){
  Wire.begin();
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

uint8_t MPU9250::readRegister(const uint8_t addr){
  Wire.beginTransmission(MPU9250_DEFAULT_ADDRESS);
  Wire.write(addr);
  Wire.endTransmission();

  Wire.requestFrom(MPU9250_DEFAULT_ADDRESS, 1);
  if(Wire.available()){
    return Wire.read();
  }
}
void MPU9250::writeRegister(const uint8_t addr, const uint8_t value){
    Wire.beginTransmission(MPU9250_DEFAULT_ADDRESS);
    Wire.write(addr);
    Wire.write(value);
    Wire.endTransmission();
}
/****************************************************************
*****************************************************************
* Magnetometer
* @see INT_PIN_CFG
* It can only BYPASS one register per request.
*/
void MPU9250::getMagXYZ(int16_t*mx, int16_t*my, int16_t*mz){
  uint8_t mxl, mxh, myl, myh, mzl, mzh;

  // BYPASS_EN
  // Set I2C bypass enable to access magnetometer.
  if(bypass_en!=true){
    if(readRegister(INT_PIN_CFG)!=0x02){
      writeRegister(INT_PIN_CFG, 0x02);
      bypass_en=true;
    }
  }

  mxl = readMagRegister(MAG_XOUT_L);
  mxh = readMagRegister(MAG_XOUT_H);
  myl = readMagRegister(MAG_YOUT_L);
  myh = readMagRegister(MAG_YOUT_H);
  mzl = readMagRegister(MAG_ZOUT_L);
  mzh = readMagRegister(MAG_ZOUT_H);

  *mx = (mxh << 8) | mxl;
  *my = (myh << 8) | myl;
  *mz = (mzh << 8) | mzl;
    mxl = readMagRegister(MAG_XOUT_L);
    mxh = readMagRegister(MAG_XOUT_H);
    myl = readMagRegister(MAG_YOUT_L);
    myh = readMagRegister(MAG_YOUT_H);
    mzl = readMagRegister(MAG_ZOUT_L);
    mzh = readMagRegister(MAG_ZOUT_H);

    *mx = ((mxh << 8) | mxl);
    *my = ((myh << 8) | myl);
    *mz = ((mzh << 8) | mzl);
}

uint8_t MPU9250::readMagRegister(const uint8_t addr){
  Wire.beginTransmission(MPU9250_MAG_ADDRESS);
  Wire.write(addr);
  Wire.endTransmission();

  Wire.requestFrom(MPU9250_DEFAULT_ADDRESS, 1);
  if(Wire.available()){
    return Wire.read();
  }
}
void MPU9250::writeMagRegister(const uint8_t addr, const uint8_t value) {
    Wire.beginTransmission(MPU9250_MAG_ADDRESS);
    Wire.write(addr);
    Wire.write(value);
    Wire.endTransmission();
}
