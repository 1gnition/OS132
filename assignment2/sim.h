#ifndef SIM_H
#define SIM_H

typedef struct {
  int id;
} Cup;

typedef struct {
  int type;
  Cup *cup;
  int tid;
} Action;

#endif
