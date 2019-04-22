# MPU9250 Library for Arduino IDE.
Tested on Sensor Board Module GY-91 integrated MPU9250/BMP280.

To read all the raw data output from MPU9250 multi-chip module (MCM).

- void **getMagXYZ**(int16_t* mx, int16_t* my, int16_t* mz);
- void **getAccXYZ**(int16_t* ax, int16_t* ay, int16_t* az);
- void **getGyrXYZ**(int16_t* gx, int16_t* gy, int16_t* gz);
- void **getTemp**(int16_t* t);
