/*
 * Authors: Ori Popowski & Lihi Sharkanski
 */


/**STUDENT**/

#include "types.h"
#include "user.h" 
 
int
main(int argc, char **argv)
{
	char *path;
	
	if (argc != 2) {
		printf(1, "invalid number of arguments\n");
		exit();
	}
	
	path = argv[1];
	printf(1, "%s\n", path);
	fileBlocks(path);
	exit();
	return 1;
}
