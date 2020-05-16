// 
// 
// 

#include "BMP280BarometerSensor.h"
#include "SenseUtils.h"

BMP280BarometerSensor::BMP280BarometerSensor(uint8_t sensorId) : SenseNode(sensorId) {}

void BMP280BarometerSensor::initialize() {
  sensorActive = bmp.begin();
  if (sensorActive) {
    // first readings are wrong (initialization?), get them out of the way
    bmp.readPressure();
    bmp.readTemperature();
  }
}

int32_t BMP280BarometerSensor::getlastPressure() {
  return lastValues.pressure;
}

int32_t BMP280BarometerSensor::getPreviousPressure() {
  return prevValues.pressure;
}

int BMP280BarometerSensor::getValueAsInt() {
  return lastValues.pressure;
}


void BMP280BarometerSensor::readRawValue() {
  lastValues.tempInCelcius = round(bmp.readTemperature() * 10);
  lastValues.pressure = round(bmp.readPressure()/100);
}

void BMP280BarometerSensor::saveLastNotifiedState() {
  prevValues = lastValues;
}

bool BMP280BarometerSensor::observersMustBeNotified() {
  return ((prevValues.pressure != lastValues.pressure) || (prevValues.tempInCelcius != lastValues.tempInCelcius) );
}

byte* BMP280BarometerSensor::getValueInBuffer(byte* buffer) {
  memcpy(buffer, &lastValues, sizeof(lastValues)); 
  return buffer;
}

uint8_t BMP280BarometerSensor::getMinBufferSize() {
  return sizeof(lastValues);
}

char* BMP280BarometerSensor::getValueAsChar(char* buffer, uint8_t size) {
  char temp[10];
  dtostrf((float)lastValues.tempInCelcius/10, 2, 1, temp);
  sprintf_P(buffer, PSTR("P: %d hPa T: %s C"), lastValues.pressure, temp);
  return buffer;
}

