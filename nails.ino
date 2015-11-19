#include <Arduino.h>
#include <SPI.h>

#include "Adafruit_BLE.h"

#include "ext.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("loop the loop of nails forever");
  //print_output();
  print_something();
}
