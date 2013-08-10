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
/* TODO
 * make fork, wait and exit work with threads
 * make file sharing
 */

#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"
#include "spinlock.h"

struct {
  struct spinlock lock;
  struct proc proc[NPROC];
} ptable;

static struct proc *initproc;

int nextpid = 1;
extern void forkret(void);
extern void trapret(void);

static void wakeup1(void *chan);

void
pinit(void)
{
  initlock(&ptable.lock, "ptable");
}

//PAGEBREAK: 32
// Look in the process table for an UNUSED proc.
// If found, change state to EMBRYO and initialize
// state required to run in the kernel.
// Otherwise return 0.
static struct proc*
allocproc(void)
{
  struct proc *p;
  char *sp;

  acquire(&ptable.lock);
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
    if(p->state == UNUSED)
      goto found;
  release(&ptable.lock);
  return 0;

found:
  p->state = EMBRYO;
  p->pid = nextpid++;
  release(&ptable.lock);

  // Allocate kernel stack.
  if((p->kstack = kalloc()) == 0){
    p->state = UNUSED;
    return 0;
  }
  sp = p->kstack + KSTACKSIZE;
  
  // Leave room for trap frame.
  sp -= sizeof *p->tf;
  p->tf = (struct trapframe*)sp;
  
  // Set up new context to start executing at forkret,
  // which returns to trapret.
  sp -= 4;
  *(uint*)sp = (uint)trapret;

  sp -= sizeof *p->context;
  p->context = (struct context*)sp;
  memset(p->context, 0, sizeof *p->context);
  p->context->eip = (uint)forkret;

  return p;
}

//PAGEBREAK: 32
// Set up first user process.
void
userinit(void)
{
  struct proc *p;
  extern char _binary_initcode_start[], _binary_initcode_size[];
  
  p = allocproc();
  initproc = p;
  if((p->pgdir = setupkvm(kalloc)) == 0)
    panic("userinit: out of memory?");
  inituvm(p->pgdir, _binary_initcode_start, (int)_binary_initcode_size);
  p->sz = PGSIZE;
  memset(p->tf, 0, sizeof(*p->tf));
  p->tf->cs = (SEG_UCODE << 3) | DPL_USER;
  p->tf->ds = (SEG_UDATA << 3) | DPL_USER;
  p->tf->es = p->tf->ds;
  p->tf->ss = p->tf->ds;
  p->tf->eflags = FL_IF;
  p->tf->esp = PGSIZE;
  p->tf->eip = 0;  // beginning of initcode.S

  safestrcpy(p->name, "initcode", sizeof(p->name));
  p->cwd = namei("/");

  p->state = RUNNABLE;
}

// Grow current process's memory by n bytes.
// Return 0 on success, -1 on failure.
int
growproc(int n)
{
  uint sz;
  
  sz = proc->sz;
  if(n > 0){
    if((sz = allocuvm(proc->pgdir, sz, sz + n)) == 0)
      return -1;
  } else if(n < 0){
    if((sz = deallocuvm(proc->pgdir, sz, sz + n)) == 0)
      return -1;
  }
  proc->sz = sz;
  switchuvm(proc);
  return 0;
}

// Create a new process copying p as the parent.
// Sets up stack to return as if from system call.
// Caller must set state of returned proc to RUNNABLE.
int
fork(void)
{
  int i, pid;
  struct proc *np;

  // Allocate process.
  if((np = allocproc()) == 0)
    return -1;

  // Copy process state from p.
  if((np->pgdir = copyuvm(proc->pgdir, proc->sz)) == 0){
    kfree(np->kstack);
    np->kstack = 0;
    np->state = UNUSED;
    return -1;
  }
  np->sz = proc->sz;
  np->parent = proc;
  *np->tf = *proc->tf;

  // Clear %eax so that fork returns 0 in the child.
  np->tf->eax = 0;

  for(i = 0; i < NOFILE; i++)
    if(proc->ofile[i])
      np->ofile[i] = filedup(proc->ofile[i]);
  np->cwd = idup(proc->cwd);
 
  pid = np->pid;
  np->state = RUNNABLE;
  safestrcpy(np->name, proc->name, sizeof(proc->name));
  np->tid = 0;     /**STUDENT**/
  np->main = np;   /**STUDENT**/
  np->nexttid = 1; /**STUDENT**/
  np->retval = 0;  /**STUDENT**/
  np->joined = 0;  /**STUDENT**/
  return pid;
}

// Exit the current process.  Does not return.
// An exited process remains in the zombie state
// until its parent calls wait() to find out it exited.
void
exit(void)
{
  struct proc *p;
  int fd;

  if(proc == initproc)
    panic("init exiting");

  // Close all open files.
  for(fd = 0; fd < NOFILE; fd++){
    if(proc->ofile[fd]){
      fileclose(proc->ofile[fd]);
      proc->ofile[fd] = 0;
    }
  }

  iput(proc->cwd);
  proc->cwd = 0;

  acquire(&ptable.lock);

  // Parent might be sleeping in wait().
  wakeup1(proc->parent);

  // Pass abandoned children to init.
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->parent == proc){
      p->parent = initproc;
      if(p->state == ZOMBIE)
        wakeup1(initproc);
    }
  }

  // Jump into the scheduler, never to return.
  proc->state = ZOMBIE;
  sched();
  panic("zombie exit");
}

// Wait for a child process to exit and return its pid.
// Return -1 if this process has no children.
int
wait(void)
{
  struct proc *p;
  int havekids, pid;

  acquire(&ptable.lock);
  for(;;){
    // Scan through table looking for zombie children.
    havekids = 0;
    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
      if(p->parent != proc)
        continue;
      havekids = 1;
      if(p->state == ZOMBIE){
        // Found one.
        pid = p->pid;
        kfree(p->kstack);
        p->kstack = 0;
        freevm(p->pgdir);
        p->state = UNUSED;
        p->pid = 0;
        p->parent = 0;
        p->name[0] = 0;
        p->killed = 0;
        release(&ptable.lock);
        return pid;
      }
    }

    // No point waiting if we don't have any children.
    if(!havekids || proc->killed){
      release(&ptable.lock);
      return -1;
    }

    // Wait for children to exit.  (See wakeup1 call in proc_exit.)
    sleep(proc, &ptable.lock);  //DOC: wait-sleep
  }
}

void
register_handler(sighandler_t sighandler)
{
  char* addr = uva2ka(proc->pgdir, (char*)proc->tf->esp);
  if ((proc->tf->esp & 0xFFF) == 0)
    panic("esp_offset == 0");

    /* open a new frame */
  *(int*)(addr + ((proc->tf->esp - 4) & 0xFFF))
          = proc->tf->eip;
  proc->tf->esp -= 4;

    /* update eip */
  proc->tf->eip = (uint)sighandler;
}


//PAGEBREAK: 42
// Per-CPU process scheduler.
// Each CPU calls scheduler() after setting itself up.
// Scheduler never returns.  It loops, doing:
//  - choose a process to run
//  - swtch to start running that process
//  - eventually that process transfers control
//      via swtch back to the scheduler.
void
scheduler(void)
{
  struct proc *p;

  for(;;){
    // Enable interrupts on this processor.
    sti();

    // Loop over process table looking for process to run.
    acquire(&ptable.lock);
    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
      if(p->state != RUNNABLE)
        continue;

      // Switch to chosen process.  It is the process's job
      // to release ptable.lock and then reacquire it
      // before jumping back to us.
      proc = p;
      switchuvm(p);
      p->state = RUNNING;
      swtch(&cpu->scheduler, proc->context);
      switchkvm();

      // Process is done running for now.
      // It should have changed its p->state before coming back.
      proc = 0;
    }
    release(&ptable.lock);

  }
}

// Enter scheduler.  Must hold only ptable.lock
// and have changed proc->state.
void
sched(void)
{
  int intena;

  if(!holding(&ptable.lock))
    panic("sched ptable.lock");
  if(cpu->ncli != 1)
    panic("sched locks");
  if(proc->state == RUNNING)
    panic("sched running");
  if(readeflags()&FL_IF)
    panic("sched interruptible");
  intena = cpu->intena;
  swtch(&proc->context, cpu->scheduler);
  cpu->intena = intena;
}

// Give up the CPU for one scheduling round.
void
yield(void)
{
  acquire(&ptable.lock);  //DOC: yieldlock
  proc->state = RUNNABLE;
  sched();
  release(&ptable.lock);
}

// A fork child's very first scheduling by scheduler()
// will swtch here.  "Return" to user space.
void
forkret(void)
{
  static int first = 1;
  // Still holding ptable.lock from scheduler.
  release(&ptable.lock);

  if (first) {
    // Some initialization functions must be run in the context
    // of a regular process (e.g., they call sleep), and thus cannot 
    // be run from main().
    first = 0;
    initlog();
  }
  
  // Return to "caller", actually trapret (see allocproc).
}

// Atomically release lock and sleep on chan.
// Reacquires lock when awakened.
void
sleep(void *chan, struct spinlock *lk)
{
  if(proc == 0)
    panic("sleep");

  if(lk == 0)
    panic("sleep without lk");

  // Must acquire ptable.lock in order to
  // change p->state and then call sched.
  // Once we hold ptable.lock, we can be
  // guaranteed that we won't miss any wakeup
  // (wakeup runs with ptable.lock locked),
  // so it's okay to release lk.
  if(lk != &ptable.lock){  //DOC: sleeplock0
    acquire(&ptable.lock);  //DOC: sleeplock1
    release(lk);
  }

  // Go to sleep.
  proc->chan = chan;
  proc->state = SLEEPING;
  sched();

  // Tidy up.
  proc->chan = 0;

  // Reacquire original lock.
  if(lk != &ptable.lock){  //DOC: sleeplock2
    release(&ptable.lock);
    acquire(lk);
  }
}

//PAGEBREAK!
// Wake up all processes sleeping on chan.
// The ptable lock must be held.
static void
wakeup1(void *chan)
{
  struct proc *p;

  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
    if(p->state == SLEEPING && p->chan == chan)
      p->state = RUNNABLE;
}

// Wake up all processes sleeping on chan.
void
wakeup(void *chan)
{
  acquire(&ptable.lock);
  wakeup1(chan);
  release(&ptable.lock);
}

// Kill the process with the given pid.
// Process won't exit until it returns
// to user space (see trap in trap.c).
int
kill(int pid)
{
  struct proc *p;

  acquire(&ptable.lock);
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->pid == pid){
      p->killed = 1;
      // Wake process from sleep if necessary.
      if(p->state == SLEEPING)
        p->state = RUNNABLE;
      release(&ptable.lock);
      return 0;
    }
  }
  release(&ptable.lock);
  return -1;
}

//PAGEBREAK: 36
// Print a process listing to console.  For debugging.
// Runs when user types ^P on console.
// No lock to avoid wedging a stuck machine further.
void
procdump(void)
{
  static char *states[] = {
  [UNUSED]    "unused",
  [EMBRYO]    "embryo",
  [SLEEPING]  "sleep ",
  [RUNNABLE]  "runble",
  [RUNNING]   "run   ",
  [ZOMBIE]    "zombie"
  };
  int i;
  struct proc *p;
  char *state;
  uint pc[10];
  
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->state == UNUSED)
      continue;
    if(p->state >= 0 && p->state < NELEM(states) && states[p->state])
      state = states[p->state];
    else
      state = "???";
    cprintf("%d %s %s", p->pid, state, p->name);
    if(p->state == SLEEPING){
      getcallerpcs((uint*)p->context->ebp+2, pc);
      for(i=0; i<10 && pc[i] != 0; i++)
        cprintf(" %p", pc[i]);
    }
    cprintf("\n");
  }
}

/*********************************STUDENT*********************************/

int
thread_create(void *(*start)(), void *stack, uint stacksz)
{
  int i, tid;
  struct proc *nt;

  /* allocate process */
  if ((nt = allocproc()) == 0)
    return -1;
  
  /* copy open files */
  for (i = 0; i < NOFILE; i++)
    if (proc->ofile[i])
      nt->ofile[i] = filedup(proc->ofile[i]);

  nt->sz = proc->sz;
  nt->pgdir = proc->pgdir;   /* same virtual memory */
  nt->pid = proc->pid;       /* same pid */
  nt->parent = proc->parent; /* same parent */
  *nt->tf = *proc->tf;       /* doesn't matter, but safer to copy */
  nt->cwd = idup(proc->cwd); /* same cwd */
  safestrcpy(nt->name, proc->name, sizeof(proc->name)); /* same name */
  
  nt->tid = proc->nexttid++;
  nt->main = proc;
  nt->nexttid = -1;
  nt->retval = 0;
  nt->joined = 0;
  
  nt->tf->eip = (uint) start;
  nt->tf->esp = (uint) stack + stacksz;
  
  tid = nt->tid;
  nt->state = RUNNABLE;
  
  return tid;
}

int
thread_getid(void)
{
  return proc->tid;
}

int 
thread_getprocid(void)
{
  return proc->pid;
}

int
thread_join(int tid, void **retval)
{
  struct proc *p;
  int found;

  acquire(&ptable.lock);
  
  for(;;) {
    /* scan through table looking for the thread */
    found = 0;
    for (p = ptable.proc; p < &ptable.proc[NPROC]; p++) {
      if (p->pid != proc->pid || p->tid != tid)
        continue;
      found = 1;
      if (p->joined && p->joined != proc) {
        release(&ptable.lock);
        return -2;
      }
      p->joined = proc;
      if (p->state == ZOMBIE) {
        *retval = p->retval;
        kfree(p->kstack);
        p->kstack = 0;
        //freevm(p->pgdir); /* DON'T free vm because it is shared */
        p->state = UNUSED;
        p->pid = 0;
        p->parent = 0;
        p->name[0] = 0;
        p->killed = 0;
        p->tid = 0;
        p->main = 0;
        p->joined = 0;
        p->retval = 0;
        release(&ptable.lock);
        return 0;
      }
    }
    
    /* if thread not found don't join */
    if(!found || proc->killed) {
      release(&ptable.lock);
      return -1;
    }
    
    /* if thread found but isn't zombie yet, sleep until he exists */
    sleep(proc, &ptable.lock);
  }
}


void *memcpy(void *dst, const void *src, uint n);
void *memset(void *dst, int c, uint n);

void
thread_exit(void *retval)
{
  struct proc *p;
  int fd;
  int solo;

  if (proc == initproc)
    panic("init exiting");
    
  /* close all open files */
  for (fd = 0; fd < NOFILE; fd++) {
    if (proc->ofile[fd]) {
      fileclose(proc->ofile[fd]);
      proc->ofile[fd] = 0;
    }
  }
  
  iput(proc->cwd);
  proc->cwd = 0;
  
  acquire(&ptable.lock);
  
  proc->retval = retval;
  
  /* if the thread is not main thread */
  if (proc != proc->main) {
    if (proc->joined)
      wakeup1(proc->joined);
    /* jump into the scheduler, never to return */
    proc->state = ZOMBIE;
    sched();
    panic("zombie exit");
    /* never return */
  }
  
  solo = 1;
  /* find a thread to make him main thread */
  for (p = ptable.proc; p < &ptable.proc[NPROC]; p++) {
    if ((p->pid == proc->pid) && (p->tid != proc->tid)) {
      solo = 0;
      break;
    }
  }
  
  /* if main thread is the sole thread, exit the process */
  if (solo) {
    release(&ptable.lock);
    exit();
    /* never return */
  }
  
  /* otherwise, make `p' the main thread of the process */
  p->nexttid = proc->nexttid;
  memcpy(proc, p, sizeof *proc);
  memset(p, 0, sizeof *p);
  sched();
  panic("ori");
}

/********************************^STUDENT^********************************/
