#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#include <sys/ioctl.h>
#include <linux/spi/spidev.h>

#define LENGTH 3

int main(int argc, char **argv) {
	int spi_fd = 0;
	int mode = SPI_MODE_0;
	int result;
	int value;
	struct spi_ioc_transfer spi;
	unsigned char data_out[LENGTH] = {0x1,0x00,0x0};
	unsigned char data_in[LENGTH];
	double Vin = 0;
	double deg_c = 0,max = 0 ,min = 24;
	double c2Value;
	int i = 0;
	
	ioctl(spi_fd,SPI_IOC_WR_MODE,&mode);
	memset(&spi,0,sizeof(struct spi_ioc_transfer));
	
	spi . tx_buf = (unsigned long)&data_out;
	spi . rx_buf = (unsigned long)&data_in;
	spi . len = LENGTH;
	spi . delay_usecs = 0;
	spi . speed_hz = 100000;
	spi . bits_per_word = 8;
	spi . cs_change = 0;

	/* Open SPI device */
	spi_fd = open("/dev/spidev0.0",O_RDWR);

	/* Set SPI Mode_0 */
	result = ioctl(spi_fd, SPI_IOC_MESSAGE(1), &spi);
	if(result < 0) printf("Error\n");
	/* Loop forever printing the CH0 and CH1 Voltages 	*/
	/* Once per second.					*/

	while(1){
	data_out[1] = 0x10; //setting what channel i want to read
	ioctl(spi_fd,SPI_IOC_MESSAGE(1),&spi);// storing the data into data_in
	value = (data_in[1] << 8) | data_in[2];
//	printf("First byte: %d\n", data_in[1]);
//	printf("Second byte: %d\n", data_in[2]);
	Vin = (value * 3.3) /1024;
	


	data_out[1] = 0xA0; //setting what channel i want to read
	ioctl(spi_fd,SPI_IOC_MESSAGE(1),&spi);// storing the data into data_in
	c2Value = ((data_in[1] << 8) +  data_in[2]) & 0x03FF;;
	c2Value = (c2Value * Vin) / 1024;
	deg_c = (100 * c2Value) - 50;
	printf("Degrees(C): %f\n",deg_c);
	usleep(1000000);
	
	//setting up max and min values
	if(deg_c > max) max = deg_c;
	if(deg_c < min) min = deg_c;
	i = i+1;
	printf("%d\n",i);
	

	//printing max and min values after 15 seconds
	if(i == 15){
	i = 0;
	printf("Max: %f Celcius & Min: %f Celcius\n",max,min);
	}
	}

	/* Use the SPI_IOC_MESSAGE(1) ioctl() as described in the class notes */

	return 0;
}
