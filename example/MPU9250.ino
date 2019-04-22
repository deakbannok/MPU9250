#include <MPU9250.h>
MPU9250 TENDOF;
unsigned long timing;

int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t mx, my, mz;
int16_t temperature;

void setup(){
  Serial.begin(9600);
  while(!Serial){ delay(1000); }
  Serial.println("10 DOF GY-91 MPU9280.");
  timing = millis();
}

void loop(){
  if((timing+1000) < millis()){
    timing = millis();
    TENDOF.getAccXYZ(&ax, &ay, &az);
    Serial.print("ACC:\t"); Serial.print(ax); Serial.print(" : "); Serial.print(ay); Serial.print(" : "); Serial.println(az);
    TENDOF.getGyrXYZ(&gx, &gy, &gz);
    Serial.print("GYR\t"); Serial.print(gx); Serial.print(" : "); Serial.print(gy); Serial.print(" : "); Serial.println(gz);
    TENDOF.getMagXYZ(&mx, &my, &mz);
    Serial.print("MAG:\t"); Serial.print(mx); Serial.print(" : "); Serial.print(my); Serial.print(" : "); Serial.println(mz);
    TENDOF.getTemp(&temperature);
    Serial.print("TEMPERATURE:\t"); Serial.println(temperature);
  }
}
