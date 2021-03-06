#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/times.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <stdio.h>
#include <errno.h>

#include "syscalls.h"

typedef unsigned long sreg_t;

static inline long __syscall(sreg_t number,
    sreg_t arg1, sreg_t arg2, sreg_t arg3,
    sreg_t arg4, sreg_t arg5, sreg_t arg6)
{
    sreg_t ret = 0;
    __asm__ volatile (
        "mov %0, %%rax;"
        "mov %1, %%r8;"
        "mov %2, %%r9;"
        "mov %3, %%r10;"
        "mov %4, %%r11;"
        "mov %5, %%r12;"
        "mov %6, %%r13;"
        "int $0x80;"
        "mov %%rax, %0;"
        : "=r"(ret)
        : "g"(number),
        "g"(arg1), "g"(arg2), "g"(arg3),
        "g"(arg4), "g"(arg5), "g"(arg6)
        : "rax", "r8", "r9",
        "r10", "r11", "r12", "r13"
    );
    return ret;
}

#define SYSCALL_RETURN_ERRNO(x) \
  if ((x) >= 0) { return ret; } \
  errno = -ret;                 \
  return -1;
 
void _exit(int status)
{
  __syscall(SYS_EXIT, status, 0, 0, 0, 0, 0);

  /* never reached */
}

int read(int file, char *ptr, int len)
{
  ssize_t ret = __syscall(SYS_READ, file, (sreg_t)ptr, len, 0, 0, 0);
  SYSCALL_RETURN_ERRNO(ret);
}

int write(int file, char *ptr, int len)
{
  ssize_t ret = __syscall(SYS_WRITE, file, (sreg_t)ptr, len, 0, 0, 0);
  SYSCALL_RETURN_ERRNO(ret);
}

int close(int file)
{
  ssize_t ret = __syscall(SYS_CLOSE, file, 0, 0, 0, 0, 0);
  SYSCALL_RETURN_ERRNO(ret);
}

int open(const char *name, int flags, ...)
{
  ssize_t ret = __syscall(SYS_OPEN, (sreg_t)name, flags, 0, 0, 0, 0);
  SYSCALL_RETURN_ERRNO(ret);
}

int getpid()
{
  return __syscall(SYS_GETPID, 0, 0, 0, 0, 0, 0);
}

int fork()
{
  ssize_t ret = __syscall(SYS_FORK, 0, 0, 0, 0, 0, 0);
  SYSCALL_RETURN_ERRNO(ret);
}

int execve(char *name, char **argv, char **envp)
{
  ssize_t ret = __syscall(SYS_EXECVE, (sreg_t)name, (sreg_t)argv, (sreg_t)envp, 0, 0, 0);
  SYSCALL_RETURN_ERRNO(ret);
}

int fstat(int file, struct stat *st)
{
  errno = ENOSYS;
  return -1;
}

int isatty(int file)
{
  errno = ENOSYS;
  return -1;
}

int kill(int pid, int sig)
{
  errno = ENOSYS;
  return -1;
}

int link(char *oldpath, char *newpath)
{
  ssize_t ret = __syscall(SYS_LINK, (sreg_t)oldpath, (sreg_t)newpath, 0, 0, 0, 0);
  SYSCALL_RETURN_ERRNO(ret);
}

int lseek(int file, int ptr, int dir)
{
  ssize_t ret = __syscall(SYS_LSEEK, file, (sreg_t)ptr, dir, 0, 0, 0);
  SYSCALL_RETURN_ERRNO(ret);
}

caddr_t sbrk(int incr)
{
  return (caddr_t)__syscall(SYS_SBRK, incr, 0, 0, 0, 0, 0);
}

int stat(const char *file, struct stat *st)
{  
  errno = ENOSYS;
  return -1;
}

clock_t times(struct tms *buf)
{
  return (clock_t)-1;
}

int unlink(char *name)
{
  errno = ENOSYS;
  return -1;
}

int wait(int *status)
{
  errno = ENOSYS;
  return -1;
}

int gettimeofday(struct timeval *p, void *z)
{
  errno = ENOSYS;
  return -1;
}