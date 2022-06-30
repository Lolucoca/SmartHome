/*
 * LoRaFunctions.c
 *
 * Created: 05.05.2022 21:41:53
 *  Author: lucas
 */ 

#include "LoRaFunctions.h"

void createHeader(u16 receiver, u16 len, u8 * headerPtr){
	/*memcpy(headerPtr + HDR_RECV_IDX, &receiver, HDR_RECV_LEN);
	memcpy(headerPtr + HDR_SENDER_IDX, &deviceID, HDR_SENDER_LEN);
	memcpy(headerPtr + HDR_MSG_LEN_IDX, &len, HDR_MSGLEN_LEN);*/
	*(headerPtr + HDR_RECV_IDX) = receiver >> 8; 
	*(headerPtr + HDR_RECV_IDX + 1) = receiver;
	*(headerPtr + HDR_SENDER_IDX) = deviceID >> 8; 
	*(headerPtr + HDR_SENDER_IDX + 1) = deviceID;
	*(headerPtr + HDR_MSGLEN_IDX) = len >> 8; 
	*(headerPtr + HDR_MSGLEN_IDX + 1) = len;
	*(headerPtr + HDR_MISC_IDX) = 0x00 >> 8; 
	*(headerPtr + HDR_MISC_IDX + 1) = 0x00; 
}

