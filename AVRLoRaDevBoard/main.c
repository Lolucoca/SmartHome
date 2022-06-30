/*
 * AVRLoRaDevBoard.c
 *
 * Created: 05.05.2022 20:56:11
 * Author : lucas
 */ 

#include "General.h"
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
    
	u8 message[] = {0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55};//{0xAA, 0x55, 0x00, 0xFF, 0xDE, 0xAD, 0xBE, 0xEF};
	u8 msgBuffer[128];
	Message msg = {0x0000, 0x0000, 0x0000, 0x0000, msgBuffer}; 
		
	startReceiver(); 
	
	while (1){
		
		if(!digitalRead(RESET)){
			//stopReceiver();
			digitalWrite(LED0, 1);
			transmit(message, 0x0008, 0x0001);
			startReceiver();
			_delay_ms(1000);
			digitalWrite(LED0, 0);
		}
		
		//startReceiver();
		if((RFMInterrupt) handleRFMInterrupts() == rxdone){
			receive(&msg);
			for(u8 i = 0; i < msg.msglen; i++){
				debugOutput(msg.data[i]);
				_delay_ms(100);
			}
			stopReceiver();
			transmit(msg.data, msg.msglen, msg.recv);
			startReceiver();
		}
		//stopReceiver();
			
			
		/*
		if(deviceType == receiver){
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
		
			startReceiver();
			
			//Wait for RX Done Interrupt on DIO0
			if(handleRFMInterrupts() == rxdone){
				receive(&msg);
				for(u8 i = 0; i < msg.msglen; i++){
					debugOutput(msg.data[i]);
					_delay_ms(100);
				}
				stopReceiver();
				transmit(msg.data, msg.msglen, msg.recv);
			}
			stopReceiver();
		}
		*/
    }
}

