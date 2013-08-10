/*
 * Authors: Ori Popowski & Lihi Sharkanski
 */


/**STUDENT**/

#include "semaphore.h"

typedef struct {
  semaphore *mutex;
  semaphore *empty;
  semaphore *full;
  void **buffer;
  int head;
  int tail;
  int max;
  int flag;
} boundbuf;


boundbuf *BB_create(int max);
void BB_put(boundbuf *, void *);
void *BB_pop(boundbuf *);
void BB_put_wakeup(boundbuf *, void *, int, semaphore *);
void freebufs(void);
void stop(boundbuf *b);
