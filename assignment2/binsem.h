/*
 * Authors: Ori Popowski & Lihi Sharkanski
 */


/**STUDENT**/

#include "spinlock.h"

#define QSIZE 1024

typedef struct {
  struct spinlock mutex;
  struct proc *queue[QSIZE];
  uint s;
  int head;
  int tail;
} binsem;

int binary_semaphore_create(int init);
int binary_semaphore_down(int id);
int binary_semaphore_up(int id);
