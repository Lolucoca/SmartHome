/*
 * SPIFunctions.c
 *
 * Created: 05.05.2022 21:43:00
 *  Author: lucas
 */ 

#include "SPIFunctions.h"

void initializeSPI(){
	PORTMUX_SPIROUTEA = 0b00000001; //Set SPI0 to alternate position (PE0..4)
	//PORTE_DIRSET = 0b00001101; //Set SS, SCK, MOSI to output
	SPI0_CTRLA = 0b00100000; //Set to Master Mode and enable SPI with prescaler /4, do not enable yet
	SPI0_CTRLB = 0b10000000; //Enable Buffered Mode. This avoids Write collisions.
	SPI0_INTCTRL = 0b11100000; //Enable RX/TX Complete interrupts as well as Data Register Empty Interrupt 00000001
	SPI0_CTRLA |= 0b00000001; 

	_delay_ms(1); //Minimum before use
}

u8 rfmSpiRecv(u8 addr){
	digitalWrite(RFM_SS, 0);
	spiSend(RFM_SPI_READ | addr);
	u8 temp;
	for(u8 i = 0; i < 2; i++){ //Clear read buffer because the RFM95W sends register contents even during writes
		temp = (u8) SPI0.DATA;
	}
	u8 data = spiRecv();
	digitalWrite(RFM_SS, 1);
	return data; 
}

u8 spiRecv(){
	u8 data; 
	while((SPI0.INTFLAGS & INTFLAG_DREIF) == 0);
	SPI0.DATA = 0xFF; //Send empty bits for clock to continue
	while((SPI0.INTFLAGS & INTFLAG_TXCIF) == 0);
	data = (u8) SPI0.DATA; //Data is initially 0
	
	//Read only the last byte of buffer
	while(SPI0.INTFLAGS & INTFLAG_RXCIF){
		data = (u8) SPI0.DATA; 
	}
	
	SPI0_INTFLAGS = 0xC0; //Reset Interrupts
	return data;
	
}

void rfmSpiSend(u8 addr, u8 data){
	u8 temp;
	digitalWrite(RFM_SS, 0);
	
	spiSend(RFM_SPI_WRITE | addr);
	//Clear read buffer because the RFM95W sends register contents even during writes
	temp = (u8) SPI0.DATA;
	
	spiSend(data);
	//Clear read buffer because the RFM95W sends register contents even during writes
	temp = (u8) SPI0.DATA;
	
	digitalWrite(RFM_SS, 1);
	SPI0_INTFLAGS = 0xC0;
}

void spiSend(u8 data){
	while((SPI0.INTFLAGS & INTFLAG_DREIF) == 0);
	SPI0.DATA = data;
	while((SPI0.INTFLAGS & INTFLAG_TXCIF) == 0);
	SPI0_INTFLAGS = 0xC0; //Reset Interrupts
	
}


