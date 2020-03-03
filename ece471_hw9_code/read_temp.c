#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "read_temp.h"

 double read_temp(void) {
	char *filename = "/sys/bus/w1/devices/28-0416565043ff/w1_slave";
	int len = 0;
	double temp_f, result=0.0;
	char string1[256], string2[256], temp[256];
	FILE *fff;
	fff = fopen(filename,"r"); //opening the file to read
	fscanf(fff,"%*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %s %*s %*s %*s %*s %*s %*s %*s %*s %*s %s ",string1,string2); //reading first two lines of the file
	if(strcmp(string1,"YES") != 0){
	printf("Error!! NOT \"YES\"");
	return -999; //returning invalid temperature
	}
	
	len = strlen(string2); //storing the length of the string2 into len for incrementing purposes
	
	for(int i=2;i<=len;i++){
	temp[i-2] = string2[i]; //storing the tempature value into temp
	}
	temp_f = atof(temp); //asci into float
	result = temp_f / 1000; //converting into celcius 
	return result;
}

/*int main(int argc, char **argv) {

	double temp1;

	while(1) {

		temp1=read_temp(SENSOR_NAME);
		printf("%.2lfC\n",temp1);
		sleep(1);
	}

	return 0;
}*/
