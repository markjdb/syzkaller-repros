Syzkaller hit 'panic: ASan: Invalid access 4-byte read at ADDR, RedZonePartial' bug.

login: panic: ASan: Invalid access 4-byte read at 0xfffffe00025c0364, RedZonePartial
cpuid = 1
time = 1608307996
KDB: stack backtrace:
db_trace_self_wrapper() at db_trace_self_wrapper+0x47/frame 0xfffffe0045b765c0
vpanic() at vpanic+0x263/frame 0xfffffe0045b76620
panic() at panic+0x4f/frame 0xfffffe0045b76680
__asan_load4_noabort() at __asan_load4_noabort+0x1db/frame 0xfffffe0045b76740
rip_send() at rip_send+0xbe/frame 0xfffffe0045b76780
sosend_generic() at sosend_generic+0x9cf/frame 0xfffffe0045b768b0
sosend() at sosend+0x11e/frame 0xfffffe0045b76920
kern_sendit() at kern_sendit+0x435/frame 0xfffffe0045b769d0
sendit() at sendit+0x2b2/frame 0xfffffe0045b76a20
sys_sendmsg() at sys_sendmsg+0xda/frame 0xfffffe0045b76a90
amd64_syscall() at amd64_syscall+0x377/frame 0xfffffe0045b76bf0
fast_syscall_common() at fast_syscall_common+0xf8/frame 0xfffffe0045b76bf0
--- syscall (0, FreeBSD ELF64, nosys), rip = 0x400aca, rsp = 0x7fffffffea98, rbp = 0x7fffffffeab0 ---
Uptime: 56s


Syzkaller reproducer:
# {Threaded:false Collide:false Repeat:false RepeatTimes:0 Procs:1 Sandbox: Fault:false FaultCall:-1 FaultNth:0 Leak:false NetInjection:false NetDevices:false NetReset:false Cgroups:false BinfmtMisc:false CloseFDs:false KCSAN:false DevlinkPCI:false USB:false VhciInjection:false Wifi:false Sysctl:false UseTmpDir:false HandleSegv:false Repro:false Trace:false}
r0 = socket$inet_icmp_raw(0x2, 0x3, 0x1)
sendmsg$inet_sctp(r0, &(0x7f0000000000)={&(0x7f0000000140)=@in6={0x1c, 0x1c, 0x3, 0x0, @empty}, 0x2, &(0x7f0000000800)=[{&(0x7f0000000640)="8a090db45b6e53d93c6d9d2e04", 0xd}, {&(0x7f0000000680)="0be5444d1d67631b526ec9cad040010cd853593d3cdb6bb411668a10fa2ab5eb6526c1f9897502398c3bc0790dfc68e7c61ea631dbcb469b780e8928f019ff5d5cfff95da615a3d046d4272c6dee4d", 0x4f}, {0x0}, {&(0x7f0000000700)="94", 0x1}], 0x4}, 0x0)


C reproducer:
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
  res = syscall(SYS_socket, 2ul, 3ul, 1);
  if (res != -1)
    r[0] = res;
  *(uint64_t*)0x20000000 = 0x20000140;
  *(uint8_t*)0x20000140 = 0x1c;
  *(uint8_t*)0x20000141 = 0x1c;
  *(uint16_t*)0x20000142 = htobe16(0x4e23);
  *(uint32_t*)0x20000144 = 0;
  *(uint8_t*)0x20000148 = 0;
  *(uint8_t*)0x20000149 = 0;
  *(uint8_t*)0x2000014a = 0;
  *(uint8_t*)0x2000014b = 0;
  *(uint8_t*)0x2000014c = 0;
  *(uint8_t*)0x2000014d = 0;
  *(uint8_t*)0x2000014e = 0;
  *(uint8_t*)0x2000014f = 0;
  *(uint8_t*)0x20000150 = 0;
  *(uint8_t*)0x20000151 = 0;
  *(uint8_t*)0x20000152 = 0;
  *(uint8_t*)0x20000153 = 0;
  *(uint8_t*)0x20000154 = 0;
  *(uint8_t*)0x20000155 = 0;
  *(uint8_t*)0x20000156 = 0;
  *(uint8_t*)0x20000157 = 0;
  *(uint32_t*)0x20000158 = 0;
  *(uint32_t*)0x20000008 = 2;
  *(uint64_t*)0x20000010 = 0x20000800;
  *(uint64_t*)0x20000800 = 0x20000640;
  memcpy((void*)0x20000640,
         "\x8a\x09\x0d\xb4\x5b\x6e\x53\xd9\x3c\x6d\x9d\x2e\x04", 13);
  *(uint64_t*)0x20000808 = 0xd;
  *(uint64_t*)0x20000810 = 0x20000680;
  memcpy((void*)0x20000680,
         "\x0b\xe5\x44\x4d\x1d\x67\x63\x1b\x52\x6e\xc9\xca\xd0\x40\x01\x0c\xd8"
         "\x53\x59\x3d\x3c\xdb\x6b\xb4\x11\x66\x8a\x10\xfa\x2a\xb5\xeb\x65\x26"
         "\xc1\xf9\x89\x75\x02\x39\x8c\x3b\xc0\x79\x0d\xfc\x68\xe7\xc6\x1e\xa6"
         "\x31\xdb\xcb\x46\x9b\x78\x0e\x89\x28\xf0\x19\xff\x5d\x5c\xff\xf9\x5d"
         "\xa6\x15\xa3\xd0\x46\xd4\x27\x2c\x6d\xee\x4d",
         79);
  *(uint64_t*)0x20000818 = 0x4f;
  *(uint64_t*)0x20000820 = 0;
  *(uint64_t*)0x20000828 = 0;
  *(uint64_t*)0x20000830 = 0x20000700;
  memcpy((void*)0x20000700, "\x94", 1);
  *(uint64_t*)0x20000838 = 1;
  *(uint32_t*)0x20000018 = 4;
  *(uint64_t*)0x20000020 = 0;
  *(uint32_t*)0x20000028 = 0;
  *(uint32_t*)0x2000002c = 0;
  syscall(SYS_sendmsg, r[0], 0x20000000ul, 0ul);
  return 0;
}


