// https://syzkaller.appspot.com/bug?id=66d11d71c4266e16f71ac6a16aba794a1ed75358
// autogenerated by syzkaller (https://github.com/google/syzkaller)

#define _GNU_SOURCE

#include <sys/types.h>

#include <errno.h>
#include <pthread.h>
#include <pwd.h>
#include <setjmp.h>
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/endian.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

unsigned long long procid;

static __thread int skip_segv;
static __thread jmp_buf segv_env;

static void segv_handler(int sig, siginfo_t* info, void* ctx)
{
  uintptr_t addr = (uintptr_t)info->si_addr;
  const uintptr_t prog_start = 1 << 20;
  const uintptr_t prog_end = 100 << 20;
  if (__atomic_load_n(&skip_segv, __ATOMIC_RELAXED) &&
      (addr < prog_start || addr > prog_end)) {
    _longjmp(segv_env, 1);
  }
  exit(sig);
}

static void install_segv_handler(void)
{
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sa.sa_sigaction = segv_handler;
  sa.sa_flags = SA_NODEFER | SA_SIGINFO;
  sigaction(SIGSEGV, &sa, NULL);
  sigaction(SIGBUS, &sa, NULL);
}

#define NONFAILING(...)                                                        \
  {                                                                            \
    __atomic_fetch_add(&skip_segv, 1, __ATOMIC_SEQ_CST);                       \
    if (_setjmp(segv_env) == 0) {                                              \
      __VA_ARGS__;                                                             \
    }                                                                          \
    __atomic_fetch_sub(&skip_segv, 1, __ATOMIC_SEQ_CST);                       \
  }

static void kill_and_wait(int pid, int* status)
{
  kill(pid, SIGKILL);
  while (waitpid(-1, status, 0) != pid) {
  }
}

static void sleep_ms(uint64_t ms)
{
  usleep(ms * 1000);
}

static uint64_t current_time_ms(void)
{
  struct timespec ts;
  if (clock_gettime(CLOCK_MONOTONIC, &ts))
    exit(1);
  return (uint64_t)ts.tv_sec * 1000 + (uint64_t)ts.tv_nsec / 1000000;
}

static void thread_start(void* (*fn)(void*), void* arg)
{
  pthread_t th;
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setstacksize(&attr, 128 << 10);
  int i;
  for (i = 0; i < 100; i++) {
    if (pthread_create(&th, &attr, fn, arg) == 0) {
      pthread_attr_destroy(&attr);
      return;
    }
    if (errno == EAGAIN) {
      usleep(50);
      continue;
    }
    break;
  }
  exit(1);
}

typedef struct {
  pthread_mutex_t mu;
  pthread_cond_t cv;
  int state;
} event_t;

static void event_init(event_t* ev)
{
  if (pthread_mutex_init(&ev->mu, 0))
    exit(1);
  if (pthread_cond_init(&ev->cv, 0))
    exit(1);
  ev->state = 0;
}

static void event_reset(event_t* ev)
{
  ev->state = 0;
}

static void event_set(event_t* ev)
{
  pthread_mutex_lock(&ev->mu);
  if (ev->state)
    exit(1);
  ev->state = 1;
  pthread_mutex_unlock(&ev->mu);
  pthread_cond_broadcast(&ev->cv);
}

static void event_wait(event_t* ev)
{
  pthread_mutex_lock(&ev->mu);
  while (!ev->state)
    pthread_cond_wait(&ev->cv, &ev->mu);
  pthread_mutex_unlock(&ev->mu);
}

static int event_isset(event_t* ev)
{
  pthread_mutex_lock(&ev->mu);
  int res = ev->state;
  pthread_mutex_unlock(&ev->mu);
  return res;
}

static int event_timedwait(event_t* ev, uint64_t timeout)
{
  uint64_t start = current_time_ms();
  uint64_t now = start;
  pthread_mutex_lock(&ev->mu);
  for (;;) {
    if (ev->state)
      break;
    uint64_t remain = timeout - (now - start);
    struct timespec ts;
    ts.tv_sec = remain / 1000;
    ts.tv_nsec = (remain % 1000) * 1000 * 1000;
    pthread_cond_timedwait(&ev->cv, &ev->mu, &ts);
    now = current_time_ms();
    if (now - start > timeout)
      break;
  }
  int res = ev->state;
  pthread_mutex_unlock(&ev->mu);
  return res;
}

static long syz_execute_func(volatile long text)
{
  volatile long p[8] = {0};
  (void)p;
  asm volatile("" ::"r"(0l), "r"(1l), "r"(2l), "r"(3l), "r"(4l), "r"(5l),
               "r"(6l), "r"(7l), "r"(8l), "r"(9l), "r"(10l), "r"(11l), "r"(12l),
               "r"(13l));
  NONFAILING(((void (*)(void))(text))());
  return 0;
}

struct thread_t {
  int created, call;
  event_t ready, done;
};

static struct thread_t threads[16];
static void execute_call(int call);
static int running;

static void* thr(void* arg)
{
  struct thread_t* th = (struct thread_t*)arg;
  for (;;) {
    event_wait(&th->ready);
    event_reset(&th->ready);
    execute_call(th->call);
    __atomic_fetch_sub(&running, 1, __ATOMIC_RELAXED);
    event_set(&th->done);
  }
  return 0;
}

static void execute_one(void)
{
  int i, call, thread;
  int collide = 0;
again:
  for (call = 0; call < 6; call++) {
    for (thread = 0; thread < (int)(sizeof(threads) / sizeof(threads[0]));
         thread++) {
      struct thread_t* th = &threads[thread];
      if (!th->created) {
        th->created = 1;
        event_init(&th->ready);
        event_init(&th->done);
        event_set(&th->done);
        thread_start(thr, th);
      }
      if (!event_isset(&th->done))
        continue;
      event_reset(&th->done);
      th->call = call;
      __atomic_fetch_add(&running, 1, __ATOMIC_RELAXED);
      event_set(&th->ready);
      if (collide && (call % 2) == 0)
        break;
      event_timedwait(&th->done, 45);
      break;
    }
  }
  for (i = 0; i < 100 && __atomic_load_n(&running, __ATOMIC_RELAXED); i++)
    sleep_ms(1);
  if (!collide) {
    collide = 1;
    goto again;
  }
}

static void execute_one(void);

#define WAIT_FLAGS 0

static void loop(void)
{
  int iter;
  for (iter = 0;; iter++) {
    int pid = fork();
    if (pid < 0)
      exit(1);
    if (pid == 0) {
      execute_one();
      exit(0);
    }
    int status = 0;
    uint64_t start = current_time_ms();
    for (;;) {
      if (waitpid(-1, &status, WNOHANG | WAIT_FLAGS) == pid)
        break;
      sleep_ms(1);
      if (current_time_ms() - start < 5 * 1000)
        continue;
      kill_and_wait(pid, &status);
      break;
    }
  }
}

uint64_t r[2] = {0xffffffffffffffff, 0xffffffffffffffff};

void execute_call(int call)
{
  long res;
  switch (call) {
  case 0:
    NONFAILING(memcpy(
        (void*)0x20000000,
        "\x98\x26\x47\x3e\x43\x1c\x13\x0f\x05\xf3\x0f\x59\xbf\xd9\x13\x00\x00"
        "\xc4\xa3\x7b\xf0\xc5\x3e\x41\xe2\xe9\xb5\x57\x67\x66\x0f\x6b\x32\xfb"
        "\x66\x0f\x72\xd5\x0f\x0f\xb8\xc4\x05\x4e\x4e\xed\x75\x1e\x0f\xa0\x45"
        "\x0f\x0f\xaa\x00\x00\x15\x21\xb7\xab\x34\xd1\xc4\xe1\x0b\xf8\xc4\x70"
        "\xc4\xc4\x61\xcd\x58\x3d\x00\x00\x00\x81\xc6\x6d\xb7\x12\xfd\x83\x39"
        "\x7f\xd3\x00\xc9\xdc\xdc\x0f\xbc\xaf\x00\xea\xe8\x00\xf3\x45\xd9\xc6"
        "\xac\xac\xc4\xc3\x21\x4c\xb9\xa5\x60\x54\x19\xc2\x01\xb0\x0b\x00\x00"
        "\x00\xf0\x81\x71\xa3\x0b\x8a\x82\x6e\xa8\x0d\xd4\xd4\x8c\xc7\xe8\x62"
        "\x8f\x68\x08\xa3\x05\x6f\x00\x00\x00\x4e\x00\xc4\x61\x8d\xe3\xc0\xf5"
        "\x26\x26\x47\x88\xfe\x58\xc4\xa1\xdd\x7d\xbb\xbf\xdd\x5c\xc6\x00\xd0"
        "\x30\xa1\xc9\xfb\x11\x0f\xd3\xc4\xa2\x61\xb7\xe2",
        182));
    syz_execute_func(0x20000000);
    break;
  case 1:
    res = syscall(SYS_socket, 0x1c, 1, 0x84);
    if (res != -1)
      r[0] = res;
    break;
  case 2:
    NONFAILING(*(uint8_t*)0x20000280 = 0);
    NONFAILING(*(uint8_t*)0x20000281 = 0);
    NONFAILING(*(uint8_t*)0x20000282 = 4);
    NONFAILING(*(uint8_t*)0x20000283 = 7);
    NONFAILING(*(uint8_t*)0x20000284 = 0xef);
    NONFAILING(*(uint8_t*)0x20000285 = 0);
    NONFAILING(*(uint8_t*)0x20000286 = 0x20);
    NONFAILING(*(uint8_t*)0x20000287 = 7);
    NONFAILING(*(uint8_t*)0x20000288 = 0x62);
    NONFAILING(*(uint8_t*)0x20000289 = 4);
    NONFAILING(*(uint8_t*)0x2000028a = 3);
    syscall(SYS_setsockopt, r[0], 0x84, 0xc, 0x20000280, 0xb);
    break;
  case 3:
    syscall(SYS_listen, r[0], 0);
    break;
  case 4:
    res = syscall(SYS_fcntl, r[0], 0, r[0]);
    if (res != -1)
      r[1] = res;
    break;
  case 5:
    NONFAILING(*(uint32_t*)0x20000000 = 0);
    syscall(SYS_setsockopt, r[1], 0x84, 0x8008, 0x20000000, 0xffba);
    break;
  }
}
int main(void)
{
  syscall(SYS_mmap, 0x20000000, 0x1000000, 3, 0x1012, -1, 0);
  install_segv_handler();
  for (procid = 0; procid < 4; procid++) {
    if (fork() == 0) {
      loop();
    }
  }
  sleep(1000000);
  return 0;
}