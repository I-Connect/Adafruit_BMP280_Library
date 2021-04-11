
#include "Arduino.h"
#include "BMP280BarometerSensor.h"

BMP280BarometerSensor sensor{234, 0x77};

void setup() {
    pinMode(26, OUTPUT);
    pinMode(27, OUTPUT);
    digitalWrite(26, LOW);
    digitalWrite(27, LOW);
    Wire.begin();
    // Wire.setClock(400000);
    Serial.begin(115200);
    Serial.println("Testing BMP280");
    // sensor.initialize();
    Serial.println("Setup done");
}

void loop() {
    sensor.updateState();
    char buffer[50];
    Serial.println(sensor.getReadableValue(buffer, 50));
    delay(1000);
}