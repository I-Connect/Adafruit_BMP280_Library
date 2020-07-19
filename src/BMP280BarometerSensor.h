
#pragma once

#include "SenseNode.h"
#include "SenseI2CBusSensor.h"
#include "Adafruit_BMP280.h"

struct BarometerResult
{
  int16_t tempInCelcius; // times 10
  uint16_t pressure;
};

/*
  I2C barometer sensor, address = 0x77
*/
class BMP280BarometerSensor : virtual SenseI2CWireUser, public SenseNode
{
public:
  BMP280BarometerSensor(uint8_t sensorId);
  
  int32_t getlastPressure();
  int32_t getPreviousPressure();

  int getValueAsInt() override;
  byte* getValueInBuffer(byte* buffer) override; 
  uint8_t getMinBufferSize() override; 
  char* getValueAsChar(char* buffer, uint8_t size) override;
  
protected:
  void readRawValue() override;
  void saveLastNotifiedState() override;
  bool observersMustBeNotified();
  void initialize();
private:
  Adafruit_BMP280 bmp;
  BarometerResult prevValues;
  BarometerResult lastValues;
};

