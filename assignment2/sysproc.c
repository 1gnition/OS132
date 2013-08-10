/*
 * Modified by Ori Popowski & Lihi Sharkanski
 */


#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "binsem.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;
  
  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

/********************STUDENT********************/

int
sys_thread_create(void)
{
  char *f;
  char *s;
  int sz;
  
  if (argint(0, (int *) &f) < 0)
    return -1;
  if (argint(1, (int *) &s) < 0)
    return -1;
  if (argint(2, &sz) < 0)
    return -1;
    
  return thread_create((void *) f, (void *) s, sz);
}

int
sys_thread_getid(void)
{
  return thread_getid();
}

int 
sys_thread_getprocid(void)
{
  return thread_getprocid();
}

int
sys_thread_join(void)
{
  int t;
  int *r;
  
  if (argint(0, &t) < 0)
    return -1;
  if (argptr(1, (void *) &r, sizeof *r) < 0)
    return -1;
    
  return thread_join(t, (void **) r);
}

int
sys_thread_exit(void)
{
  int *r;
  if (argptr(0, (void *) &r, sizeof *r) < 0)
    return -1;
  thread_exit((void *) r);
  return 0;   /* not reached */
}

int
sys_binary_semaphore_create(void)
{
  int init;
  if (argint(0, &init) < 0)
    return -1;
  return binary_semaphore_create(init);
  return 0;   /* not reached */
}

int
sys_binary_semaphore_down(void)
{
  int id;
  
  if (argint(0, &id) < 0)
    return -1;
  return binary_semaphore_down(id);
}

int
sys_binary_semaphore_up(void)
{
  int id;
  
  if (argint(0, &id) < 0)
    return -1;
  return binary_semaphore_up(id);
}

/*******************^STUDENT^*******************/
