/*
 * Authors: Ori Popowski & Lihi Sharkanski
 */


/**STUDENT**/

typedef struct {
  int s1;
  int s2;
  int val;
} semaphore;

semaphore *semaphore_create(int init);
void semaphore_down(semaphore *sem);
void semaphore_up(semaphore *sem);
