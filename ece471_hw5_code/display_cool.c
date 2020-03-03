#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>



int main(int argc, char **argv) {

	int fd, i;

	char i2c_device[]="/dev/i2c-1";

	unsigned char buffer[17] = {0x00} ;
	
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
if(result < 0) fprintf(stderr,"Error!\n");
	/* Turn on Display, No Blink */

buffer[0] = 0x81; // turning on display with blinking off
write(fd, buffer,1); // writing the value to the buffer

	/* Set Brightness */

buffer[0] = 0xEC; // set dimming to 13 
write(fd, buffer, 1); //writing to the display

// 	Printing ece 471 

	char name[] = {0x79,0x39,0x79,0x66,0x07,0x06,0x00,0x00,0x00,0x00};	


	while(1){
	buffer[0] = 0x00;

//	usleep(100000);
	// iterating 10 times because it takes 10 shifts to get the message on and off the screen
	for(i=0;i<10;i++){
	buffer[9] = name[i]; 
	if(i >=1) buffer[7] = name[i-1]; 
	if(i >=2) buffer[3] = name[i-2]; //these if statements shift the hex values to the left
	if(i >=3) buffer[1] = name[i-3]; //it sets the next buffer to the previous buffer 
	write(fd,buffer,17);
	usleep(240000);
	}
	
}

close(fd);

	return 0;
}
