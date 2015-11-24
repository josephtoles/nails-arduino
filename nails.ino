// Arduino headers
#include <Arduino.h>
#include <SPI.h>


// Bluetooth headers
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"
#include "bluefruit_config.h"
/* ...hardware SPI, using SCK/MOSI/MISO hardware SPI pins and then user selected CS/IRQ/RST */
Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);


// ADXL345 headers
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);


// Global variables
double x, y, z;  // Acceleration along each axis.
int loop_count = 0;


void setup() {
  Serial.begin(9600);
  adxl345_setup();
  bluefruit_setup();
}

void loop() {
  Serial.print("Loop ");Serial.println(++loop_count);
  adxl345_loop();
  bluefruit_loop();
}
