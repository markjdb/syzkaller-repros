Syzkaller hit 'Fatal trap NUM: page fault in __mtx_lock_flags' bug.

Fatal trap 12: page fault while in kernel mode
cpuid = 1; apic id = 01
fault virtual address	= 0x18
fault code		= supervisor read data, page not present
instruction pointer	= 0x20:0xffffffff8165d165
stack pointer	        = 0x28:0xfffffe00753b2300
frame pointer	        = 0x28:0xfffffe00753b23d0
code segment		= base 0x0, limit 0xfffff, type 0x1b
			= DPL 0, pres 1, long 1, def32 0, gran 1
processor eflags	= interrupt enabled, resume, IOPL = 0
current process		= 901 (syz-executor3877901)
rdi:               18 rsi:                0 rdx:                0
rcx: fffffe00033ef038  r8: fffff78000000000  r9:      20000000000
rax: fffffe00033ef038 rbx:                0 rbp: fffffe00753b23d0
r10:                0 r11: fffffe008fee2700 r12: ffffffff82c37ee0
r13: ffffffff82c37ee0 r14:               18 r15:              4eb
trap number		= 12
panic: page fault
cpuid = 1
time = 1676001921
KDB: stack backtrace:
db_trace_self_wrapper() at db_trace_self_wrapper+0xc7/frame 0xfffffe00753b1b10
kdb_backtrace() at kdb_backtrace+0xd3/frame 0xfffffe00753b1c70
vpanic() at vpanic+0x254/frame 0xfffffe00753b1d50
panic() at panic+0xb5/frame 0xfffffe00753b1e10
trap_fatal() at trap_fatal+0x7cf/frame 0xfffffe00753b1f10
trap_pfault() at trap_pfault+0x186/frame 0xfffffe00753b2050
trap() at trap+0x5de/frame 0xfffffe00753b2230
calltrap() at calltrap+0x8/frame 0xfffffe00753b2230
--- trap 0xc, rip = 0xffffffff8165d165, rsp = 0xfffffe00753b2300, rbp = 0xfffffe00753b23d0 ---
__mtx_lock_flags() at __mtx_lock_flags+0x125/frame 0xfffffe00753b23d0
ktls_enable_rx() at ktls_enable_rx+0x29b/frame 0xfffffe00753b24b0
tcp_default_ctloutput() at tcp_default_ctloutput+0x193d/frame 0xfffffe00753b2810
tcp_ctloutput_set() at tcp_ctloutput_set+0x4e2/frame 0xfffffe00753b2970
tcp_ctloutput() at tcp_ctloutput+0x132/frame 0xfffffe00753b2a70
sosetopt() at sosetopt+0x214/frame 0xfffffe00753b2bd0
kern_setsockopt() at kern_setsockopt+0x262/frame 0xfffffe00753b2d00
sys_setsockopt() at sys_setsockopt+0x76/frame 0xfffffe00753b2d50
amd64_syscall() at amd64_syscall+0x3d7/frame 0xfffffe00753b2f30
fast_syscall_common() at fast_syscall_common+0xf8/frame 0xfffffe00753b2f30
--- syscall (0, FreeBSD ELF64, syscall), rip = 0x23404a, rsp = 0x825183f78, rbp = 0x825183f80 ---
KDB: enter: panic
[ thread pid 901 tid 100262 ]
Stopped at      kdb_enter+0x6b: movq    $0,0x271259a(%rip)
db> 
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
rcx         0xb178b3621790b75d
rdx         0xdffff7c000000000
rbx                          0
rsp         0xfffffe00753b1c50
rbp         0xfffffe00753b1c70
rsi                        0x1
rdi                          0
r8                         0x3
r9                  0xffffffff
r10                          0
r11         0xfffffe008fee2700
r12                          0
r13         0xfffffe008fee21e0
r14         0xffffffff82bf1340  .str.26
r15         0xffffffff82bf1340  .str.26
rip         0xffffffff81779cfb  kdb_enter+0x6b
rflags                    0x46
kdb_enter+0x6b: movq    $0,0x271259a(%rip)
db> show proc
Process 901 (syz-executor3877901) at 0xfffffe008f811560:
 state: NORMAL
 uid: 0  gids: 0, 0, 5
 parent: pid 818 at 0xfffffe008f810ab0
 ABI: FreeBSD ELF64
 flag: 0x10000080  flag2: 0
 arguments: /root/syz-executor3877901472
 reaper: 0xfffffe0053dc7010 reapsubtree: 1
 sigparent: 20
 vmspace: 0xfffffe008f7f3400
   (map 0xfffffe008f7f3400)
   (map.pmap 0xfffffe008f7f34c0)
   (pmap 0xfffffe008f7f3530)
 threads: 3
100083                   RunQ                                syz-executor3877901
100262                   Run     CPU 1                       syz-executor3877901
100263                   S       uwait   0xfffffe005428ab80  syz-executor3877901
db> show routetable

Route table for AF 2 (INET):
dst <0.0.0.0> gateway <169.254.0.1> netmask <0.0.0.0> ifp <on link> ifa <169.254.0.218> flags UP,GATEWAY,STATIC
dst <127.0.0.1> gateway <on link> netmask <NULL> ifp <on link> ifa <127.0.0.1> flags UP,HOST,PINNED
dst <169.254.0.0> gateway <on link> netmask <255.255.255.0> ifp <on link> ifa <169.254.0.218> flags UP,PINNED
dst <169.254.0.218> gateway <on link> netmask <NULL> ifp <on link> ifa <127.0.0.1> flags UP,HOST,STATIC,PINNED

Route table for AF 28 (INET6):
dst <::> gateway <::1> netmask <ffff:ffff:ffff:ffff:ffff:ffff::> ifp <on link> ifa <::1> flags UP,GATEWAY,REJECT,STATIC
dst <::1> gateway <on link> netmask <NULL> ifp <on link> ifa <::1> flags UP,HOST,STATIC,PINNED
dst <::ffff:0.0.0.0> gateway <::1> netmask <ffff:ffff:ffff:ffff:ffff:ffff::> ifp <on link> ifa <::1> flags UP,GATEWAY,REJECT,STATIC
dst <fe80::> gateway <::1> netmask <ffc0::> ifp <on link> ifa <::1> flags UP,GATEWAY,REJECT,STATIC
dst <fe80:2::> gateway <on link> netmask <ffff:ffff:ffff:ffff::> ifp <on link> ifa <fe80:2::1> flags UP,PINNED
dst <fe80:2::1> gateway <on link> netmask <NULL> ifp <on link> ifa <fe80:2::1> flags UP,HOST,STATIC,PINNED
dst <ff02::> gateway <::1> netmask <ffff::> ifp <on link> ifa <::1> flags UP,GATEWAY,REJECT,STATIC
db> show all ifnets
              vtnet0 ifp=0xfffffe00543a0800
                 lo0 ifp=0xfffffe00543a0000
db> ps
  pid  ppid  pgrp   uid  state   wmesg   wchan               cmd
  901   818   816     0  R       (threaded)                  syz-executor3877901
100083                   RunQ                                syz-executor3877901
100262                   Run     CPU 1                       syz-executor3877901
100263                   S       uwait   0xfffffe005428ab80  syz-executor3877901
  821     0     0     0  DL      (threaded)                  [KTLS]
100081                   D       -       0xfffffe00543b4000  [thr_0]
100103                   D       -       0xfffffe00543b4080  [thr_1]
100104                   D       -       0xffffffff83f7a1a8  [alloc_0]
  818   816   816     0  R                                   syz-executor3877901
  817   816   816     0  R                                   syz-executor3877901
  816   814   816     0  Ss      nanslp  0xffffffff83e59a01  syz-executor3877901
  814   745   814     0  Ss      select  0xfffffe0054323540  sshd
  805     1   805     0  Ss+     ttyin   0xfffffe00543a90b0  getty
  785     1   785     0  Ss      nanslp  0xffffffff83e59a00  cron
  781     1   781    25  Ss      pause   0xfffffe00572ad610  sendmail
  777     1   777     0  Ss      select  0xfffffe00543236c0  sendmail
  745     1   745     0  Ss      select  0xfffffe00543239c0  sshd
  648     1   648     0  Ss      select  0xfffffe0054323940  syslogd
  453     1   453     0  Ss      select  0xfffffe0054323a40  devd
  351     1   351    65  Ss      select  0xfffffe0056d093c0  dhclient
  269     1   269     0  Ss      select  0xfffffe0056d08e40  dhclient
  266     1   266     0  Ss      select  0xfffffe0056d08dc0  dhclient
   94     0     0     0  RL                                  [pf purge]
   15     0     0     0  RL                                  [syncer]
    9     0     0     0  DL      vlruwt  0xfffffe00542e7008  [vnlru]
    8     0     0     0  RL      (threaded)                  [bufdaemon]
100063                   RunQ                                [bufdaemon]
100064                   RunQ                                [bufspacedaemon-0]
100076                   RunQ                                [/ worker]
    7     0     0     0  DL      psleep  0xffffffff83fb1a40  [vmdaemon]
    6     0     0     0  RL      (threaded)                  [pagedaemon]
100061                   RunQ                                [dom0]
100065                   D       launds  0xffffffff83fa5904  [laundry: dom0]
100066                   D       umarcl  0xffffffff81ed8e60  [uma]
    5     0     0     0  RL                                  [rand_harvestq]
    4     0     0     0  DL      (threaded)                  [cam]
100042                   D       -       0xffffffff83ab8340  [doneq0]
100043                   D       -       0xffffffff83ab82c0  [async]
100060                   D       -       0xffffffff83ab8140  [scanner]
   14     0     0     0  DL      seqstat 0xfffffe0053f65888  [sequencer 00]
    3     0     0     0  DL      (threaded)                  [crypto]
100038                   D       crypto_ 0xffffffff83fa10e0  [crypto]
100039                   D       crypto_ 0xfffffe0053e7d930  [crypto returns 0]
100040                   D       crypto_ 0xfffffe0053e7d980  [crypto returns 1]
   13     0     0     0  DL      (threaded)                  [geom]
100033                   D       -       0xffffffff83e2ee80  [g_event]
100034                   D       -       0xffffffff83e2eea0  [g_up]
100035                   D       -       0xffffffff83e2eec0  [g_down]
    2     0     0     0  WL      (threaded)                  [clock]
100029                   I                                   [clock (0)]
100030                   I                                   [clock (1)]
   12     0     0     0  WL      (threaded)                  [intr]
100013                   I                                   [swi6: Giant taskq]
100015                   I                                   [swi5: fast taskq]
100019                   I                                   [swi6: task queue]
100031                   I                                   [swi1: netisr 0]
100044                   I                                   [irq40: virtio_pci0]
100045                   I                                   [irq41: virtio_pci0]
100046                   I                                   [irq42: virtio_pci0]
100049                   I                                   [irq43: virtio_pci1]
100050                   I                                   [irq44: virtio_pci1]
100051                   I                                   [irq1: atkbd0]
100052                   I                                   [irq12: psm0]
100053                   I                                   [swi0: uart uart++]
100079                   I                                   [swi1: pf send]
   11     0     0     0  RL      (threaded)                  [idle]
100003                   Run     CPU 0                       [idle: cpu0]
100004                   CanRun                              [idle: cpu1]
    1     0     1     0  SLs     wait    0xfffffe0053dc7010  [init]
   10     0     0     0  DL      audit_w 0xffffffff83fa1c40  [audit]
    0     0     0     0  DLs     (threaded)                  [kernel]
100000                   D       swapin  0xffffffff83e2f8a0  [swapper]
100005                   D       -       0xfffffe0053c7a000  [if_io_tqg_0]
100006                   D       -       0xfffffe0053c79e00  [if_io_tqg_1]
100007                   D       -       0xfffffe0053c79d00  [if_config_tqg_0]
100008                   D       -       0xfffffe0053c79c00  [softirq_0]
100009                   D       -       0xfffffe0053c79b00  [softirq_1]
100010                   D       -       0xfffffe00081f9000  [linuxkpi_irq_wq]
100011                   D       -       0xfffffe00081f8e00  [aiod_kick taskq]
100012                   D       -       0xfffffe00081f8d00  [deferred_unmount ta]
100014                   D       -       0xfffffe00081f8b00  [thread taskq]
100016                   D       -       0xfffffe00081f8900  [kqueue_ctx taskq]
100017                   D       -       0xfffffe00081f8800  [in6m_free taskq]
100018                   D       -       0xfffffe00081f8700  [pci_hp taskq]
100020                   D       -       0xfffffe00081f8500  [inm_free taskq]
100021                   D       -       0xfffffe00081f8400  [linuxkpi_short_wq_0]
100022                   D       -       0xfffffe00081f8400  [linuxkpi_short_wq_1]
100023                   D       -       0xfffffe00081f8400  [linuxkpi_short_wq_2]
100024                   D       -       0xfffffe00081f8400  [linuxkpi_short_wq_3]
100025                   D       -       0xfffffe00081f8300  [linuxkpi_long_wq_0]
100026                   D       -       0xfffffe00081f8300  [linuxkpi_long_wq_1]
100027                   D       -       0xfffffe00081f8300  [linuxkpi_long_wq_2]
100028                   D       -       0xfffffe00081f8300  [linuxkpi_long_wq_3]
100032                   D       -       0xfffffe00081f8200  [firmware taskq]
100036                   D       -       0xfffffe00081f8100  [crypto_0]
100037                   D       -       0xfffffe00081f8100  [crypto_1]
100047                   D       -       0xfffffe00543b5300  [vtnet0 rxq 0]
100048                   D       -       0xfffffe00543b5200  [vtnet0 txq 0]
100054                   D       -       0xffffffff82bf73e0  [deadlkres]
100055                   D       -       0xfffffe00543b4300  [acpi_task_0]
100056                   D       -       0xfffffe00543b4300  [acpi_task_1]
100057                   D       -       0xfffffe00543b4300  [acpi_task_2]
100059                   D       -       0xfffffe00081f8000  [CAM taskq]
  902   817   816     0  Z                                   syz-executor3877901
db> show all locks
db> show malloc
              Type        InUse        MemUse     Requests
           pf_hash            5        11524K            5
         sysctloid        31376         1846K        31418
            linker          257         1387K          275
              kobj          327         1308K          491
            newblk          812         1227K          904
            devbuf         1357         1137K         1374
          vfscache            3         1025K            3
               pcb           17          525K           27
          inodedep           29          523K          103
         ufs_quota            1          512K            1
          vfs_hash            1          512K            1
           callout            2          512K            2
              intr            4          472K            4
           subproc           90          157K          959
           tidhash            3          141K            3
           pagedep           12          131K           35
        tfo_ccache            1          128K            1
          IP reass            1          128K            1
         vnet_data            1          112K            1
               sem            4          106K            4
            DEVFS1           92           92K          104
               bus          974           79K         3688
            bus-sc           31           76K         1058
              vmem            3           73K            5
          mtx_pool            2           72K            2
          syncache            1           68K            1
          acpitask            1           64K            1
       ddb_capture            1           64K            1
            module          501           63K          501
            acpica          420           39K        63706
               LRO            2           33K            2
         hostcache            1           32K            1
               shm            1           32K            1
              umtx          242           31K          242
               msg            4           30K            4
           kdtrace          142           30K         1168
            DEVFS3          111           28K          127
            kbdmux            5           28K            5
        gtaskqueue           18           26K           18
        DEVFS_RULE           62           22K           62
               BPF           10           18K           10
           ithread           95           18K           95
              temp           15           17K         1573
         ufs_mount            4           17K            5
              proc            3           17K            3
            KTRACE          100           13K          100
           devstat            6           13K            6
      eventhandler          143           12K          143
              rman          102           12K          526
            ifaddr           29           11K           30
              GEOM           61           11K          496
              kenv           59           10K           59
          routetbl           44           10K          142
              UART           12            9K           12
               rpc            2            8K            2
         bmsafemap            1            8K           94
             shmfd            1            8K            1
       pfs_vncache            1            8K            1
         pfs_nodes           20            8K           20
     audit_evclass          237            8K          296
              cred           28            7K          300
         taskqueue           56            6K           56
            sglist            3            6K            3
       ufs_dirhash           24            5K           24
             ifnet            3            5K            3
               UMA          252            5K          252
           io_apic            1            4K            1
               tty            4            4K            4
          filedesc            1            4K            1
             evdev            4            4K            4
             hhook           15            4K           17
            diradd           26            4K          107
          pf_ifnet            5            3K            6
            plimit           12            3K          255
           lltable           10            3K           10
           acpisem           21            3K           21
           uidinfo            4            3K           10
             lockf           22            3K           36
            crypto            8            3K          332
            kqueue           34            3K          903
           pwddesc           33            3K          903
        local_apic            1            2K            1
       fpukern_ctx            2            2K            2
         ipsec-saq            2            2K            2
             clone            8            2K            8
           CAM DEV            1            2K            2
             selfd           27            2K        12031
               msi           13            2K           13
           session           13            2K           32
         proc-args           45            2K         1883
          pci_link           16            2K           16
            Unitno           25            2K           47
           acpidev           22            2K           22
         toponodes           10            2K           10
         CAM queue            2            2K            5
           softdep            1            1K            1
       ipsecpolicy            1            1K            1
            sahead            1            1K            1
          secasvar            1            1K            1
       ether_multi           13            1K           18
       vnodemarker            2            1K           16
            select            8            1K           61
      NFSD session            1            1K            1
         in6_multi            9            1K            9
          indirdep            3            1K            3
             nhops            6            1K            6
             mount           16            1K          123
            CC Mem            5            1K           93
            isadev            5            1K            5
           CAM XPT           11            1K           12
          in_multi            2            1K            3
              pfil            4            1K            4
              cdev            2            1K            2
 encap_export_host            8            1K            8
               osd            9            1K          103
            ip6ndp            3            1K            3
    chacha20random            1            1K            1
        CAM periph            2            1K           14
              ktls            3            1K          165
      NFSD lckfile            1            1K            1
     NFSD V4client            1            1K            1
               MCA            2            1K            2
            DEVFSP            4            1K           25
             DEVFS            9            1K           10
            dirrem            1            1K           46
       inpcbpolicy            8            1K          154
               mld            2            1K            2
              igmp            2            1K            2
            vnodes            1            1K            1
            feeder            7            1K            7
        loginclass            3            1K            7
            prison            6            1K            6
       lkpikmalloc            5            1K            6
        aesni_data            2            1K            2
         cryptodev            2            1K          161
            apmdev            1            1K            1
          atkbddev            2            1K            2
         newdirblk            1            1K           15
             mkdir            1            1K           30
          ktls_ocf            1            1K           82
           netlink            1            1K            1
           CAM SIM            1            1K            1
          procdesc            1            1K           20
          pmchooks            1            1K            1
            soname            4            1K         2598
          nexusdev            6            1K            6
               tun            3            1K            3
     CAM dev queue            1            1K            1
           tcpfunc            1            1K            1
              vnet            1            1K            1
               pmc            1            1K            1
          acpiintr            1            1K            1
              cpus            2            1K            2
    vnet_data_free            1            1K            1
          CAM path            1            1K           12
           entropy            1            1K           66
           Per-cpu            1            1K            1
          freework            1            1K           26
          p1003.1b            1            1K            1
          filecaps            1            1K          101
          pf_table            0            0K            0
           pf_rule            0            0K            0
           pf_altq            0            0K            0
           pf_osfp            0            0K            0
           pf_temp            0            0K            0
           filemon            0            0K            0
     NFSCL sockreq            0            0K            0
     NFSCL devinfo            0            0K            0
        madt_table            0            0K            2
          smartpqi            0            0K            0
     NFSCL flayout            0            0K            0
      NFSCL layout            0            0K            0
     NFSD rollback            0            0K            0
               ixl            0            0K            0
      NFSCL diroff            0            0K            0
       NEWdirectio            0            0K            0
        NEWNFSnode            0            0K            0
         NFSCL lck            0            0K            0
      NFSCL lckown            0            0K            0
      NFSCL client            0            0K            0
       NFSCL deleg            0            0K            0
        ice-resmgr            0            0K            0
         ice-osdep            0            0K            0
               ice            0            0K            0
              iavf            0            0K            0
             axgbe            0            0K            0
        NFSCL open            0            0K            0
       NFSCL owner            0            0K            0
            NFS fh            0            0K            0
           NFS req            0            0K            0
     NFSD usrgroup            0            0K            0
       NFSD string            0            0K            0
       NFSD V4lock            0            0K            0
      NFSD V4state            0            0K            0
           memdesc            0            0K            0
          xen_intr            0            0K            0
     NFSD srvcache            0            0K            0
       msdosfs_fat            0            0K            0
           xen_hvm            0            0K            0
         legacydrv            0            0K            0
            bounce            0            0K            0
            busdma            0            0K            0
            qpidrv            0            0K            0
     msdosfs_mount            0            0K            0
      msdosfs_node            0            0K            0
      dmar_idpgtbl            0            0K            0
          dmar_dom            0            0K            0
          dmar_ctx            0            0K            0
              isci            0            0K            0
      iommu_dmamap            0            0K            0
     hyperv_socket            0            0K            0
           bxe_ilt            0            0K            0
            DEVFS4            0            0K            0
            xenbus            0            0K            0
            DEVFS2            0            0K            0
     vm_fictitious            0            0K            0
            gntdev            0            0K            0
       privcmd_dev            0            0K            0
        evtchn_dev            0            0K            0
          xenstore            0            0K            0
         scsi_pass            0            0K            0
         ciss_data            0            0K            0
               xnb            0            0K            0
          xen_acpi            0            0K            0
              xbbd            0            0K            0
               xbd            0            0K            0
           Balloon            0            0K            0
           UMAHash            0            0K            0
          sysmouse            0            0K            0
            vtfont            0            0K            0
         vm_pgdata            0            0K            0
           jblocks            0            0K            0
          savedino            0            0K           26
          sentinel            0            0K            0
            jfsync            0            0K            0
            jtrunc            0            0K            0
             sbdep            0            0K            6
           jsegdep            0            0K            0
              jseg            0            0K            0
         jfreefrag            0            0K            0
          jfreeblk            0            0K            0
           jnewblk            0            0K            0
            jmvref            0            0K            0
           jremref            0            0K            0
           jaddref            0            0K            0
           freedep            0            0K            0
          freefile            0            0K           27
          freeblks            0            0K           25
          freefrag            0            0K            7
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
                vt            0            0K            0
             vtbuf            0            0K            0
         BACKLIGHT            0            0K            0
           ath_hal            0            0K            0
            athdev            0            0K            0
           ata_pci            0            0K            0
           ata_dma            0            0K            0
       ata_generic            0            0K            0
            pvscsi            0            0K            0
           scsi_da            0            0K            0
            ata_da            0            0K            0
           scsi_ch            0            0K            0
           scsi_cd            0            0K            0
       AHCI driver            0            0K            0
            USBdev            0            0K            0
               USB            0            0K            0
        MLX5EEPROM            0            0K            0
        MLX5EEPROM            0            0K            0
        MLX5EEPROM            0            0K            0
        MLX5EEPROM            0            0K            0
        MLX5EEPROM            0            0K            0
      MLX5E_TLS_RX            0            0K            0
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
        MLX5EEPROM            0            0K            0
       simple_attr            0            0K            0
          seq_file            0            0K            0
           lkpiskb            0            0K            0
             radix            0            0K            0
               idr            0            0K            0
          lkpindev            0            0K            0
            lkpifw            0            0K            0
         lkpi80211            0            0K            0
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
               agp            0            0K            0
            statfs            0            0K           14
     namei_tracker            0            0K            2
       export_host            0            0K            0
        cl_savebuf            0            0K            6
           nvme_da            0            0K            0
 CAM I/O Scheduler            0            0K            0
           acpipwr            0            0K            0
         acpi_perf            0            0K            0
            twsbuf            0            0K            0
      twe_commands            0            0K            0
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
            biobuf            0            0K            0
               aio            0            0K            0
               lio            0            0K            0
               acl            0            0K            0
          mbuf_tag            0            0K            0
               PUC            0            0K            0
          ppbusdev            0            0K            0
agtiapi_MemAlloc malloc            0            0K            0
    osti_cacheable            0            0K            0
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
              accf            0            0K            0
               pts            0            0K            0
               iov            0            0K         8031
          ioctlops            0            0K           78
           eventfd            0            0K            0
           Witness            0            0K            0
          terminal            0            0K            0
             stack            0            0K            0
          mpt_user            0            0K            0
          mps_user            0            0K            0
            MPSSAS            0            0K            0
               mps            0            0K            0
          mpr_user            0            0K            0
              sbuf            0            0K          364
            MPRSAS            0            0K            0
          firmware            0            0K            0
        compressor            0            0K            0
               mpr            0            0K            0
              SWAP            0            0K            0
            mfibuf            0            0K            0
        md_sectors            0            0K            0
         sysctltmp            0            0K          531
            sysctl            0            0K           34
           md_disk            0            0K            0
              ekcd            0            0K            0
            dumper            0            0K            0
          sendfile            0            0K            0
              rctl            0            0K            0
           malodev            0            0K            0
               LED            0            0K            0
          ix_sriov            0            0K            0
             cache            0            0K            0
        aacraidcam            0            0K            0
                ix            0            0K            0
          kcovinfo            0            0K            0
      prison_racct            0            0K            0
       Fail Points            0            0K            0
             sigio            0            0K            1
filedesc_to_leader            0            0K            0
               pwd            0            0K            0
       tty console            0            0K            0
            ipsbuf            0            0K            0
       aacraid_buf            0            0K            0
            aaccam            0            0K            0
            aacbuf            0            0K            0
         boottrace            0            0K            0
              zstd            0            0K            0
            XZ_DEC            0            0K            0
            nvlist            0            0K            0
          SCSI ENC            0            0K            0
           SCSI sa            0            0K            0
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
     tmpfs extattr            0            0K            0
           NFS FHA            0            0K            0
         newnfsmnt            0            0K            0
  newnfsclient_req            0            0K            0
   NFSCL layrecall            0            0K            0
     NFSCL session            0            0K            0
db> show uma
              Zone   Size    Used    Free    Requests  Sleeps  Bucket  Total Mem    XFree
   mbuf_jumbo_page   4096    1088    1706       20222       0     254   11444224        0
              pbuf   2624       0     778           0       0       2    2041472        0
          BUF TRIE    144     184   11632         622       0      62    1701504        0
       malloc-4096   4096     367       5        1664       0       2    1523712        0
        malloc-128    128   10341     137       10459       0     126    1341184        0
      mbuf_cluster   2048     508       0         508       0     254    1040384        0
              mbuf    256    1346    1716       31291       0     254     783872        0
        malloc-512    512    1028      52        1042       0      30     552960        0
            socket    960      19     489        1105       0     254     487680        0
         vmem btag     56    8256      63        8256       0     254     465864        0
       UMA Slabs 0    112    4055       7        4055       0     126     454944        0
        RADIX NODE    144    2488     391       28565       0      62     414576        0
      malloc-65536  65536       6       0           6       0       1     393216        0
            lkpimm    168       1    2327           1       0      62     391104        0
          lkpicurr    168       2    2326           2       0      62     391104        0
       malloc-2048   2048     130      14         130       0       8     294912        0
        256 Bucket   2048     116      20         644       0       8     278528        0
         VM OBJECT    264     890     160       15079       0      30     277200        0
      malloc-65536  65536       3       1          72       0       1     262144        0
      malloc-65536  65536       4       0           4       0       1     262144        0
         malloc-64     64    3600     495        3921       0     254     262080        0
             VNODE    448     513      63         543       0      30     258048        0
        malloc-256    256     861      69        1005       0      62     238080        0
            THREAD   1824     107      14         264       0       8     220704        0
         malloc-16     16   13267     233       14657       0     254     216000        0
            DEVCTL   1024       0     196          94       0       0     200704        0
         UMA Zones    768     224       0         224       0      16     172032        0
         malloc-32     32    4538     376        4954       0     254     157248        0
       FFS2 dinode    256     492      78         519       0      62     145920        0
      malloc-65536  65536       0       2          31       0       1     131072        0
             unpcb    256      10     500         940       0     254     130560        0
       mbuf_packet    256       0     508          90       0     254     130048        0
       S VFS Cache    104     978     192        1058       0     126     121680        0
         MAP ENTRY     96     732     528       44048       0     126     120960        0
          ksiginfo    112      37    1007          70       0     126     116928        0
       malloc-1024   1024      97      15         109       0      16     114688        0
     FPU_save_area    832     109      26         279       0      16     112320        0
         FFS inode    192     492      75         519       0      62     108864        0
        malloc-128    128     554     221         850       0     126      99200        0
      malloc-32768  32768       3       0           3       0       1      98304        0
          syncache    168       0     528           5       0     254      88704        0
            clpbuf   2624       0      32          36       0      16      83968        0
          UMA Kegs    384     209       4         209       0      30      81792        0
           VMSPACE   2560      16      14         887       0       4      76800        0
              PROC   1368      33      22         902       0       8      75240        0
        128 Bucket   1024      42      25         171       0      16      68608        0
        malloc-128    128     288     239         317       0     126      67456        0
        malloc-128    128     345     182       31679       0     126      67456        0
      malloc-65536  65536       1       0           1       0       1      65536        0
      malloc-32768  32768       0       2          49       0       1      65536        0
      malloc-32768  32768       2       0           2       0       1      65536        0
       malloc-8192   8192       8       0          77       0       1      65536        0
        malloc-256    256     115     140         140       0      62      65280        0
        malloc-256    256     158      97         664       0      62      65280        0
             g_bio    384       0     150        5087       0      30      57600        0
         64 Bucket    512      70      34        1537       0      30      53248        0
         filedesc0   1072      33      16         903       0       8      52528        0
         malloc-64     64     616     203         831       0     254      52416        0
        malloc-128    128     301     102         980       0     126      51584        0
        malloc-256    256      53     142         465       0      62      49920        0
         32 Bucket    256      57     138        5311       0      62      49920        0
           DIRHASH   1024      33      15          33       0      16      49152        0
       malloc-8192   8192       6       0           6       0       1      49152        0
       malloc-1024   1024      18      30          25       0      16      49152        0
           pcpu-64     64     467     301         467       0     254      49152        0
         udp_inpcb    472       2      94          60       0      30      45312        0
         tcp_inpcb   1312       5      28          93       0       8      43296        0
         malloc-64     64       0     567           2       0     254      36288        0
         malloc-64     64     114     453         175       0     254      36288        0
         malloc-64     64      45     522         929       0     254      36288        0
         malloc-64     64     133     434       13964       0     254      36288        0
         malloc-64     64     169     398        9422       0     254      36288        0
         malloc-64     64      33     534          69       0     254      36288        0
        malloc-128    128      10     269          18       0     126      35712        0
        malloc-128    128     158     121         845       0     126      35712        0
        malloc-128    128      39     240         109       0     126      35712        0
      ktls_session    256       1     134          82       0      62      34560        0
     routing nhops    256       8     127          14       0      62      34560        0
        malloc-384    384      59      31         240       0      30      34560        0
        malloc-384    384      63      27          63       0      30      34560        0
        malloc-384    384      28      62         102       0      30      34560        0
        malloc-256    256      15     120          64       0      62      34560        0
        malloc-256    256      36      99         657       0      62      34560        0
        malloc-256    256       5     130         418       0      62      34560        0
        malloc-256    256      59      76         179       0      62      34560        0
             NAMEI   1024       0      32       12286       0      16      32768        0
      malloc-32768  32768       0       1           1       0       1      32768        0
      malloc-16384  16384       2       0          66       0       1      32768        0
       malloc-4096   4096       7       1           7       0       2      32768        0
       malloc-2048   2048       3      13          36       0       8      32768        0
       malloc-2048   2048       6      10          12       0       8      32768        0
       malloc-2048   2048       4      12           4       0       8      32768        0
       malloc-2048   2048       0      16         214       0       8      32768        0
       malloc-2048   2048       2      14          19       0       8      32768        0
       malloc-1024   1024       7      25         168       0      16      32768        0
       malloc-1024   1024       4      28          25       0      16      32768        0
       malloc-1024   1024       7      25           7       0      16      32768        0
       malloc-1024   1024      12      20         991       0      16      32768        0
        malloc-512    512       3      61         176       0      30      32768        0
        malloc-512    512       3      61           3       0      30      32768        0
        malloc-512    512       8      56          15       0      30      32768        0
            cpuset    104       8     271           8       0     126      29016        0
            pcpu-8      8    3323     261        3346       0     254      28672        0
          4 Bucket     48       6     582          23       0     254      28224        0
         TURNSTILE    136     122      67         122       0      62      25704        0
       malloc-4096   4096       3       3           5       0       2      24576        0
              PGRP     88      13     263          32       0     126      24288        0
          rl_entry     40      30     576          32       0     254      24240        0
           rtentry    168      11     133          14       0      62      24192        0
              pipe    728       5      28         291       0      16      24024        0
             Files     80      69     231        6960       0     126      24000        0
          8 Bucket     80      36     264         190       0     126      24000        0
        malloc-384    384      10      50          19       0      30      23040        0
        malloc-384    384      11      49          23       0      30      23040        0
        malloc-384    384       1      59           5       0      30      23040        0
        SLEEPQUEUE     88     122     134         122       0     126      22528        0
         hostcache     64       1     314           1       0     254      20160        0
   udp_inpcb ports     32       1     629           7       0     254      20160        0
   tcp_inpcb ports     32       3     627          85       0     254      20160        0
              ertt     72       5     275          93       0     126      20160        0
               PWD     32      11     619          97       0     254      20160        0
         malloc-32     32     247     383         308       0     254      20160        0
         malloc-32     32      57     573          82       0     254      20160        0
         malloc-32     32      39     591         142       0     254      20160        0
         malloc-32     32      31     599         100       0     254      20160        0
         malloc-32     32      40     590         592       0     254      20160        0
         malloc-32     32      29     601        5169       0     254      20160        0
         malloc-32     32      21     609         148       0     254      20160        0
         16 Bucket    144      39     101         173       0      62      20160        0
          2 Bucket     32      45     585         293       0     254      20160        0
       Mountpoints   2752       2       5           2       0       4      19264        0
           ttyoutq    256       8      67          24       0      62      19200        0
 epoch_record pcpu    256       4      60           4       0      62      16384        0
      malloc-16384  16384       1       0           1       0       1      16384        0
       malloc-8192   8192       2       0           2       0       1      16384        0
       malloc-8192   8192       1       1           3       0       1      16384        0
       malloc-8192   8192       2       0           2       0       1      16384        0
       malloc-8192   8192       2       0           2       0       1      16384        0
       malloc-4096   4096       1       3          52       0       2      16384        0
       malloc-4096   4096       1       3          17       0       2      16384        0
       malloc-4096   4096       0       4           6       0       2      16384        0
       malloc-2048   2048       2       6           2       0       8      16384        0
       malloc-1024   1024       2      14           2       0      16      16384        0
        malloc-512    512       1      31           1       0      30      16384        0
        malloc-512    512       0      32           1       0      30      16384        0
           SMR CPU     32       7     504           7       0     254      16352        0
             ripcb    440       1      35           1       0      30      15840        0
              kenv    258       2      58         693       0      30      15480        0
              vmem   1856       1       7           1       0       8      14848        0
        SMR SHARED     24       7     504           7       0     254      12264        0
    ertt_txseginfo     40       0     303         386       0     254      12120        0
            ttyinq    160      15      60          45       0      62      12000        0
         malloc-16     16       6     744          98       0     254      12000        0
         malloc-16     16      14     736         137       0     254      12000        0
         malloc-16     16     265     485         432       0     254      12000        0
         malloc-16     16      15     735          72       0     254      12000        0
         malloc-16     16     177     573        1870       0     254      12000        0
         malloc-16     16      28     722       27907       0     254      12000        0
         malloc-16     16      18     732          96       0     254      12000        0
       L VFS Cache    320       0      36           1       0      30      11520        0
        malloc-384    384      20      10          20       0      30      11520        0
       malloc-8192   8192       1       0           1       0       1       8192        0
       malloc-8192   8192       1       0           1       0       1       8192        0
       malloc-4096   4096       1       1           2       0       2       8192        0
       malloc-4096   4096       1       1           1       0       2       8192        0
      vtnet_tx_hdr     24       1     333        9978       0     254       8016        0
           pcpu-16     16       7     249           7       0     254       4096        0
       UMA Slabs 1    176       6      16           6       0      62       3872        0
        KMAP ENTRY     96      14      25          17       0       0       3744        0
   pf state scrubs     40       0       0           0       0     254          0        0
   pf frag entries     40       0       0           0       0     254          0        0
          pf frags    248       0       0           0       0      62          0        0
  pf table entries    160       0       0           0       0     254          0        0
pf table entry counters     64       0       0           0       0     254          0        0
   pf source nodes    136       0       0           0       0     254          0        0
     pf state keys     88       0       0           0       0     126          0        0
         pf states    312       0       0           0       0     254          0        0
           pf tags    104       0       0           0       0     126          0        0
          pf mtags    184       0       0           0       0      62          0        0
            da_ccb    544       0       0           0       0      16          0        0
           ada_ccb    272       0       0           0       0      30          0        0
             swblk    136       0       0           0       0      62          0        0
          swpctrie    144       0       0           0       0      62          0        0
       FFS1 dinode    128       0       0           0       0     126          0        0
tfo_ccache_entries     80       0       0           0       0     126          0        0
               tfo      4       0       0           0       0     254          0        0
          sackhole     32       0       0           0       0     254          0        0
               ipq     56       0       0           0       0     254          0        0
   tcp_log_id_node    120       0       0           0       0     126          0        0
 tcp_log_id_bucket    176       0       0           0       0      62          0        0
           tcp_log    416       0       0           0       0     254          0        0
          tcpreass     48       0       0           0       0     254          0        0
       ripcb ports     32       0       0           0       0     254          0        0
udplite_inpcb ports     32       0       0           0       0     254          0        0
     udplite_inpcb    472       0       0           0       0      30          0        0
    IPsec SA lft_c     16       0       0           0       0     254          0        0
             KNOTE    160       0       0           0       0      62          0        0
            itimer    352       0       0           0       0      30          0        0
            AIOLIO    272       0       0           0       0      30          0        0
             AIOCB    552       0       0           0       0      16          0        0
               AIO    208       0       0           0       0      62          0        0
           NCLNODE    608       0       0           0       0      16          0        0
        TMPFS node    232       0       0           0       0      62          0        0
     LTS VFS Cache    360       0       0           0       0      30          0        0
     STS VFS Cache    144       0       0           0       0      62          0        0
           cryptop    280       0       0           0       0      30          0        0
  linux_dma_object     32       0       0           0       0     254          0        0
  linux_dma_pctrie    144       0       0           0       0      62          0        0
   IOMMU_MAP_ENTRY    104       0       0           0       0     126          0        0
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
      malloc-65536  65536       0       0           0       0       1          0        0
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
       malloc-2048   2048       0       0           0       0       8          0        0
       malloc-1024   1024       0       0           0       0      16          0        0
        malloc-512    512       0       0           0       0      30          0        0
        malloc-512    512       0       0           0       0      30          0        0
        malloc-384    384       0       0           0       0      30          0        0
           pcpu-32     32       0       0           0       0     254          0        0
            pcpu-4      4       0       0           0       0     254          0        0
            fakepg    104       0       0           0       0     126          0        0
          UMA Hash    256       0       0           0       0      62          0        0


Syzkaller reproducer:
# {Threaded:true Repeat:true RepeatTimes:0 Procs:2 Slowdown:1 Sandbox:none SandboxArg:0 Leak:false NetInjection:false NetDevices:false NetReset:false Cgroups:false BinfmtMisc:false CloseFDs:false KCSAN:false DevlinkPCI:false NicVF:false USB:false VhciInjection:false Wifi:false IEEE802154:false Sysctl:false UseTmpDir:false HandleSegv:true Repro:false Trace:false LegacyOptions:{Collide:false Fault:false FaultCall:0 FaultNth:0}}
r0 = socket$inet_tcp(0x2, 0x1, 0x0)
setsockopt$inet_tcp_TCP_RXTLS_ENABLE(r0, 0x6, 0x29, &(0x7f00000002c0)={&(0x7f0000000040)="e84ef4ade4f5ef1a650400763b9402ad00"/32, 0x0, &(0x7f0000000000)="b4", 0xb, 0x20, 0x0, 0x7, 0x1, 0x0, 0x3, 0x3, 'i0;\x00\x00\b\x00'}, 0x40) (async)
listen(r0, 0x8)


C reproducer:
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
#include <sys/resource.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

static unsigned long long procid;

static __thread int clone_ongoing;
static __thread int skip_segv;
static __thread jmp_buf segv_env;

static void segv_handler(int sig, siginfo_t* info, void* ctx)
{
  if (__atomic_load_n(&clone_ongoing, __ATOMIC_RELAXED) != 0) {
    exit(sig);
  }
  uintptr_t addr = (uintptr_t)info->si_addr;
  const uintptr_t prog_start = 1 << 20;
  const uintptr_t prog_end = 100 << 20;
  int skip = __atomic_load_n(&skip_segv, __ATOMIC_RELAXED) != 0;
  int valid = addr < prog_start || addr > prog_end;
  if (sig == SIGBUS)
    valid = 1;
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
  for (call = 0; call < 3; call++) {
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
      if (call == 1)
        break;
      event_timedwait(&th->done, 50);
      break;
    }
  }
  for (i = 0; i < 100 && __atomic_load_n(&running, __ATOMIC_RELAXED); i++)
    sleep_ms(1);
}

static void execute_one(void);

#define WAIT_FLAGS 0

static void loop(void)
{
  int iter = 0;
  for (;; iter++) {
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
      if (current_time_ms() - start < 5000)
        continue;
      kill_and_wait(pid, &status);
      break;
    }
  }
}

uint64_t r[1] = {0xffffffffffffffff};

void execute_call(int call)
{
  intptr_t res = 0;
  switch (call) {
  case 0:
    res = syscall(SYS_socket, 2ul, 1ul, 0);
    if (res != -1)
      r[0] = res;
    break;
  case 1:
    NONFAILING(*(uint64_t*)0x200002c0 = 0x20000040);
    NONFAILING(memcpy(
        (void*)0x20000040,
        "\xe8\x4e\xf4\xad\xe4\xf5\xef\x1a\x65\x04\x00\x76\x3b\x94\x02\xad\x00"
        "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00",
        32));
    NONFAILING(*(uint64_t*)0x200002c8 = 0);
    NONFAILING(*(uint64_t*)0x200002d0 = 0x20000000);
    NONFAILING(memset((void*)0x20000000, 180, 1));
    NONFAILING(*(uint32_t*)0x200002d8 = 0xb);
    NONFAILING(*(uint32_t*)0x200002dc = 0x20);
    NONFAILING(*(uint32_t*)0x200002e0 = 0);
    NONFAILING(*(uint32_t*)0x200002e4 = 7);
    NONFAILING(*(uint32_t*)0x200002e8 = 1);
    NONFAILING(*(uint32_t*)0x200002ec = 0);
    NONFAILING(*(uint8_t*)0x200002f0 = 3);
    NONFAILING(*(uint8_t*)0x200002f1 = 3);
    NONFAILING(memcpy((void*)0x200002f2, "i0;\000\000\b\000\000", 8));
    syscall(SYS_setsockopt, r[0], 6, 0x29, 0x200002c0ul, 0x40ul);
    break;
  case 2:
    syscall(SYS_listen, r[0], 8);
    break;
  }
}
int main(void)
{
  syscall(SYS_mmap, 0x20000000ul, 0x1000000ul, 7ul, 0x1012ul, -1, 0ul);
  install_segv_handler();
  for (procid = 0; procid < 2; procid++) {
    if (fork() == 0) {
      do_sandbox_none();
    }
  }
  sleep(1000000);
  return 0;
}


