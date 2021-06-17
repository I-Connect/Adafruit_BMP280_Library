// 
// 
// 

#include "BMP280BarometerSensor.h"
#include "SenseUtils.h"

const char* BMP280_SEMAPHORE_OWNER = "BMP280_Barometer";

BMP280BarometerSensor::BMP280BarometerSensor(uint8_t sensorId, const uint8_t address) : Sense::ObservableNode<BarometerResult>(sensorId), address(address) {}

void BMP280BarometerSensor::initialize() {
  if (takeI2CSemaphore(BMP280_SEMAPHORE_OWNER)) {
    sensorActive = bmp.begin(address);
    if (sensorActive) {
      // first readings are wrong (initialization?), get them out of the way
      bmp.readPressure();
      bmp.readTemperature();
    }
     giveI2CSemaphore();
  }
  if (sensorActive){
    Sense::ObservableNode<BarometerResult>::initialize();
  }
}

void BMP280BarometerSensor::readRawValue() {
  BarometerResult lastValues;
  if (takeI2CSemaphore(BMP280_SEMAPHORE_OWNER)) {
    lastValues.tempInCelcius = round(bmp.readTemperature() * 10);
    lastValues.pressure = round(bmp.readPressure()/100);
  }
  giveI2CSemaphore();
  setSingleValue(lastValues, false);
}

char* BMP280BarometerSensor::getReadableValue(char* buffer, const uint8_t size) {
  if (size >= 20) {
    BarometerResult lastValues = getSingleValue();
    char temp[10];
    dtostrf((float)lastValues.tempInCelcius/10, 2, 1, temp);
    sprintf_P(buffer, PSTR("P: %d hPa T: %s C"), lastValues.pressure, temp);
  }
  return buffer;
}

