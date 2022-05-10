/*
 * AVRLoRaDevBoard.c
 *
 * Created: 05.05.2022 20:56:11
 * Author : lucas
 */ 

#include "AVRFunctions.h"
#include "GPIOFunctions.h"
#include "LoRaFunctions.h"
#include "RFM95W.h"
#include "SPIFunctions.h"


int main(void){
	initializeGPIO();
	initializeAVR();
	initializeSPI();
	initializeLoRa();
    /* Replace with your application code */
    
	u8 message[] = {0xAA, 0x55, 0x00, 0xFF, 0xDE, 0xAD, 0xBE, 0xEF};
	
	while (1){
		digitalWrite(LED0, 0);
		transmit(message, 8, 0x01);
		for(u32 i = 0; i < 5000000; i++){
			asm("nop");
		}
		digitalWrite(LED0, 1);
    }
}

