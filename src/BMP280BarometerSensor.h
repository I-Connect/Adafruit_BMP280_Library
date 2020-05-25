
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
class BMP280BarometerSensor : virtual Sense::I2CBusSensor, public Sense::ObservableNode<BarometerResult> {
public:
  BMP280BarometerSensor(uint8_t sensorId);
  
  void initialize() override;
  char* getReadableValue(char* buffer, const uint8_t size) override;
  
protected:
  void readRawValue() override;
private:
  Adafruit_BMP280 bmp;
};

