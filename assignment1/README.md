Assignment 1

In this assignment the following features added:
- Added the PATH environment variable
- Add a function `wait2(int *wtime, int *rtime)'
  which does the same thing as the original UNIX
  `wait' system call, but stores the waiting time
  and the running time of the child process waited
  upon.
- Added three additional scheduling policied to the
  default scheduling policy:
  1. Round Robin.
  2. FIFO Round Robin.
  3. Guaranteed Fair Share.
  4. Multi-level scheduling policy with three
     different waiting queues, each implements
     different scheduling policy of the above.
- Add the `nice()' system call which demotes the
  priority of the calling process.

File created by Ori Popowski
