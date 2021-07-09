#include "max7219.h"

MAX7219::MAX7219(int din,int cs,int clk,int number){
	pin_din=din;
	pinMode(din,OUTPUT);
	pin_cs=cs;
	pinMode(cs,OUTPUT);
	pin_clk=clk;
	pinMode(clk,OUTPUT);
	numberOfMax=number;
}

void MAX7219::init()
{	
	digitalWrite(pin_din,LOW);
	digitalWrite(pin_cs,HIGH);
	digitalWrite(pin_clk,LOW);
	
	
	displayTest(ALL_MAX,1);
	delay(200);
	displayTest(ALL_MAX,0);
	shutdown(ALL_MAX,1);
	setDecodeMode(ALL_MAX,0);
	clear(ALL_MAX);
	setIntensity(ALL_MAX,0x05);
	setScanLimit(ALL_MAX,0x07);
	shutdown(ALL_MAX,0);
	
}

void MAX7219::set_all_register(uint16_t data){
	pullCSDown();
	char i=0;
	for(i=0;i<numberOfMax;i++){
		shiftOut(data);
	}
	pullCSUp();
}

void MAX7219::set_single_register(uint8_t index,uint16_t data){
	pullCSDown();
	for(int i=numberOfMax-1;i>=0;i--){
		if(i==index){
			shiftOut(data);
		}else{
			shiftOut(0);
		}
	}
	
	pullCSUp();
}
void MAX7219::set_register(int index,uint16_t data){
	if(index==ALL_MAX)
		set_all_register(data);
	else
		set_single_register(index,data);
}

void MAX7219::clear(int index){
	uint8_t i=0;
	for(;i<8;i++){
		setDigit(index,i,0);
	}
}

void MAX7219::shiftOut(uint16_t data){
	uint8_t i=0;
	_Bool d=0;
	
	for(;i<16;i++){
		d=((data&0x8000)!=0);
		if(d){
			digitalWrite(pin_din,HIGH);
		}else{
			digitalWrite(pin_din,LOW);
		}
		
		digitalWrite(pin_clk,HIGH);
		
		digitalWrite(pin_clk,LOW);
		
		data=((data<<1)&0xffff);
	}
		digitalWrite(pin_din,LOW);
}

void MAX7219::setDigit(int index,uint8_t digit,uint8_t data){
	set_register(index,MAX7219_ADRR_DIGIT(digit)|data);
}

void MAX7219::shutdown(int index,_Bool enable){
	set_register(index,MAX7219_ADRR_SHUTDOWN|!enable);
}

void MAX7219::displayTest(int index,_Bool enable){
	set_register(index,MAX7219_ADRR_DISPLAY_TEST|enable);
}

void MAX7219::setDecodeMode(int index,uint8_t decode){
	set_register(index,MAX7219_ADRR_DECODE_MODE|decode);
}

void MAX7219::setIntensity(int index,uint8_t intensity){
	set_register(index,MAX7219_ADRR_INTENSITY|intensity);
}

void MAX7219::setScanLimit(int index,uint8_t limit){
	set_register(index,MAX7219_ADRR_SCAN_LIMIT|limit);
}

void MAX7219::pullCSDown(){
	digitalWrite(pin_cs,LOW);
}

void MAX7219::pullCSUp(){
	digitalWrite(pin_cs,HIGH);
}
