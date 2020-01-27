
#pragma once

#include "SenseNode.h"
#include "SenseI2CBusSensor.h"
#include "Adafruit_BMP280.h"

struct BarometerResult
{
  float tempInCelcius;
  int32_t pressure;
};

/*
  I2C barometer sensor, address = 0x77
*/
class BMP280BarometerSensor : virtual SenseI2CWireUser, public SenseNode
{
public:
  BMP280BarometerSensor(uint8_t sensorId);
  
  virtual int32_t getlastPressure();
  virtual int32_t getPreviousPressure();

  int getValueAsInt();
protected:
  virtual void readRawValue();
  virtual void saveLastNotifiedState();
  virtual bool observersMustBeNotified();
  virtual void initialize();
private:
  Adafruit_BMP280 bmp;
  BarometerResult prevValues;
  BarometerResult lastValues;
};

