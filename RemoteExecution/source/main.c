// Get binary data over serial, store it in memory, execute it from memory.
// Written by UNIX - LibXenon.org

// TODO: Test.

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "video_init.h"

#include <xenon_uart/xenon_uart.h>
#include <elf/elf.h>
#include <time/time.h>

// An array of bytes containing the ELF magic number.
unsigned char ELF_MAGIC[4] = {'E', 'L', 'F'};

// Variable used to store ELF check pass or fail.
int isELF = 0;

// Scan first 4 bytes of memory buffer to see if  it matches 
// the ELF magic number. 
void checkIsELF(void *memoryAddress){
	// Create a temporary 4 byte buffer.
	void *checksumBuffer = malloc(0x4);

	// Do the copy of the first 4 bytes.
	memcpy(memoryAddress, checksumBuffer, 4);

	// Check the checksumBuffer against the magic number.
	if(checksumBuffer == ELF_MAGIC) isELF = 1;
	else exit(-2);
}

int main(){
	// Initialize the screen and clear the console.
	videoInit();
	console_clrscr();

	/* Setup two memory addresses to store data in.
	   tempAddress is where raw incoming binary data is stored. 
	   elfAddress is where tempAddress is copied to, post ELF verification.
	*/
	void *tempAddress = malloc(0x1000000);
	unsigned char *elfAddress = malloc(sizeof(tempAddress));

	while(1){
		// Print status.
		printf("Reading");
		printf(".");

		// Variable to hold read binary data.
		unsigned char data = getch();

		// Instantiate a counter for the number of bytes we have read.
		long int bytesRead = 0;

		// Up the counter of the number of bytes we have read.
		bytesRead++;
		int numBytes = bytesRead;

		// Copy data to memory buffer.
		memcpy(tempAddress, data, numBytes);

		/* If no more data is being received, perform ELF check.
		   If check passes, copy temporary buffer contents to 
		   final buffer, free temporary buffer, and execute
		   the elf from final memory address.
		*/
		if(data == NULL){
			checkIsELF(tempAddress);

			if(isELF == 1){
				printf("do nothing");
			}
		}
	}

	return 0;
}

