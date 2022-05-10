/*
 * RFM95W.c
 *
 * Created: 05.05.2022 21:28:50
 *  Author: lucas
 */ 

#include "RFM95W.h"

void initializeLoRa(){
	
	digitalWrite(RFM_SS, 0);
	
	//Set to Sleep Mode so we can write registers
	setSleepMode();
	
	//Reset both FIFOs to 0 using their base address registers
	rfmSpiSend(REG_FIFO_TX_BASE_ADDR_PTR, 0x00);
	rfmSpiSend(REG_FIFO_RX_BASE_ADDR_PTR, 0x00);
	
	//Set to Standby Mode
	setStdbyMode();
	
	//Set Modem Config
	rfmSpiSend(REG_MODEM_CONFIG, MODEM_CONFIG1);
	rfmSpiSend(REG_MODEM_CONFIG2, MODEM_CONFIG2);
	rfmSpiSend(REG_MODEM_CONFIG3, MODEM_CONFIG3);
	
	//Set Preamble Length to desired value
	setPreambleLength(PREAMBLELEN);
	
	//Set Frequency
	u32 frf = ((u32) RF_FREQ / (u32) OSC_FREQ) * ((u32) 1 << 19);
	rfmSpiSend(REG_FRF_MSB, ((u32) frf & 0xFF0000) >> 16);
	rfmSpiSend(REG_FRF_MID, ((u32) frf & 0x00FF00) >> 8);
	rfmSpiSend(REG_FRF_LSB, (u32) frf & 0x0000FF);
	
	//Set TX Power
	rfmSpiSend(REG_PA_CONFIG, PA_CONFIG);
	
	digitalWrite(RFM_SS, 1);
}

void setPreambleLength(u16 len){
	rfmSpiSend(REG_PREAMBLE_MSB, (len & 0xFF00) >> 8);
	rfmSpiSend(REG_PREAMBLE_LSB, len & 0x00FF);
}

void setSleepMode(){
	//Switch to Sleep Mode
	//Set Sleep Mode as well as LoRa Mode bits
	rfmSpiSend(REG_OP_MODE, OP_MODE_LORA | OP_MODE_SLEEP);

	//Verify
	u8 opModeReg = rfmSpiRecv(REG_OP_MODE);
	
	if(opModeReg != (OP_MODE_LORA | OP_MODE_SLEEP)){
		while(1){}
	}
}

void setStdbyMode(){
	//Switch to Standby Mode
	//Set Standby Mode as well as LoRa Mode bits
	rfmSpiSend(REG_OP_MODE, OP_MODE_LORA | OP_MODE_STDBY);

	//Verify
	u8 opModeReg = rfmSpiRecv(REG_OP_MODE);
	
	if(opModeReg != (OP_MODE_LORA | OP_MODE_STDBY)){
		while(1){}
	}
}

void setFSTXMode(){
	//Switch to FSTX Mode
	//Set FSTX Mode as well as LoRa Mode bits
	rfmSpiSend(REG_OP_MODE, OP_MODE_LORA | OP_MODE_FSTX);

	//Verify
	u8 opModeReg = rfmSpiRecv(REG_OP_MODE);
	
	if(opModeReg != (OP_MODE_LORA | OP_MODE_FSTX)){
		while(1){}
	}
}

void setTXMode(){
	//Switch to TX Mode
	//Set TX Mode as well as LoRa Mode bits
	rfmSpiSend(REG_OP_MODE, OP_MODE_LORA | OP_MODE_TX);

	//Verify
	u8 opModeReg = rfmSpiRecv(REG_OP_MODE);
	
	if(opModeReg != (OP_MODE_LORA | OP_MODE_TX)){
		while(1){}
	}
}

void setFSRXMode(){
	//Switch to FSRX Mode 
	//Set FSRX Mode as well as LoRa Mode bits
	rfmSpiSend(REG_OP_MODE, OP_MODE_LORA | OP_MODE_FSRX);

	//Verify
	u8 opModeReg = rfmSpiRecv(REG_OP_MODE);
	
	if(opModeReg != (OP_MODE_LORA | OP_MODE_FSRX)){
		while(1){}
	}
}

void setRXMode(){
	//Switch to RX Single Packet Mode
	//Set RX Mode as well as LoRa Mode bits
	rfmSpiSend(REG_OP_MODE, OP_MODE_LORA | OP_MODE_RXSINGLE);

	//Verify
	u8 opModeReg = rfmSpiRecv(REG_OP_MODE);
	
	if(opModeReg != (OP_MODE_LORA | OP_MODE_RXSINGLE)){
		while(1){}
	}
}

void setCADMode(){
	//Switch to CAD Mode
	//Set CAD Mode as well as LoRa Mode bits
	rfmSpiSend(REG_OP_MODE, OP_MODE_LORA | OP_MODE_CAD);

	//Verify
	u8 opModeReg = rfmSpiRecv(REG_OP_MODE);
	
	if(opModeReg != (OP_MODE_LORA | OP_MODE_CAD)){
		while(1){}
	}
}


void transmit(u8 * msg, u16 msglen, u16 receiver){
	
	digitalWrite(RFM_SS, 0);
	
	u8 header[HDR_LEN];
	memset(header, 0, HDR_LEN * sizeof(u8));
	createHeader(receiver, msglen, header);
	
	//Set FIFO to address 0
	
	spiSend(RFM_SPI_READ | 0x00); //Send Address of FIFO
	for(u16 i = 0; i < HDR_LEN; i++){
		//Write Header to FIFO
		spiSend(header[i]);
	}
	
	for(u16 i = 0; i < msglen; i++){
		//Write Message to FIFO
		spiSend(msg[i]);
	}
	
	//Set DIO config
	rfmSpiSend(REG_DIO_MAPPING1, DIO0_MAPPING1);
	
	//Set TX Mode to on and wait for interrupt
	setTXMode();
	
	//Wait for TXDone Interrupt
	while(!digitalRead(DIO0)){
		
	}
	
	digitalWrite(RFM_SS, 1);
}