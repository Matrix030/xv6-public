#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h" 

extern struct {
    struct spinlock lock;
    struct proc proc[NPROC];
} ptable;

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
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
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
    if(myproc()->killed){
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

int
sys_cps(void)
{
  return cps();
}

int
sys_nice(void)
{
  int pid, pr;
  if(argint(0, &pid) < 0)
    return -1;
  if(argint(1, &pr) < 0)
    return -1;

  return nice(pid, pr);
}



// sysproc.c

int sys_lock(void) {
    int id;
    if (argint(0, &id) < 0 || id < 0 || id >= MAX_LOCKS) return -1;

    struct lock_t *lk = &locks[id];
    acquire(&lk->lk_lock);

    if (lk->locked) {
        if (myproc()->priority > lk->owner->priority) {
            lk->owner->original_priority = lk->owner->priority;
            lk->owner->priority = myproc()->priority;
        }
        sleep(lk, &lk->lk_lock);
    } else {
        lk->locked = 1;
        lk->owner = myproc();
    }

    release(&lk->lk_lock);
    return 0;
}

int sys_release(void) {
    int id;
    if (argint(0, &id) < 0 || id < 0 || id >= MAX_LOCKS) return -1;

    struct lock_t *lk = &locks[id];
    acquire(&lk->lk_lock);

    if (lk->owner != myproc()) {
        release(&lk->lk_lock);
        return -1;
    }

    if (lk->owner->original_priority != -1) {
        lk->owner->priority = lk->owner->original_priority;
        lk->owner->original_priority = -1;
    }

    lk->locked = 0;
    lk->owner = 0;  // Use 0 instead of NULL
    wakeup(lk);

    release(&lk->lk_lock);
    return 0;
}

int sys_set_priority(void) {
    int priority;
    if (argint(0, &priority) < 0)
        return -1;
    return set_priority(priority);
}