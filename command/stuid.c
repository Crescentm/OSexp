#include "stdio.h"

int main(int argc,char *argv[])
{
    if(argc != 2) {
		printf("Please input member's name!\n");
	} else {
		if (argv[1][0] == 'l'&&argv[1][1] == 'x'&&argv[1][2]=='t'&&argv[1][3]==0) {
			printf("2019302180141\n");
		} else if (argv[1][0] == 'l'&&argv[1][1] == 'n'&&argv[1][2]==0){
			printf("2019302180130\n");
		}else if (argv[1][0] == 'w'&&argv[1][1]=='k'&&argv[1][2]=='l'&&argv[1][3]==0){
			printf("2018302080201\n");
		} else if (argv[1][0] == 'h'&&argv[1][1]=='y'&&argv[1][2]=='y'&&argv[1][3]==0){
			printf("2019302180161\n");
		} else {
			printf("NOT IN GROUP!\n");
		}
	}
    return 0;
}
