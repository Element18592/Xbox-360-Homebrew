/* This header contains the trivial initialization code to set the 
\  GPU output resolution, initializte the system console, and initialize
\  USB. This code will almost never need to be modified, unless you want 
\  to specify the default resolution which is set to automatic. 
*/

#include <xenos/xenos.h>
#include <console/console.h>
#include <usb/usbmain.h>

void mainInit(){	
	xenos_init(VIDEO_MODE_AUTO);
	console_init();
}
