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
/**STUDENT**/

#include "types.h"
#include "param.h"
#include "mmu.h"
#include "binsem.h"
#include "proc.h"
#include "boundedbuffer.h"
#include "user.h"

/* function names are obscenely lengthy */
#define up(x)     semaphore_up(x)
#define down(x)   semaphore_down(x)

#define BBUFS 128

boundbuf bbufs[BBUFS];
int bid = 0;
void *bufmal[BBUFS];    /* pointers to all the buffer
                           mallocs for later freeing */


/* Creates a bounded buffer with
   capacity `max' and returns it */
boundbuf *
BB_create(int max)
{
  boundbuf *b;
  
  b = &bbufs[bid];
  bufmal[bid] = malloc((max+1) * (sizeof b->buffer[0]));
  
  b->max = max;
  b->buffer = bufmal[bid];
  b->mutex = semaphore_create(1);
  b->empty = semaphore_create(max);
  b->full = semaphore_create(0);
  b->head = 0;
  b->tail = 0;
  ++bid;
  
  return b;
}

/* Puts item `item' in bounded buffer `b' */
void
BB_put(boundbuf *b, void *item)
{
  down(b->empty);
  down(b->mutex);
  b->buffer[b->tail++] = item;
  b->tail %= b->max;
  up(b->mutex);
  up(b->full);
}

/* Pops item `item' in bounded buffer `b' */
void *
BB_pop(boundbuf *b)
{
  void *item;
  down(b->full);
  down(b->mutex);
  if (b->flag) {   /* this is interesting */
    up(b->full);
    up(b->mutex);
    return 0;
  }
  item = b->buffer[b->head++];
  b->head %= b->max;
  up(b->mutex);
  up(b->empty);
  return item;
}

/* Puts item `item' in bounded buffer `b'. Ups
   semaphore `s' when `b' is `perc' percent full */
void
BB_put_wakeup(boundbuf *b, void *item, int perc, semaphore *s)
{
  double val;
  double max;
  down(b->empty);
  down(b->mutex);
  b->buffer[b->tail++] = item;
  b->tail %= b->max;
  val = (double) b->full->val;
  max = (double) b->max;
  if (perc <= val / max * 100.0)
    up(s);
  up(b->mutex);
  up(b->full);
}

/* Frees all allocated buffers */
void
freebufs(void)
{
  int i;
  for (i = 0; i < bid; ++i)
    free(bufmal[i]);
}

/* Stops all producers */
void
stop(boundbuf *b)
{
  down(b->mutex);
  b->flag = 1;
  up(b->full);
  up(b->mutex);
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
/**STUDENT**/

#include "types.h"
#include "param.h"
#include "mmu.h"
#include "binsem.h"
#include "proc.h"
#include "boundedbuffer.h"
#include "user.h"

/* function names are obscenely lengthy */
#define up(x)     semaphore_up(x)
#define down(x)   semaphore_down(x)

#define BBUFS 128

boundbuf bbufs[BBUFS];
int bid = 0;
void *bufmal[BBUFS];    /* pointers to all the buffer
                           mallocs for later freeing */


/* Creates a bounded buffer with
   capacity `max' and returns it */
boundbuf *
BB_create(int max)
{
  boundbuf *b;
  
  b = &bbufs[bid];
  bufmal[bid] = malloc((max+1) * (sizeof b->buffer[0]));
  
  b->max = max;
  b->buffer = bufmal[bid];
  b->mutex = semaphore_create(1);
  b->empty = semaphore_create(max);
  b->full = semaphore_create(0);
  b->head = 0;
  b->tail = 0;
  ++bid;
  
  return b;
}

/* Puts item `item' in bounded buffer `b' */
void
BB_put(boundbuf *b, void *item)
{
  down(b->empty);
  down(b->mutex);
  b->buffer[b->tail++] = item;
  b->tail %= b->max;
  up(b->mutex);
  up(b->full);
}

/* Pops item `item' in bounded buffer `b' */
void *
BB_pop(boundbuf *b)
{
  void *item;
  down(b->full);
  down(b->mutex);
  if (b->flag) {   /* this is interesting */
    up(b->full);
    up(b->mutex);
    return 0;
  }
  item = b->buffer[b->head++];
  b->head %= b->max;
  up(b->mutex);
  up(b->empty);
  return item;
}

/* Puts item `item' in bounded buffer `b'. Ups
   semaphore `s' when `b' is `perc' percent full */
void
BB_put_wakeup(boundbuf *b, void *item, int perc, semaphore *s)
{
  double val;
  double max;
  down(b->empty);
  down(b->mutex);
  b->buffer[b->tail++] = item;
  b->tail %= b->max;
  val = (double) b->full->val;
  max = (double) b->max;
  if (perc <= val / max * 100.0)
    up(s);
  up(b->mutex);
  up(b->full);
}

/* Frees all allocated buffers */
void
freebufs(void)
{
  int i;
  for (i = 0; i < bid; ++i)
    free(bufmal[i]);
}

/* Stops all producers */
void
stop(boundbuf *b)
{
  down(b->mutex);
  b->flag = 1;
  up(b->full);
  up(b->mutex);
}
/**STUDENT**/

/*
 * This file handles the creation and freeing
 * of Cup types for the simulation.
 */

#include "sim.h"
#include "cups.h"
#include "types.h"
#include "user.h"

/* linked list of Cups */
struct cupnode {
  Cup *cup;
  struct cupnode *next;
};

struct cupnode *chead;
struct cupnode *ctail;
int cupid;


/* Creates a Cup with a
   unique id and returns it */
Cup *
makecup(void)
{
  Cup *cup;
  struct cupnode *node;
  
  cup = malloc(sizeof *cup);
  node = malloc(sizeof *node);
  
  cup->id = cupid++;
  
  node->cup = cup;
  node->next = 0;
  
  if (chead == 0) {
    chead = node;
    ctail = node;
  } else {
    ctail->next = node;
    ctail = node;
  }
  return cup;
}

/* Frees all allocated memory for Actions */
void
freecups(void)
{
  struct cupnode *tmp;
  while (chead != 0) {
    tmp = chead;
    chead = chead->next;
    free(tmp->cup);
    free(tmp);
  }
}


//#define __CUPS 4096

//Cup _cups[__CUPS];
//int _cupid;

//Cup *
//makecup(void)
//{
  //Cup *cup;
  //cup = &_cups[_cupid];
  //cup->id = _cupid++;
  //return cup;
//}

//void
//freecups(void)
//{
  
//}
