// https://syzkaller.appspot.com/bug?id=b6aff64ebd79a1ee5ee7e787ca5b8673ba722226
// autogenerated by syzkaller (https://github.com/google/syzkaller)

#define _GNU_SOURCE

#include <sys/types.h>

#include <dirent.h>
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
#include <sys/resource.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

static unsigned long long procid;

static __thread int skip_segv;
static __thread jmp_buf segv_env;

static void segv_handler(int sig, siginfo_t* info, void* ctx)
{
  uintptr_t addr = (uintptr_t)info->si_addr;
  const uintptr_t prog_start = 1 << 20;
  const uintptr_t prog_end = 100 << 20;
  int skip = __atomic_load_n(&skip_segv, __ATOMIC_RELAXED) != 0;
  int valid = addr < prog_start || addr > prog_end;
  if (sig == SIGBUS) {
    valid = 1;
  }
  if (skip && valid) {
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
  ({                                                                           \
    int ok = 1;                                                                \
    __atomic_fetch_add(&skip_segv, 1, __ATOMIC_SEQ_CST);                       \
    if (_setjmp(segv_env) == 0) {                                              \
      __VA_ARGS__;                                                             \
    } else                                                                     \
      ok = 0;                                                                  \
    __atomic_fetch_sub(&skip_segv, 1, __ATOMIC_SEQ_CST);                       \
    ok;                                                                        \
  })

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

static void __attribute__((noinline)) remove_dir(const char* dir)
{
  DIR* dp = opendir(dir);
  if (dp == NULL) {
    if (errno == EACCES) {
      if (rmdir(dir))
        exit(1);
      return;
    }
    exit(1);
  }
  struct dirent* ep = 0;
  while ((ep = readdir(dp))) {
    if (strcmp(ep->d_name, ".") == 0 || strcmp(ep->d_name, "..") == 0)
      continue;
    char filename[FILENAME_MAX];
    snprintf(filename, sizeof(filename), "%s/%s", dir, ep->d_name);
    struct stat st;
    if (lstat(filename, &st))
      exit(1);
    if (S_ISDIR(st.st_mode)) {
      remove_dir(filename);
      continue;
    }
    if (unlink(filename))
      exit(1);
  }
  closedir(dp);
  if (rmdir(dir))
    exit(1);
}

static void thread_start(void* (*fn)(void*), void* arg)
{
  pthread_t th;
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setstacksize(&attr, 128 << 10);
  int i = 0;
  for (; i < 100; i++) {
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

static void sandbox_common()
{
  struct rlimit rlim;
  rlim.rlim_cur = rlim.rlim_max = 128 << 20;
  setrlimit(RLIMIT_AS, &rlim);
  rlim.rlim_cur = rlim.rlim_max = 8 << 20;
  setrlimit(RLIMIT_MEMLOCK, &rlim);
  rlim.rlim_cur = rlim.rlim_max = 1 << 20;
  setrlimit(RLIMIT_FSIZE, &rlim);
  rlim.rlim_cur = rlim.rlim_max = 1 << 20;
  setrlimit(RLIMIT_STACK, &rlim);
  rlim.rlim_cur = rlim.rlim_max = 0;
  setrlimit(RLIMIT_CORE, &rlim);
  rlim.rlim_cur = rlim.rlim_max = 256;
  setrlimit(RLIMIT_NOFILE, &rlim);
}

static void loop();

static int do_sandbox_none(void)
{
  sandbox_common();
  loop();
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
  for (call = 0; call < 10; call++) {
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
      event_timedwait(&th->done, 50);
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
  int iter = 0;
  for (;; iter++) {
    char cwdbuf[32];
    sprintf(cwdbuf, "./%d", iter);
    if (mkdir(cwdbuf, 0777))
      exit(1);
    int pid = fork();
    if (pid < 0)
      exit(1);
    if (pid == 0) {
      if (chdir(cwdbuf))
        exit(1);
      execute_one();
      exit(0);
    }
    int status = 0;
    uint64_t start = current_time_ms();
    for (;;) {
      if (waitpid(-1, &status, WNOHANG | WAIT_FLAGS) == pid)
        break;
      sleep_ms(1);
      if (current_time_ms() - start < 5000) {
        continue;
      }
      kill_and_wait(pid, &status);
      break;
    }
    remove_dir(cwdbuf);
  }
}

uint64_t r[1] = {0xffffffffffffffff};

void execute_call(int call)
{
  intptr_t res = 0;
  switch (call) {
  case 0:
    NONFAILING(*(uint16_t*)0x20000040 = 0);
    NONFAILING(*(uint16_t*)0x20000042 = 1);
    NONFAILING(*(uint16_t*)0x20000044 = 0);
    NONFAILING(*(uint16_t*)0x20000046 = 0);
    syscall(SYS_setsockopt, -1, 0x84, 3, 0x20000040ul, 8ul);
    break;
  case 1:
    syscall(SYS_bind, -1, 0ul, 0ul);
    break;
  case 2:
    NONFAILING(*(uint64_t*)0x200001c0 = 0);
    NONFAILING(*(uint32_t*)0x200001c8 = 0);
    NONFAILING(*(uint64_t*)0x200001d0 = 0);
    NONFAILING(*(uint32_t*)0x200001d8 = 0);
    NONFAILING(*(uint64_t*)0x200001e0 = 0);
    NONFAILING(*(uint32_t*)0x200001e8 = 0);
    NONFAILING(*(uint32_t*)0x200001ec = 1);
    syscall(SYS_sendmsg, -1, 0x200001c0ul, 0ul);
    break;
  case 3:
    syscall(SYS_open, 0ul, 0x40000400000002c2ul, 0ul);
    break;
  case 4:
    res = syscall(SYS_socket, 0x1cul, 1ul, 0x84);
    if (res != -1)
      r[0] = res;
    break;
  case 5:
    syscall(SYS_connect, -1, 0ul, 0ul);
    break;
  case 6:
    NONFAILING(*(uint8_t*)0x20000000 = 0x1c);
    NONFAILING(*(uint8_t*)0x20000001 = 0x1c);
    NONFAILING(*(uint16_t*)0x20000002 = htobe16(0x4e22 + procid * 4));
    NONFAILING(*(uint32_t*)0x20000004 = 0);
    NONFAILING(memset((void*)0x20000008, 0, 16));
    NONFAILING(*(uint32_t*)0x20000018 = 0);
    syscall(SYS_bind, r[0], 0x20000000ul, 0x1cul);
    break;
  case 7:
    NONFAILING(*(uint8_t*)0x20000340 = 0x1c);
    NONFAILING(*(uint8_t*)0x20000341 = 0x1c);
    NONFAILING(*(uint16_t*)0x20000342 = htobe16(0x4e22 + procid * 4));
    NONFAILING(*(uint32_t*)0x20000344 = 0);
    NONFAILING(*(uint64_t*)0x20000348 = htobe64(0));
    NONFAILING(*(uint64_t*)0x20000350 = htobe64(1));
    NONFAILING(*(uint32_t*)0x20000358 = 0);
    syscall(SYS_connect, r[0], 0x20000340ul, 0x1cul);
    break;
  case 8:
    syscall(SYS_sendto, r[0], 0ul, 0ul, 0x20000ul, 0ul, 0ul);
    break;
  case 9:
    NONFAILING(*(uint8_t*)0x20000180 = 0x10);
    NONFAILING(*(uint8_t*)0x20000181 = 2);
    NONFAILING(*(uint16_t*)0x20000182 = htobe16(0x4e20 + procid * 4));
    NONFAILING(*(uint8_t*)0x20000184 = 0xac);
    NONFAILING(*(uint8_t*)0x20000185 = 0x14);
    NONFAILING(*(uint8_t*)0x20000186 = 0 + procid * 1);
    NONFAILING(*(uint8_t*)0x20000187 = 0xaa);
    NONFAILING(memset((void*)0x20000188, 0, 8));
    NONFAILING(memset((void*)0x20000190, 0, 112));
    NONFAILING(*(uint32_t*)0x20000200 = 0);
    syscall(SYS_setsockopt, r[0], 0x84, 6, 0x20000180ul, 0x8cul);
    break;
  }
}
int main(void)
{
  syscall(SYS_mmap, 0x20000000ul, 0x1000000ul, 7ul, 0x1012ul, -1, 0ul);
  install_segv_handler();
  for (procid = 0; procid < 4; procid++) {
    if (fork() == 0) {
      use_temporary_dir();
      do_sandbox_none();
    }
  }
  sleep(1000000);
  return 0;
}
