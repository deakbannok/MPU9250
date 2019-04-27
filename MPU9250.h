#ifndef MPU9250_H
#define MPU9250_H
/******************
* DEFAULT SETTINGS
*******************
* GYROSCOPE    = Angular rate sensors.
* TEMPERATURE  = ((TEMP_OUT – RoomTemp_Offset)/Temp_Sensitivity) + (21 deg C)
* MAGNETOMETER = Y:North-South, X:East-West, Z:Up-Down

  H = (MAG_ASA-128)*0.5;
  H = (H/128)+1;

  32760 to -32760
  AR = 250DPG / 32760;
  AR * GYRO_OUT_PUT = result;

  AR = 2.0g / 32760;
  AR * ACCEL_OUT_PUT = result;
*/
class MPU9250 {
  public:
    MPU9250();
    void begin(void);
    void getMagXYZ(int16_t* mx, int16_t* my, int16_t* mz);
    void getAccXYZ(int16_t* ax, int16_t* ay, int16_t* az);
    void getGyrXYZ(int16_t* gx, int16_t* gy, int16_t* gz);
    void getTemp(int16_t* t);

  private:
    uint8_t readRegister(const uint8_t host, const uint8_t addr);
    uint8_t writeRegister(const uint8_t host, const uint8_t addr, const uint8_t value);
};

#endif //MPU9250_H
