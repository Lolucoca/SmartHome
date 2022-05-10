/*
 * SPIFunctions.c
 *
 * Created: 05.05.2022 21:43:00
 *  Author: lucas
 */ 

#include "SPIFunctions.h"

void initializeSPI(){
	PORTMUX_SPIROUTEA = 0b00000001; //Set SPI0 to alternate position (PE0..4)
	PORTE_DIRSET = 0b00001101; //Set SS, SCK, MOSI to output
	PORTE_PIN3CTRL = 0b00001000; //Set SS to have pullup
	PORTE_OUTSET = 0b00001000;  //Set SS to high
	SPI0_CTRLA = 0b00100001; //Set to Master Mode and enable SPI
	SPI0_INTCTRL = 0b11100000; //Enable RX/TX Complete interrupts as well as Data Register Empty Interrupt

	_delay_ms(1); //Minimum before use
}

inline u8 rfmSpiRecv(u8 addr){
	spiSend(RFM_SPI_READ | addr);
	return spiRecv();
}

inline u8 spiRecv(){
	while((SPI0.INTFLAGS & INTFLAG_DREIF) == 0);
	//SPI0.DATA = 0x00;
	while((SPI0.INTFLAGS & INTFLAG_TXCIF) == 0);
	while((SPI0.INTFLAGS & INTFLAG_RXCIF) == 0);
	return (u8) SPI0.DATA;
}

inline void rfmSpiSend(u8 addr, u8 data){
	spiSend(RFM_SPI_WRITE | addr);
	spiSend(data);
}

inline void spiSend(u8 data){
	while((SPI0.INTFLAGS & INTFLAG_DREIF) == 0);
	SPI0.DATA = data;
	while((SPI0.INTFLAGS & INTFLAG_TXCIF) == 0);
	while((SPI0.INTFLAGS & INTFLAG_RXCIF) == 0);
}


