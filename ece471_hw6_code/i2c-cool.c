#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>

#include "i2c-bitbang.h"


int main(int argc, char **argv) {

	int result;
	unsigned char buffer[17] = {0};

	/*******************************************/
	/* Init the GPIO lines we are going to use */
	/* to bitbang the i2c                      */
	/*******************************************/
	result=i2c_init_gpios(SDA_GPIO,SCL_GPIO);
	if (result<0) {
		exit(1);
	}


	/****************************************/
	/****************************************/
	/* Start the display			*/
	/****************************************/
	/****************************************/

	/* Address of device, and we want to write */
        buffer[0]= 0x70<<1 | 0x0;
	/* Command 0x20 = SYSTEM SETUP  (See p30 of manual) */
	/* Action  0x01 = Turn on oscillator */
        buffer[1]= 0x20 | 0x01;

	/* Write the two bytes in our buffer */
	result=write_i2c(buffer,2);
        if ( result<0 ) {
                fprintf(stderr,"Error starting display (enable oscilator)!\n");
                return -1;
        }

	/****************************************/
	/****************************************/
	/* Turn display on, no blinking		*/
	/****************************************/
	/****************************************/

	/* Address of device, and we want to write */
        buffer[0]= 0x70<<1 | 0x0;

	/* Command = 0x80 Setup*/
	/* Action = Blinking off, display on */
        buffer[1]= 0x80 | 0x1;

	/* Write the two bytes in our buffer */
	result=write_i2c(buffer,2);
        if ( result<0 ) {
                fprintf(stderr,"Error starting display (turning on)!\n");
                return -1;
        }



	/****************************************/
	/****************************************/
	/* Set Brightness			*/
	/****************************************/
	/****************************************/

	/* Address of device, and we want to write */
        buffer[0]= 0x70<<1 | 0x0;

	/* Command = 0xe0 Dimming */
	/* Action = Brightness = 10/16 */
        buffer[1]= 0xe0 | 0xa;

	/* Write the two bytes in our buffer */
	result=write_i2c(buffer,2);
        if ( result<0 ) {
                fprintf(stderr,"Error setting brightness!\n");
                return -1;
        }
	
	
// -----------------------------------------------------------------------------------


	char name[] = {0x79,0x39,0x79,0x66,0x07,0x06,0x00,0x00,0x00,0x00};	
	

	while(1) {
	
		/* Address of device, and we want to write */
		buffer[0]= 0x70<<1 | 0x0;

		/* Command 0x0, address = 0x0 */
		buffer[1]=0x00;

	// iterating 10 times because it takes 10 shifts to get the message on and off the screen
		for(int i=0;i<10;i++){
			buffer[10] = name[i]; 
			if(i >=1) buffer[8] = name[i-1]; 
			if(i >=2) buffer[4] = name[i-2]; //these if statements shift the hex values to the left
			if(i >=3) buffer[2] = name[i-3]; //it sets the next buffer to the previous buffer 
			result = write_i2c(buffer,17);
			usleep(240000);
		}		

		

//		result=write_i2c(buffer,17);

//		usleep(500000);


		/* Address of device, and we want to write */

//		buffer[0]= 0xe0;


		/* Command 0x0, address = 0x0 */

//		buffer[1]=0x0;

		/* Turn off all bits in display */


	}
	return 0;

}
