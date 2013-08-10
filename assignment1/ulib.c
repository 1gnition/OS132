/*
 * Modified by Ori Popowski & Lihi Sharkanski
 */
#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"

char*
strcpy(char *s, char *t)
{
  char *os;

  os = s;
  while((*s++ = *t++) != 0)
    ;
  return os;
}

int
strcmp(const char *p, const char *q)
{
  while(*p && *p == *q)
    p++, q++;
  return (uchar)*p - (uchar)*q;
}

uint
strlen(char *s)
{
  int n;

  for(n = 0; s[n]; n++)
    ;
  return n;
}

void*
memset(void *dst, int c, uint n)
{
  stosb(dst, c, n);
  return dst;
}

char*
strchr(const char *s, char c)
{
  for(; *s; s++)
    if(*s == c)
      return (char*)s;
  return 0;
}

char*
gets(char *buf, int max)
{
  int i, cc;
  char c;

  for(i=0; i+1 < max; ){
    cc = read(0, &c, 1);
    if(cc < 1)
      break;
    buf[i++] = c;
    if(c == '\n' || c == '\r')
      break;
  }
  buf[i] = '\0';
  return buf;
}

int
stat(char *n, struct stat *st)
{
  int fd;
  int r;

  fd = open(n, O_RDONLY);
  if(fd < 0)
    return -1;
  r = fstat(fd, st);
  close(fd);
  return r;
}

int
atoi(const char *s)
{
  int n;

  n = 0;
  while('0' <= *s && *s <= '9')
    n = n*10 + *s++ - '0';
  return n;
}

void*
memmove(void *vdst, void *vsrc, int n)
{
  char *dst, *src;
  
  dst = vdst;
  src = vsrc;
  while(n-- > 0)
    *dst++ = *src++;
  return vdst;
}

// Like strncpy but guaranteed to NUL-terminate.
char*
safestrcpy(char *s, const char *t, int n)
{
  char *os;
  
  os = s;
  if(n <= 0)
    return os;
  while(--n > 0 && (*s++ = *t++) != 0)
    ;
  *s = 0;
  return os;
}

/*******************************STUDENT*******************************/

/***********************************************
 * standard library functions re-implemented.
 * see "man <function>" for details.
 **********************************************/
  
int
strspn(const char *s1, const char *s2)
{
	const char *sc1, *sc2;
	
	for (sc1 = s1; *sc1 != '\0'; ++sc1)
		for (sc2 = s2; ; ++sc2)
			if (*sc2 == '\0')
				return sc1 - s1;
			else if (*sc1 == *sc2)
				break;
	return sc1 - s1;
}


int
strcspn(const char *s1, const char *s2)
{
	const char *sc1, *sc2;
	
	for (sc1 = s1; *sc1 != '\0'; ++sc1)
		for (sc2 = s2; *sc2 != '\0'; ++sc2)
			if (*sc1 == *sc2)
				return sc1 - s1;
	return sc1 - s1;
}


char
*strpbrk(const char *s1, const char *s2)
{
	const char *sc1, *sc2;
	
	for (sc1 = s1; *sc1 != '\0'; ++sc1)
		for (sc2 = s2; *sc2 != '\0'; ++sc2)
			if (*sc1 == *sc2)
				return (char *) sc1;
	return 0;
}


char
*strsep(char **stringp, const char *delim)
{
  char *begin, *end;

  begin = *stringp;
  if(begin == 0)
    return 0;

  if(delim[0] == '\0' || delim[1] == '\0') {
    char ch = delim[0];

    if(ch == '\0')
      end = 0;
    else {
      if(*begin == ch)
        end = begin;
      else if(*begin == '\0')
        end = 0;
      else
        end = strchr(begin + 1, ch);
    }
  }
  else
    end = strpbrk(begin, delim);

  if(end) {
    *end++ = '\0';
    *stringp = end;
  }
  else
    *stringp = 0;

  return begin;
}


char
*strcat(char *s1, char *s2)
{
	char *s;
	
	for (s = s1; *s != '\0'; ++s)
		;
	for (; (*s = *s2) != '\0'; ++s, ++s2)
		;
	return s1;
}
/******************************^STUDENT^******************************/
