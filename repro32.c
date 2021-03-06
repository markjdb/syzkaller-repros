// https://syzkaller.appspot.com/bug?id=736923a6266d676e003edc5e8834a1460305f866
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
#include <sys/stat.h>
#include <sys/syscall.h>
#include <unistd.h>

static void use_temporary_dir(void)
{
  char tmpdir_template[] = "./syzkaller.XXXXXX";
  char* tmpdir = mkdtemp(tmpdir_template);
  if (!tmpdir)
    exit(1);
  if (chmod(tmpdir, 0777))
    exit(1);
  if (chdir(tmpdir))
    exit(1);
}

uint64_t r[1] = {0xffffffffffffffff};

int main(void)
{
  syscall(SYS_mmap, 0x20000000ul, 0x1000000ul, 7ul, 0x1012ul, -1, 0ul);
  use_temporary_dir();
  intptr_t res = 0;
  res = syscall(SYS_socket, 2ul, 1ul, 0);
  if (res != -1)
    r[0] = res;
  *(uint8_t*)0x20000000 = 2;
  *(uint8_t*)0x20000001 = 0;
  *(uint16_t*)0x20000002 = htobe16(0);
  *(uint32_t*)0x20000004 = htobe32(0);
  memset((void*)0x20000008, 0, 8);
  syscall(SYS_bind, r[0], 0x20000000ul, 2ul);
  return 0;
}
