Syzkaller hit 'Fatal trap NUM: page fault in filt_bpfwrite' bug.

Fatal trap 12: page fault while in kernel mode
cpuid = 0; apic id = 00
fault virtual address	= 0x28
fault code		= supervisor read data, page not present
instruction pointer	= 0x20:0xffffffff8198c23f
stack pointer	        = 0x28:0xfffffe008e5424a0
frame pointer	        = 0x28:0xfffffe008e5424b0
code segment		= base 0x0, limit 0xfffff, type 0x1b
			= DPL 0, pres 1, long 1, def32 0, gran 1
processor eflags	= interrupt enabled, resume, IOPL = 0
current process		= 817 (syz-executor5636372)
trap number		= 12
panic: page fault
cpuid = 0
time = 1634355456
KDB: stack backtrace:
db_trace_self_wrapper() at db_trace_self_wrapper+0xc7/frame 0xfffffe008e541cb0
kdb_backtrace() at kdb_backtrace+0xd3/frame 0xfffffe008e541e10
vpanic() at vpanic+0x2c5/frame 0xfffffe008e541ef0
panic() at panic+0xb5/frame 0xfffffe008e541fb0
trap_fatal() at trap_fatal+0x6a4/frame 0xfffffe008e5420b0
trap_pfault() at trap_pfault+0x186/frame 0xfffffe008e5421f0
trap() at trap+0x5e7/frame 0xfffffe008e5423d0
calltrap() at calltrap+0x8/frame 0xfffffe008e5423d0
--- trap 0xc, rip = 0xffffffff8198c23f, rsp = 0xfffffe008e5424a0, rbp = 0xfffffe008e5424b0 ---
filt_bpfwrite() at filt_bpfwrite+0x4f/frame 0xfffffe008e5424b0
kqueue_register() at kqueue_register+0x1364/frame 0xfffffe008e5425f0
kqueue_kevent() at kqueue_kevent+0x218/frame 0xfffffe008e542a00
kern_kevent_fp() at kern_kevent_fp+0xec/frame 0xfffffe008e542a50
kern_kevent() at kern_kevent+0x157/frame 0xfffffe008e542b30
kern_kevent_generic() at kern_kevent_generic+0x17c/frame 0xfffffe008e542c10
sys_kevent() at sys_kevent+0x1e6/frame 0xfffffe008e542d50
amd64_syscall() at amd64_syscall+0x3dc/frame 0xfffffe008e542f30
fast_syscall_common() at fast_syscall_common+0xf8/frame 0xfffffe008e542f30
--- syscall (0, FreeBSD ELF64, nosys), rip = 0x2333fa, rsp = 0x7fffffffea68, rbp = 0x7fffffffea80 ---
KDB: enter: panic
[ thread pid 817 tid 100099 ]
Stopped at      kdb_enter+0x6b: movq    $0,0x28d0efa(%rip)
db> set $lines = 0
db> set $maxwidth = 0
db> show registers
cs                        0x20
ds                        0x3b
es                        0x3b
fs                        0x13
gs                        0x1b
ss                        0x28
rax                       0x12
rcx         0x4553d7a3b377da64
rdx         0xdffff7c000000000
rbx                          0
rsp         0xfffffe008e541df0
rbp         0xfffffe008e541e10
rsi                        0x1
rdi                          0
r8                         0x3
r9          0xfffffe008e541928
r10                          0
r11         0xfffffe008ff02c70
r12         0xfffffe008ff02740
r13         0xfffffe008e541e01
r14         0xffffffff82c51ec0  .str.18
r15         0xffffffff82c51ec0  .str.18
rip         0xffffffff817b19bb  kdb_enter+0x6b
rflags                    0x46
kdb_enter+0x6b: movq    $0,0x28d0efa(%rip)
db> show proc
Process 817 (syz-executor5636372) at 0xfffffe008fee4000:
 state: NORMAL
 uid: 0  gids: 0, 0, 5
 parent: pid 815 at 0xfffffe008ff03a70
 ABI: FreeBSD ELF64
 flag: 0x10004000  flag2: 0
 arguments: /root/syz-executor563637270
 reaper: 0xfffffe0053d50538 reapsubtree: 1
 sigparent: 20
 vmspace: 0xfffffe00695e29f8
   (map 0xfffffe00695e29f8)
   (map.pmap 0xfffffe00695e2ab8)
   (pmap 0xfffffe00695e2b20)
 threads: 1
100099                   Run     CPU 0                       syz-executor5636372
db> ps
  pid  ppid  pgrp   uid  state   wmesg   wchan               cmd
  817   815   815     0  R       CPU 0                       syz-executor5636372
  815   813   815     0  Ss      pause   0xfffffe008ff03b20  csh
  813   730   813     0  Ss      select  0xfffffe008f97c9c0  sshd
  792     1   792     0  Rs+     CPU 1                       getty
  788     1   788     0  Ss      select  0xfffffe008f97ce40  logger
  782     1    15     0  S+      piperd  0xfffffe008f9ff8b8  logger
  781   780    15     0  S+      nanslp  0xffffffff8404f800  sleep
  780     1    15     0  S+      wait    0xfffffe008f97f538  sh
  776     1   776    25  Ss      pause   0xfffffe005420c0b0  sendmail
  773     1   773     0  Ss      select  0xfffffe00543c9dc0  sendmail
  734     1   734     0  Ss      nanslp  0xffffffff8404f800  cron
  730     1   730     0  Ss      select  0xfffffe00543c99c0  sshd
  641     1   641     0  Ss      select  0xfffffe008f97cdc0  syslogd
  444     1   444     0  Ss      select  0xfffffe00543c9940  devd
  347     1   347    65  Ss      select  0xfffffe00543c9ac0  dhclient
  265     1   265     0  Ss      select  0xfffffe00695f6240  dhclient
  262     1   262     0  Ss      select  0xfffffe005422c040  dhclient
   90     0     0     0  DL      pftm    0xffffffff8491e340  [pf purge]
   20     0     0     0  DL      syncer  0xffffffff84177ba0  [syncer]
   19     0     0     0  DL      vlruwt  0xfffffe005711d538  [vnlru]
    9     0     0     0  DL      (threaded)                  [bufdaemon]
100064                   D       qsleep  0xffffffff841758a0  [bufdaemon]
100067                   D       -       0xffffffff83411f80  [bufspacedaemon-0]
100078                   D       sdflush 0xfffffe00543d10e8  [/ worker]
    8     0     0     0  DL      psleep  0xffffffff841aad80  [vmdaemon]
    7     0     0     0  DL      (threaded)                  [pagedaemon]
100062                   D       psleep  0xffffffff8419e8b8  [dom0]
100065                   D       launds  0xffffffff8419e8c4  [laundry: dom0]
100066                   D       umarcl  0xffffffff81e95aa0  [uma]
    6     0     0     0  DL      -       0xffffffff83e05a60  [rand_harvestq]
    5     0     0     0  DL      (threaded)                  [cam]
100043                   D       -       0xffffffff83c8b240  [doneq0]
100044                   D       -       0xffffffff83c8b1c0  [async]
100061                   D       -       0xffffffff83c8b040  [scanner]
   14     0     0     0  DL      seqstat 0xfffffe0053eab888  [sequencer 00]
    4     0     0     0  DL      crypto_ 0xfffffe0053dea480  [crypto returns 1]
    3     0     0     0  DL      crypto_ 0xfffffe0053dea430  [crypto returns 0]
    2     0     0     0  DL      crypto_ 0xffffffff841989e0  [crypto]
   13     0     0     0  DL      (threaded)                  [geom]
100034                   D       -       0xffffffff84022980  [g_event]
100035                   D       -       0xffffffff840229c0  [g_up]
100036                   D       -       0xffffffff84022a00  [g_down]
   12     0     0     0  WL      (threaded)                  [intr]
100012                   I                                   [swi6: task queue]
100013                   I                                   [swi6: Giant taskq]
100019                   I                                   [swi5: fast taskq]
100029                   I                                   [swi1: netisr 0]
100030                   I                                   [swi4: clock (0)]
100031                   I                                   [swi4: clock (1)]
100032                   I                                   [swi3: vm]
100045                   I                                   [irq40: virtio_pci0]
100046                   I                                   [irq41: virtio_pci0]
100047                   I                                   [irq42: virtio_pci0]
100050                   I                                   [irq43: virtio_pci1]
100051                   I                                   [irq44: virtio_pci1]
100052                   I                                   [irq1: atkbd0]
100053                   I                                   [irq12: psm0]
100054                   I                                   [swi0: uart uart++]
100081                   I                                   [swi1: pf send]
   11     0     0     0  RL      (threaded)                  [idle]
100003                   CanRun                              [idle: cpu0]
100004                   CanRun                              [idle: cpu1]
    1     0     1     0  SLs     wait    0xfffffe0053d50538  [init]
   10     0     0     0  DL      audit_w 0xffffffff84199980  [audit]
    0     0     0     0  DLs     (threaded)                  [kernel]
100000                   D       swapin  0xffffffff84023880  [swapper]
100005                   D       -       0xfffffe0053c0cd00  [if_io_tqg_0]
100006                   D       -       0xfffffe0053c0cc00  [if_io_tqg_1]
100007                   D       -       0xfffffe0053c0cb00  [if_config_tqg_0]
100008                   D       -       0xfffffe0053c0ca00  [softirq_0]
100009                   D       -       0xfffffe0053c0c900  [softirq_1]
100010                   D       -       0xfffffe0053c0c800  [pci_hp taskq]
100011                   D       -       0xfffffe0053c0c700  [in6m_free taskq]
100014                   D       -       0xfffffe0053c0c400  [aiod_kick taskq]
100015                   D       -       0xfffffe0053c0c300  [inm_free taskq]
100016                   D       -       0xfffffe0053c0c200  [deferred_unmount ta]
100017                   D       -       0xfffffe0053c0c100  [linuxkpi_irq_wq]
100018                   D       -       0xfffffe0053c0c000  [thread taskq]
100020                   D       -       0xfffffe0053e02d00  [kqueue_ctx taskq]
100021                   D       -       0xfffffe0053e02c00  [linuxkpi_short_wq_0]
100022                   D       -       0xfffffe0053e02c00  [linuxkpi_short_wq_1]
100023                   D       -       0xfffffe0053e02c00  [linuxkpi_short_wq_2]
100024                   D       -       0xfffffe0053e02c00  [linuxkpi_short_wq_3]
100025                   D       -       0xfffffe0053e02b00  [linuxkpi_long_wq_0]
100026                   D       -       0xfffffe0053e02b00  [linuxkpi_long_wq_1]
100027                   D       -       0xfffffe0053e02b00  [linuxkpi_long_wq_2]
100028                   D       -       0xfffffe0053e02b00  [linuxkpi_long_wq_3]
100033                   D       -       0xfffffe0053e02a00  [firmware taskq]
100037                   D       -       0xfffffe0053e02000  [crypto_0]
100038                   D       -       0xfffffe0053e02000  [crypto_1]
100048                   D       -       0xfffffe0053f7ab00  [vtnet0 rxq 0]
100049                   D       -       0xfffffe0053f7ac00  [vtnet0 txq 0]
100055                   D       -       0xffffffff82c58d60  [deadlkres]
100056                   D       -       0xfffffe0053e02400  [acpi_task_0]
100057                   D       -       0xfffffe0053e02400  [acpi_task_1]
100058                   D       -       0xfffffe0053e02400  [acpi_task_2]
100060                   D       -       0xfffffe0053f7a800  [CAM taskq]
db> show all locks
Process 817 (syz-executor5636372) thread 0xfffffe008ff02740 (100099)
exclusive sleep mutex bpf (bpf cdev lock) r = 0 (0xfffffe008f966ae0) locked @ /root/freebsd/sys/kern/kern_event.c:2491
Process 792 (getty) thread 0xfffffe00694d3000 (100072)
exclusive sleep mutex ttymtx (ttymtx) r = 0 (0xfffffe0054284008) locked @ /root/freebsd/sys/kern/tty_ttydisc.c:489
db> show malloc
              Type        InUse        MemUse     Requests
           pf_hash            5        11524K            5
         sysctloid        30929         1820K        30971
              kobj          323         1292K          485
            linker          232         1205K          245
            newblk          672         1192K          763
            devbuf         1356         1136K         1373
          vfscache            3         1025K            3
          inodedep           49          530K           99
         ufs_quota            1          512K            1
          vfs_hash            1          512K            1
           callout            2          512K            2
              intr            4          472K            4
               pcb           16          393K           32
         vnet_data            1          168K            1
           subproc           84          159K          867
           tidhash            3          141K            3
           pagedep           22          134K           33
        tfo_ccache            1          128K            1
               sem            4          106K            4
            DEVFS1           91           91K          103
               bus          963           77K         2574
            bus-sc           31           76K         1066
              vmem            3           73K            3
          mtx_pool            2           72K            2
          syncache            1           68K            1
          acpitask            1           64K            1
       ddb_capture            1           64K            1
            module          491           62K          491
            acpica          420           39K        63114
               LRO            2           33K            2
         hostcache            1           32K            1
               shm            1           32K            1
               msg            4           30K            4
            DEVFS3          110           28K          126
           kdtrace          136           28K          919
        gtaskqueue           18           26K           18
              umtx          200           25K          200
            kbdmux            5           22K            5
        DEVFS_RULE           59           21K           59
           ithread          104           19K          104
               BPF           11           19K           11
              temp           15           17K         1519
         ufs_mount            4           17K            5
              proc            3           17K            3
            KTRACE          100           13K          100
           devstat            6           13K            6
              rman          102           12K          526
            ifaddr           29           11K           30
      eventhandler          125           11K          125
              GEOM           61           10K          512
              kenv           59           10K           59
          routetbl           44           10K          142
         bmsafemap            2            9K           92
              UART           12            9K           12
               rpc            2            8K            2
             shmfd            1            8K            1
       pfs_vncache            1            8K            1
         pfs_nodes           20            8K           20
     audit_evclass          237            8K          295
            diradd           46            6K          107
         taskqueue           54            6K           54
            sglist            3            6K            3
              cred           20            5K          290
            kqueue           38            5K          821
       ufs_dirhash           24            5K           24
             ifnet            3            5K            3
               UMA          248            5K          248
           io_apic            1            4K            1
       fpukern_ctx            2            4K            2
               tty            4            4K            4
             evdev            4            4K            4
          filedesc            1            4K            1
             hhook           13            4K           13
          pf_ifnet            5            3K            6
           lltable           10            3K           10
            plimit           11            3K          228
           acpisem           21            3K           21
           uidinfo            4            3K            9
             lockf           21            3K           32
           pwddesc           35            3K          818
             selfd           33            3K        16163
        local_apic            1            2K            1
         ipsec-saq            2            2K            2
           CAM DEV            1            2K            2
           session           15            2K           31
               msi           13            2K           13
          pci_link           16            2K           16
            Unitno           25            2K           45
         proc-args           34            2K          506
           acpidev           22            2K           22
            select           10            2K           61
         toponodes           10            2K           10
         CAM queue            2            2K            5
           softdep            1            1K            1
         newdirblk            8            1K           15
             mkdir            8            1K           30
       ipsecpolicy            1            1K            1
            sahead            1            1K            1
          secasvar            1            1K            1
             clone            8            1K            8
       ether_multi           13            1K           18
       vnodemarker            2            1K           10
      NFSD session            1            1K            1
         in6_multi            9            1K            9
          indirdep            3            1K            3
             nhops            6            1K            6
             mount           16            1K          123
            crypto            4            1K            4
            isadev            5            1K            5
           CAM XPT           11            1K           12
          in_multi            2            1K            3
              pfil            4            1K            4
              cdev            2            1K            2
 encap_export_host            8            1K            8
            DEVFSP            6            1K           23
            ip6ndp            3            1K            3
    chacha20random            1            1K            1
        CAM periph            2            1K           14
               osd            3            1K            9
      NFSD lckfile            1            1K            1
     NFSD V4client            1            1K            1
             DEVFS            9            1K           10
               MCA            2            1K            2
            dirrem            1            1K           46
               mld            2            1K            2
              igmp            2            1K            2
            vnodes            1            1K            1
          procdesc            2            1K           20
       inpcbpolicy            7            1K           71
            feeder            7            1K            7
             xform            3            1K          140
        loginclass            3            1K            7
            prison            6            1K            6
       lkpikmalloc            5            1K            6
        aesni_data            2            1K            2
            apmdev            1            1K            1
          atkbddev            2            1K            2
          freefile            1            1K           27
           CAM SIM            1            1K            1
          pmchooks            1            1K            1
            soname            4            1K         2568
          filecaps            4            1K          101
          nexusdev            6            1K            6
               tun            3            1K            3
     CAM dev queue            1            1K            1
          freework            1            1K           26
           tcpfunc            1            1K            1
              vnet            1            1K            1
          acpiintr            1            1K            1
               pmc            1            1K            1
              cpus            2            1K            2
    vnet_data_free            1            1K            1
          CAM path            1            1K           12
           entropy            1            1K           55
           Per-cpu            1            1K            1
          p1003.1b            1            1K            1
          pf_table            0            0K            0
           pf_rule            0            0K            0
           pf_altq            0            0K            0
           pf_osfp            0            0K            0
           pf_temp            0            0K            0
         NFSCL lck            0            0K            0
      NFSCL lckown            0            0K            0
        madt_table            0            0K            2
          smartpqi            0            0K            0
      NFSCL client            0            0K            0
       NFSCL deleg            0            0K            0
        NFSCL open            0            0K            0
       NFSCL owner            0            0K            0
            NFS fh            0            0K            0
           NFS req            0            0K            0
     NFSD usrgroup            0            0K            0
       NFSD string            0            0K            0
              iavf            0            0K            0
               ixl            0            0K            0
       NFSD V4lock            0            0K            0
      NFSD V4state            0            0K            0
     NFSD srvcache            0            0K            0
       msdosfs_fat            0            0K            0
     msdosfs_mount            0            0K            0
        ice-resmgr            0            0K            0
         ice-osdep            0            0K            0
               ice            0            0K            0
             axgbe            0            0K            0
      msdosfs_node            0            0K            0
            DEVFS4            0            0K            0
            DEVFS2            0            0K            0
            gntdev            0            0K            0
           memdesc            0            0K            0
       privcmd_dev            0            0K            0
          xen_intr            0            0K            0
        evtchn_dev            0            0K            0
          xenstore            0            0K            0
           xen_hvm            0            0K            0
         legacydrv            0            0K            0
            qpidrv            0            0K            0
         ciss_data            0            0K            0
         BACKLIGHT            0            0K            0
      dmar_idpgtbl            0            0K            0
          dmar_dom            0            0K            0
          dmar_ctx            0            0K            0
               xnb            0            0K            0
              xbbd            0            0K            0
               xbd            0            0K            0
              isci            0            0K            0
      iommu_dmamap            0            0K            0
     hyperv_socket            0            0K            0
           bxe_ilt            0            0K            0
           Balloon            0            0K            0
            xenbus            0            0K            0
          sysmouse            0            0K            0
            vtfont            0            0K            0
                vt            0            0K            0
     vm_fictitious            0            0K            0
             vtbuf            0            0K            0
           ath_hal            0            0K            0
            athdev            0            0K            0
           ata_pci            0            0K            0
           ata_dma            0            0K            0
       ata_generic            0            0K            0
               amr            0            0K            0
            pvscsi            0            0K            0
           scsi_da            0            0K            0
            ata_da            0            0K            0
           UMAHash            0            0K            0
           scsi_ch            0            0K            0
           scsi_cd            0            0K            0
         vm_pgdata            0            0K            0
           jblocks            0            0K            0
          savedino            0            0K            1
          sentinel            0            0K            0
            jfsync            0            0K            0
            jtrunc            0            0K            0
             sbdep            0            0K            3
           jsegdep            0            0K            0
              jseg            0            0K            0
         jfreefrag            0            0K            0
          jfreeblk            0            0K            0
           jnewblk            0            0K            0
            jmvref            0            0K            0
           jremref            0            0K            0
           jaddref            0            0K            0
           freedep            0            0K            0
          freeblks            0            0K           25
          freefrag            0            0K            1
        allocindir            0            0K            0
       allocdirect            0            0K            0
          ufs_trim            0            0K            0
           mactemp            0            0K            0
     audit_trigger            0            0K            0
 audit_pipe_presel            0            0K            0
     audit_pipeent            0            0K            0
        audit_pipe            0            0K            0
      audit_evname            0            0K            0
         audit_bsm            0            0K            0
      audit_gidset            0            0K            0
        audit_text            0            0K            0
        audit_path            0            0K            0
        audit_data            0            0K            0
        audit_cred            0            0K            0
       AHCI driver            0            0K            0
            USBdev            0            0K            0
               USB            0            0K            0
               agp            0            0K            0
           nvme_da            0            0K            0
 CAM I/O Scheduler            0            0K            0
           acpipwr            0            0K            0
          ktls_ocf            0            0K            0
         acpi_perf            0            0K            0
        MLX5EEPROM            0            0K            0
        MLX5EEPROM            0            0K            0
        MLX5EEPROM            0            0K            0
        MLX5EEPROM            0            0K            0
         MLX5E_TLS            0            0K            0
        MLX5EEPROM            0            0K            0
        MLX5EEPROM            0            0K            0
        MLX5EEPROM            0            0K            0
            MLX5EN            0            0K            0
        MLX5EEPROM            0            0K            0
        MLX5EEPROM            0            0K            0
        MLX5EEPROM            0            0K            0
          MLX5DUMP            0            0K            0
        MLX5EEPROM            0            0K            0
        MLX5EEPROM            0            0K            0
          seq_file            0            0K            0
             radix            0            0K            0
               idr            0            0K            0
            lkpifw            0            0K            0
               NLM            0            0K            0
    ipsec-spdcache            0            0K            0
         ipsec-reg            0            0K            0
        ipsec-misc            0            0K            0
      ipsecrequest            0            0K            0
            ip6opt            0            0K            0
       ip6_msource            0            0K            0
      ip6_moptions            0            0K            0
       in6_mfilter            0            0K            0
             frag6            0            0K            0
            tcplog            0            0K            0
      newreno data            0            0K            0
        ip_msource            0            0K            0
       ip_moptions            0            0K            0
        in_mfilter            0            0K            0
              ipid            0            0K            0
         80211scan            0            0K            0
      80211ratectl            0            0K            0
        80211power            0            0K            0
       80211nodeie            0            0K            0
         80211node            0            0K            0
      80211mesh_gt            0            0K            0
      80211mesh_rt            0            0K            0
         80211perr            0            0K            0
         80211prep            0            0K            0
         80211preq            0            0K            0
          80211dfs            0            0K            0
       80211crypto            0            0K            0
          80211vap            0            0K            0
             iflib            0            0K            0
              vlan            0            0K            0
               gif            0            0K            0
           ifdescr            0            0K            0
              zlib            0            0K            0
           fadvise            0            0K            0
           VN POLL            0            0K            0
            twsbuf            0            0K            0
            statfs            0            0K         1092
     namei_tracker            0            0K            2
       export_host            0            0K            0
        cl_savebuf            0            0K            4
      twe_commands            0            0K            0
      twa_commands            0            0K            0
       tcp_log_dev            0            0K            0
      midi buffers            0            0K            0
             mixer            0            0K            0
              ac97            0            0K            0
             hdacc            0            0K            0
              hdac            0            0K            0
              hdaa            0            0K            0
         acpicmbat            0            0K            0
       SIIS driver            0            0K            0
           CAM CCB            0            0K            0
               PUC            0            0K            0
          ppbusdev            0            0K            0
agtiapi_MemAlloc malloc            0            0K            0
            biobuf            0            0K            0
              aios            0            0K            0
               lio            0            0K            0
               acl            0            0K            0
    osti_cacheable            0            0K            0
          mbuf_tag            0            0K           16
              ktls            0            0K            0
          tempbuff            0            0K            0
          tempbuff            0            0K            0
ag_tgt_map_t malloc            0            0K            0
ag_slr_map_t malloc            0            0K            0
lDevFlags * malloc            0            0K            0
tiDeviceHandle_t * malloc            0            0K            0
ag_portal_data_t malloc            0            0K            0
ag_device_t malloc            0            0K            0
     STLock malloc            0            0K            0
          CCB List            0            0K            0
            sr_iov            0            0K            0
               OCS            0            0K            0
               OCS            0            0K            0
              nvme            0            0K            0
               nvd            0            0K            0
            netmap            0            0K            0
            mwldev            0            0K            0
        MVS driver            0            0K            0
     CAM ccb queue            0            0K            0
          mrsasbuf            0            0K            0
          mpt_user            0            0K            0
          mps_user            0            0K            0
            MPSSAS            0            0K            0
              accf            0            0K            0
               pts            0            0K            0
               iov            0            0K         7900
          ioctlops            0            0K           75
           eventfd            0            0K            0
           Witness            0            0K            0
          terminal            0            0K            0
             stack            0            0K            0
               mps            0            0K            0
          mpr_user            0            0K            0
            MPRSAS            0            0K            0
               mpr            0            0K            0
            mfibuf            0            0K            0
        md_sectors            0            0K            0
              sbuf            0            0K          364
           md_disk            0            0K            0
          firmware            0            0K            0
        compressor            0            0K            0
           malodev            0            0K            0
              SWAP            0            0K            0
               LED            0            0K            0
         sysctltmp            0            0K          533
            sysctl            0            0K           34
              ekcd            0            0K            0
            dumper            0            0K            0
          sendfile            0            0K            0
              rctl            0            0K            0
          ix_sriov            0            0K            0
        aacraidcam            0            0K            0
       aacraid_buf            0            0K            0
                ix            0            0K            0
            ipsbuf            0            0K            0
            iirbuf            0            0K            0
             cache            0            0K            0
            aaccam            0            0K            0
          kcovinfo            0            0K            0
      prison_racct            0            0K            0
       Fail Points            0            0K            0
             sigio            0            0K            1
filedesc_to_leader            0            0K            0
               pwd            0            0K            0
       tty console            0            0K            0
            aacbuf            0            0K            0
              zstd            0            0K            0
            XZ_DEC            0            0K            0
            nvlist            0            0K            0
          SCSI ENC            0            0K            0
           SCSI sa            0            0K            0
         scsi_pass            0            0K            0
        isofs_node            0            0K            0
       isofs_mount            0            0K            0
     tr_raid5_data            0            0K            0
    tr_raid1e_data            0            0K            0
     tr_raid1_data            0            0K            0
     tr_raid0_data            0            0K            0
    tr_concat_data            0            0K            0
       md_sii_data            0            0K            0
   md_promise_data            0            0K            0
    md_nvidia_data            0            0K            0
   md_jmicron_data            0            0K            0
     md_intel_data            0            0K            0
       md_ddf_data            0            0K            0
         raid_data            0            0K           72
     geom_flashmap            0            0K            0
         tmpfs dir            0            0K            0
        tmpfs name            0            0K            0
       tmpfs mount            0            0K            0
           NFS FHA            0            0K            0
         newnfsmnt            0            0K            0
  newnfsclient_req            0            0K            0
   NFSCL layrecall            0            0K            0
     NFSCL session            0            0K            0
     NFSCL sockreq            0            0K            0
     NFSCL devinfo            0            0K            0
     NFSCL flayout            0            0K            0
      NFSCL layout            0            0K            0
     NFSD rollback            0            0K            0
      NFSCL diroff            0            0K            0
       NEWdirectio            0            0K            0
        NEWNFSnode            0            0K            0
db> show uma
              Zone   Size    Used    Free    Requests  Sleeps  Bucket  Total Mem    XFree
   mbuf_jumbo_page   4096    1088    1010       16875       0     254    8593408        0
              pbuf   2624       0     794           0       0       2    2083456        0
          BUF TRIE    144     179   11637         520       0      62    1701504        0
       malloc-4096   4096     324       2         486       0       2    1335296        0
        malloc-128    128   10172      27       10173       0     126    1305472        0
              mbuf    256    1346    1009       26055       0     254     602880        0
        malloc-512    512    1028      12        1028       0      30     532480        0
        RADIX NODE    144    2394     373       29198       0      62     398448        0
            lkpimm    168       1    2327           1       0      62     391104        0
          lkpicurr    168       2    2326           2       0      62     391104        0
         vmem btag     56    6550     121        6550       0     254     373576        0
       UMA Slabs 0    112    2968      17        2968       0     126     334320        0
       malloc-2048   2048     131       1         131       0       8     270336        0
      malloc-65536  65536       4       0           4       0       1     262144        0
         VM OBJECT    264     926      64       11825       0      30     261360        0
             VNODE    448     523      35         553       0      30     249984        0
        256 Bucket   2048     100      18        2906       0       8     241664        0
         malloc-64     64    3340      62        3359       0     254     217728        0
         malloc-16     16   13028     222       13114       0     254     212000        0
        malloc-256    256     740      55        1166       0      62     203520        0
            DEVCTL   1024       0     192          93       0       0     196608        0
      malloc-65536  65536       2       1         102       0       1     196608        0
       malloc-4096   4096      41       4        1091       0       2     184320        0
            THREAD   1840     100       0         100       0       8     184000        0
         UMA Zones    768     220       4         220       0      16     172032        0
         malloc-32     32    4413     123        4493       0     254     145152        0
       FFS2 dinode    256     502      23         529       0      62     134400        0
      malloc-65536  65536       2       0           2       0       1     131072        0
      malloc-65536  65536       2       0           2       0       1     131072        0
      malloc-32768  32768       4       0           4       0       1     131072        0
     FPU_save_area   1088     102      10         118       0       8     121856        0
       S VFS Cache    104     997     134        1077       0     126     117624        0
          ksiginfo    112      35    1009          67       0     126     116928        0
        malloc-128    128     832      36        1929       0     126     111104        0
       malloc-8192   8192      13       0          86       0       1     106496        0
         FFS inode    192     502      44         529       0      62     104832        0
       malloc-1024   1024      93       7         105       0      16     102400        0
         MAP ENTRY     96     803     247       38687       0     126     100800        0
          UMA Kegs    384     206       7         206       0      30      81792        0
      mbuf_cluster   2048      30       2          30       0     254      65536        0
      malloc-65536  65536       1       0           1       0       1      65536        0
      malloc-65536  65536       1       0           1       0       1      65536        0
      malloc-65536  65536       1       0           1       0       1      65536        0
              PROC   1336      34      14         817       0       8      64128        0
           VMSPACE   2552      18       6         802       0       4      61248        0
         filedesc0   1072      35      14         818       0       8      52528        0
        128 Bucket   1024      35      16         519       0      16      52224        0
        malloc-128    128     369      34       31435       0     126      51584        0
         malloc-64     64     612     144        1109       0     254      48384        0
        malloc-384    384      78      32         137       0      30      42240        0
            clpbuf   2624       0      16          33       0      16      41984        0
       malloc-8192   8192       3       2           5       0       1      40960        0
         64 Bucket    512      57      23        1182       0      30      40960        0
        malloc-128    128     290      20         541       0     126      39680        0
        malloc-256    256     115      35         132       0      62      38400        0
             NAMEI   1024       0      36       12410       0      16      36864        0
        malloc-256    256     127       8         680       0      62      34560        0
         32 Bucket    256      39      96        2706       0      62      34560        0
           DIRHASH   1024      32       0          32       0      16      32768        0
      malloc-32768  32768       0       1          52       0       1      32768        0
      malloc-32768  32768       1       0           1       0       1      32768        0
      malloc-32768  32768       0       1           1       0       1      32768        0
      malloc-16384  16384       2       0          66       0       1      32768        0
       malloc-8192   8192       4       0           4       0       1      32768        0
           pcpu-64     64     454      58         454       0     254      32768        0
            pcpu-8      8    3295     289        3318       0     254      28672        0
            socket    960      20       8        1013       0     254      26880        0
             g_bio    384       0      70        4784       0      30      26880        0
        malloc-256    256      67      38         590       0      62      26880        0
         malloc-64     64     220     158       17966       0     254      24192        0
        malloc-384    384      55       5         234       0      30      23040        0
        malloc-384    384      56       4          56       0      30      23040        0
       malloc-4096   4096       5       0           5       0       2      20480        0
       malloc-1024   1024      13       7          33       0      16      20480        0
         malloc-64     64     200     115         206       0     254      20160        0
        malloc-128    128     101      54         170       0     126      19840        0
       Mountpoints   2752       2       5           2       0       4      19264        0
      malloc-16384  16384       1       0           1       0       1      16384        0
       malloc-2048   2048       5       3          55       0       8      16384        0
       malloc-2048   2048       3       5           9       0       8      16384        0
         malloc-64     64     178      74        9321       0     254      16128        0
         malloc-32     32     277     227         407       0     254      16128        0
        malloc-256    256      56       4          56       0      62      15360        0
             tcpcb   1096       4      10          10       0     254      15344        0
              pipe    744       7      13         297       0      16      14880        0
         TURNSTILE    136     101       4         101       0      62      14280        0
       malloc-4096   4096       3       0           3       0       2      12288        0
       malloc-4096   4096       2       1          47       0       2      12288        0
       malloc-4096   4096       1       2        1095       0       2      12288        0
       malloc-2048   2048       4       2           4       0       8      12288        0
       malloc-1024   1024       6       6        1030       0      16      12288        0
       malloc-1024   1024      10       2          10       0      16      12288        0
             Files     80      81      69        7009       0     126      12000        0
         malloc-16     16     303     447         561       0     254      12000        0
         udp_inpcb    496       2      22          60       0     254      11904        0
        malloc-256    256      35      10         130       0      62      11520        0
        SLEEPQUEUE     88     101      27         101       0     126      11264        0
       malloc-8192   8192       1       0           1       0       1       8192        0
       malloc-8192   8192       1       0           1       0       1       8192        0
       malloc-2048   2048       3       1           3       0       8       8192        0
       malloc-2048   2048       0       4         213       0       8       8192        0
       malloc-1024   1024       0       8           4       0      16       8192        0
       malloc-1024   1024       5       3           5       0      16       8192        0
       malloc-1024   1024       4       4           4       0      16       8192        0
       malloc-1024   1024       7       1           7       0      16       8192        0
        malloc-512    512      10       6          18       0      30       8192        0
        malloc-512    512       4      12         189       0      30       8192        0
        malloc-512    512       3      13           3       0      30       8192        0
           rtentry    176      11      35          14       0      62       8096        0
              PGRP     88      15      77          31       0     126       8096        0
          rl_entry     40      27     175          29       0     254       8080        0
             udpcb     32       2     250          60       0     254       8064        0
               PWD     32      11     241          95       0     254       8064        0
         malloc-64     64      13     113          30       0     254       8064        0
         malloc-64     64      63      63         914       0     254       8064        0
         malloc-64     64      29      97          35       0     254       8064        0
         malloc-32     32      15     237          79       0     254       8064        0
         malloc-32     32     115     137         264       0     254       8064        0
         malloc-32     32      18     234          59       0     254       8064        0
         malloc-32     32      61     191         764       0     254       8064        0
         malloc-32     32      22     230        5037       0     254       8064        0
         malloc-32     32      17     235          27       0     254       8064        0
         16 Bucket    144      30      26         198       0      62       8064        0
          4 Bucket     48       5     163          52       0     254       8064        0
          2 Bucket     32      40     212         452       0     254       8064        0
      vtnet_tx_hdr     24       1     333        8130       0     254       8016        0
         malloc-16     16      16     484          17       0     254       8000        0
         malloc-16     16       9     491          10       0     254       8000        0
         malloc-16     16     179     321         916       0     254       8000        0
         malloc-16     16      31     469       27655       0     254       8000        0
         malloc-16     16       4     496           4       0     254       8000        0
          8 Bucket     80      30      70         337       0     126       8000        0
         tcp_inpcb    496       4      12          10       0     254       7936        0
        malloc-128    128       7      55           7       0     126       7936        0
        malloc-128    128      32      30          56       0     126       7936        0
        malloc-128    128      55       7          55       0     126       7936        0
              kenv    258       2      28         709       0      30       7740        0
     routing nhops    256       8      22          14       0      62       7680        0
             unpcb    256      12      18         931       0     254       7680        0
       mbuf_packet    256       0      30         101       0     254       7680        0
        malloc-384    384       0      20          12       0      30       7680        0
        malloc-384    384       1      19           5       0      30       7680        0
        malloc-256    256       5      25           5       0      62       7680        0
        malloc-256    256       5      25         382       0      62       7680        0
            cpuset    104       7      55           7       0     126       6448        0
 epoch_record pcpu    256       4      12           4       0      62       4096        0
       malloc-4096   4096       1       0           1       0       2       4096        0
       malloc-2048   2048       2       0           2       0       8       4096        0
       malloc-2048   2048       1       1           1       0       8       4096        0
        malloc-512    512       0       8           1       0      30       4096        0
           pcpu-16     16       7     249           7       0     254       4096        0
         hostcache     64       1      62           1       0     254       4032        0
          syncache    168       0      24           5       0     254       4032        0
             KNOTE    160       2      23           2       0      62       4000        0
            ttyinq    160      15      10          45       0      62       4000        0
         malloc-16     16       8     242          12       0     254       4000        0
             ripcb    496       1       7           1       0     254       3968        0
       UMA Slabs 1    176       6      16           6       0      62       3872        0
       L VFS Cache    320       0      12           1       0      30       3840        0
           ttyoutq    256       8       7          24       0      62       3840        0
        malloc-384    384       8       2           8       0      30       3840        0
        KMAP ENTRY     96      12      27          15       0       0       3744        0
              vmem   1856       1       1           1       0       8       3712        0
           SMR CPU     32       3      60           3       0     254       2016        0
        SMR SHARED     24       3      60           3       0     254       1512        0
   pf state scrubs     40       0       0           0       0     254          0        0
   pf frag entries     40       0       0           0       0     254          0        0
          pf frags    248       0       0           0       0      62          0        0
  pf table entries    160       0       0           0       0      62          0        0
pf table entry counters     64       0       0           0       0     254          0        0
   pf source nodes    136       0       0           0       0     254          0        0
     pf state keys     88       0       0           0       0     126          0        0
         pf states    312       0       0           0       0     254          0        0
           pf tags    104       0       0           0       0     126          0        0
          pf mtags     48       0       0           0       0     254          0        0
             swblk    136       0       0           0       0      62          0        0
          swpctrie    144       0       0           0       0      62          0        0
       FFS1 dinode    128       0       0           0       0     126          0        0
            da_ccb    544       0       0           0       0      16          0        0
           ada_ccb    272       0       0           0       0      30          0        0
    IPsec SA lft_c     16       0       0           0       0     254          0        0
     udplite_inpcb    496       0       0           0       0     254          0        0
      tcp_log_node    120       0       0           0       0     126          0        0
    tcp_log_bucket    176       0       0           0       0      62          0        0
           tcp_log    416       0       0           0       0     254          0        0
          tcpreass     48       0       0           0       0     254          0        0
tfo_ccache_entries     80       0       0           0       0     126          0        0
               tfo      4       0       0           0       0     254          0        0
          sackhole     32       0       0           0       0     254          0        0
             tcptw     88       0       0           0       0     254          0        0
               ipq     56       0       0           0       0     254          0        0
            itimer    352       0       0           0       0      30          0        0
            AIOLIO    272       0       0           0       0      30          0        0
             AIOCB    552       0       0           0       0      16          0        0
              AIOP     32       0       0           0       0     254          0        0
               AIO    208       0       0           0       0      62          0        0
        TMPFS node    224       0       0           0       0      62          0        0
           NCLNODE    592       0       0           0       0      16          0        0
     LTS VFS Cache    360       0       0           0       0      30          0        0
     STS VFS Cache    144       0       0           0       0      62          0        0
           cryptop    280       0       0           0       0      30          0        0
  linux_dma_object     32       0       0           0       0     254          0        0
  linux_dma_pctrie    144       0       0           0       0      62          0        0
   IOMMU_MAP_ENTRY    120       0       0           0       0     126          0        0
    mbuf_jumbo_16k  16384       0       0           0       0     254          0        0
     mbuf_jumbo_9k   9216       0       0           0       0     254          0        0
      audit_record   1280       0       0           0       0       8          0        0
         domainset     40       0       0           0       0     254          0        0
        MAC labels     40       0       0           0       0     254          0        0
            vnpbuf   2624       0       0           0       0      64          0        0
            mdpbuf   2624       0       0           0       0       3          0        0
           nfspbuf   2624       0       0           0       0      16          0        0
            swwbuf   2624       0       0           0       0       8          0        0
            swrbuf   2624       0       0           0       0      16          0        0
          umtx_shm     88       0       0           0       0     126          0        0
           umtx pi     96       0       0           0       0     126          0        0
rangeset pctrie nodes    144       0       0           0       0      62          0        0
      malloc-65536  65536       0       0           0       0       1          0        0
      malloc-32768  32768       0       0           0       0       1          0        0
      malloc-32768  32768       0       0           0       0       1          0        0
      malloc-32768  32768       0       0           0       0       1          0        0
      malloc-32768  32768       0       0           0       0       1          0        0
      malloc-16384  16384       0       0           0       0       1          0        0
      malloc-16384  16384       0       0           0       0       1          0        0
      malloc-16384  16384       0       0           0       0       1          0        0
      malloc-16384  16384       0       0           0       0       1          0        0
      malloc-16384  16384       0       0           0       0       1          0        0
      malloc-16384  16384       0       0           0       0       1          0        0
       malloc-8192   8192       0       0           0       0       1          0        0
       malloc-8192   8192       0       0           0       0       1          0        0
       malloc-8192   8192       0       0           0       0       1          0        0
       malloc-4096   4096       0       0           0       0       2          0        0
        malloc-512    512       0       0           0       0      30          0        0
        malloc-512    512       0       0           0       0      30          0        0
        malloc-512    512       0       0           0       0      30          0        0
        malloc-384    384       0       0           0       0      30          0        0
        malloc-384    384       0       0           0       0      30          0        0
           pcpu-32     32       0       0           0       0     254          0        0
            pcpu-4      4       0       0           0       0     254          0        0
            fakepg    104       0       0           0       0     126          0        0
          UMA Hash    256       0       0           0       0      62          0        0


Syzkaller reproducer:
# {Threaded:false Collide:false Repeat:false RepeatTimes:0 Procs:1 Slowdown:1 Sandbox: Leak:false NetInjection:false NetDevices:false NetReset:false Cgroups:false BinfmtMisc:false CloseFDs:false KCSAN:false DevlinkPCI:false USB:false VhciInjection:false Wifi:false IEEE802154:false Sysctl:false UseTmpDir:false HandleSegv:false Repro:false Trace:false LegacyOptions:{Fault:false FaultCall:0 FaultNth:0}}
openat$bpf(0xffffffffffffff9c, &(0x7f0000001280), 0x0, 0x0)
r0 = kqueue()
kevent(r0, &(0x7f0000000000)=[{0x3a7d1fdf, 0xfffffffffffffffa, 0x1, 0x8, 0x4, 0xfb0, [0x1, 0x7f, 0x6, 0x8000000000]}, {0x3, 0xfffffffffffffffe, 0x21, 0x40, 0x7, 0xfffffffffffffc00, [0x808, 0xffff, 0x10001, 0x20]}, {0x7ff, 0xe, 0x8020, 0x2, 0x100000000, 0x5, [0x1, 0x1, 0x81, 0x1]}, {0x20, 0xfffffffffffffffb, 0x18, 0x1, 0x6, 0x8, [0x3ff, 0xfffffffffffffffa, 0x0, 0x8]}], 0x4, 0x0, 0x0, 0x0)


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
  memcpy((void*)0x20001280, "/dev/bpf\000", 9);
  syscall(SYS_openat, 0xffffffffffffff9cul, 0x20001280ul, 0ul, 0ul);
  res = syscall(SYS_kqueue);
  if (res != -1)
    r[0] = res;
  *(uint64_t*)0x20000000 = 0x3a7d1fdf;
  *(uint16_t*)0x20000008 = 0xfffa;
  *(uint16_t*)0x2000000a = 1;
  *(uint32_t*)0x2000000c = 8;
  *(uint64_t*)0x20000010 = 4;
  *(uint64_t*)0x20000018 = 0xfb0;
  *(uint64_t*)0x20000020 = 1;
  *(uint64_t*)0x20000028 = 0x7f;
  *(uint64_t*)0x20000030 = 6;
  *(uint64_t*)0x20000038 = 0x8000000000;
  *(uint64_t*)0x20000040 = 3;
  *(uint16_t*)0x20000048 = 0xfffe;
  *(uint16_t*)0x2000004a = 0x21;
  *(uint32_t*)0x2000004c = 0x40;
  *(uint64_t*)0x20000050 = 7;
  *(uint64_t*)0x20000058 = 0xfffffffffffffc00;
  *(uint64_t*)0x20000060 = 0x808;
  *(uint64_t*)0x20000068 = 0xffff;
  *(uint64_t*)0x20000070 = 0x10001;
  *(uint64_t*)0x20000078 = 0x20;
  *(uint64_t*)0x20000080 = 0x7ff;
  *(uint16_t*)0x20000088 = 0xe;
  *(uint16_t*)0x2000008a = 0x8020;
  *(uint32_t*)0x2000008c = 2;
  *(uint64_t*)0x20000090 = 0x100000000;
  *(uint64_t*)0x20000098 = 5;
  *(uint64_t*)0x200000a0 = 1;
  *(uint64_t*)0x200000a8 = 1;
  *(uint64_t*)0x200000b0 = 0x81;
  *(uint64_t*)0x200000b8 = 1;
  *(uint64_t*)0x200000c0 = 0x20;
  *(uint16_t*)0x200000c8 = 0xfffb;
  *(uint16_t*)0x200000ca = 0x18;
  *(uint32_t*)0x200000cc = 1;
  *(uint64_t*)0x200000d0 = 6;
  *(uint64_t*)0x200000d8 = 8;
  *(uint64_t*)0x200000e0 = 0x3ff;
  *(uint64_t*)0x200000e8 = 0xfffffffffffffffa;
  *(uint64_t*)0x200000f0 = 0;
  *(uint64_t*)0x200000f8 = 8;
  syscall(SYS_kevent, r[0], 0x20000000ul, 4ul, 0ul, 0ul, 0ul);
  return 0;
}


