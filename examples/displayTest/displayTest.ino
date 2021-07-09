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
  max7219.displayTest(MAX7219::ALL_MAX,1);
  delay(1000);
  max7219.displayTest(MAX7219::ALL_MAX,0);
  delay(1000);
}
