/*
 * SPIFunctions.h
 *
 * Created: 05.05.2022 21:42:40
 *  Author: lucas
 */ 


#ifndef SPIFUNCTIONS_H_
#define SPIFUNCTIONS_H_

#include "Config.h"
#include "GPIOFunctions.h"
#include <avr/io.h>
#include <util/delay.h>

#define INTFLAG_RXCIF  0b10000000
#define INTFLAG_TXCIF  0b01000000
#define INTFLAG_DREIF  0b00100000
#define INTFLAG_SSIF   0b00010000
#define INTFLAG_BUFOVF 0b00000001

#define RFM_SPI_READ 0x00
#define RFM_SPI_WRITE 0x80


void initializeSPI();
u8 rfmSpiRecv(u8 addr);
u8 spiRecv();
void rfmSpiSend(u8 addr, u8 data);
void spiSend(u8 data);

#endif /* SPIFUNCTIONS_H_ */