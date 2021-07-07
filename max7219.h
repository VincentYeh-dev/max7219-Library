#ifndef __MAX7219
#define __MAX7219

#include "Arduino.h"


#define MAX7219_NUMBER 2
#define MAX7219_ADRR_DIGIT(d) ((d+1)<<8)
#define MAX7219_ADRR_DECODE_MODE 0x0900
#define MAX7219_ADRR_INTENSITY 0x0a00
#define MAX7219_ADRR_SCAN_LIMIT 0x0b00
#define MAX7219_ADRR_SHUTDOWN 0x0C00
#define MAX7219_ADRR_DISPLAY_TEST 0x0f00



class MAX7219
{
  public:
    MAX7219(int din,int cs,int clk,int numberOfMax);
	void init();
	void clear();
	void shutdown(_Bool enable);
	void displayTest(_Bool enable);
	void setDecodeMode(uint8_t decode);
	void setIntensity(uint8_t intensity);
	void setScanLimit(uint8_t limit);
	void setDigit(uint8_t index,uint8_t digit,uint8_t data);
  private:
	int pin_din;
	int pin_cs;
	int pin_clk;
	int numberOfMax;
	void set_all_register(uint16_t);
	void set_single_register(uint8_t,uint16_t);
	void shiftOut(uint16_t);
	void pullCSDown();
	void pullCSUp();
	
};


#endif
