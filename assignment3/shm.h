/*
 * Authors: Ori Popowski & Lihi Sharkanski
 */


/***STUDENT***/

#define SHM_RDWR   0x002
#define SHM_RDONLY 0x000
#define SHMMAX     1024   /* max num. of shared memories at any given time */
#define PGMAX      16     /* max num. of shared memory pages per request */

enum {CREAT, GET};

int shmget(int key, uint size, int shmflg);
int shmdel(int shmid);
void *shmat(int shmid, int shmflg);
int shmdt(const void *shmaddr);
