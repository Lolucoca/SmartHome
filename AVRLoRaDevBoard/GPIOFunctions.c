/*
 * GPIOFunctions.c
 *
 * Created: 05.05.2022 23:20:10
 *  Author: lucas
 */ 

#include "GPIOFunctions.h"

void initializeGPIO(){
	//PORTA: LEDs
	PORTA_DIRSET = 0xFF; 
	
	//PORTC: GPIO Low Byte
	PORTC_DIRSET = 0xFF; 
	
	//PORTD: GPIO High Byte
	PORTD_DIRSET = 0xFF; 
	
	//PORTF: DIOs (All Inputs)
	PORTF_DIRSET = 0x00;
}

void digitalWrite(GPIO pin, u8 value){

	if(value > 0){
		*(pin.port + OUTSET_OFFSET) = pin.pin; //OUTSET-Register
	} else {
		*(pin.port + OUTCLR_OFFSET) = pin.pin; //OUTCLEAR-Register
	}
}

u8 digitalRead(GPIO pin){
	u8 bankData = *(pin.port + IN_OFFSET);
	return bankData;
}
