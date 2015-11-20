// Arduino headers
#include <Arduino.h>
#include <SPI.h>

// Bluetooth headers
#include "Adafruit_BLE.h"

// ADXL345 headers
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);



void setup() {
  Serial.begin(9600);

  ADXL345_setup();
}

void loop() {
  Serial.println("loop the loop of nails forever");
  print_something();
}
