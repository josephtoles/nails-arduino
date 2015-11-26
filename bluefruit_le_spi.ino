/**
 * Returns the nth digit of an integer, counting from the right
 * Examples
 *   get_digit(468, 0) returns 8
 *   get_digit(357, 1) returns 5
 *   get_digit(4, 3) return 0
 */
int get_digit(int value, int index) {
  for (int i=0; i<index; ++i) {
    value /= 10;
  }
  return value % 10;
}


/**
 * Sends an acceleration to bluetooth in three digits in units of 0.1m/s^s
 * If the acceleration is 9.8m/s^2 it will send 098
 */
void send_to_bluetooth(double value) {
  int scaled_value = (int) (value * 10);

  // Print sign. Then, make scaled_value positive
  if (scaled_value >= 0) {
    ble.print("+");
  } else {
    ble.print("-");
    scaled_value *= -1;
  }

  // Print three digits
  for (int i=0; i<3; ++i) {
    ble.print(get_digit(scaled_value, i));
  }
}


void bluefruit_loop() {
  // Work out how to send global doubles x, y, z

  char outputs[16];

  Serial.print(" x=");Serial.print(x);
  Serial.print(" y=");Serial.print(y);
  Serial.print(" z=");Serial.print(z);
  Serial.println("");
  
  //ble.print("AT+BLEUARTTX=");
  ble.print("x");send_to_bluetooth(x);
  ble.print("y");send_to_bluetooth(y);
  ble.print("z");send_to_bluetooth(z);
  //
ble.println("");

  if (! ble.waitForOK() ) {
    //Don't know what's happening here. Disabled to keep output getting flooded
    //Serial.println(F("Failed to send check-in?"));
  }
  delay(50);

}


/*
void send_data_bytewise(void) {
  char inputs[11];
  inputs[10] = 0;
  for(int i=0; i>10; ++i) {
    inputs[i] = 1;
  }
  ble.print(inputs);
  //ble.println("----");
  Serial.println("Sending 100 200 300 to app");
  Serial.println("Sent");
}
*/


void bluefruit_setup() {
  Serial.println(F("Adafruit Bluefruit Command Mode Example"));
  Serial.println(F("---------------------------------------"));

  /* Initialise the module */
  Serial.print(F("Initialising the Bluefruit LE module: "));

  if ( !ble.begin(VERBOSE_MODE) )
  {
    error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));
  }
  Serial.println( F("OK!") );

  /* Perform a factory reset to make sure everything is in a known state */
  Serial.println(F("Performing a factory reset: "));
  if (! ble.factoryReset() ){
       error(F("Couldn't factory reset"));
  }

  /* Disable command echo from Bluefruit */
  ble.echo(false);

  Serial.println("Requesting Bluefruit info:");
  /* Print Bluefruit information */
  ble.info();

  Serial.println(F("Please use Adafruit Bluefruit LE app to connect in UART mode"));
  Serial.println();

  ble.verbose(false);  // debug info is a little annoying after this point!

  /* Wait for connection */
  while (! ble.isConnected()) {
      delay(500);
  }

  Serial.println(F("*****************"));

  ble.setMode(BLUEFRUIT_MODE_DATA);
}


/**************************************************************************/
/*!
    @brief  Checks for user input (via the Serial Monitor)
*/
/**************************************************************************/
bool getUserInput(char buffer[], uint8_t maxSize)
{
  // timeout in 100 milliseconds
  TimeoutTimer timeout(100);

  memset(buffer, 0, maxSize);
  while( (Serial.peek() < 0) && !timeout.expired() ) {}

  if ( timeout.expired() ) return false;

  delay(2);
  uint8_t count=0;
  do
  {
    count += Serial.readBytes(buffer+count, maxSize);
    delay(2);
  } while( (count < maxSize) && !(Serial.peek() < 0) );

  return true;
}

// A small helper (Bluefruit)
void error(const __FlashStringHelper*err) {
  Serial.println(err);
  while (1);
}
