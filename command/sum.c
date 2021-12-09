#include "type.h"
#include "stdio.h"
/*
************************************************
二个数加法                                     *
************************************************
*/
int atoi(char *nums) {
	char *p = nums;
	int res = 0;
	int minus = 0;
	if(*p == '-') {
		minus = 1;
		p++;
	}
	while(p != '\0') {
		if(*p >= 0x30 && *p <= 0x39) {
			res = res * 10 + (*p - 0x30);
		} else {
			if(minus) {
				res = -res;
			}
			return res;
		}
		p++;
	}
	if(minus) {
		res = -res;
	}
	return res;
}

int main(int argc, char * argv[])
{
	if(argc != 3) {
		printf("this proc need 2 prams!\n");
		return 0;
	}
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	printf("%d + %d = %d\n", a, b, a+b);
	return 0;
}