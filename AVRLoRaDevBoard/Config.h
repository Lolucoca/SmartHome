/*
 * Config.h
 *
 * Created: 05.05.2022 20:58:10
 *  Author: lucas
 */ 


#ifndef CONFIG_H_
#define CONFIG_H_

#include "General.h"

typedef enum{transmitter, receiver} TYPE;
//typedef enum{7.8, 10.4, 15.6, 20.8, 31.25, 41.7, 62.5, 125, 250, 500} BANDWIDTH;
//typedef enum{45, 46, 47, 48} CODINGRATE;
//typedef enum{64, 128, 256, 512, 1024, 2048, 4096} SPREADFACTOR;

#define NUM_LEDS 8
#define NUM_GPIOS 16
#define NUM_DIOS 6

#define deviceType receiver
#define BANDWIDTH 125
#define CODINGRATE 48
#define SPREADFACTOR 4096
#define CRC 1
#define RF_FREQ 915000000.0
#define OUTPUTPOWER 5 //0-15
#define RFHIPWR 1
#define OUTPUTPOWERDBM (17 - (15 - OUTPUTPOWER)) + (RFHIPWR ? 3 : 0);
#define PREAMBLELEN 8 //?

static const u16 deviceID = 0x0001; //Master




#endif /* CONFIG_H_ */