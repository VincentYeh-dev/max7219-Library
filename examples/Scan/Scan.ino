#include "max7219.h"

// Din pin : D10
// CS pin  : D12
// CLK pin : D11
// Number of Max7219 : 2
MAX7219 max7219(10,12,11,2);

void setup() {
  max7219.init();
}

void loop() {
  for (int i = 0; i < 8; i++)
  {
    max7219.setDigit(MAX7219::ALL_MAX,i,0xff);
    delay(1000);
  }
  max7219.clear(MAX7219::ALL_MAX);
}
