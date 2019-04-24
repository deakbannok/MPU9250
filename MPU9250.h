#ifndef MPU9250_H
#define MPU9250_H
/*
* GYROSCOPE    = Angular rate sensors.
* TEMPERATURE  = ((TEMP_OUT – RoomTemp_Offset)/Temp_Sensitivity) + (21 deg C)
* MAGNETOMETER = Y:North-South, X:East-West, Z:Up-Down
  32760 to -32760
*/
class MPU9250 {
  public:
    MPU9250();
    void getMagXYZ(int16_t* mx, int16_t* my, int16_t* mz);
    void getAccXYZ(int16_t* ax, int16_t* ay, int16_t* az);
    void getGyrXYZ(int16_t* gx, int16_t* gy, int16_t* gz);
    void getTemp(int16_t* t);

  private:
    uint8_t readRegister(const uint8_t addr);
    uint8_t readMagRegister(const uint8_t addr);
    void writeRegister(const uint8_t addr, const uint8_t value);
    void writeMagRegister(const uint8_t addr, const uint8_t value);

    bool bypass_en;
};

#endif //MPU9250_H
