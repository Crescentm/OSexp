#include "type.h"
#include "stdio.h"



int main(int argc, char * argv[])
{
	printf("\nA start\n");
	for(int i = 0; i < 400; i++) {
		printf("A");
		for(int j=0;j<1000000;j++)
			{}
	}
	printf("\nA final\n");
	return 0;
}
