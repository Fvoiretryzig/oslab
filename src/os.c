#include <os.h>
#include <libc.h>

static void os_init();
static void os_run();
static _RegSet *os_interrupt(_Event ev, _RegSet *regs);

MOD_DEF(os) {
  .init = os_init,
  .run = os_run,
  .interrupt = os_interrupt,
};

static void os_init() {
  for (const char *p = "Hello, OS World!\n"; *p; p++) {
    _putc(*p);
  }
}

static void os_run() {
  _intr_write(1); // enable interrupt
  while (1) ; // should never return
}

static _RegSet *os_interrupt(_Event ev, _RegSet *regs) {
  if (ev.event == _EVENT_IRQ_TIMER){
  	printf("eax:0x%08x, ebx:0x%08x, ecx:0x%08x, edx:0x%08x, ebp:0x%08x, eflags:0x%08x, eip:0x%08x\n",
  			regs->eax, regs->ebx, regs->ecx, regs->edx, regs->ebp, regs->eflags, regs->eip);
  }
  //_putc('*');
  if (ev.event == _EVENT_IRQ_IODEV) _putc('I');
  if (ev.event == _EVENT_ERROR) {
    _putc('x');
    _halt(1);
  }
  //return NULL; // this is allowed by AM
  return regs;
}
