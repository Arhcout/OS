#include "Serial.h"
#include "kio.h"
#include <stdbool.h>
#include <stdint.h>

#define COM1 0x3F8
#define COM2 0x2F8
#define COM3 0x3E8
#define COM4 0x2E8

#define DEBUG_DIVISOR 3

typedef struct{
	uint8_t com1;
	uint8_t com2;
	uint8_t com3;
	uint8_t com4;
}COMQueue;
static COMQueue _bytesToRead;

void QueueRead(uint32_t port){
	switch (port) {
		case COM1:
			_bytesToRead.com1++;
			break;
		case COM2:
			_bytesToRead.com2++;
			break;
		case COM3:
			_bytesToRead.com3++;
			break;
		case COM4:
			_bytesToRead.com4++;
			break;
	}
}

void UpdateSerial(uint32_t port){
	uint8_t byteToRead; 
	switch (port) {
		case COM1:
			byteToRead = _bytesToRead.com1;
			break;
		case COM2:
			byteToRead = _bytesToRead.com2;
			break;
		case COM3:
			byteToRead = _bytesToRead.com3;
			break;
		case COM4:
			byteToRead = _bytesToRead.com4;
			break;
		default:
			return;
	}
	for (uint8_t i = 0; i < byteToRead; i++) {
		// echo the chararcter
		WriteSerial(port, ReadSerial(port));
	}
}

// static for now
static int _SerialReceived(uint32_t port) {
   return inb(port + 5) & 1;
}
 
char ReadSerial(uint32_t port) {
   while (_SerialReceived(port) == 0);
 
   return inb(port);
}

static int _IsTransmitEmpty(uint32_t port) {
   return inb(port + 5) & 0x20;
}
 
void WriteSerial(uint32_t port, char a) {
   while (_IsTransmitEmpty(port) == 0);
 
   outb(port,a);
}

int InitDebugSerial(uint32_t port){
	// Disable interrupts
	outb(port + 1, 0x00);

	// Set baud rate of port
	outb(port + 3, 0x80);
	outb(port + 0, DEBUG_DIVISOR & 0xFF);
	outb(port + 1, DEBUG_DIVISOR >> 8);

	outb(port + 3, 0x03); // 8 bit/chars, 1 stop bit, no parity bit,
	outb(port + 2, 0xC7); // Enable FIFO, clear them, with 14-byte threshold
	outb(port + 4, 0x0B); // IRQs enabled, RTS/DSR set
	outb(port + 4, 0x1E); // Set in loopback mode, test the serial chip
	outb(port + 0, 0xAE); // Test serial chip (send byte 0xAE and check if serial returns same byte)

	// Check if serial is faulty (i.e: not same byte as sent)
   if(inb(port + 0) != 0xAE) {
      return 1;
   }

	 // If serial is not faulty set it in normal operation mode
   // (not-loopback with IRQs enabled and OUT#1 and OUT#2 bits enabled)
   outb(port + 4, 0x0F);
	 outb(port+1, 1);
   return 0;
}
