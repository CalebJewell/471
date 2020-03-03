#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
			
int init_display(void) {
	int fd, i;

	char i2c_device[]="/dev/i2c-1";

	unsigned char buffer[17];
	
	int result;

	/* Open i2c device */

fd  = open(i2c_device, O_RDWR);
if(fd < 0) fprintf(stderr,"Error!\n"); // error checking to make sure we opened the write file

	/* Set slave address */

result = ioctl(fd, I2C_SLAVE,0x70); 
if(result < 0) fprintf(stderr,"Error!\n");

	/* Turn on oscillator */

buffer[0] = (0x2<<4) | (0x1);
result = write(fd, buffer, 1);

	/* Turn on Display, No Blink */

buffer[0] = 0x81; // turning on display with blinking off
write(fd, buffer,1); // writing the value to the buffer

	/* Set Brightness */

buffer[0] = 0xEC; // set dimming to 13 
write(fd, buffer, 1); //writing to the display


	return fd;
}

int write_display(int fd, double value) {
	
	return 0;
}



int shutdown_display(int fd) {

	return 0;

}




/*int main(int argc, char **argv) {


// 	Printing ece 471 
	
	while(1){

//output being ECE
	buffer[0] = 0x00;*/
