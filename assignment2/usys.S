#include "syscall.h"
#include "traps.h"

#define SYSCALL(name) \
  .globl name; \
  name: \
    movl $SYS_ ## name, %eax; \
    int $T_SYSCALL; \
    ret

SYSCALL(fork)
SYSCALL(exit)
SYSCALL(wait)
SYSCALL(pipe)
SYSCALL(read)
SYSCALL(write)
SYSCALL(close)
SYSCALL(kill)
SYSCALL(exec)
SYSCALL(open)
SYSCALL(mknod)
SYSCALL(unlink)
SYSCALL(fstat)
SYSCALL(link)
SYSCALL(mkdir)
SYSCALL(chdir)
SYSCALL(dup)
SYSCALL(getpid)
SYSCALL(sbrk)
SYSCALL(sleep)
SYSCALL(uptime)
SYSCALL(thread_create)            /**STUDENT**/
SYSCALL(thread_getid)             /**STUDENT**/
SYSCALL(thread_getprocid)         /**STUDENT**/
SYSCALL(thread_join)              /**STUDENT**/
SYSCALL(thread_exit)              /**STUDENT**/
SYSCALL(binary_semaphore_create)  /**STUDENT**/
SYSCALL(binary_semaphore_down)    /**STUDENT**/
SYSCALL(binary_semaphore_up)      /**STUDENT**/
