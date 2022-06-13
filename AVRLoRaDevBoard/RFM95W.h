/*
 * RFM95W.h
 *
 * Created: 05.05.2022 21:28:39
 *  Author: lucas
 */ 


#ifndef RFM95W_H_
#define RFM95W_H_

#include "General.h"
#include "LoRaFunctions.h"
#include "SPIFunctions.h"
#include "GPIOFunctions.h"

#define REG_FIFO 0x00
#define REG_OP_MODE 0x01
//7: 0: FSK/OOK Mode, 1: LoRa Mode WICHTIG: KANN NUR IM SLEEP-MODUS GESCHRIEBEN WERDEN
#define OP_MODE_FSK 0x00
#define OP_MODE_LORA 0x80
//6: 0: Konfigurationsregister sind für LoRa, 1: Konfigurationsregister sind für FSK/OOK WICHTIG: GEHT NUR IM LoRa-MODUS
//5-4 : Reserviert
//3: 0: High Frequency Mode, 1: Low Frequency Mode
#define LF_MODE_ON 0x08
//3-0 : 000 Sleep (SLEEP)
//		001 Standby (STDBY)
//		010 Frequency Synthesis TX (FSTX)
//		011 Transmit (TX)
//		100 Frequency Synthesis RX (FSRX)
//		101 Receive Continuous (RXCONTINUOUS)
//		110 Receive Single (RXSINGLE)
//		111 Channel Activity Detection (CAD)
#define OP_MODE_SLEEP 		 0x00
#define OP_MODE_STDBY 		 0x01
#define OP_MODE_FSTX 		 0x02
#define OP_MODE_TX 			 0x03
#define OP_MODE_FSRX 		 0x04
#define OP_MODE_RXCONTINUOUS 0x05
#define OP_MODE_RXSINGLE 	 0x06
#define OP_MODE_CAD          0x07

#define REG_FRF_MSB 0x06
#define REG_FRF_MID 0x07
#define REG_FRF_LSB 0x08
//f_Rf = (XOSC * Frf)/2^19 WICHTIG: KANN NUR IM SLEEP- ODER IM STANDBY-MODUS GESCHRIEBEN WERDEN

#define REG_PA_CONFIG 0x09
//7: 0: PA-Output: RFO-Pin, Output-Power-Limit 14dBm, 1: PA_BOOST-Pin, Output-Power-Limit 20dBm
//6-4 : Setzt maximale Output-Leistung: PMax = 10.8 + 0.6 * MaxPower [dBm]
//3-0 : Wenn Bit 7 gesetzt POut = 17-(15-OutputPower), sonst POut = PMax - (15-OutputPower)

#define REG_PA_RAMP 0x0A
//      Rise/Fall Time of Ramp Up/Down in FSK
//3-0 : 0000 3.4ms
//		0001 2ms
//		0010 1ms
// 		0011 500µs
//		0100 250µs
// 		0101 125µs
//		0110 100µs
// 		0111 62µs
//		1000 50µs
// 		1001 40µs
//		1010 31µs
// 		1011 25µs
//		1100 20µs
// 		1101 15µs
//		1110 12µs
// 		1111 10µs

#define REG_OCP 0x0B
//5: 0: OverCurrent Protection aus, 1: OCP an
//4-0 : OCP-Trim: Stellt den Strom ein, siehe Datenblatt

#define REG_LNA 0x0C
//7-5 : Stellt Gain ein
//		000: Unbenutzt
//		001: G1 (Maximum)
//		010: G2
//		011: G3
//		100: G4
//		101: G5
//		110: G6 (Minimum)
//		111: Unbenutzt

#define REG_FIFO_ADDR_PTR 0x0D
//SPI interface address pointer in FIFO data buffer

#define REG_FIFO_TX_BASE_ADDR_PTR 0x0E
//Write base address in FIFO data buffer for TX modulator

#define REG_FIFO_RX_BASE_ADDR_PTR 0x0F
//Read base address in FIFO data buffer for RX demodulator

#define REG_FIFO_RX_CURRENT_ADDR 0x10
//Start address (in data buffer) of last packet received

#define REG_IRQ_FLAGS_MASK 0x11
//7: RXTimeout-Mask
//6: RXDone-Mask
//5: PayloadCrcError-Mask
//4: ValidHeader-Mask
//3: TXDone-Mask
//2: CadDone-Mask
//1: FhssChangeChannel-Mask
//0: CadDetected-Mask
#define IRQ_RXTIMEOUT_MASK 		   0x80
#define IRQ_RXDONE_MASK    		   0x40
#define IRQ_PAYLOAD_CRC_ERROR_MASK 0x20
#define IRQ_VALID_HEADER_MASK 	   0x10
#define IRQ_TXDONE_MASK 		   0x08
#define IRQ_CADDONE_MASK 		   0x04
#define IRQ_FHSS_CHG_CHANNEL_MASK  0x02
#define IRQ_CADDETECTED_MASK 	   0x01

#define REG_IRQ_FLAGS 0x12
//7: RXTimeout
//6: RXDone
//5: PayloadCrcError
//4: ValidHeader
//3: TXDone
//2: CadDone
//1: FhssChangeChannel
//0: CadDetected
#define IRQ_RXTIMEOUT 		   0x80
#define IRQ_RXDONE    		   0x40
#define IRQ_PAYLOAD_CRC_ERROR  0x20
#define IRQ_VALID_HEADER 	   0x10
#define IRQ_TXDONE  		   0x08
#define IRQ_CADDONE 		   0x04
#define IRQ_FHSS_CHG_CHANNEL   0x02
#define IRQ_CADDETECTED 	   0x01

#define REG_RX_NB_BYTES 0x13
//Number of payload bytes of latest packet received

#define REG_RX_HEADER_CNT_VALUE_MSB 0x14
#define REG_RX_HEADER_CNT_VALUE_LSB 0x15
//Number of valid headers received since last transition into Rx mode. Header and packet counters are reseted in Sleep mode.

#define REG_RX_PACKET_CNT_VALUE_MSB 0x16
#define REG_RX_PACKET_CNT_VALUE_LSB 0x17
//Number of valid packets received since last transition into Rx mode. Header and packet counters are reseted in Sleep mode.

#define REG_MODEM_STAT 0x18
//7-5 : Coderate des letzten erkannten Headers
//4: 1: Modem Clear
//3: 1: Header Info Valid
//2: 1: RX On-Going
//1: 1: Signal synchronisiert
//0: 1: Signal erkannt
#define LAST_HDR_CODERATE 0xE0
#define MODEM_CLR		  0x10
#define HDR_INFO_VALID    0x08
#define RX_ONGOING		  0x04
#define SIGNAL_SYNCED	  0x02
#define SIGNAL_DETECTED	  0x01

#define REG_PKT_SNR_VALUE 0x19
//SNR-Wert-Schätzung des letzten Paketes im folgenden Format: SNR[dB] = (Registerwert (Zweierkomplement!!!))/4

#define REG_PKT_RSSI_VALUE 0x1A
//RSSI-Wert des letzten erkannten Paketes im folgenden Format: RSSI[dBm] = -137 + Registerwert

#define REG_RSSI_VALUE 0x1B
//Aktueller RSSI-Wert im folgenden Format: RSSI[dBm] = -137 + Registerwert

#define REG_HOP_CHANNEL 0x1C
//7: 1: PLL konnte nicht gelockt werden während einer TX/RX/CAD-Operation
//6: 0: Paket enthält keine CRC, 1: Paket enthält CRC
//5-0 : Aktueller Frequenz-Hopping-Kanal

#define REG_MODEM_CONFIG 0x1D
//7-4 : Signalbandbreite
//		0000: 7.8kHz
//		0001: 10.4kHz
//		0010: 15.6kHz
//		0011: 20.8kHz
//		0100: 31.25kHz
//		0101: 41.7kHz
//		0110: 62.5kHz
//		0111: 125kHz
//		1000: 250kHz
//		1001: 500kHz
//		WICHTIG: Im niedrigeren Band (169MHz) werden 8 und 9 nicht unterstützt
//
//3-1 : Coderate
//		000: 4/5
//		001: 4/6
//		010: 4/7
//		011: 4/8
//		WICHTIG: Sollte im Implicit Header Mode im Receiver gesetzt werden
//
//0: 0: Explicit Header Mode, 1: Implicit Header Mode


#define REG_MODEM_CONFIG2 0x1E
//7-4 : Spread-Faktor als Basis-2-Logarithmus
//		6:  64   Chips/Symbol
//		7:  128  Chips/Symbol
//		8:  256  Chips/Symbol
//		9:  512  Chips/Symbol
//		10: 1024 Chips/Symbol
//		11: 2048 Chips/Symbol
//		12: 4096 Chips/Symbol
//
//3:    TX Continuous Mode: 0: Normaler Modus, nur ein Paket wird gesendet, 1: Kontinuierlicher Modus (Continuous Mode), Sendet mehrere Pakete aus der FIFO (für Spektralanalyse)
//2:	RX Payload CRC On: 0: Empfangenes Paket enthält keine CRC, 1: Empfangenes Paket enthält CRC
//1-0 : RX Timeout MSB

#define REG_SYMB_TIMEOUT_LSB 0x1F
//RX Time-Out LSB, RX operation time-out value expressed as number of symbols: TimeOut = Registerinhalt * Ts

#define REG_PREAMBLE_MSB 0x20
//Preamble length MSB, = PreambleLength + 4.25 Symbols

#define REG_PREAMBLE_LSB 0x21
//Preamble Length LSB

#define REG_PAYLOAD_LENGTH 0x22
//Payload length in bytes. WICHTIG: Das Register muss im Implicit Header Mode auf die erwartete Paketlänge gesetzt sein, 0 geht nicht

#define REG_MAX_PAYLOAD_LENGTH 0x23
//Maximum payload length; if header payload length exceeds value a header CRC error is generated. Allows filtering of packet with a bad size.

#define REG_HOP_PERIOD 0x24
//Symbol periods between frequency hops. (0 = disabled). 1st hop always happen after the 1st header symbol

#define REG_FIFO_RX_BYTE_ADDR 0x25
//Current value of RX databuffer pointer (address of last byte written by Lora receiver)

#define REG_MODEM_CONFIG3 0x26
//3: MobileNode: 0: Für statischen Knoten zu verwenden, 1 für mobilen Knoten
//2: AgcAutoOn: 0: LNA Gain durch Register gesetzt, 1 setzt das automatisch

#define REG_FEI_MSB 0x28
#define REG_FEI_MID 0x29
#define REG_FEI_LSB 0x2A
//Estimated frequency error

#define REG_RSSI_WIDEBAND 0x2C
//Wideband RSSI measurement

#define REG_IF_FREQ1 0x2F
#define REG_IF_FREQ2 0x30
//Optimize Receiver

#define REG_DETECT_OPTIMIZE 0x31
//LoRa detection Optimize for SF6

#define REG_INVERT_IQ 0x33
//Invert LoRa I andQ signals

#define REG_HIGH_BW_OPTIMIZE1 0x36
//Sensitivity optimisation for 500kHz bandwidth

#define REG_DETECTION_THRESHOLD 0x37
//LoRa detection threshold for SF6

#define REG_SYNC_WORD 0x39
//LoRa Sync Word

#define REG_HIGH_BW_OPTIMIZE2 0x3A
//Sensitivity optimisation for 500kHz bandwidth

#define REG_INVERT_IQ2 0x3B
//Optimizefor invertedIQ

#define REG_DIO_MAPPING1 0x40
//Mapping of pins DIO0 to DIO3
#define DIO0_MAPPING0 0x00
#define DIO0_MAPPING1 0x40
#define DIO0_MAPPING2 0x80
#define DIO0_MAPPING3 0xC0

#define DIO1_MAPPING0 0x00
#define DIO1_MAPPING1 0x10
#define DIO1_MAPPING2 0x20
#define DIO1_MAPPING3 0x30

#define DIO2_MAPPING0 0x00
#define DIO2_MAPPING1 0x04
#define DIO2_MAPPING2 0x08
#define DIO2_MAPPING3 0x0C

#define DIO3_MAPPING0 0x00
#define DIO3_MAPPING1 0x01
#define DIO3_MAPPING2 0x02
#define DIO3_MAPPING3 0x03

#define REG_DIO_MAPPING2 0x41
//Mapping of pins DIO4 and DIO5, ClkOutfrequency
#define DIO4_MAPPING0 0x00
#define DIO4_MAPPING1 0x40
#define DIO4_MAPPING2 0x80
#define DIO4_MAPPING3 0xC0

#define DIO5_MAPPING0 0x00
#define DIO5_MAPPING1 0x10
#define DIO5_MAPPING2 0x20
#define DIO5_MAPPING3 0x30

#define REG_VERSION 0x42#
//Semtech ID relating the silicon revision

#define REG_TCXO 0x4B
//TCXO or XTAL input setting

#define REG_PA_DAC 0x4D
//Higher power settings of thePA

#define REG_FORMER_TEMP 0x5B
//Stored temperature during the former IQ Calibration

#define REG_AGC_REF 0x61
#define REG_AGC_THRESH1 0x62
#define REG_AGC_THRESH2 0x63
#define REG_AGC_THRESH3 0x64
//Adjustment of the AGC thresholds

#define REG_PLL 0x70
//Control of the PLL bandwidth


#define OSC_FREQ 32000000.0

#define MODEM_CONFIG1   ( \
						(BANDWIDTH == 7.8   ? 0b00000000 : 0b00000000) | \
						(BANDWIDTH == 10.4  ? 0b00010000 : 0b00000000) | \
						(BANDWIDTH == 15.6  ? 0b00100000 : 0b00000000) | \
						(BANDWIDTH == 20.8  ? 0b00110000 : 0b00000000) | \
						(BANDWIDTH == 31.25 ? 0b01000000 : 0b00000000) | \
						(BANDWIDTH == 41.7  ? 0b01010000 : 0b00000000) | \
						(BANDWIDTH == 62.5  ? 0b01100000 : 0b00000000) | \
						(BANDWIDTH == 125.0 ? 0b01110000 : 0b00000000) | \
						(BANDWIDTH == 250.0 ? 0b10000000 : 0b00000000) | \
						(BANDWIDTH == 500.0 ? 0b10010000 : 0b00000000) | \
						(CODINGRATE == 45   ? 0b00000010 : 0b00000000) | \
						(CODINGRATE == 46   ? 0b00000100 : 0b00000000) | \
						(CODINGRATE == 47   ? 0b00000110 : 0b00000000) | \
						(CODINGRATE == 48   ? 0b00001000 : 0b00000000)   \
						)

#define MODEM_CONFIG2   ( \
						(SPREADFACTOR == 64   ? 0b01100000 : 0b00000000) | \
						(SPREADFACTOR == 128  ? 0b01110000 : 0b00000000) | \
						(SPREADFACTOR == 256  ? 0b10000000 : 0b00000000) | \
						(SPREADFACTOR == 512  ? 0b10010000 : 0b00000000) | \
						(SPREADFACTOR == 1024 ? 0b10100000 : 0b00000000) | \
						(SPREADFACTOR == 2048 ? 0b10110000 : 0b00000000) | \
						(SPREADFACTOR == 4096 ? 0b11000000 : 0b00000000) | \
						(CRC		          ? 0b00000100 : 0b00000000)   \
						)

#define MODEM_CONFIG3  0x00

//#define FRF (u32) ((u32) RF_FREQ / (u32) OSC_FREQ) * (1 << 19)

#define PA_DAC ((RFHIPWR && (OUTPUTPOWER == 15)) ? 0x07 : 0x04)

//PA Select always to PA_BOOST, set Max Power to the maximum value allowed (0x07)
#define PA_CONFIG ( 0b11110000 | (15-OUTPUTPOWER))




void initializeLoRa();
void setPreambleLength(u16 len);
void setSleepMode();
void setStdbyMode();
void setFSTXMode();
void setTXMode();
void setFSRXMode();
void setRXMode();
void setCADMode();

void transmit(u8 * msg, u16 msglen, u16 receiver);
void receive(u8 * msgPtr);

#endif /* RFM95W_H_ */