// See LICENSE for license details.

#ifndef _RISCV_FRONTEND_H
#define _RISCV_FRONTEND_H

#include <stdint.h>
#include <sys/stat.h>

#ifdef __riscv64
# define TOHOST_CMD(dev, cmd, payload) \
  (((uint64_t)(dev) << 56) | ((uint64_t)(cmd) << 48) | (uint64_t)(payload))
#else
# define TOHOST_CMD(dev, cmd, payload) ({ \
  if ((dev) || (cmd)) __builtin_trap(); \
  (payload); })
#endif
#define FROMHOST_DEV(fromhost_value) ((uint64_t)(fromhost_value) >> 56)
#define FROMHOST_CMD(fromhost_value) ((uint64_t)(fromhost_value) << 8 >> 56)
#define FROMHOST_DATA(fromhost_value) ((uint64_t)(fromhost_value) << 16 >> 16)

void die(int) __attribute__((noreturn));
long frontend_syscall(long n, long a0, long a1, long a2, long a3, long a4, long a5, long a6);
uint64_t tohost_sync(unsigned dev, unsigned cmd, uint64_t payload);

struct frontend_stat {
  uint64_t dev;
  uint64_t ino;
  uint32_t mode;
  uint32_t nlink;
  uint32_t uid;
  uint32_t gid;
  uint64_t rdev;
  uint64_t __pad1;
  uint64_t size;
  uint32_t blksize;
  uint32_t __pad2;
  uint64_t blocks;
  uint64_t atime;
  uint64_t __pad3;
  uint64_t mtime;
  uint64_t __pad4;
  uint64_t ctime;
  uint64_t __pad5;
  uint32_t __unused4;
  uint32_t __unused5;
};

void copy_stat(struct stat* dest, struct frontend_stat* src);

#endif
