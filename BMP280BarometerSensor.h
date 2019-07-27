
#pragma once

#include "SenseI2CBusSensor.h"
#include "Adafruit_BMP280.h"
#include "TemperatureSensor.h"

struct BarometerResult
{
  float tempInCelcius;
  int32_t pressure;
};

/*
  I2C barometer sensor, address = 0x77
*/
class BMP280BarometerSensor : virtual SenseI2CWireUser, public TemperatureSensor
{
public:
  BMP280BarometerSensor(uint8_t sensorId);
  
  virtual int32_t getlastPressure();
  virtual int32_t getPreviousPressure();

  int getValueAsInt() override;
protected:
  virtual void readRawValue() override;
  virtual void saveLastNotifiedState() override;
  virtual bool observersMustBeNotified() override;
  virtual void initialize() override;
private:
  Adafruit_BMP280 bmp;
  BarometerResult prevValues;
  BarometerResult lastValues;
};

