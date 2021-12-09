#include "type.h"
#include "stdio.h"


int main(int argc, char * argv[])
{
	printf("\nB start\n");
	for(int i = 0; i < 400; i++) {
		printf("B");
		for(int j=0;j<1000000;j++){}
	}
	printf("\nB final\n");
	return 0;
}
