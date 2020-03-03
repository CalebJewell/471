#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>



int main(int argc, char **argv) {

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

// 	Printing ece 471 
	
	while(1){

//output being ECE
	buffer[0] = 0x00;
	buffer[1] = 0x79; // printing a E
  	buffer[2] = 0x00;
 	buffer[3] = 0x39; // printing a C
	buffer[4] = 0x00;
	buffer[5] = 0x00;
	buffer[6] = 0x00;
	buffer[7] = 0x79; // printing a E
	buffer[8] = 0x00; 	
	buffer[9] = 0x00;
	write(fd,buffer,17); // writing all 17 bytes to the device at once 

	usleep(1000000);	

//clearing the bits of the board
	for(i=0;i<16;i++) buffer[1+i] = 0x00;
	write(fd,buffer,17);

	usleep(1000000);// delaying by a second

//setting the board to output 471
	buffer[0] = 0x00;
	buffer[1] = 0x66; // printing a 4
  	buffer[2] = 0x00;
 	buffer[3] = 0x07; // printing a 7
	buffer[4] = 0x00;
	buffer[5] = 0x00;
	buffer[6] = 0x00;
	buffer[7] = 0x06; // priting a 1
	buffer[8] = 0x00; 	
	buffer[9] = 0x00;
	write(fd,buffer,17);
	usleep(1000000);

//clearing the board
	for(i=0;i<16;i++) buffer[1+i] = 0x00;
	write(fd,buffer,17);
	usleep(1000000);// delaying by a second


	}
	
	/* Close device */

close(fd);

	return 0;
}
