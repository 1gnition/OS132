/*
 * Authors: Ori Popowski & Lihi Sharkanski
 */


/**STUDENT**/

#include "sim.h"

#ifndef ACTIONS_H
#define ACTIONS_H

Action *makeact(int type, Cup *cup, int tid);
void freeacts(void);

#endif
