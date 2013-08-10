/*
 * Modified by Ori Popowski & Lihi Sharkanski
 */
/***STUDENT***/


/*
 * This program will print “Father pid is <pid>”, and then sleep
 * for 10 seconds. Then it will fork once, and both child and parent will print 50 times (each
 * time in a new line): “process <pid> is printing for the <i> time”, and then exit.
 */ 


#include "types.h"
#include "user.h"

#define TIMES 50

int
main(void)
{
	int i;
	uint pid;
	
	printf(1, "father pid is %d.\n", getpid());
	sleep(1000);
	pid = fork();
	for (i = 0; i < TIMES; ++i)
		printf(1, "process %d is printing for the %d time.\n", getpid(), i);
	if (pid != 0)
		wait();
	exit();
}
