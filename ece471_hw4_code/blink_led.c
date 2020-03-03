#include <stdio.h>

#include <fcntl.h>	/* open() */
#include <unistd.h>	/* close() */
#include <string.h>


int main(int argc, char **argv) {
	char buffer[10];
	int fd;

	fd = open("/sys/class/gpio/export",O_WRONLY); //Enabling gpio pin 18
	if(fd < 0) fprintf(stderr,"Error!\n");
	strcpy(buffer,"18");
	write(fd,buffer,2);
	close(fd);

	fd = open("/sys/class/gpio/gpio18/direction",O_WRONLY); // setting gpio18 to be an output
	if(fd < 0) fprintf(stderr,"Error!\n");
	write(fd,"out",3);
	close(fd);
	
	
	
	while(1){
	fd = open("/sys/class/gpio/gpio18/value",O_WRONLY); // turning pin 18 on
	if(fd < 0) fprintf(stderr,"Error!\n");
	write(fd,"1",1);
	close(fd);

	usleep(1000000); // delaying between

	fd = open("/sys/class/gpio/gpio18/value",O_WRONLY); // turning gpio 18 off
	if(fd < 0) fprintf(stderr,"Error!\n");
	write(fd,"0",1);
	close(fd);
	
	usleep(1000000); // delay again 
	}



	return 0;
}

