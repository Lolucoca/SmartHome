/*
 * GPIOFunctions.h
 *
 * Created: 05.05.2022 23:20:21
 *  Author: lucas
 */ 


#ifndef GPIOFUNCTIONS_H_
#define GPIOFUNCTIONS_H_

#include "General.h"
#include "AVRFunctions.h"

void initializeGPIO();
void digitalWrite(GPIO pin, u8 value);
u8 digitalRead(GPIO pin);


#endif /* GPIOFUNCTIONS_H_ */