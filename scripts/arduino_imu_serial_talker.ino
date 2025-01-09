#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>  // NOTE: PACKAGES NOT INCLUDED IN SENSOR_FUSION BRANCH YET

// i2c
Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1();

#define LSM9DS1_SCK A5
#define LSM9DS1_MISO 12
#define LSM9DS1_MOSI A4
#define LSM9DS1_XGCS 6
#define LSM9DS1_MCS 5
// You can also use software SPI
//Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1(LSM9DS1_SCK, LSM9DS1_MISO, LSM9DS1_MOSI, LSM9DS1_XGCS, LSM9DS1_MCS);
// Or hardware SPI! In this case, only CS pins are passed in
//Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1(LSM9DS1_XGCS, LSM9DS1_MCS);


void setupSensor()
{
  // 1.) Set the accelerometer range
  lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_2G, lsm.LSM9DS1_ACCELDATARATE_10HZ);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_4G, lsm.LSM9DS1_ACCELDATARATE_119HZ);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_8G, lsm.LSM9DS1_ACCELDATARATE_476HZ);
  //lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_16G, lsm.LSM9DS1_ACCELDATARATE_952HZ);
  
  // 2.) Set the magnetometer sensitivity
  lsm.setupMag(lsm.LSM9DS1_MAGGAIN_4GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_8GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_12GAUSS);
  //lsm.setupMag(lsm.LSM9DS1_MAGGAIN_16GAUSS);

  // 3.) Setup the gyroscope
  lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_245DPS);
  //lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_500DPS);
  //lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_2000DPS);
}


void setup() 
{
  Serial.begin(115200);

  while (!Serial) {
    delay(1); // will pause Zero, Leonardo, etc until serial console opens
  } 
  lsm.begin();
  // helper to just set the default scaling we want, see above!
  setupSensor();
}

void loop() 
{
  lsm.read();  /* ask it to read in the data */ 

  /* Get a new sensor event */ 
  sensors_event_t a, m, g, temp;

  lsm.getEvent(&a, &m, &g, &temp); 

  Serial.print(a.acceleration.x); Serial.print(" ");
  Serial.print(a.acceleration.y); Serial.print(" ");
  Serial.print(a.acceleration.z); Serial.print(" ");

  Serial.print(m.magnetic.x); Serial.print(" ");
  Serial.print(m.magnetic.y); Serial.print(" ");
  Serial.print(m.magnetic.z); Serial.print(" ");

  Serial.print(g.gyro.x); Serial.print(" ");
  Serial.print(g.gyro.y); Serial.print(" ");
  Serial.print(g.gyro.z); Serial.print(" ");
  delay(200);
}
