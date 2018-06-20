#include <SPI.h>

void setup() {
  pinMode(10, OUTPUT);

  SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE0));
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  digitalWrite(10, HIGH);
  digitalWrite(10, LOW);

  SPI.transfer(0xC);
  SPI.transfer(0x1);

  digitalWrite(10, HIGH);
  digitalWrite(10, LOW);

  // Scan limit
  SPI.transfer(0xB);
  SPI.transfer(0x7);

  digitalWrite(10, HIGH);
  digitalWrite(10, LOW);

  //Decode
  SPI.transfer(0x9);
  SPI.transfer(0xFF);

  digitalWrite(10, HIGH);
  digitalWrite(10, LOW);

  SPI.transfer(0x1);
  SPI.transfer(0xa);

  digitalWrite(10, HIGH);
  delay(500);
}

void loop() {

  for (long counter = 0; counter < 6000; counter++) {
    count(counter);
    delay(4);
  }
}

void count (long number) {

  long diva = 0;
  for (int counter = 8; counter >= 1; counter--) {
    
    if (counter == 8) {
      diva = 10000000;
    }
    if (counter == 7) {
      diva = 1000000;
    }
    if (counter == 6) {
      diva = 100000;
    }
    if (counter == 5) {
      diva = 10000;
    }
    if (counter == 4) {
      diva = 1000;
    }
    if (counter == 3) {
      diva = 100;
    }
    if (counter == 2) {
      diva = 10;
    }
    if (counter == 1) {
      diva = 1;
    }
    digitalWrite(10, LOW);

    SPI.transfer(counter);
    // SPI.transfer((uint8_t)((number / (long)pow(10.0, counter - 1.0)) % 10));
    SPI.transfer((uint8_t)((number / diva) % 10));

    digitalWrite(10, HIGH);
  }

  SPI.transfer(0xf0 | number);
}

