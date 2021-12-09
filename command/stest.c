#include "type.h"
#include "stdio.h"
#include "sys/const.h"
#include "sys/protect.h"
#include "string.h"
#include "sys/fs.h"
#include "sys/proc.h"
#include "sys/tty.h"
#include "sys/console.h"
#include "sys/global.h"
#include "sys/proto.h"
/*
************************************************
fork  是父还是子进程 打印10次                  *
************************************************
*/
int main(int argc, char * argv[])
{
	int pid = fork();
	if(pid == 0) {
		for(int i = 0; i < 10; i++) {
			printf("child.\n");
		}
	} else {
		for(int i = 0; i < 10; i++) {
			printf("father.\n");
		}
	}
}