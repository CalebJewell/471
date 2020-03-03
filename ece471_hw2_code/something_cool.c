#include <stdio.h>

int main(int argc, char **argv) {
int j = 31;
int color = 0;

	for(int i=1;i<16;i++){ //printing all 15 lines of my message
		printf("\033[%d;4;%dm",color,j); //assinging color coordinates
		printf("#%d: Whats up Jenny! \n",i);
		color++;
		//these next two for loops make sure the values don't exceed ANSI codes
		if(color == 2){
		j++;
		color = 0;
		}
		if(j==38){
		j = 31;
		}
	}
	printf("\n");
	return 0;
}
