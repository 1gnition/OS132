/*
 * Modified by Ori Popowski & Lihi Sharkanski
 */
struct stat;

// system calls
int fork(void);
int exit(void) __attribute__((noreturn));
int wait(void);
int pipe(int*);
int write(int, void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(char*, char**);
int open(char*, int);
int mknod(char*, short, short);
int unlink(char*);
int fstat(int fd, struct stat*);
int link(char*, char*);
int mkdir(char*);
int chdir(char*);
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int uptime(void);
int wait2(int *wtime, int *rtime); /****STUDENT****/
int nice(void);                    /****STUDENT****/

// ulib.c
int stat(char*, struct stat*);
char* strcpy(char*, char*);
void *memmove(void*, void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void printf(int, char*, ...);
char* gets(char*, int max);
uint strlen(char*);
void* memset(void*, int, uint);
void* malloc(uint nbytes);
void free(void*);
int atoi(const char*);
char* safestrcpy(char *s, const char *t, int n);
/***STUDENT***/
int strcspn(const char *s1, const char *s2);
char *strpbrk(const char *s1, const char *s2);
char *strtok(char *s1, const char *s2);
char *strsep(char **stringp, const char *delim);
char *strcat(char *s1, char *s2);
/**^STUDENT^**/
