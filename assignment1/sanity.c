/*
 * Created by Ori Popowski & Lihi Sharkanski
 */
/***STUDENT***/

/*
 * Add a program called sanity. This program will fork 30 child processes. Each child process
 * will have a unique id (from 0 to 29) denoted by cid. All processes whose cid%3=0 will
 * immediately activate the nice system call once, reducing their priority to medium priority.
 * All processes whose cid%3=1 will immediately activate the nice system call twice, reducing
 * their priority to low priority. All processes whose cid%3=2 will remain with high priority.
 * The code of the child processes will print its cid 500 times and will then call exit.

 * The parent process will wait until its children exit, and then
 * 1. print the average waiting time, running time and turnaround time of all its children.
 * 2. print the waiting time, running time and turnaround time of all children in each priority group (i.e the statistics for each group),
 * 3. print the waiting time, running time and turnaround time of each child process.
 */

#include "types.h"
#include "user.h"

#define CHILDS 30
#define TIMES 500

int
main(void)
{
	int i, j;
	int wait, run;
	int highs, meds, lows;
	uint cid;
	uint cs[CHILDS]; /* cids */
	uint ws[CHILDS]; /* waits */
	uint rs[CHILDS]; /* runs */
	int ow, or;   /* overall wait and run times */
	int hw, hr;   /* high    wait and run times */
	int mw, mr;   /* medium  wait and run times */
	int lw, lr;   /* low     wait and run times */
	
	for (i = 0; i < CHILDS; ++i) {
		/* child */
		if (fork() == 0) {
			cid = getpid();
			switch (cid % 3) {
			case 1: nice();   /* fall through */
			case 0: nice();
			}
			for (j = 0; j < TIMES; ++j)
				printf(1, "%d\n", cid);
			exit();
		}
	}
	
	/* parent */
	highs = meds = lows = 0;
	ow = or = hw = hr = mw = mr = lw = lr = 0;
	for (i = 0; i < CHILDS; ++i) {
		cs[i] = wait2(&wait, &run);
		ws[i] = wait;
		rs[i] = run;
		ow += wait;
		or += run;
		switch (cs[i] % 3) {
		case 0: mw += wait;
		        mr += run;
		        ++meds;
		        break;
		case 1: lw += wait;
		        lr += run;
		        ++lows;
		        break;
		case 2: hw += wait;
		        hr += run;
		        ++highs;
		}
	}
	
	printf(1, "overall\t\tavg. run time: %d\n",                 or / CHILDS);
	printf(1, "overall\t\tavg. wait time: %d\n",                ow / CHILDS);
	printf(1, "overall\t\tavg. turnaround time: %d\n\n",       (ow + or) / CHILDS);
	printf(1, "high-priority\tavg. run time: %d\n",             hr / highs);
	printf(1, "high-priority\tavg. wait time: %d\n",            hw / highs);
	printf(1, "high-priority\tavg. turnaround time: %d\n\n",   (hw + hr) / highs);
	printf(1, "medium-priority\tavg. run time: %d\n",           mr / meds);
	printf(1, "medium-priority\tavg. wait time: %d\n",          mw / meds);
	printf(1, "medium-priority\tavg. turnaround time: %d\n\n", (mw + mr) / meds);
	printf(1, "low-priority\tavg. run time: %d\n",              lr / lows);
	printf(1, "low-priority\tavg. wait time: %d\n",             lw / lows);
	printf(1, "low-priority\tavg. turnaround time: %d\n\n",    (lw + lr) / lows);
	
	for (i = 0; i < CHILDS; ++i) {
		printf(1, "child %d run time: %d\n",          cs[i], rs[i]);
		printf(1, "child %d wait time: %d\n",         cs[i], ws[i]);
		printf(1, "child %d turnaround time: %d\n\n", cs[i], rs[i] + ws[i]);
	}
	exit();
}
