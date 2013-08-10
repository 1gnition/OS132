/*
 * Authores: Ori Popowski & Lihi Sharkanski
 */


/**STUDENT**/
/*
 * This file handles the creation and freeing
 * of Action types for the simulation.
 */

#include "actions.h"
#include "sim.h"
#include "types.h"
#include "user.h"

/* linked list of Actions */
struct actnode {
  Action *act;
  struct actnode *next;
};

struct actnode *ahead;
struct actnode *atail;


/* Creates an Action with the given 
   attributes and returns it */
Action *
makeact(int type, Cup *cup, int tid)
{
  Action *act;
  struct actnode *node;
  
  act = malloc(sizeof *act);
  node = malloc(sizeof *node);
  
  act->type = type;
  act->cup = cup;
  act->tid = tid;
  
  node->act = act;
  node->next = 0;
  
  if (ahead == 0) {
    ahead = node;
    atail = node;
  } else {
    atail->next = node;
    atail = node;
  }
  
  return act;
}

/* Frees all allocated memory for Actions */
void
freeacts(void)
{
  struct actnode *tmp;
  while (ahead != 0) {
    tmp = ahead;
    ahead = ahead->next;
    free(tmp->act);
    free(tmp);
  }
}


/*
 * Authores: Ori Popowski & Lihi Sharkanski
 */


/**STUDENT**/
/*
 * This file handles the creation and freeing
 * of Action types for the simulation.
 */

#include "actions.h"
#include "sim.h"
#include "types.h"
#include "user.h"

/* linked list of Actions */
struct actnode {
  Action *act;
  struct actnode *next;
};

struct actnode *ahead;
struct actnode *atail;


/* Creates an Action with the given 
   attributes and returns it */
Action *
makeact(int type, Cup *cup, int tid)
{
  Action *act;
  struct actnode *node;
  
  act = malloc(sizeof *act);
  node = malloc(sizeof *node);
  
  act->type = type;
  act->cup = cup;
  act->tid = tid;
  
  node->act = act;
  node->next = 0;
  
  if (ahead == 0) {
    ahead = node;
    atail = node;
  } else {
    atail->next = node;
    atail = node;
  }
  
  return act;
}

/* Frees all allocated memory for Actions */
void
freeacts(void)
{
  struct actnode *tmp;
  while (ahead != 0) {
    tmp = ahead;
    ahead = ahead->next;
    free(tmp->act);
    free(tmp);
  }
}


/**STUDENT**/

#include "types.h"
//#include "defs.h"
#include "user.h"
#include "boundedbuffer.h"

#define FOO 10

boundbuf *b;

void *
producer(void)
{
  int i;
  int **items;
  int *retval;
  int *nums;
  
  items = malloc(FOO * (sizeof items[0]));
  retval = malloc(sizeof *retval);
  nums = malloc(FOO * (sizeof nums[0]));
  
  for (i = 0; i < FOO; ++i)
    nums[i] = i + 3;
  
  for (i = 0; i < FOO; ++i)
    items[i] = &nums[i];
  
  for (i = 0; i < FOO; ++i) {
    BB_put(b, items[i]);
    printf(1, "put #%d\n", *items[i]);
    sleep(10);
  }
  
  thread_exit(retval);
  return (void *) 1;
}

void *
consumer(void)
{
  int i;
  int *item;
  int *retval;
  
  retval = malloc(sizeof *retval);
  
  for (i = 0; i < FOO; ++i) {
    printf(1, "waiting to pop...\n");
    item = BB_pop(b);
    printf(1, "pop #%d\n", *item);
  }
  
  thread_exit(retval);
  return (void *) 1;
}

int
main(void)
{
  int tid1, tid2;
  char stack1[512], stack2[512];
  int *retval;
  
  b = BB_create(FOO);
  
  tid1 = thread_create(producer, stack1, 512);
  tid2 = thread_create(consumer, stack2, 512);
  
  thread_join(tid1, (void **) &retval);
  thread_join(tid2, (void **) &retval);
  
  exit();
}
/*
 * Authores: Ori Popowski & Lihi Sharkanski
 */


/**STUDENT**/
/*
 * This file handles the creation and freeing
 * of Action types for the simulation.
 */

#include "actions.h"
#include "sim.h"
#include "types.h"
#include "user.h"

/* linked list of Actions */
struct actnode {
  Action *act;
  struct actnode *next;
};

struct actnode *ahead;
struct actnode *atail;


/* Creates an Action with the given 
   attributes and returns it */
Action *
makeact(int type, Cup *cup, int tid)
{
  Action *act;
  struct actnode *node;
  
  act = malloc(sizeof *act);
  node = malloc(sizeof *node);
  
  act->type = type;
  act->cup = cup;
  act->tid = tid;
  
  node->act = act;
  node->next = 0;
  
  if (ahead == 0) {
    ahead = node;
    atail = node;
  } else {
    atail->next = node;
    atail = node;
  }
  
  return act;
}

/* Frees all allocated memory for Actions */
void
freeacts(void)
{
  struct actnode *tmp;
  while (ahead != 0) {
    tmp = ahead;
    ahead = ahead->next;
    free(tmp->act);
    free(tmp);
  }
}


/**STUDENT**/

#include "types.h"
//#include "defs.h"
#include "user.h"
#include "boundedbuffer.h"

#define FOO 10

boundbuf *b;

void *
producer(void)
{
  int i;
  int **items;
  int *retval;
  int *nums;
  
  items = malloc(FOO * (sizeof items[0]));
  retval = malloc(sizeof *retval);
  nums = malloc(FOO * (sizeof nums[0]));
  
  for (i = 0; i < FOO; ++i)
    nums[i] = i + 3;
  
  for (i = 0; i < FOO; ++i)
    items[i] = &nums[i];
  
  for (i = 0; i < FOO; ++i) {
    BB_put(b, items[i]);
    printf(1, "put #%d\n", *items[i]);
    sleep(10);
  }
  
  thread_exit(retval);
  return (void *) 1;
}

void *
consumer(void)
{
  int i;
  int *item;
  int *retval;
  
  retval = malloc(sizeof *retval);
  
  for (i = 0; i < FOO; ++i) {
    printf(1, "waiting to pop...\n");
    item = BB_pop(b);
    printf(1, "pop #%d\n", *item);
  }
  
  thread_exit(retval);
  return (void *) 1;
}

int
main(void)
{
  int tid1, tid2;
  char stack1[512], stack2[512];
  int *retval;
  
  b = BB_create(FOO);
  
  tid1 = thread_create(producer, stack1, 512);
  tid2 = thread_create(consumer, stack2, 512);
  
  thread_join(tid1, (void **) &retval);
  thread_join(tid2, (void **) &retval);
  
  exit();
}
/**STUDENT**/

#include "types.h"
#include "param.h"
#include "mmu.h"
#include "binsem.h"
#include "proc.h"
#include "defs.h"

#define BINSEMS 128

binsem binsems[BINSEMS];
int bsid = 0;

/* Takes id and returns the
   corresponding binary semaphore */
binsem *
getsem(int id)
{
  return &binsems[id];
}

/* Checks if binary semaphore's
   block queue is empty */
int
empty(binsem *sem)
{
  return sem->head == sem->tail;
}

/* Checks if binary semaphore's
   block queue is full */
int
full(binsem *sem)
{
  return ((sem->tail+1) % QSIZE) == (sem->head % QSIZE);
}  

/* Blocks the current process
   in the binary semaphore */
void
sem_block(binsem *sem)
{
  if (full(sem))
    panic("semaphore");
  sem->queue[sem->tail++] = proc;
  sem->tail %= QSIZE;
  sleep(proc, &sem->mutex);
}

/* Wakes up the oldest process in
   binary semaphore's queue */
void
sem_wakeup(binsem *sem)
{
  struct proc *p;
  
  if (empty(sem))
    panic("semaphore");
  p = sem->queue[sem->head++];
  sem->head %= QSIZE;
  wakeup(p);
}


/* Creates a binary semaphore with initial
   value `init' and returns its id */
int
binary_semaphore_create(int init)
{
  initlock(&binsems[bsid].mutex, "rasputin");
  binsems[bsid].head = 0;
  binsems[bsid].tail = 0;
  binsems[bsid].s = init;
  ++bsid;
  return bsid - 1;
}

/* Ups binary semaphore `id' */
int
binary_semaphore_down(int id)
{
  binsem *sem;
  
  sem = getsem(id);
  acquire(&sem->mutex);
  if (sem->s <= 0)
    sem_block(sem);
  else
    --sem->s;
  release(&sem->mutex);
  return 0;
}


/* Downs binary semaphore `id' */
int
binary_semaphore_up(int id)
{
  binsem *sem;
  
  sem = getsem(id);
  acquire(&sem->mutex);
  if (!empty(sem))
    sem_wakeup(sem);
  else
    ++sem->s;
  release(&sem->mutex);
  return 0;
}
