#include <stdio.h>
#include <stdlib.h>	/* atof() */

#include "write_display.h"

int main(int argc, char **argv) {

	double temperature=42.0;

	if (argc>1) {
		temperature=atof(argv[1]);
	}
	printf("Testing temperature with %.4lf\n",temperature);

	return 0;
}

