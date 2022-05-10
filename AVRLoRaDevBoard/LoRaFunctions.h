/*
 * LoRaFunctions.h
 *
 * Created: 05.05.2022 21:42:05
 *  Author: lucas
 */ 


#ifndef LORAFUNCTIONS_H_
#define LORAFUNCTIONS_H_

#include <string.h>
#include "Config.h"
#include "General.h"


#define HDR_RECV_LEN 2
#define HDR_SENDER_LEN 2
#define HDR_MSG_LEN 2
#define HDR_MISC_LEN 2
#define HDR_LEN HDR_RECV_LEN + HDR_SENDER_LEN + HDR_MSG_LEN + HDR_MISC_LEN
//Header consists of the following:
//Byte 7-6: Message To (Receiver)
//Byte 5-4: Message To (Sender)
//Byte 3-2: Message Length in Bytes
//Byte 1-0: TBD

#define HDR_RECV_IDX 0
#define HDR_SENDER_IDX 2
#define HDR_MSG_IDX 4
#define HDR_MISC_IDX 6

u8 hdrBuf[HDR_LEN];

void createHeader(u16 receiver, u16 len, u8 * headerPtr);

#endif /* LORAFUNCTIONS_H_ */