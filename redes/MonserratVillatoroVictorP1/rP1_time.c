#include <stdio.h>
#include <time.h>

#include "rP1_time.h"

void getTime(int choice, char *buffer){
	time_t t;
	struct tm *stTm;

	t = time(NULL);
	stTm = localtime(&t);
	switch(choice){
		case 1:
			strftime(buffer,80,"%A, %d de %B de %Y", stTm);
			break;
		case 2:
			strftime(buffer,80,"%H:%M:%S", stTm);
			break;
		case 3:
			strftime(buffer,80,"%A, %d de %B de %Y; %H:%M:%S", stTm);
			break;
	}
}
