/*
 * Authors: Ori Popowski & Lihi Sharkanski
 */


/**STUDENT**/

#include "types.h"
#include "user.h"
#include "shm.h"
#include "mmu.h"


char *s = 
"!!!\n\
the following test attatches shared memory, then it\n\
detatches it and try to write into it. if a trap is\n\
raised, then this test succeeded.\n\
!!!\n\
press any key to continue.\n"
;


char *t = 
"!!!\n\
the following test attatches shared memory with\n\
readonly flag and then tries to write into it. if a\n\
trap is, then this test succeeded.\n\
!!!\n\
press any key to continue.\n"
;


/* Parent writes to shared memory and child prints
   the content. Further, the writing spans accross
   two pages to see if works also in this case */
void
share(void)
{
	int shmid;
	char *shm;
	printf(1, "shared memory test ");
	
	if (fork() == 0) {
		/* child */
		sleep(100);
		shmid = shmget(1234, 5000, GET);
		shm = (char *) shmat(shmid, SHM_RDONLY);
		if (strcmp(shm+PGSIZE-3, "valar morghulis") != 0)
			printf(1, "failed\n");
		else
			printf(1, "ok\n");
		shmdt(shm);
		exit();
	}
	/* parent */
	shmid = shmget(1234, 5000, CREAT);
	shm = (char *) shmat(shmid, SHM_RDWR);
	strcpy(shm+PGSIZE-3, "valar morghulis");
	shmdt(shm);
	wait();
}

/* Try to delete an attached shared memory */
void
delete1(void)
{
	int shmid;
	printf(1, "delete1 test ");
	
	shmid = shmget(5678, 100, CREAT);
	shmat(shmid, SHM_RDWR);
	
	if (shmdel(shmid) == -1)
		printf(1, "ok\n");
	else
		printf(1, "failed\n");
}

/* Try to delete a shmid that was never created */
void
delete2(void)
{
		printf(1, "delete2 test ");
	
	if (shmdel(14) == -1)
		printf(1, "ok\n");
	else
		printf(1, "failed\n");
}

void
delete3(void)
{
	int shmid;
	
	printf(1, "delete3 test ");
	
	shmid = shmget(112, 100, CREAT);
	if (shmdel(shmid) >= 0)
		printf(1, "ok\n");
	else
		printf(1, "failed\n");
}

/* Try to write into a detached share memory.
   If a trap is raised, then this test is ok */
void
detach(void)
{
	int shmid;
	char *shm;
	char c;
	
	printf(1, s);
	read(0, &c, 1);
		
	shmid = shmget(111, 100, CREAT);
	shm = (char *) shmat(shmid, SHM_RDWR);
	shmdt(shm);
	strcpy(shm, "123");
}

/* Try to write into a read-only shared memory.
   If a trap is raised, then this test is ok */
void
readonly(void)
{
	int shmid;
	char *shm;
	char c;
	
	printf(1, t);
	read(0, &c, 1);
	
	shmid = shmget(321, 100, CREAT);
	shm = shmat(shmid, SHM_RDONLY);
	
	strcpy(shm, "valar morghulis");
}

int
main(void)
{
	share();
	delete1();
	delete2();
	delete3();
	detach();
	readonly();
	exit();
}

