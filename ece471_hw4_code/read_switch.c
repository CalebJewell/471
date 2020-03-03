#include <stdio.h>

#include <fcntl.h>	/* open() */
#include <unistd.h>	/* close() */
#include <string.h>


int main(int argc, char **argv) {
	char buffer[10];
//	char readme[16];
	char *str = "I hate my life";
	int fd,i = 0;
//	printf("Reading pin...\n");
	fd = open("/sys/class/gpio/export",O_WRONLY); //Library to enable a gpio
	strcpy(buffer,"17"); 
	write(fd,buffer,2); //write to gpio17 to enable
	close(fd);

	while(str[i] != '\0'){
	putchar(str[i]);
	fflush(stdout);
	usleep(125000);
	i++;
	}
	printf("\n");

//	int x = readme[0]; //initializing x after readme[0] has been delcared
/*	while(1){ // Reading gpio17 in an infinte while loop
		
		
		while(readme[0] == x){
		usleep(2000000);
		fd = open("/sys/class/gpio/gpio17/value",O_RDONLY); //file to read from a gpo	
		read(fd,readme,16); 
		close(fd);
		}
		
		if(readme[0] == 48){ // checking if it is not "pressed"
			printf("Button Not Pressed\n");
			x = readme[0];

		}

		if(readme[0] == 49){ // checking if it is " pressed"
			printf("Button Pressed \n");
			x = readme[0];
		}	
	}*/
	return 0;

}
