/*
 * Modified by Ori Popowski & Lihi Sharkanski
 */
// Console input and output.
// Input is from the keyboard or serial port.
// Output is written to the screen and serial port.

#include "types.h"
#include "defs.h"
#include "param.h"
#include "traps.h"
#include "spinlock.h"
#include "fs.h"
#include "file.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "x86.h"

static void consputc(int);

static int panicked = 0;

static struct {
  struct spinlock lock;
  int locking;
} cons;

static void
printint(int xx, int base, int sign)
{
  static char digits[] = "0123456789abcdef";
  char buf[16];
  int i;
  uint x;

  if(sign && (sign = xx < 0))
    x = -xx;
  else
    x = xx;

  i = 0;
  do{
    buf[i++] = digits[x % base];
  }while((x /= base) != 0);

  if(sign)
    buf[i++] = '-';

  while(--i >= 0)
    consputc(buf[i]);
}
//PAGEBREAK: 50

// Print to the console. only understands %d, %x, %p, %s.
void
cprintf(char *fmt, ...)
{
  int i, c, locking;
  uint *argp;
  char *s;

  locking = cons.locking;
  if(locking)
    acquire(&cons.lock);

  if (fmt == 0)
    panic("null fmt");

  argp = (uint*)(void*)(&fmt + 1);
  for(i = 0; (c = fmt[i] & 0xff) != 0; i++){
    if(c != '%'){
      consputc(c);
      continue;
    }
    c = fmt[++i] & 0xff;
    if(c == 0)
      break;
    switch(c){
    case 'd':
      printint(*argp++, 10, 1);
      break;
    case 'x':
    case 'p':
      printint(*argp++, 16, 0);
      break;
    case 's':
      if((s = (char*)*argp++) == 0)
        s = "(null)";
      for(; *s; s++)
        consputc(*s);
      break;
    case '%':
      consputc('%');
      break;
    default:
      // Print unknown % sequence to draw attention.
      consputc('%');
      consputc(c);
      break;
    }
  }

  if(locking)
    release(&cons.lock);
}

void
panic(char *s)
{
  int i;
  uint pcs[10];
  
  cli();
  cons.locking = 0;
  cprintf("cpu%d: panic: ", cpu->id);
  cprintf(s);
  cprintf("\n");
  getcallerpcs(&s, pcs);
  for(i=0; i<10; i++)
    cprintf(" %p", pcs[i]);
  panicked = 1; // freeze other CPU
  for(;;)
    ;
}

//PAGEBREAK: 50
#define BACKSPACE 0x100
#define CRTPORT 0x3d4
#define KEY_LF  0xE4   /**STUDENT**/
#define KEY_RT 0xE5    /**STUDENT**/
static ushort *crt = (ushort*)P2V(0xb8000);  // CGA memory

/**************************STUDENT**************************/
static void
cgaputc(int c)
{
  int pos;
  static int end = 0;      /* end of line */
  static int begin;        /* begin of line */
  static int prompt = 1;   /* are we in the same line as $? */
  static ushort tmp = 0;   /* temp storage for char overriden by cursor */
  
  // Cursor position: col + 80*row.
  outb(CRTPORT, 14);
  pos = inb(CRTPORT+1) << 8;
  outb(CRTPORT, 15);
  pos |= inb(CRTPORT+1);
  
  if (end == 0)
		end = pos;
    
  if (prompt)
		begin = pos + 2;  /* compensate for $ */
	prompt = 0;
  
  switch (c) {
	case '\n':
		pos += 80 - pos%80;
    prompt = 1;    /* initialize prompt, end and temp */
    tmp = 0;
    end = 0;
    break;
  case BACKSPACE:
		if(pos > begin) {
			int t;
			for (t = pos + 1; t < end - 1; ++t)   /* shift line left*/
				crt[t-1] = crt[t];
			--pos;
			crt[--end] = 0;
		}
		break;
	case KEY_LF:
		if (pos > begin) {
			if (tmp != 0)
				crt[pos] = tmp;
			tmp = crt[pos-1];
			--pos;
		}
		break;
	case KEY_RT:
		if (pos < end) {
			if (tmp != 0)
				crt[pos] = tmp;
			tmp = crt[pos+1];
			++pos;
		}
		break;
  default:
		if (pos < end) {
			int t;
			for (t = end; t > pos; --t)   /* shift line right */
				crt[t] = crt[t-1];
		}
    crt[pos++] = (c&0xff) | 0x0700;  // black on white
    ++end;
	}  
  if((pos/80) >= 24){  // Scroll up.
    memmove(crt, crt+80, sizeof(crt[0])*23*80);
    pos -= 80;
    memset(crt+pos, 0, sizeof(crt[0])*(24*80 - pos));
  }
  
  outb(CRTPORT, 14);
  outb(CRTPORT+1, pos>>8);
  outb(CRTPORT, 15);
  outb(CRTPORT+1, pos);
  crt[pos] = ' ' | 0x0700;
}

/************************^^STUDENT^^************************/

void
consputc(int c)
{
  if(panicked){
    cli();
    for(;;)
      ;
  }

  if(c == BACKSPACE){
    uartputc('\b'); uartputc(' '); uartputc('\b');
  } else
    uartputc(c);
  cgaputc(c);
}

#define INPUT_BUF 128
struct {
  struct spinlock lock;
  char buf[INPUT_BUF];
  uint r;  // Read index
  uint w;  // Write index
  uint e;  // Edit index
  int o;   // Edit index's offset
} input;


#define C(x)  ((x)-'@')  // Control-x
/**************************STUDENT**************************/
void
consoleintr(int (*getc)(void))
{
  int c;

  acquire(&input.lock);
  while((c = getc()) >= 0){
    switch(c){
    case C('P'):  // Process listing.
      procdump();
      break;
    case C('U'):  // Kill line.
      while(input.e != input.w &&
            input.buf[(input.e-1) % INPUT_BUF] != '\n'){
        input.e--;
        consputc(BACKSPACE);
      }
      break;
    case C('H'): case '\x7f':  // Backspace
      if (input.e != input.w && input.o + input.e > input.r) {
				int i;
				for (i = input.e + input.o; i < input.e; ++i) /* shift buffer left */
					input.buf[i-1] = input.buf[i];
        input.e--;
        consputc(BACKSPACE);
      }
      break;
    case KEY_LF:
			if (input.o + input.e > input.r) {
				input.o--;
				consputc(c);
			}
			break;
    case KEY_RT:
			if (input.o < 0) {
				input.o++;
				consputc(c);
			}
			break;
    default:
      if(c != 0 && input.e-input.r < INPUT_BUF){
        c = (c == '\r') ? '\n' : c;
        if (c == '\n')
					input.buf[input.e++ % INPUT_BUF] = c;
				else {
					int i;
					for (i = input.e; i > input.e + input.o; --i)  /* shift buffer right */
						input.buf[i] = input.buf[i-1];
					input.buf[(input.e + input.o) % INPUT_BUF] = c;
					input.e++;
				}
        consputc(c);
        if(c == '\n' || c == C('D') || input.e == input.r+INPUT_BUF){
          input.w = input.e;
          input.o = 0;
          wakeup(&input.r);
        }
      }
      break;
    }
  }
  release(&input.lock);
}
/************************^^STUDENT^^************************/

int
consoleread(struct inode *ip, char *dst, int n)
{
  uint target;
  int c;

  iunlock(ip);
  target = n;
  acquire(&input.lock);
  while(n > 0){
    while(input.r == input.w){
      if(proc->killed){
        release(&input.lock);
        ilock(ip);
        return -1;
      }
      sleep(&input.r, &input.lock);
    }
    c = input.buf[input.r++ % INPUT_BUF];
    if(c == C('D')){  // EOF
      if(n < target){
        // Save ^D for next time, to make sure
        // caller gets a 0-byte result.
        input.r--;
      }
      break;
    }
    *dst++ = c;
    --n;
    if(c == '\n')
      break;
  }
  release(&input.lock);
  ilock(ip);

  return target - n;
}

int
consolewrite(struct inode *ip, char *buf, int n)
{
  int i;

  iunlock(ip);
  acquire(&cons.lock);
  for(i = 0; i < n; i++)
    consputc(buf[i] & 0xff);
  release(&cons.lock);
  ilock(ip);

  return n;
}

void
consoleinit(void)
{
  initlock(&cons.lock, "console");
  initlock(&input.lock, "input");

  devsw[CONSOLE].write = consolewrite;
  devsw[CONSOLE].read = consoleread;
  cons.locking = 1;

  picenable(IRQ_KBD);
  ioapicenable(IRQ_KBD, 0);
}

