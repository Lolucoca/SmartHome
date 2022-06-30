/*
 * AVRFunctions.c
 *
 * Created: 05.05.2022 20:57:39
 *  Author: lucas
 */ 

#include "AVRFunctions.h"
GPIO LED0, LED1, LED2, LED3, LED4, LED5, LED6, LED7;
GPIO GPIO0, GPIO1, GPIO2, GPIO3, GPIO4, GPIO5, GPIO6, GPIO7, GPIO8, GPIO9, GPIO10, GPIO11, GPIO12, GPIO13, GPIO14, GPIO15;
GPIO DIO0, DIO1, DIO2, DIO3, DIO4, DIO5;
GPIO RFM_SS, RFM_RST;
GPIO RESET;

GPIO LEDs[NUM_LEDS];
GPIO GPIOs[NUM_GPIOS];
GPIO DIOs[NUM_DIOS];



void initializeAVR(){
	
	//Disable the Clock prescaler
	CLKCTRL_MCLKCTRLA = 0x00;
	//Set the Clock prescaler register to 0 (no division)
	CLKCTRL_MCLKCTRLB = 0x00;
	//Disable Configuration Change Protection
	CCP = 0xD8;
	//Set the Internal Oscillator to 24MHz
	CLKCTRL_OSCHFCTRLA = 0x26; 
	
	
	LED0 = (GPIO) {0b00000001, (volatile u8 *) &PORTA};
	LED1 = (GPIO) {0b00000010, (volatile u8 *) &PORTA};
	LED2 = (GPIO) {0b00000100, (volatile u8 *) &PORTA};
	LED3 = (GPIO) {0b00001000, (volatile u8 *) &PORTA};
	LED4 = (GPIO) {0b00010000, (volatile u8 *) &PORTA};
	LED5 = (GPIO) {0b00100000, (volatile u8 *) &PORTA};
	LED6 = (GPIO) {0b01000000, (volatile u8 *) &PORTA};
	LED7 = (GPIO) {0b10000000, (volatile u8 *) &PORTA};
		
	RFM_RST = (GPIO) {0b00010000, (volatile u8 *) &PORTB};
		
	GPIO0 = (GPIO) {0b00000001, (volatile u8 *) &PORTC};
	GPIO1 = (GPIO) {0b00000010, (volatile u8 *) &PORTC};
	GPIO2 = (GPIO) {0b00000100, (volatile u8 *) &PORTC};
	GPIO3 = (GPIO) {0b00001000, (volatile u8 *) &PORTC};
	GPIO4 = (GPIO) {0b00010000, (volatile u8 *) &PORTC};
	GPIO5 = (GPIO) {0b00100000, (volatile u8 *) &PORTC};
	GPIO6 = (GPIO) {0b01000000, (volatile u8 *) &PORTC};
	GPIO7 = (GPIO) {0b10000000, (volatile u8 *) &PORTC};
		
	GPIO8 = (GPIO) {0b00000001, (volatile u8 *) &PORTD};
	GPIO9 = (GPIO) {0b00000010, (volatile u8 *) &PORTD};
	GPIO10 = (GPIO) {0b00000100, (volatile u8 *) &PORTD};
	GPIO11 = (GPIO) {0b00001000, (volatile u8 *) &PORTD};
	GPIO12 = (GPIO) {0b00010000, (volatile u8 *) &PORTD};
	GPIO13 = (GPIO) {0b00100000, (volatile u8 *) &PORTD};
	GPIO14 = (GPIO) {0b01000000, (volatile u8 *) &PORTD};
	GPIO15 = (GPIO) {0b10000000, (volatile u8 *) &PORTD};
	
	RFM_SS = (GPIO) {0b00001000, (volatile u8 *) &PORTE};
		
	DIO0 = (GPIO) {0b00000001, (volatile u8 *) &PORTF};
	DIO1 = (GPIO) {0b00000010, (volatile u8 *) &PORTF};
	DIO2 = (GPIO) {0b00000100, (volatile u8 *) &PORTF};
	DIO3 = (GPIO) {0b00001000, (volatile u8 *) &PORTF};
	DIO4 = (GPIO) {0b00010000, (volatile u8 *) &PORTF};
	DIO5 = (GPIO) {0b00100000, (volatile u8 *) &PORTF};
		
	RESET = (GPIO) {0b01000000, (volatile u8 *) &PORTF};
		
		
	LEDs[0] = LED0;
	LEDs[1] = LED1;
	LEDs[2] = LED2;
	LEDs[3] = LED3;
	LEDs[4] = LED4;
	LEDs[5] = LED5;
	LEDs[6] = LED6;
	LEDs[7] = LED7;
	
	GPIOs[0] = GPIO0;
	GPIOs[1] = GPIO1;
	GPIOs[2] = GPIO2;
	GPIOs[3] = GPIO3;
	GPIOs[4] = GPIO4;
	GPIOs[5] = GPIO5;
	GPIOs[6] = GPIO6;
	GPIOs[7] = GPIO7;
	
	GPIOs[8] = GPIO8;
	GPIOs[9] = GPIO9;
	GPIOs[10] = GPIO10;
	GPIOs[11] = GPIO11;
	GPIOs[12] = GPIO12;
	GPIOs[13] = GPIO13;
	GPIOs[14] = GPIO14;
	GPIOs[15] = GPIO15;
	
	DIOs[0] = DIO0;
	DIOs[1] = DIO1;
	DIOs[2] = DIO2;
	DIOs[3] = DIO3;
	DIOs[4] = DIO4;
	DIOs[5] = DIO5;
	
}






