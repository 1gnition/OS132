/*
 * Authors: Ori Popowski & Lihi Sharkanski
 */


#include "types.h"
#include "user.h"

void printf(int, char*, ...);
 
int
main(void)
{
	printf (1, "number of free blocks is %d\n", freeBlocks());
	exit();
	return 1;
}
