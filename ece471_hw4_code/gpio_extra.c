#include <stdio.h>

#include <fcntl.h>	/* open() */
#include <unistd.h>	/* close() */
#include <string.h>


int main(int argc, char **argv) {
	char buffer[10];
	int fd;
	char buffer1[10];
	char readme[16];
	char *str = "Reading pin...";
	int i = 0;

	fd = open("/sys/class/gpio/export",O_WRONLY); //Enabling gpio pin 18
	if(fd < 0) fprintf(stderr,"Error!\n");
	strcpy(buffer,"18");
	write(fd,buffer,2);
	close(fd);

	fd = open("/sys/class/gpio/gpio18/direction",O_WRONLY); // setting gpio18 to be an output
	if(fd < 0) fprintf(stderr,"Error!\n");
	write(fd,"out",3);
	close(fd);
	
	fd = open("/sys/class/gpio/export",O_WRONLY); //Library to enable a gpio
	strcpy(buffer1,"17"); 
	write(fd,buffer,2); //write to gpio17 to enable
	close(fd);

	while(str[i] != '\0'){ // did this for fu
	putchar(str[i]);
	fflush(stdout);
	usleep(125000);
	i++;
	}


	int x = readme[0]; //initializing x after readme[0] has been delcared
	while(1){ // Reading gpio17 in an infinte while loop
		
		
		while(readme[0] == x){
		usleep(1500000);
		fd = open("/sys/class/gpio/gpio17/value",O_RDONLY); //file to read from a gpio	
		read(fd,readme,16); 
		close(fd);
		}
		
		if(readme[0] == 48){ // checking if it is not "pressed"
			fd = open("/sys/class/gpio/gpio18/value",O_WRONLY); // turning gpio 18 off
			if(fd < 0) fprintf(stderr,"Error!\n");
			write(fd,"0",1);
			close(fd);
			printf("Button Not Pressed\n");
			x = readme[0];

		}

		if(readme[0] == 49){ // checking if it is " pressed"
			fd = open("/sys/class/gpio/gpio18/value",O_WRONLY); // turning pin 18 on
			if(fd < 0) fprintf(stderr,"Error!\n");
			write(fd,"1",1);
			close(fd);
			printf("Button Pressed \n");
			x = readme[0];
		}
	}




	return 0;
}

