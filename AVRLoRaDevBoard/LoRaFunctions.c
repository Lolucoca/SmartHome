/*
 * LoRaFunctions.c
 *
 * Created: 05.05.2022 21:41:53
 *  Author: lucas
 */ 

#include "LoRaFunctions.h"

void createHeader(u16 receiver, u16 len, u8 * headerPtr){
	memcpy(headerPtr + HDR_RECV_IDX, &receiver, HDR_RECV_LEN);
	memcpy(headerPtr + HDR_SENDER_IDX, &deviceID, HDR_SENDER_LEN);
	memcpy(headerPtr + HDR_MSG_IDX, &len, HDR_MSG_LEN);
}

