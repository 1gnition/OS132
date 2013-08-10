/*
 * Created by Ori Popowski & Lihi Sharkanski
 */
/***STUDENT***/


#include "types.h"
#include "user.h"

#define TIMES 200
#define CHILDS 5

int
main(void)
{
  int pid;
	int i, j;
	int w, r;
	int ws[CHILDS];
	int rs[CHILDS];
	int ps[CHILDS];
	
	for (i = 0; i < CHILDS; ++i) {
		/* child */
		if ((pid = fork()) == 0) {
			for (j = 0; j < TIMES; ++j)
				printf(1, "child %d prints for the %d time.\n", getpid(), j);
			exit();
		}
	}
	/* parent */
	for (i = 0; i < CHILDS; ++i) {
		r = w = 0;
		ps[i] = wait2(&w, &r);
		ws[i] = w;
		rs[i] = r;
	}
	for (i = 0; i < CHILDS; ++i)
		printf(1, "child %d: wait: %d, run: %d\n", ps[i], ws[i], rs[i]);
	exit();
}
