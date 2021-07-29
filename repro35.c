Syzkaller hit 'panic: Assertion lock == sq->sq_lock failed at /root/freebsd/sys/kern/subr_sleepqueue.c:LINE' bug.

login: panic: Assertion lock == sq->sq_lock failed at /root/freebsd/sys/kern/subr_sleepqueue.c:371
cpuid = 1
time = 1627526435
KDB: stack backtrace:
db_trace_self_wrapper() at db_trace_self_wrapper+0xde/frame 0xfffffe001a72e2b0
vpanic() at vpanic+0x639/frame 0xfffffe001a72e370
panic() at panic+0x1b3/frame 0xfffffe001a72e480
sleepq_add() at sleepq_add+0x1034/frame 0xfffffe001a72e550
_sleep() at _sleep+0xcb4/frame 0xfffffe001a72e6b0
kern_sigtimedwait() at kern_sigtimedwait+0x1405/frame 0xfffffe001a72e920
sys_sigwaitinfo() at sys_sigwaitinfo+0x1ab/frame 0xfffffe001a72ea10
amd64_syscall() at amd64_syscall+0xa4e/frame 0xfffffe001a72ebf0
fast_syscall_common() at fast_syscall_common+0x104/frame 0xfffffe001a72ebf0
--- syscall (0, FreeBSD ELF64, nosys), rip = 0x23358a, rsp = 0x7fffffffea18, rbp = 0x7fffffffea60 ---
KDB: enter: panic
[ thread pid 829 tid 100091 ]
Stopped at      kdb_enter+0x1c7:        movq    $0x87024010,%rdi
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
rax         0xffffffff863362da
rcx                          0
rdx         0xffffffff8702b000  msan_dummy_orig
rbx                          0
rsp         0xfffffe001a72e250
rbp         0xfffffe001a72e2b0
rsi                        0x1
rdi         0xffffffff87024010  kdb_why
r8                           0
r9               0x1ff80000000
r10         0xffffffffffffffff
r11                  0x6bb8d00
r12                          0
r13         0xfffffe003a8d6f01
r14         0xfffffe003a8d6fb8
r15         0xffffffff863362da
rip         0xffffffff83f9d3c7  kdb_enter+0x1c7
rflags                    0x46
kdb_enter+0x1c7:        movq    $0x87024010,%rdi
db> show proc
Process 829 (syz-executor0973984) at 0xfffffe003a8d5a70:
 state: NORMAL
 uid: 0  gids: 0, 0, 5
 parent: pid 1 at 0xfffffe0011383538
 leader: pid 827 at 0xfffffe001f9d1a70
 ABI: FreeBSD ELF64
 flag: 0x10000000  flag2: 0
 arguments: /root/syz-executor097398468
 reaper: 0xfffffe0011383538 reapsubtree: 1
 sigparent: 0
 vmspace: 0xfffffe001f980000
   (map 0xfffffe001f980000)
   (map.pmap 0xfffffe001f9800c0)
   (pmap 0xfffffe001f980120)
 threads: 1
100091                   Run     CPU 1                       syz-executor0973984
db> ps
  pid  ppid  pgrp   uid  state   wmesg   wchan               cmd
  829     1   822     0  R       CPU 1                       syz-executor0973984
  828   826   822     0  R       CPU 0                       syz-executor0973984
  827   825   822     0  S       sigwait 0xfffffe003ae44000  syz-executor0973984
  826   824   822     0  S       nanslp  0xffffffff86ff77a1  syz-executor0973984
  825   824   822     0  S       nanslp  0xffffffff86ff77a1  syz-executor0973984
  824   822   822     0  S       nanslp  0xffffffff86ff77a1  syz-executor0973984
  822   820   822     0  Ss      pause   0xfffffe003b332b20  csh
  820   735   820     0  Ss      select  0xfffffe001137d4c0  sshd
  797     1   797     0  Ss+     ttyin   0xfffffe001aadacb0  getty
  781     1   781    25  Ss      pause   0xfffffe003ae5cb20  sendmail
  778     1   778     0  Ss      select  0xfffffe001a96b840  sendmail
  739     1   739     0  Ss      nanslp  0xffffffff86ff77a0  cron
  735     1   735     0  Ss      select  0xfffffe001137d240  sshd
  646     1   646     0  Ss      select  0xfffffe001a96ba40  syslogd
  449     1   449     0  Ss      select  0xfffffe001a96b7c0  devd
  352     1   352    65  Ss      select  0xfffffe001a96b8c0  dhclient
  270     1   270     0  Ss      select  0xfffffe001137d740  dhclient
  267     1   267     0  Ss      select  0xfffffe001137d7c0  dhclient
   95     0     0     0  DL      pftm    0xffffffff87731b30  [pf purge]
   21     0     0     0  DL      vlruwt  0xfffffe001f926a70  [vnlru]
   20     0     0     0  DL      syncer  0xffffffff870ef800  [syncer]
   19     0     0     0  DL      (threaded)                  [bufdaemon]
100070                   D       qsleep  0xffffffff870ee8a0  [bufdaemon]
100071                   D       -       0xffffffff86a0af80  [bufspacedaemon-0]
100084                   D       sdflush 0xfffffe0010b190e8  [/ worker]
   18     0     0     0  DL      psleep  0xffffffff87114588  [vmdaemon]
   17     0     0     0  DL      (threaded)                  [pagedaemon]
100068                   D       psleep  0xffffffff871089f8  [dom0]
100074                   D       launds  0xffffffff87108a04  [laundry: dom0]
100075                   D       umarcl  0xffffffff853706b0  [uma]
   16     0     0     0  DL      -       0xffffffff86e2bb58  [rand_harvestq]
   15     0     0     0  DL      -       0xffffffff870ebf5c  [soaiod4]
    9     0     0     0  DL      -       0xffffffff870ebf5c  [soaiod3]
    8     0     0     0  DL      -       0xffffffff870ebf5c  [soaiod2]
    7     0     0     0  DL      -       0xffffffff870ebf5c  [soaiod1]
    6     0     0     0  DL      (threaded)                  [cam]
100045                   D       -       0xffffffff86d03240  [doneq0]
100046                   D       -       0xffffffff86d031c0  [async]
100067                   D       -       0xffffffff86d03090  [scanner]
   14     0     0     0  DL      seqstat 0xfffffe001a58b488  [sequencer 00]
    5     0     0     0  DL      crypto_ 0xfffffe001a4c3c80  [crypto returns 1]
    4     0     0     0  DL      crypto_ 0xfffffe001a4c3c30  [crypto returns 0]
    3     0     0     0  DL      crypto_ 0xffffffff87105f20  [crypto]
   13     0     0     0  DL      (threaded)                  [geom]
100036                   D       -       0xffffffff86fd6fe0  [g_event]
100037                   D       -       0xffffffff86fd6fe8  [g_up]
100038                   D       -       0xffffffff86fd6ff0  [g_down]
    2     0     0     0  DL      (threaded)                  [KTLS]
100029                   D       -       0xfffffe001a4c3e00  [thr_0]
100030                   D       -       0xfffffe001a4c3e80  [thr_1]
   12     0     0     0  WL      (threaded)                  [intr]
100010                   I                                   [swi5: fast taskq]
100018                   I                                   [swi6: task queue]
100019                   I                                   [swi6: Giant taskq]
100031                   I                                   [swi1: netisr 0]
100032                   I                                   [swi4: clock (0)]
100033                   I                                   [swi4: clock (1)]
100034                   I                                   [swi3: vm]
100047                   I                                   [irq40: virtio_pci0]
100048                   I                                   [irq41: virtio_pci0]
100049                   I                                   [irq42: virtio_pci0]
100052                   I                                   [irq43: virtio_pci1]
100053                   I                                   [irq44: virtio_pci1]
100054                   I                                   [irq1: atkbd0]
100055                   I                                   [irq12: psm0]
100056                   I                                   [swi0: uart uart++]
100085                   I                                   [swi1: pf send]
   11     0     0     0  RL      (threaded)                  [idle]
100003                   CanRun                              [idle: cpu0]
100004                   CanRun                              [idle: cpu1]
    1     0     1     0  SLs     wait    0xfffffe0011383538  [init]
   10     0     0     0  DL      audit_w 0xffffffff87106430  [audit]
    0     0     0     0  DLs     (threaded)                  [kernel]
100000                   D       swapin  0xffffffff86fd7570  [swapper]
100005                   D       -       0xfffffe001123ec00  [if_io_tqg_0]
100006                   D       -       0xfffffe001123eb00  [if_io_tqg_1]
100007                   D       -       0xfffffe001123ea00  [if_config_tqg_0]
100008                   D       -       0xfffffe001123e900  [softirq_0]
100009                   D       -       0xfffffe001123e800  [softirq_1]
100011                   D       -       0xfffffe00113efa00  [in6m_free taskq]
100012                   D       -       0xfffffe00113ef900  [pci_hp taskq]
100013                   D       -       0xfffffe00113ef800  [aiod_kick taskq]
100014                   D       -       0xfffffe00113ef700  [kqueue_ctx taskq]
100015                   D       -       0xfffffe00113ef600  [inm_free taskq]
100016                   D       -       0xfffffe00113ef500  [deferred_unmount ta]
100017                   D       -       0xfffffe00113ef400  [linuxkpi_irq_wq]
100020                   D       -       0xfffffe001a47be00  [thread taskq]
100021                   D       -       0xfffffe001a47bd00  [linuxkpi_short_wq_0]
100022                   D       -       0xfffffe001a47bd00  [linuxkpi_short_wq_1]
100023                   D       -       0xfffffe001a47bd00  [linuxkpi_short_wq_2]
100024                   D       -       0xfffffe001a47bd00  [linuxkpi_short_wq_3]
100025                   D       -       0xfffffe001a47bc00  [linuxkpi_long_wq_0]
100026                   D       -       0xfffffe001a47bc00  [linuxkpi_long_wq_1]
100027                   D       -       0xfffffe001a47bc00  [linuxkpi_long_wq_2]
100028                   D       -       0xfffffe001a47bc00  [linuxkpi_long_wq_3]
100035                   D       -       0xfffffe001a4d9900  [firmware taskq]
100039                   D       -       0xfffffe001a4d9800  [crypto_0]
100040                   D       -       0xfffffe001a4d9800  [crypto_1]
100050                   D       -       0xfffffe001a93bd00  [vtnet0 rxq 0]
100051                   D       -       0xfffffe001a93bc00  [vtnet0 txq 0]
100059                   D       -       0xffffffff866de8c0  [deadlkres]
100062                   D       -       0xfffffe001a93b500  [acpi_task_0]
100063                   D       -       0xfffffe001a93b500  [acpi_task_1]
100064                   D       -       0xfffffe001a93b500  [acpi_task_2]
100066                   D       -       0xfffffe001a4d9700  [CAM taskq]
db> show all locks
Process 828 (syz-executor0973984) thread 0xfffffe003ae5d720 (100106)
exclusive rw vm object (vm object) r = 0 (0xfffffe003af0ca50) locked @ /root/freebsd/sys/vm/vm_fault.c:1332
shared sx vm map (user) (vm map (user)) r = 0 (0xfffffe003af2d060) locked @ /root/freebsd/sys/vm/vm_map.c:4935
db> show malloc
              Type        InUse        MemUse     Requests
           pf_hash            5        11524K            5
         sysctloid        30404         1794K        30446
             kmsan          106         1696K          106
            linker          227         1496K          240
              kobj          323         1292K          483
            newblk          571         1167K          668
            devbuf         1360         1150K         1377
          vfscache            3         1025K            3
               pcb           16          777K           32
          inodedep           18          519K          102
         ufs_quota            1          512K            1
          vfs_hash            1          512K            1
           callout            2          512K            2
              intr            4          472K            4
           subproc           95          181K          884
         vnet_data            1          168K            1
           tidhash            3          158K            3
           pagedep           13          131K           34
        tfo_ccache            1          128K            1
               sem            4          106K            4
            DEVFS1           91           91K          103
              vmem            3           84K            5
               bus          965           77K         2576
            bus-sc           31           76K         1061
          mtx_pool            2           72K            2
          syncache            1           68K            1
          acpitask            1           64K            1
       ddb_capture            1           64K            1
            module          491           62K          491
            acpica          420           39K        61577
               LRO            2           33K            2
              proc            3           33K            3
         hostcache            1           32K            1
               shm            1           32K            1
               msg            4           30K            4
           kdtrace          148           30K          937
            DEVFS3          110           28K          126
              umtx          220           28K          220
        gtaskqueue           18           26K           18
            kbdmux            5           22K            5
        DEVFS_RULE           59           21K           59
           ithread          104           19K          104
               BPF           10           18K           10
              temp           15           17K         1532
         ufs_mount            4           17K            5
       pfs_vncache            1           16K            1
            KTRACE          100           13K          100
           devstat            6           13K            6
              rman          103           12K          527
            ifaddr           29           11K           30
      eventhandler          125           11K          125
              GEOM           61           10K          508
              kenv           59           10K           59
          routetbl           44           10K          142
         bmsafemap            2            9K           92
              UART           12            9K           12
               rpc            2            8K            2
             shmfd            1            8K            1
         pfs_nodes           20            8K           20
     audit_evclass          236            8K          294
         taskqueue           54            6K           54
            sglist            3            6K            3
       ufs_dirhash           24            5K           24
              cred           18            5K          300
           uidinfo            4            5K           10
             ifnet            3            5K            3
               UMA          250            5K          250
           io_apic            1            4K            1
               tty            4            4K            4
             evdev            4            4K            4
          filedesc            1            4K            1
             hhook           13            4K           13
          pf_ifnet            5            3K            6
       fpukern_ctx            3            3K            3
           lltable           10            3K           10
           acpisem           21            3K           21
            kqueue           41            3K          830
           pwddesc           41            3K          830
            plimit           10            3K          243
             lockf           22            3K           36
        local_apic            1            2K            1
         ipsec-saq            2            2K            2
           CAM DEV            1            2K            2
             selfd           29            2K        16858
            diradd           14            2K          107
               msi           13            2K           13
           session           13            2K           32
          pci_link           16            2K           16
            Unitno           25            2K           45
           acpidev           22            2K           22
         toponodes           10            2K           10
         proc-args           30            2K          517
         CAM queue            2            2K            5
           softdep            1            1K            1
         newdirblk            8            1K           15
             mkdir            8            1K           30
       ipsecpolicy            1            1K            1
            sahead            1            1K            1
          secasvar            1            1K            1
             clone            8            1K            8
       ether_multi           13            1K           18
       vnodemarker            2            1K           12
            select            8            1K           61
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
            ip6ndp            3            1K            3
    chacha20random            1            1K            1
        CAM periph            2            1K           14
            DEVFSP            5            1K           22
               osd            3            1K            9
      NFSD lckfile            1            1K            1
     NFSD V4client            1            1K            1
             DEVFS            9            1K           10
               MCA            2            1K            2
               mld            2            1K            2
              igmp            2            1K            2
            vnodes            1            1K            1
              ktls            1            1K            1
       inpcbpolicy            7            1K           71
            feeder            7            1K            7
             xform            3            1K          140
        loginclass            3            1K            7
            prison            6            1K            6
       lkpikmalloc            5            1K            6
        aesni_data            2            1K            2
            apmdev            1            1K            1
          atkbddev            2            1K            2
          freefile            1            1K           28
           CAM SIM            1            1K            1
          procdesc            1            1K           20
          pmchooks            1            1K            1
            soname            4            1K         2570
          nexusdev            6            1K            6
               tun            3            1K            3
     CAM dev queue            1            1K            1
           tcpfunc            1            1K            1
              vnet            1            1K            1
          acpiintr            1            1K            1
               pmc            1            1K            1
              cpus            2            1K            2
          freework            1            1K           26
    vnet_data_free            1            1K            1
          CAM path            1            1K           12
           entropy            1            1K           55
           Per-cpu            1            1K            1
          p1003.1b            1            1K            1
          filecaps            1            1K          101
          pf_table            0            0K            0
           pf_rule            0            0K            0
           pf_altq            0            0K            0
           pf_osfp            0            0K            0
           pf_temp            0            0K            0
      NFSCL client            0            0K            0
       NFSCL deleg            0            0K            0
        madt_table            0            0K            2
          smartpqi            0            0K            0
        NFSCL open            0            0K            0
       NFSCL owner            0            0K            0
            NFS fh            0            0K            0
           NFS req            0            0K            0
     NFSD usrgroup            0            0K            0
       NFSD string            0            0K            0
       NFSD V4lock            0            0K            0
              iavf            0            0K            0
               ixl            0            0K            0
      NFSD V4state            0            0K            0
     NFSD srvcache            0            0K            0
       msdosfs_fat            0            0K            0
     msdosfs_mount            0            0K            0
      msdosfs_node            0            0K            0
        ice-resmgr            0            0K            0
         ice-osdep            0            0K            0
               ice            0            0K            0
             axgbe            0            0K            0
            DEVFS4            0            0K            0
            DEVFS2            0            0K            0
            gntdev            0            0K            0
       privcmd_dev            0            0K            0
        evtchn_dev            0            0K            0
           memdesc            0            0K            0
          xenstore            0            0K            0
          xen_intr            0            0K            0
         ciss_data            0            0K            0
         BACKLIGHT            0            0K            0
           xen_hvm            0            0K            0
         legacydrv            0            0K            0
            qpidrv            0            0K            0
               xnb            0            0K            0
              xbbd            0            0K            0
      dmar_idpgtbl            0            0K            0
          dmar_dom            0            0K            0
          dmar_ctx            0            0K            0
               xbd            0            0K            0
           Balloon            0            0K            0
          sysmouse            0            0K            0
              isci            0            0K            0
      iommu_dmamap            0            0K            0
     hyperv_socket            0            0K            0
           bxe_ilt            0            0K            0
            xenbus            0            0K            0
            vtfont            0            0K            0
                vt            0            0K            0
             vtbuf            0            0K            0
     vm_fictitious            0            0K            0
           ath_hal            0            0K            0
            athdev            0            0K            0
           ata_pci            0            0K            0
           ata_dma            0            0K            0
       ata_generic            0            0K            0
               amr            0            0K            0
            pvscsi            0            0K            0
           scsi_da            0            0K            0
            ata_da            0            0K            0
           scsi_ch            0            0K            0
           UMAHash            0            0K            0
           scsi_cd            0            0K            0
       AHCI driver            0            0K            0
         vm_pgdata            0            0K            0
           jblocks            0            0K            0
          savedino            0            0K            1
          sentinel            0            0K            0
            jfsync            0            0K            0
            jtrunc            0            0K            0
             sbdep            0            0K            4
           jsegdep            0            0K            0
              jseg            0            0K            0
         jfreefrag            0            0K            0
          jfreeblk            0            0K            0
           jnewblk            0            0K            0
            jmvref            0            0K            0
           jremref            0            0K            0
           jaddref            0            0K            0
           freedep            0            0K            0
            dirrem            0            0K           46
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
            USBdev            0            0K            0
               USB            0            0K            0
               agp            0            0K            0
           nvme_da            0            0K            0
 CAM I/O Scheduler            0            0K            0
           acpipwr            0            0K            0
         acpi_perf            0            0K            0
          ktls_ocf            0            0K            0
            twsbuf            0            0K            0
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
      twe_commands            0            0K            0
            statfs            0            0K           14
     namei_tracker            0            0K            2
       export_host            0            0K            0
        cl_savebuf            0            0K            6
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
    osti_cacheable            0            0K            0
            biobuf            0            0K            0
              aios            0            0K            0
               lio            0            0K            0
               acl            0            0K            0
          tempbuff            0            0K            0
          mbuf_tag            0            0K           16
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
               iov            0            0K         7812
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
         sysctltmp            0            0K          534
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
         NFSCL lck            0            0K            0
      NFSCL lckown            0            0K            0
db> show uma
              Zone   Size    Used    Free    Requests  Sleeps  Bucket  Total Mem    XFree
   mbuf_jumbo_page   4096    1088     877       14629       0     254    8048640        0
      malloc-16384  16384     109       0         109       0       1    1785856        0
        malloc-128    128   10731      88       10826       0     126    1384832        0
       malloc-4096   4096     323       1         483       0       2    1327104        0
          BUF TRIE    144     175    8981         473       0      62    1318464        0
              pbuf   2624       0     269           0       0       2     705856        0
              mbuf    256    1347     858       22640       0     254     564480        0
        malloc-512    512    1026      14        1034       0      30     532480        0
      malloc-65536  65536       6       1          37       0       1     458752        0
         vmem btag     56    7166      81        7166       0     254     405832        0
        RADIX NODE    144    2280     486       28688       0      62     398304        0
          lkpicurr    160       2    2348           2       0      62     376000        0
            lkpimm    160       1    2324           1       0      62     372000        0
       UMA Slabs 0    112    2945       4        2945       0     126     330288        0
       malloc-2048   2048     136       6         160       0       8     290816        0
             VNODE    448     526      41         557       0      30     254016        0
         VM OBJECT    264     886      74       12201       0      30     253440        0
        256 Bucket   2048     100      16        2770       0       8     237568        0
         malloc-64     64    3374      91        3430       0     254     221760        0
         malloc-16     16   12635     115       12683       0     254     204000        0
            THREAD   1808     106       4         106       0       8     198880        0
            DEVCTL   1024       0     192          93       0       0     196608        0
      malloc-65536  65536       3       0           3       0       1     196608        0
       malloc-4096   4096      40       4         833       0       2     180224        0
         UMA Zones    768     222       2         222       0      16     172032        0
        malloc-256    256     590      25        1194       0      62     157440        0
         malloc-32     32    4676     238        4823       0     254     157248        0
       FFS2 dinode    256     505      20         533       0      62     134400        0
      malloc-65536  65536       1       1          70       0       1     131072        0
      malloc-65536  65536       2       0           2       0       1     131072        0
      malloc-32768  32768       2       2           4       0       1     131072        0
       S VFS Cache    104    1004     127        1084       0     126     117624        0
          ksiginfo    112      35    1009          68       0     126     116928        0
       malloc-1024   1024     101      11         229       0      16     114688        0
         MAP ENTRY     96     722     454       38213       0     126     112896        0
       malloc-8192   8192      11       2          14       0       1     106496        0
         FFS inode    192     505      41         533       0      62     104832        0
          UMA Kegs    384     207       6         207       0      30      81792        0
         malloc-64     64     978     156       19139       0     254      72576        0
              PROC   1336      40      14         829       0       8      72144        0
      mbuf_cluster   2048      30       2          30       0     254      65536        0
      malloc-32768  32768       2       0          54       0       1      65536        0
        128 Bucket   1024      45      18         682       0      16      64512        0
        malloc-256    256     228      12         475       0      62      61440        0
           VMSPACE   2544      18       6         808       0       4      61056        0
         filedesc0   1072      41      15         830       0       8      60032        0
        malloc-128    128     374      29        3650       0     126      51584        0
        malloc-128    128     346      57       28257       0     126      51584        0
        malloc-384    384      73      57         159       0      30      49920        0
         32 Bucket    256      38     112         478       0      62      38400        0
           DIRHASH   1024      32       4          32       0      16      36864        0
             NAMEI   1024       0      36       12466       0      16      36864        0
      malloc-32768  32768       1       0           1       0       1      32768        0
      malloc-32768  32768       1       0           1       0       1      32768        0
      malloc-16384  16384       2       0           2       0       1      32768        0
           pcpu-64     64     455      57         455       0     254      32768        0
        malloc-256    256      94      26         573       0      62      30720        0
            socket    944      18      14        1014       0     254      30208        0
       malloc-4096   4096       6       1           8       0       2      28672        0
            pcpu-8      8    3292     292        3315       0     254      28672        0
         64 Bucket    512      51       5         712       0      30      28672        0
         malloc-64     64     261     180        3339       0     254      28224        0
             g_bio    384       0      70        4957       0      30      26880        0
        malloc-256    256      83      22         316       0      62      26880        0
            clpbuf   2624       0      10          29       0       5      26240        0
       malloc-4096   4096       4       2         274       0       2      24576        0
        malloc-128    128     149      37         580       0     126      23808        0
        malloc-384    384      54       6          54       0      30      23040        0
       malloc-1024   1024      14       6         883       0      16      20480        0
       Mountpoints   2752       2       5           2       0       4      19264        0
        malloc-256    256      29      46         401       0      62      19200        0
         TURNSTILE    136     111      15         111       0      62      17136        0
      malloc-16384  16384       1       0           1       0       1      16384        0
      malloc-16384  16384       1       0          65       0       1      16384        0
       malloc-8192   8192       0       2          32       0       1      16384        0
       malloc-8192   8192       2       0           2       0       1      16384        0
       malloc-8192   8192       2       0          43       0       1      16384        0
       malloc-8192   8192       2       0           2       0       1      16384        0
       malloc-4096   4096       4       0           5       0       2      16384        0
       malloc-2048   2048       5       3         232       0       8      16384        0
             tcpcb   1080       4      10          10       0     254      15120        0
              pipe    744       6      14         299       0      16      14880        0
       malloc-4096   4096       1       2          15       0       2      12288        0
       malloc-1024   1024       4       8          21       0      16      12288        0
       malloc-1024   1024       9       3           9       0      16      12288        0
             Files     80      71      79        7042       0     126      12000        0
        malloc-128    128      41      52         165       0     126      11904        0
        malloc-384    384      17      13          25       0      30      11520        0
        SLEEPQUEUE     88     111      17         111       0     126      11264        0
       malloc-4096   4096       2       0           2       0       2       8192        0
       malloc-4096   4096       2       0          39       0       2       8192        0
       malloc-2048   2048       1       3          13       0       8       8192        0
       malloc-1024   1024       4       4          53       0      16       8192        0
       malloc-1024   1024       4       4           4       0      16       8192        0
        malloc-512    512      10       6          20       0      30       8192        0
           rtentry    176      11      35          14       0      62       8096        0
              PGRP     88      13      79          32       0     126       8096        0
          rl_entry     40      27     175          29       0     254       8080        0
             udpcb     32       2     250          60       0     254       8064        0
               PWD     32      11     241          97       0     254       8064        0
         malloc-64     64      23     103        7588       0     254       8064        0
         malloc-64     64      34      92          51       0     254       8064        0
         malloc-64     64       5     121           9       0     254       8064        0
         malloc-64     64       8     118           9       0     254       8064        0
         malloc-64     64       7     119          29       0     254       8064        0
         malloc-32     32      61     191         225       0     254       8064        0
         malloc-32     32     120     132         881       0     254       8064        0
         malloc-32     32      29     223        4971       0     254       8064        0
         malloc-32     32      48     204          50       0     254       8064        0
         malloc-32     32      13     239          43       0     254       8064        0
         16 Bucket    144      29      27        1521       0      62       8064        0
          4 Bucket     48       6     162          49       0     254       8064        0
          2 Bucket     32      41     211         574       0     254       8064        0
         malloc-16     16      21     479         176       0     254       8000        0
         malloc-16     16      13     487          53       0     254       8000        0
         malloc-16     16     450      50        1318       0     254       8000        0
         malloc-16     16      37     463       26957       0     254       8000        0
         malloc-16     16      16     484          19       0     254       8000        0
          8 Bucket     80      26      74         294       0     126       8000        0
         tcp_inpcb    496       4      12          10       0     254       7936        0
         udp_inpcb    496       2      14          60       0     254       7936        0
        malloc-128    128      16      46          22       0     126       7936        0
        malloc-128    128       1      61          10       0     126       7936        0
              kenv    258       2      28         704       0      30       7740        0
     routing nhops    256       8      22          14       0      62       7680        0
             unpcb    256      10      20         932       0     254       7680        0
       mbuf_packet    256       0      30         102       0     254       7680        0
        malloc-384    384      20       0          20       0      30       7680        0
        malloc-384    384       8      12           9       0      30       7680        0
        malloc-384    384       0      20         194       0      30       7680        0
        malloc-256    256       1      29          92       0      62       7680        0
     FPU_save_area    832       1       8           1       0      16       7488        0
            cpuset    104       7      55           7       0     126       6448        0
 epoch_record pcpu    256       4      12           4       0      62       4096        0
       malloc-2048   2048       2       0           2       0       8       4096        0
       malloc-2048   2048       1       1           1       0       8       4096        0
       malloc-2048   2048       1       1           1       0       8       4096        0
       malloc-1024   1024       4       0           4       0      16       4096        0
       malloc-1024   1024       2       2           3       0      16       4096        0
        malloc-512    512       0       8         139       0      30       4096        0
        malloc-512    512       3       5          40       0      30       4096        0
        malloc-512    512       2       6           2       0      30       4096        0
           pcpu-16     16       7     249           7       0     254       4096        0
         hostcache     64       1      62           1       0     254       4032        0
          syncache    168       0      24           5       0     254       4032        0
               ipq     56       0      72           2       0     254       4032        0
         malloc-32     32       9     117          47       0     254       4032        0
         malloc-32     32       0     126           2       0     254       4032        0
      vtnet_tx_hdr     24       1     166        6948       0     254       4008        0
            ttyinq    160      15      10          45       0      62       4000        0
         malloc-16     16       4     246           5       0     254       4000        0
         malloc-16     16       7     243           7       0     254       4000        0
             ripcb    496       1       7           1       0     254       3968        0
        malloc-128    128      11      20          12       0     126       3968        0
       UMA Slabs 1    176       6      16           6       0      62       3872        0
       L VFS Cache    320       0      12           1       0      30       3840        0
           ttyoutq    256       8       7          24       0      62       3840        0
        malloc-256    256       1      14           1       0      62       3840        0
        malloc-256    256      15       0          15       0      62       3840        0
        KMAP ENTRY     96      11      28          12       0       0       3744        0
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
            da_ccb    544       0       0           0       0      16          0        0
           ada_ccb    272       0       0           0       0      30          0        0
             swblk    136       0       0           0       0      62          0        0
          swpctrie    144       0       0           0       0      62          0        0
       FFS1 dinode    128       0       0           0       0     126          0        0
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
             KNOTE    160       0       0           0       0      62          0        0
            itimer    352       0       0           0       0      30          0        0
            AIOLIO    272       0       0           0       0      30          0        0
             AIOCB    552       0       0           0       0      16          0        0
              AIOP     32       0       0           0       0     254          0        0
               AIO    208       0       0           0       0      62          0        0
        TMPFS node    224       0       0           0       0      62          0        0
           NCLNODE    584       0       0           0       0      16          0        0
     LTS VFS Cache    360       0       0           0       0      30          0        0
     STS VFS Cache    144       0       0           0       0      62          0        0
           cryptop    280       0       0           0       0      30          0        0
  linux_dma_object     24       0       0           0       0     254          0        0
  linux_dma_pctrie    144       0       0           0       0      62          0        0
   IOMMU_MAP_ENTRY    120       0       0           0       0     126          0        0
      ktls_session    192       0       0           0       0      62          0        0
    mbuf_jumbo_16k  16384       0       0           0       0     254          0        0
     mbuf_jumbo_9k   9216       0       0           0       0     254          0        0
      audit_record   1280       0       0           0       0       8          0        0
         domainset     40       0       0           0       0     254          0        0
        MAC labels     40       0       0           0       0     254          0        0
            vnpbuf   2624       0       0           0       0      21          0        0
            mdpbuf   2624       0       0           0       0       1          0        0
           nfspbuf   2624       0       0           0       0       5          0        0
            swwbuf   2624       0       0           0       0       2          0        0
            swrbuf   2624       0       0           0       0       5          0        0
          umtx_shm     88       0       0           0       0     126          0        0
           umtx pi     96       0       0           0       0     126          0        0
rangeset pctrie nodes    144       0       0           0       0      62          0        0
      malloc-65536  65536       0       0           0       0       1          0        0
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
       malloc-8192   8192       0       0           0       0       1          0        0
       malloc-8192   8192       0       0           0       0       1          0        0
       malloc-8192   8192       0       0           0       0       1          0        0
       malloc-2048   2048       0       0           0       0       8          0        0
       malloc-2048   2048       0       0           0       0       8          0        0
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
# {Threaded:false Collide:false Repeat:true RepeatTimes:0 Procs:2 Slowdown:1 Sandbox: Fault:false FaultCall:-1 FaultNth:0 Leak:false NetInjection:false NetDevices:false NetReset:false Cgroups:false BinfmtMisc:false CloseFDs:false KCSAN:false DevlinkPCI:false USB:false VhciInjection:false Wifi:false IEEE802154:false Sysctl:false UseTmpDir:false HandleSegv:false Repro:false Trace:false}
rfork(0x97070)
sigwaitinfo(&(0x7f0000000080)={[0xffffffc0, 0x7, 0xffffffff, 0xf1]}, 0x0)


C reproducer:
// autogenerated by syzkaller (https://github.com/google/syzkaller)

#define _GNU_SOURCE

#include <sys/types.h>

#include <pwd.h>
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

static unsigned long long procid;

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
      if (current_time_ms() - start < 5000) {
        continue;
      }
      kill_and_wait(pid, &status);
      break;
    }
  }
}

void execute_one(void)
{
  syscall(SYS_rfork, 0x97070ul);
  *(uint32_t*)0x20000080 = 0xffffffc0;
  *(uint32_t*)0x20000084 = 7;
  *(uint32_t*)0x20000088 = -1;
  *(uint32_t*)0x2000008c = 0xf1;
  syscall(SYS_sigwaitinfo, 0x20000080ul, 0ul);
}
int main(void)
{
  syscall(SYS_mmap, 0x20000000ul, 0x1000000ul, 7ul, 0x1012ul, -1, 0ul);
  for (procid = 0; procid < 2; procid++) {
    if (fork() == 0) {
      loop();
    }
  }
  sleep(1000000);
  return 0;
}


