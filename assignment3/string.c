/*
 * Modified by Ori Popowski & Lihi Sharkanski
 */


#include "types.h"
#include "x86.h"

void*
memset(void *dst, int c, uint n)
{
  if ((int)dst%4 == 0 && n%4 == 0){
    c &= 0xFF;
    stosl(dst, (c<<24)|(c<<16)|(c<<8)|c, n/4);
  } else
    stosb(dst, c, n);
  return dst;
}

int
memcmp(const void *v1, const void *v2, uint n)
{
  const uchar *s1, *s2;
  
  s1 = v1;
  s2 = v2;
  while(n-- > 0){
    if(*s1 != *s2)
      return *s1 - *s2;
    s1++, s2++;
  }

  return 0;
}

void*
memmove(void *dst, const void *src, uint n)
{
  const char *s;
  char *d;

  s = src;
  d = dst;
  if(s < d && s + n > d){
    s += n;
    d += n;
    while(n-- > 0)
      *--d = *--s;
  } else
    while(n-- > 0)
      *d++ = *s++;

  return dst;
}

// memcpy exists to placate GCC.  Use memmove.
void*
memcpy(void *dst, const void *src, uint n)
{
  return memmove(dst, src, n);
}

int
strncmp(const char *p, const char *q, uint n)
{
  while(n > 0 && *p && *p == *q)
    n--, p++, q++;
  if(n == 0)
    return 0;
  return (uchar)*p - (uchar)*q;
}

char*
strncpy(char *s, const char *t, int n)
{
  char *os;
  
  os = s;
  while(n-- > 0 && (*s++ = *t++) != 0)
    ;
  while(n-- > 0)
    *s++ = 0;
  return os;
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

int
strlen(const char *s)
{
  int n;

  for(n = 0; s[n]; n++)
    ;
  return n;
}

/****************STUDENT****************/
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

#define SWAP(a,b) \
do {              \
  a ^= b;         \
  b ^= a;         \
  a ^= b;         \
} while (0)

void
itoa(uint n, char *s)
{
  static char digits[] = "0123456789";
  char *str;
  char *end;
  
  end = str = s;
  do {
    *end++ = digits[n % 10];
  } while((n /= 10) != 0);
  
  *end-- = '\0';
  
  while (str < end) {
    SWAP(*str, *end);
    str++;
    end--;
  }
}

/***************^STUDENT^***************/
