// https://syzkaller.appspot.com/bug?id=13f98a588a715c8c2427d5aae4831ec4e4354077
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
  res = syscall(SYS_socket, 2ul, 1ul, 0);
  if (res != -1)
    r[0] = res;
  *(uint64_t*)0x20000140 = 0x20000000;
  memset((void*)0x20000000, 236, 1);
  *(uint64_t*)0x20000148 = 0;
  *(uint64_t*)0x20000150 = 0;
  *(uint32_t*)0x20000158 = 0xb;
  *(uint32_t*)0x2000015c = 1;
  *(uint32_t*)0x20000160 = 0;
  *(uint32_t*)0x20000164 = 0x13;
  *(uint32_t*)0x20000168 = 4;
  *(uint32_t*)0x2000016c = 0;
  *(uint8_t*)0x20000170 = 3;
  *(uint8_t*)0x20000171 = 4;
  memcpy((void*)0x20000172, "\x49\xc8\xa2\xc8\xe6\x66\x9c\xee", 8);
  syscall(SYS_setsockopt, r[0], 6, 0x27, 0x20000140ul, 0x40ul);
  return 0;
}