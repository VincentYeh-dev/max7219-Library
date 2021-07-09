#ifndef __MAX7219
#define __MAX7219

#include "Arduino.h"


#define MAX7219_ADRR_DIGIT(d) ((d+1)<<8)
#define MAX7219_ADRR_DECODE_MODE 0x0900
#define MAX7219_ADRR_INTENSITY 0x0a00
#define MAX7219_ADRR_SCAN_LIMIT 0x0b00
#define MAX7219_ADRR_SHUTDOWN 0x0C00
#define MAX7219_ADRR_DISPLAY_TEST 0x0f00



class MAX7219
{
  public:
	static const int ALL_MAX=-1;

    MAX7219(int din,int cs,int clk,int numberOfMax);
	void init();
	void clear(int index);
	void shutdown(int index,_Bool enable);
	void displayTest(int index,_Bool enable);
	void setDecodeMode(int index,uint8_t decode);
	void setIntensity(int index,uint8_t intensity);
	void setScanLimit(int index,uint8_t limit);
	void setDigit(int index,uint8_t digit,uint8_t data);
  private:
	int pin_din;
	int pin_cs;
	int pin_clk;
	int numberOfMax;
	void set_all_register(uint16_t);
	void set_single_register(uint8_t,uint16_t);
	void set_register(int index,uint16_t data);
	void shiftOut(uint16_t);
	void pullCSDown();
	void pullCSUp();
	
};


#endif
