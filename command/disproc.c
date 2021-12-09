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

int main(int argc, char * argv[])
{
	MESSAGE msg;
	int i;
	struct proc p;
	printf("%d\n",NR_TASKS);
	printf("%d\n",NR_PROCS);
	for(i = 0; i < NR_TASKS + NR_PROCS; i++) {
		msg.PID = i;
		msg.type = GET_PROC;
		msg.BUF = &p;
		send_recv(BOTH, TASK_SYS, &msg);
		char *str;
		if (p.p_flags != FREE_SLOT) {
			printf("%d  %s  ", i, p.name);
			if (p.p_flags == SENDING) {
				printf("SENDING");
			} else if (p.p_flags == RECEIVING) {
				printf("RECEIVING");
			} else if (p.p_flags == WAITING) {
				printf("WAITING");
			} else if (p.p_flags == HANGING) {
				printf("HANGING");
			} else {
				printf("Unknown");
			}
		}
	}
	return 0 ;
}
