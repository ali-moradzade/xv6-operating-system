#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

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
sys_getHelloWorld(void)
{
  return getHelloWorld();
}

int 
sys_getProcCount(void)
{
  return getProcCount();
}

int 
sys_getReadCount(void)
{
  return myproc()->readid;
}

int
sys_threadCreate(void)
{
  //  stackptr is stack_pointer
  int stackptr = 0;
  if(argint(0, &stackptr) < 0)
    return -1;

  return threadCreate((void*) stackptr);
}

int
sys_threadWait(void)
{
  return threadWait();
}

/*
  this is the actual function being called from syscall.c
  @returns - pidof the terminated child process ‐ if successful
­             -1, upon failure
*/
int sys_wait2(void) {
  int *retime, *rutime, *stime, *prio;
  if (argptr(0, (void*)&retime, sizeof(retime)) < 0)
    return -1;
  if (argptr(1, (void*)&rutime, sizeof(retime)) < 0)
    return -1;
  if (argptr(2, (void*)&stime, sizeof(stime)) < 0)
    return -1;
  if (argptr(3, (void*)&prio, sizeof(prio)) < 0)
    return -1;
  return wait2(retime, rutime, stime, prio);
}

/*
  System Call for setting the priority of the process
*/
int sys_set_prio(void) {
  int priority;
  argint(0, &priority);
  return set_prio(priority);
}

/*
  System Call for getting the priority of the process
*/
int sys_get_prio(void) {
  int pid;
  argint(0, &pid);
  return get_prio(pid);
}

/*
  For manual calling yield()
*/
int sys_yield(void) {
  yield();
  return 0;
}

/*
  Change scheduling policy
*/
int sys_change_policy(void) {
  int policy;
  argint(0, &policy);
  return change_policy(policy);
}

/*
  Work
*/
int sys_work(void) {
  int pid, priority, i;
  argint(0, &pid);
  argint(1, &priority);
  argint(2, &i);
  return work(pid, priority, i);
}