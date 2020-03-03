#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include "gpio.h"
#include "i2c-bitbang.h"

/* Global variables */
static int scl_fd,sda_fd;

/* Pull the SDA gpio pin low */
static int SDA_gpio_pull_low(void) {

	int result=0;

	/* This function should set the SDA GPIO direction to out */
	/* and then write the value '0' to sda_fd		  */

	gpio_set_output(SDA_GPIO); // 
	result = write(sda_fd,"0",1);
	if(result < 0) printf("Error");

	/* return the result of the write() call */

	return result;

}

/* Pull the SCL gpio pin low */
static int SCL_gpio_pull_low(void) {

	int result=0;

	/* This function should set the GPIO direction to write */
	/* and then write the value '0' to sda_fd		*/

	gpio_set_output(SCL_GPIO);
	result = write(scl_fd,"0",1);
	if(result < 0) printf("Error");

	/* return the result of the write() call */

	return result;

}

/* Let SDA float high */
static int SDA_gpio_float_high(void) {

	int result=0;

	/* This function should set the SDA GPIO direction to input	*/
	/* Which allows the open collector bus to float high		*/

	gpio_set_input(SDA_GPIO);

	return result;

}

/* Let SCL float high */
static int SCL_gpio_float_high(void) {

	int result=0;

	/* This function should set the SCL GPIO direction to input	*/
	/* Which allows the open collector bus to float high		*/

	gpio_set_input(SCL_GPIO);

	return result;

}

/* read the value of SDA */
static int read_SDA(void) {

	unsigned char value = 0;
	char buffer[1];
	/* This function should set the GPIO direction to read	*/
	/* rewind the file descriptor, then read SDA.		*/
	/* remember to convert from ASCII before returning.	*/

	gpio_set_input(SDA_GPIO);
	lseek(sda_fd,0,SEEK_SET);
	read(sda_fd,buffer,1);
	value = buffer[0] - 48;
	return value;
}

/* read the value of SCL */
/*static int read_SCL(void) {

	unsigned char value=0;

	* This function should set the GPIO direction to read	
	* rewind the file descriptor, then read SCL		
	* remember to convert from ASCII before returning.	

	gpio_set_input(SCL_GPIO);
	lseek(scl_fd,0,SEEK_SET); // rewinding sda_fd
	read(scl_fd,value,1);
	value -= 48;
	return value;
}*/



static int I2C_delay(void) {

	usleep(4);	/* 4us, although due to sysfs overhead */
			/* and inherent usleep() limitations   */
			/* we are going to be much slower.     */

	return 0;

}


static void i2c_start_bit(void) {

	/* For a start bit, SDA goes from high to low while SCL is high */

	SCL_gpio_float_high();
	I2C_delay();
	SDA_gpio_float_high();
	SDA_gpio_pull_low();

	return;
}


static void i2c_stop_bit(void) {

	/* For a stop bit, SDA goes from low to high while SCL is high */

	SCL_gpio_float_high(); 
	I2C_delay();
	SDA_gpio_pull_low();
	SDA_gpio_float_high();

	return;
}

static int i2c_read_bit(void) {

	int bit=0;

	/* Let SDA and SCL go high.  Then read SDA.  The set SCL low */

	SDA_gpio_float_high(); // setting SDA to high
	I2C_delay();
	SCL_gpio_float_high(); // setting SCL 
	I2C_delay();
	bit = read_SDA();
	I2C_delay();
	SCL_gpio_pull_low(); //turning SCL off 
	return bit;

}

static int i2c_write_bit(int bit) {

	/* Pull SCL low.  Set sda to the value you want. */
	/* Then toggle SCL high then low */

	SCL_gpio_pull_low();
	if(bit == 1){
		SDA_gpio_float_high(); // setting to high if 1
	}
	else SDA_gpio_pull_low(); // low if 0 
	I2C_delay();
	SCL_gpio_float_high();
	I2C_delay();
	SCL_gpio_pull_low();
	return 0;

}

	/* Write 8 bits out and check for NACK */
static int i2c_write_byte(unsigned char byte) {

	int nack = 1;
	int sig = 0;
	for(int i=7;i>=0;i--){ // shifting the appropriate bits in
	sig = byte  >> i & 1; 
	i2c_write_bit(sig);
	}
	nack = i2c_read_bit();
	return nack;
}


	/* Write a series of bytes */
int write_i2c(unsigned char *bytes, int number) {

	int i;
	int result=0;

	i2c_start_bit();

	for(i=0;i<number;i++) {
		result=i2c_write_byte(bytes[i]);
		if (result<0) {
			printf("Error writing!\n");
			break;
		}

	}

	i2c_stop_bit();

	return result;

}


/* Initialize two file descriptors to be used for SDA and SCL */
/* They are global variables to make the code a bit easier    */
int i2c_init_gpios(int sda, int scl) {

        char string[BUFSIZ];

	/* Enable the GPIOs */
	if (gpio_enable(sda)<0) printf("Error enabling SDA\n");
	if (gpio_enable(scl)<0) printf("Error enabling SCL\n");

	/* Open the SDA fd */
	printf("Using GPIO%d as SDA\n",sda);
        sprintf(string,"/sys/class/gpio/gpio%d/value",sda);
        sda_fd=open(string,O_RDWR);
        if (sda_fd<0) {
                fprintf(stderr,"\tError getting value!\n");
                return -1;
        }

	/* Open the SCL fd */
	printf("Using GPIO%d as SCL\n",scl);
	sprintf(string,"/sys/class/gpio/gpio%d/value",scl);

        scl_fd=open(string,O_RDWR);
        if (scl_fd<0) {
                fprintf(stderr,"\tError getting value!\n");
                return -1;
        }

	/* Set the read/write direction of the GPIOs */
	gpio_set_input(sda);
	gpio_set_input(scl);

	return 0;
}
