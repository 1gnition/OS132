/*
 * Modified by Ori Popowski & Lihi Sharkanski
 */



/**STUDENT**/

#include "types.h"
#include "user.h"
#include "shm.h"

static char *s = 
"\nthis test forks into parent and child. the child goes\n\
to sleep immediately, while the parent allocates\n\
a shared memory and writes a string into it, then\n\
it enables swapping and invokes wait(), which causes\n\
him to free all his pages including the shared ones.\n\
then, the child wakes up and attatches itself to that\n\
shared memory. if the string remains intact then swapping\n\
out failed. otherwise, swapping out succeeded. then the\n\
parent wakes up, which swaps its memory back in, and\n\
checks if the string it put earlier still remains it that\n\
same location. if it does, the swap in succeeded.\n\
otherwise, failed.\n\n\
press any key to continue.\n";


int
main(void)
{
	int shmid;
	char *shm;
	char c;

	printf(1, s);
	read(0, &c, 1);
	
	if (fork() == 0) {
		/* child */
		sleep(10);
		/* by now parent created shared mem. and was swapped out */		
		shmid = shmget(1234, 4096, GET);
		shm = shmat(shmid, SHM_RDWR);
		/* the shared mem. was freed due to parent's
		   swap out. should get garbage */
		if (strcmp(shm, "valar morghulis") != 0)
			printf(1, "swap out works ok\n");
		else
			printf(1, "swap out works failed\n");
		shmdt(shm);
		exit();
	}
	/* parent */
	shmid = shmget(1234, 4096, CREAT);
	shm = shmat(shmid, SHM_RDWR);
	strcpy(shm, "valar morghulis");
	enableSwapping();
	/* now wait() causes a swap-out */
	wait();
	disableSwapping();
	if (strcmp(shm, "valar morghulis") == 0)
		printf(1, "swap in works ok\n");
	else
		printf(1, "swap in failed\n");
		
	exit();
	return 1;
}



