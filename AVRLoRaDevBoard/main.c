/*
 * AVRLoRaDevBoard.c
 *
 * Created: 05.05.2022 20:56:11
 * Author : lucas
 */ 

#define F_CPU 24000000UL

#include "util/delay.h"
#include "AVRFunctions.h"
#include "GPIOFunctions.h"
#include "LoRaFunctions.h"
#include "RFM95W.h"
#include "SPIFunctions.h"

 


int main(void){
	initializeAVR();
	initializeGPIO();
	initializeSPI();
	initializeLoRa();
    /* Replace with your application code */
    
	u8 message[] = {0xAA, 0x55, 0x00, 0xFF, 0xDE, 0xAD, 0xBE, 0xEF};
	transmit(message, 8, 0x01);
	while (1){
		for(u8 i = 0; i < 8; i++){
			digitalWrite(LEDs[i], 1);
			_delay_ms(25);
			digitalWrite(LEDs[i], 0);
			_delay_ms(25);
		}
		
		for(u8 i = 6; i > 0; i--){
			digitalWrite(LEDs[i], 1);
			_delay_ms(25);
			digitalWrite(LEDs[i], 0);
			_delay_ms(25);
		}
		
		
		/*digitalWrite(LED0, 1);
		//transmit(message, 8, 0x01);
		_delay_ms(250);
		digitalWrite(LED0, 0);
		
		_delay_ms(250);*/
    }
}

