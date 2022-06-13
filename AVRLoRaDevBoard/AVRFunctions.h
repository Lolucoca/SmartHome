/*
 * AVRFunctions.h
 *
 * Created: 05.05.2022 20:57:17
 *  Author: lucas
 */ 


#ifndef AVRFUNCTIONS_H_
#define AVRFUNCTIONS_H_


#include "General.h"
#include "Config.h"
#include <avr/io.h>


#define PORTA_ADDR 0x0400

#define DIR_OFFSET 0x00
#define DIRSET_OFFSET 0x01
#define DIRCLR_OFFSET 0x02
#define DIRTGL_OFFSET 0x03
#define OUT_OFFSET 0x04
#define OUTSET_OFFSET 0x05
#define OUTCLR_OFFSET 0x06
#define OUTTGL_OFFSET 0x07
#define IN_OFFSET 0x08

typedef struct GPIO{
	u8 pin;
	volatile u8 * port;
} GPIO;



#define TX PB0
#define RX PB1
#define SDA PB2
#define SCL PB3
#define LORA_RST PB4





extern GPIO LED0, LED1, LED2, LED3, LED4, LED5, LED6, LED7; 
extern GPIO GPIO0, GPIO1, GPIO2, GPIO3, GPIO4, GPIO5, GPIO6, GPIO7, GPIO8, GPIO9, GPIO10, GPIO11, GPIO12, GPIO13, GPIO14, GPIO15;
extern GPIO DIO0, DIO1, DIO2, DIO3, DIO4, DIO5; 

extern GPIO RFM_SS, RFM_RST;

extern GPIO LEDs[];
extern GPIO GPIOs[];
extern GPIO DIOs[];

void initializeAVR();


#endif /* AVRFUNCTIONS_H_ */