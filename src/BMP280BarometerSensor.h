
#pragma once

#include <ObservableNode.h>
#include <I2CBusSensor.h>
#include "Adafruit_BMP280.h"

struct BarometerResult
{
  int16_t tempInCelcius; // times 10
  uint16_t pressure;
};

/*
  I2C barometer sensor, address = 0x77
*/
class BMP280BarometerSensor : virtual public Sense::I2CBusSensor, public Sense::ObservableNode<BarometerResult> {
public:
  BMP280BarometerSensor(uint8_t sensorId, const uint8_t address);
  virtual ~BMP280BarometerSensor() {};
  
  char* getReadableValue(char* buffer, const uint8_t size) override;
  char* getMessage(char* buffer, uint8_t size) override;
  
protected:
  void readRawValue() override;
  void initialize() override;
private:
  uint8_t address;
  Adafruit_BMP280 bmp;
};

