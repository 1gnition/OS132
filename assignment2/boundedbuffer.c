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
