// https://syzkaller.appspot.com/bug?id=450959c7b8ffe8d32ee5e305e50129ee57b3a707
// autogenerated by syzkaller (https://github.com/google/syzkaller)

#define _GNU_SOURCE

#include <pwd.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/endian.h>
#include <sys/syscall.h>
#include <unistd.h>

uint64_t r[1] = {0xffffffffffffffff};

int main(void)
{
  syscall(SYS_mmap, 0x20000000ul, 0x1000000ul, 7ul, 0x1012ul, -1, 0ul);
  intptr_t res = 0;
  res = syscall(SYS_socket, 0x10000000002ul, 2ul, 0);
  if (res != -1)
    r[0] = res;
  *(uint8_t*)0x20000100 = 0x10;
  *(uint8_t*)0x20000101 = 2;
  *(uint16_t*)0x20000102 = htobe16(0x4e20);
  *(uint32_t*)0x20000104 = htobe32(0xe0000002);
  memset((void*)0x20000108, 0, 8);
  syscall(SYS_sendto, r[0], 0ul, 0ul, 0x181ul, 0x20000100ul, 0x10ul);
  return 0;
}