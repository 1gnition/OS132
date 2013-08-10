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


