#include <Wire.h>
#include "MPU9250.h"
#include "MPU9250_MAPPING.h"


MPU9250::MPU9250(){
  Wire.begin();
}
void MPU9250::getAccXYZ(int16_t*ax, int16_t*ay, int16_t*az){
  uint8_t axl, axh, ayl, ayh, azl, azh;

  axl = readRegister(ACCEL_XOUT_L);
  axh = readRegister(ACCEL_XOUT_H);
  ayl = readRegister(ACCEL_YOUT_L);
  ayh = readRegister(ACCEL_YOUT_H);
  azl = readRegister(ACCEL_ZOUT_L);
  azh = readRegister(ACCEL_ZOUT_H);

  *ax = (axh << 8) | axl;
  *ay = (ayh << 8) | ayl;
  *az = (azh << 8) | azl;
}

void MPU9250::getGyrXYZ(int16_t*gx, int16_t*gy, int16_t*gz){
  uint8_t gxl, gxh, gyl, gyh, gzl, gzh;

  gxl = readRegister(GYRO_XOUT_L);
  gxh = readRegister(GYRO_XOUT_H);
  gyl = readRegister(GYRO_YOUT_L);
  gyh = readRegister(GYRO_YOUT_H);
  gzl = readRegister(GYRO_ZOUT_L);
  gzh = readRegister(GYRO_ZOUT_H);

  *gx = (gxh << 8) | gxl;
  *gy = (gyh << 8) | gyl;
  *gz = (gzh << 8) | gzl;
}

void MPU9250::getTemp(int16_t* t){
  uint8_t tl, th;

  tl = readRegister(TEMP_OUT_L);
  th = readRegister(TEMP_OUT_H);

  *t=(th << 8) | tl;
}
uint8_t MPU9250::readRegister(const uint8_t addr){
  uint8_t data = 0;

  Wire.beginTransmission(MPU9250_DEFAULT_ADDRESS);
  Wire.write(addr);
  Wire.endTransmission();

  Wire.requestFrom(MPU9250_DEFAULT_ADDRESS, 1);
  if(Wire.available()){
    data = Wire.read();
  }

  return data;
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

}

uint8_t MPU9250::readMagRegister(const uint8_t addr){
  uint8_t data = 0;
  Wire.beginTransmission(MPU9250_MAG_ADDRESS);
  Wire.write(addr);
  Wire.endTransmission();
  Wire.requestFrom(MPU9250_DEFAULT_ADDRESS, 1);
  if(Wire.available()){
    data = Wire.read();
  }
  return data;
}
void MPU9250::writeMagRegister(const uint8_t addr, const uint8_t value) {
    Wire.beginTransmission(MPU9250_MAG_ADDRESS);
    Wire.write(addr);
    Wire.write(value);
    Wire.endTransmission();
}
