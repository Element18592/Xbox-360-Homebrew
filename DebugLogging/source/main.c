// Local Includes
#include "video_init.h"

// Standard C includes
#include <stdio.h>

// Xenon includes
#include <libfat/fat.h>

void debug(char *str){
	FILE *DebugLog;
	DebugLog = fopen("uda:/DebugLog.txt","a+");
	fprintf(DebugLog, "%s\n", str);
}

int main(){
	mainInit();
	usb_init();
	fatInitDefault ();
	usb_do_poll();

	debug("This will be logged to USB.");
	printf("This will be output to the console and UART.");
}

