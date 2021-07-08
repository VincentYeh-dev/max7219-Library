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
	
	
	displayTest(1);
	delay(200);
	displayTest(0);
	shutdown(1);
	setDecodeMode(0);
	clear();
	setIntensity(0x05);
	setScanLimit(0x07);
	shutdown(0);
	
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

void MAX7219::clear(){
	uint8_t i=0;
	for(;i<8;i++){
		set_all_register(MAX7219_ADRR_DIGIT(i));
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

void MAX7219::setDigit(uint8_t index,uint8_t digit,uint8_t data){
	set_single_register(index,MAX7219_ADRR_DIGIT(digit)|data);
}

void MAX7219::shutdown(_Bool enable){
	set_all_register(MAX7219_ADRR_SHUTDOWN|!enable);
}

void MAX7219::displayTest(_Bool enable){
	set_all_register(MAX7219_ADRR_DISPLAY_TEST|enable);
}

void MAX7219::setDecodeMode(uint8_t decode){
	set_all_register(MAX7219_ADRR_DECODE_MODE|decode);
}

void MAX7219::setIntensity(uint8_t intensity){
	set_all_register(MAX7219_ADRR_INTENSITY|intensity);
}

void MAX7219::setScanLimit(uint8_t limit){
	set_all_register(MAX7219_ADRR_SCAN_LIMIT|limit);
}

void MAX7219::pullCSDown(){
	digitalWrite(pin_cs,LOW);
}

void MAX7219::pullCSUp(){
	digitalWrite(pin_cs,HIGH);
}
