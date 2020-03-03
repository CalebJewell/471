#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#include <sys/ioctl.h>
#include <linux/spi/spidev.h>


int main(int argc, char **argv) {

        int spi_fd;

	/* Open SPI device */

	/* Set SPI Mode_0 */

	/* Loop forever printing the CH0 and CH1 Voltages 	*/
	/* Once per second.					*/

	/* Use the SPI_IOC_MESSAGE(1) ioctl() as described in the class notes */

	return 0;
}
