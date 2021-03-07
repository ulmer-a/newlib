#include <sys/stat.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/times.h>
#include <sys/errno.h>
#include <sys/time.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#include "syscalls.h"

ssize_t _ulmeros_syscall0(size_t number);
ssize_t _ulmeros_syscall1(size_t number, size_t arg1);
ssize_t _ulmeros_syscall2(size_t number, size_t arg1, size_t arg2);
ssize_t _ulmeros_syscall3(size_t number, size_t arg1, size_t arg2, size_t arg3);
ssize_t _ulmeros_syscall4(size_t number, size_t arg1, size_t arg2, size_t arg3, size_t arg4);
ssize_t _ulmeros_syscall5(size_t number, size_t arg1, size_t arg2, size_t arg3, size_t arg4, size_t arg5);

#define SYSCALL_RETURN_ERRNO(x) \
  if ((x) >= 0) { return ret; } \
  errno = -ret;                 \
  return -1;
 
void _exit(int status)
{
  _ulmeros_syscall1(SYS_EXIT, status);

  /* never reached */
}

_READ_WRITE_RETURN_TYPE read(int file, void *ptr, size_t len)
{
  ssize_t ret = _ulmeros_syscall3(SYS_READ, file, (size_t)ptr, len);
  SYSCALL_RETURN_ERRNO(ret);
}

_READ_WRITE_RETURN_TYPE write(int file, const void *ptr, size_t len)
{
  ssize_t ret = _ulmeros_syscall3(SYS_WRITE, file, (size_t)ptr, len);
  SYSCALL_RETURN_ERRNO(ret);
}

int close(int file)
{
  ssize_t ret = _ulmeros_syscall1(SYS_CLOSE, file);
  SYSCALL_RETURN_ERRNO(ret);
}

int open(const char *name, int flags, ...)
{
  ssize_t ret = _ulmeros_syscall2(SYS_OPEN, (size_t)name, flags);
  SYSCALL_RETURN_ERRNO(ret);
}

int getpid()
{
  return _ulmeros_syscall0(SYS_GETPID);
}

int fork()
{
  ssize_t ret = _ulmeros_syscall0(SYS_FORK);
  SYSCALL_RETURN_ERRNO(ret);
}

int execve(const char *name, char *const *argv, char *const *envp)
{
  ssize_t ret = _ulmeros_syscall3(SYS_EXECVE, (size_t)name, (size_t)argv, (size_t)envp);
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

int link(const char *oldpath, const char *newpath)
{
  ssize_t ret = _ulmeros_syscall2(SYS_LINK, (size_t)oldpath, (size_t)newpath);
  SYSCALL_RETURN_ERRNO(ret);
}

off_t lseek(int file, off_t ptr, int whence)
{
  ssize_t ret = _ulmeros_syscall3(SYS_LSEEK, file, (size_t)ptr, whence);
  SYSCALL_RETURN_ERRNO(ret);
}

void* sbrk(ptrdiff_t incr)
{
  return (caddr_t)_ulmeros_syscall1(SYS_SBRK, incr);
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

int unlink(const char *name)
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