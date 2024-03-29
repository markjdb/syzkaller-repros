Syzkaller hit 'panic: MSan: Uninitialized stack memory in strlen():arg1, offset 40/41, addr ADDR, from __sancov_gen_cov_switch_values.3' bug.

login: panic: MSan: Uninitialized stack memory in strlen():arg1, offset 40/41, addr 0xfffffe001a6ce988, from __sancov_gen_cov_switch_values.30+0x340
cpuid = 0
time = 1628413315
KDB: stack backtrace:
db_trace_self_wrapper() at db_trace_self_wrapper+0xde/frame 0xfffffe001a6cd970
vpanic() at vpanic+0x639/frame 0xfffffe001a6cda30
panic() at panic+0x1b3/frame 0xfffffe001a6cdb40
kmsan_report_hook() at kmsan_report_hook+0x2e8/frame 0xfffffe001a6cdcc0
kmsan_strlen() at kmsan_strlen+0x132/frame 0xfffffe001a6cdce0
pfi_skip_if() at pfi_skip_if+0x1d0/frame 0xfffffe001a6cdd50
pfi_clear_flags() at pfi_clear_flags+0x28e/frame 0xfffffe001a6cde10
pfioctl() at pfioctl+0x876c/frame 0xfffffe001a6ce400
devfs_ioctl() at devfs_ioctl+0x4b9/frame 0xfffffe001a6ce4d0
VOP_IOCTL_APV() at VOP_IOCTL_APV+0x13c/frame 0xfffffe001a6ce560
vn_ioctl() at vn_ioctl+0xa30/frame 0xfffffe001a6ce710
devfs_ioctl_f() at devfs_ioctl_f+0x18a/frame 0xfffffe001a6ce7d0
kern_ioctl() at kern_ioctl+0xee3/frame 0xfffffe001a6ce8d0
sys_ioctl() at sys_ioctl+0xa72/frame 0xfffffe001a6cea10
amd64_syscall() at amd64_syscall+0xa4e/frame 0xfffffe001a6cebf0
fast_syscall_common() at fast_syscall_common+0xf8/frame 0xfffffe001a6cebf0
--- syscall (0, FreeBSD ELF64, nosys), rip = 0x23365a, rsp = 0x7fffffffea28, rbp = 0x7fffffffea80 ---
KDB: enter: panic
[ thread pid 822 tid 100085 ]
Stopped at      kdb_enter+0x1c7:        movq    $0x87024090,%rdi
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
rax         0xffffffff863458bc
rcx                          0
rdx         0xffffffff8702c000  msan_dummy_orig
rbx                          0
rsp         0xfffffe001a6cd910
rbp         0xfffffe001a6cd970
rsi                        0x1
rdi         0xffffffff87024090  kdb_why
r8                           0
r9                           0
r10                          0
r11                          0
r12                          0
r13         0xffffffff87028e01  msan_thread0+0x3e01
r14         0xffffffff87028ec8  dummy_tls
r15         0xffffffff863458bc
rip         0xffffffff83fa1e77  kdb_enter+0x1c7
rflags                    0x46
kdb_enter+0x1c7:        movq    $0x87024090,%rdi
db> show proc
Process 822 (syz-executor3829847) at 0xfffffe0039a16000:
 state: NORMAL
 uid: 0  gids: 0, 0, 5
 parent: pid 820 at 0xfffffe0039a16538
 ABI: FreeBSD ELF64
 flag: 0x10004000  flag2: 0
 arguments: /root/syz-executor382984776
 reaper: 0xfffffe0011387538 reapsubtree: 1
 sigparent: 20
 vmspace: 0xfffffe003b41e3e0
   (map 0xfffffe003b41e3e0)
   (map.pmap 0xfffffe003b41e4a0)
   (pmap 0xfffffe003b41e500)
 threads: 1
100085                   Run     CPU 0                       syz-executor3829847
db> ps
  pid  ppid  pgrp   uid  state   wmesg   wchan               cmd
  822   820   820     0  R       CPU 0                       syz-executor3829847
  820   818   820     0  Ss      pause   0xfffffe0039a165e8  csh
  818   735   818     0  Ss      select  0xfffffe003ae49440  sshd
  797     1   797     0  Ss+     ttyin   0xfffffe001aaf8cb0  getty
  793     1   793     0  Ss      select  0xfffffe001aad5d40  logger
  787     1    22     0  S+      piperd  0xfffffe003ae742e8  logger
  786   785    22     0  S+      nanslp  0xffffffff86ff77e1  sleep
  785     1    22     0  S+      wait    0xfffffe003ae79a70  sh
  781     1   781    25  Ss      pause   0xfffffe003a90eb20  sendmail
  778     1   778     0  Ss      select  0xfffffe0039c01040  sendmail
  739     1   739     0  Ss      nanslp  0xffffffff86ff77e1  cron
  735     1   735     0  Ss      select  0xfffffe003ae49f40  sshd
  646     1   646     0  Ss      select  0xfffffe0039c01e40  syslogd
  449     1   449     0  Ss      select  0xfffffe001aad5dc0  devd
  352     1   352    65  Ss      select  0xfffffe003ae49e40  dhclient
  270     1   270     0  Ss      select  0xfffffe0039c01c40  dhclient
  267     1   267     0  Ss      select  0xfffffe001aad5e40  dhclient
   95     0     0     0  DL      pftm    0xffffffff87731b30  [pf purge]
   21     0     0     0  DL      vlruwt  0xfffffe001f86e000  [vnlru]
   20     0     0     0  DL      syncer  0xffffffff870f1140  [syncer]
   19     0     0     0  DL      (threaded)                  [bufdaemon]
100071                   D       qsleep  0xffffffff870f01c0  [bufdaemon]
100074                   D       -       0xffffffff86a0af80  [bufspacedaemon-0]
100086                   D       sdflush 0xfffffe0039a4cce8  [/ worker]
   18     0     0     0  DL      psleep  0xffffffff87115ec8  [vmdaemon]
   17     0     0     0  DL      (threaded)                  [pagedaemon]
100069                   D       psleep  0xffffffff8710a338  [dom0]
100075                   D       launds  0xffffffff8710a344  [laundry: dom0]
100076                   D       umarcl  0xffffffff8537e100  [uma]
   16     0     0     0  DL      -       0xffffffff86e2bb58  [rand_harvestq]
   15     0     0     0  DL      -       0xffffffff870ed75c  [soaiod4]
    9     0     0     0  DL      -       0xffffffff870ed75c  [soaiod3]
    8     0     0     0  DL      -       0xffffffff870ed75c  [soaiod2]
    7     0     0     0  DL      -       0xffffffff870ed75c  [soaiod1]
    6     0     0     0  DL      (threaded)                  [cam]
100046                   D       -       0xffffffff86d03240  [doneq0]
100047                   D       -       0xffffffff86d031c0  [async]
100068                   D       -       0xffffffff86d03090  [scanner]
   14     0     0     0  DL      seqstat 0xfffffe001a8a4888  [sequencer 00]
    5     0     0     0  DL      crypto_ 0xfffffe001123eb80  [crypto returns 1]
    4     0     0     0  DL      crypto_ 0xfffffe001123eb30  [crypto returns 0]
    3     0     0     0  DL      crypto_ 0xffffffff87107860  [crypto]
   13     0     0     0  DL      (threaded)                  [geom]
100037                   D       -       0xffffffff86fd6ff0  [g_event]
100038                   D       -       0xffffffff86fd6ff8  [g_up]
100039                   D       -       0xffffffff86fd7000  [g_down]
    2     0     0     0  DL      (threaded)                  [KTLS]
100029                   D       -       0xfffffe001a49ba00  [thr_0]
100030                   D       -       0xfffffe001a49ba80  [thr_1]
100031                   D       -       0xffffffff870ede48  [alloc_0]
   12     0     0     0  WL      (threaded)                  [intr]
100011                   I                                   [swi5: fast taskq]
100019                   I                                   [swi6: task queue]
100020                   I                                   [swi6: Giant taskq]
100032                   I                                   [swi3: vm]
100033                   I                                   [swi1: netisr 0]
100034                   I                                   [swi4: clock (0)]
100035                   I                                   [swi4: clock (1)]
100048                   I                                   [irq40: virtio_pci0]
100049                   I                                   [irq41: virtio_pci0]
100050                   I                                   [irq42: virtio_pci0]
100053                   I                                   [irq43: virtio_pci1]
100054                   I                                   [irq44: virtio_pci1]
100055                   I                                   [irq1: atkbd0]
100056                   I                                   [irq12: psm0]
100057                   I                                   [swi0: uart uart++]
100089                   I                                   [swi1: pf send]
   11     0     0     0  RL      (threaded)                  [idle]
100003                   CanRun                              [idle: cpu0]
100004                   Run     CPU 1                       [idle: cpu1]
    1     0     1     0  SLs     wait    0xfffffe0011387538  [init]
   10     0     0     0  DL      audit_w 0xffffffff87107d70  [audit]
    0     0     0     0  DLs     (threaded)                  [kernel]
100000                   D       swapin  0xffffffff86fd7590  [swapper]
100005                   D       -       0xfffffe00113f5e00  [softirq_0]
100006                   D       -       0xfffffe00113f5d00  [softirq_1]
100007                   D       -       0xfffffe00113f5c00  [if_io_tqg_0]
100008                   D       -       0xfffffe00113f5b00  [if_io_tqg_1]
100009                   D       -       0xfffffe00113f5a00  [if_config_tqg_0]
100010                   D       -       0xfffffe00113f5900  [thread taskq]
100012                   D       -       0xfffffe00113f5700  [in6m_free taskq]
100013                   D       -       0xfffffe00113f5600  [pci_hp taskq]
100014                   D       -       0xfffffe00113f5500  [aiod_kick taskq]
100015                   D       -       0xfffffe00113f5400  [kqueue_ctx taskq]
100016                   D       -       0xfffffe00113f5300  [inm_free taskq]
100017                   D       -       0xfffffe00113f5200  [deferred_unmount ta]
100018                   D       -       0xfffffe00113f5100  [linuxkpi_irq_wq]
100021                   D       -       0xfffffe001a47dd00  [linuxkpi_short_wq_0]
100022                   D       -       0xfffffe001a47dd00  [linuxkpi_short_wq_1]
100023                   D       -       0xfffffe001a47dd00  [linuxkpi_short_wq_2]
100024                   D       -       0xfffffe001a47dd00  [linuxkpi_short_wq_3]
100025                   D       -       0xfffffe001a47dc00  [linuxkpi_long_wq_0]
100026                   D       -       0xfffffe001a47dc00  [linuxkpi_long_wq_1]
100027                   D       -       0xfffffe001a47dc00  [linuxkpi_long_wq_2]
100028                   D       -       0xfffffe001a47dc00  [linuxkpi_long_wq_3]
100036                   D       -       0xfffffe001a47db00  [firmware taskq]
100040                   D       -       0xfffffe001a47d000  [crypto_0]
100041                   D       -       0xfffffe001a47d000  [crypto_1]
100051                   D       -       0xfffffe001a47d700  [vtnet0 rxq 0]
100052                   D       -       0xfffffe001a47d800  [vtnet0 txq 0]
100060                   D       -       0xffffffff866ee0a1  [deadlkres]
100063                   D       -       0xfffffe001aa73400  [acpi_task_0]
100064                   D       -       0xfffffe001aa73400  [acpi_task_1]
100065                   D       -       0xfffffe001aa73400  [acpi_task_2]
100067                   D       -       0xfffffe001a842700  [CAM taskq]
db> show all locks
Process 822 (syz-executor3829847) thread 0xfffffe001f999000 (100085)
exclusive rm pf rulesets (pf rulesets) r = 0 (0xffffffff878ce218) locked @ /root/freebsd/sys/netpfil/pf/pf_ioctl.c:4731
db> show malloc
              Type        InUse        MemUse     Requests
           pf_hash            5        11524K            5
         sysctloid        30416         1795K        30458
             kmsan          111         1776K          111
            linker          227         1492K          240
              kobj          323         1292K          483
            newblk          609         1176K          668
            devbuf         1360         1150K         1377
          vfscache            3         1025K            3
               pcb           16          777K           32
          inodedep           62          535K          102
         ufs_quota            1          512K            1
          vfs_hash            1          512K            1
           callout            2          512K            2
              intr            4          472K            4
           subproc           95          181K          878
         vnet_data            1          168K            1
           tidhash            3          158K            3
           pagedep           22          134K           33
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
            acpica          420           39K        62949
               LRO            2           33K            2
              proc            3           33K            3
         hostcache            1           32K            1
               shm            1           32K            1
           kdtrace          152           31K          935
              umtx          242           31K          242
               msg            4           30K            4
            DEVFS3          110           28K          126
        gtaskqueue           18           26K           18
            kbdmux            5           22K            5
        DEVFS_RULE           59           21K           59
           ithread          104           19K          104
               BPF           10           18K           10
              temp           15           17K         1520
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
     audit_evclass          237            8K          295
            diradd           46            6K          107
         taskqueue           54            6K           54
            sglist            3            6K            3
              cred           20            5K          290
       ufs_dirhash           24            5K           24
           uidinfo            4            5K            9
             ifnet            3            5K            3
               UMA          250            5K          250
           io_apic            1            4K            1
               tty            4            4K            4
             evdev            4            4K            4
          filedesc            1            4K            1
             hhook           13            4K           13
          pf_ifnet            5            3K            6
           lltable           10            3K           10
            plimit           11            3K          228
           acpisem           21            3K           21
            kqueue           40            3K          823
           pwddesc           40            3K          823
             lockf           21            3K           32
             selfd           33            3K        15331
        local_apic            1            2K            1
       fpukern_ctx            2            2K            2
         ipsec-saq            2            2K            2
           CAM DEV            1            2K            2
           session           15            2K           31
               msi           13            2K           13
          pci_link           16            2K           16
            Unitno           25            2K           45
         proc-args           34            2K          504
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
            ip6ndp            3            1K            3
    chacha20random            1            1K            1
        CAM periph            2            1K           14
            DEVFSP            5            1K           22
               osd            3            1K            9
      NFSD lckfile            1            1K            1
     NFSD V4client            1            1K            1
             DEVFS            9            1K           10
               MCA            2            1K            2
            dirrem            1            1K           46
               mld            2            1K            2
              igmp            2            1K            2
            vnodes            1            1K            1
              ktls            1            1K            1
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
            statfs            0            0K           13
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
               iov            0            0K         7785
          ioctlops            0            0K           76
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
         NFSCL lck            0            0K            0
      NFSCL lckown            0            0K            0
db> show uma
              Zone   Size    Used    Free    Requests  Sleeps  Bucket  Total Mem    XFree
   mbuf_jumbo_page   4096    1088    1034       14647       0     254    8691712        0
      malloc-16384  16384     112       0         112       0       1    1835008        0
       malloc-4096   4096     325       1         486       0       2    1335296        0
          BUF TRIE    144     170    8986         449       0      62    1318464        0
        malloc-128    128   10050      56       10143       0     126    1293568        0
              pbuf   2624       0     269           0       0       2     705856        0
              mbuf    256    1347    1053       22685       0     254     614400        0
        malloc-512    512    1028      12        1219       0      30     532480        0
      malloc-65536  65536       6       1         106       0       1     458752        0
         vmem btag     56    7374      89        7374       0     254     417928        0
        RADIX NODE    144    2379     443       28557       0      62     406368        0
            lkpimm    168       1    2327           1       0      62     391104        0
          lkpicurr    168       2    2326           2       0      62     391104        0
       UMA Slabs 0    112    3114      15        3114       0     126     350448        0
       malloc-2048   2048     130       4         175       0       8     274432        0
         VM OBJECT    264     917      58       12093       0      30     257400        0
             VNODE    448     524      43         554       0      30     254016        0
         malloc-64     64    3594     123        4425       0     254     237888        0
        256 Bucket   2048      97      17        2946       0       8     233472        0
            THREAD   1808     111      10         111       0       8     218768        0
        malloc-256    256     818       7        1615       0      62     211200        0
       malloc-4096   4096      47       3        1139       0       2     204800        0
         malloc-16     16   12648     102       12698       0     254     204000        0
            DEVCTL   1024       0     192          93       0       0     196608        0
         UMA Zones    768     222       2         222       0      16     172032        0
         malloc-32     32    4456      80        4555       0     254     145152        0
       FFS2 dinode    256     502      23         529       0      62     134400        0
      malloc-65536  65536       2       0           2       0       1     131072        0
      malloc-65536  65536       2       0           2       0       1     131072        0
       S VFS Cache    104     997     134        1077       0     126     117624        0
          ksiginfo    112      39    1005          71       0     126     116928        0
       malloc-1024   1024     102      10        1147       0      16     114688        0
         FFS inode    192     502      44         529       0      62     104832        0
         MAP ENTRY     96     792     300       37956       0     126     104832        0
      malloc-32768  32768       3       0           3       0       1      98304        0
      mbuf_cluster   2048      45       1          45       0     254      94208        0
        malloc-128    128     675      38        1786       0     126      91264        0
       malloc-8192   8192       8       3          82       0       1      90112        0
          UMA Kegs    384     207       6         207       0      30      81792        0
              PROC   1336      39      15         822       0       8      72144        0
        malloc-128    128     495      63        3035       0     126      71424        0
      malloc-65536  65536       1       0           1       0       1      65536        0
      malloc-65536  65536       1       0           1       0       1      65536        0
      malloc-32768  32768       1       1           2       0       1      65536        0
      malloc-32768  32768       2       0           2       0       1      65536        0
        128 Bucket   1024      43      20         689       0      16      64512        0
           VMSPACE   2544      18       6         802       0       4      61056        0
         filedesc0   1072      40      16         823       0       8      60032        0
        malloc-384    384     136       4         316       0      30      53760        0
        malloc-256    256     200      10         519       0      62      53760        0
      malloc-16384  16384       3       0           3       0       1      49152        0
         malloc-64     64     634      59         915       0     254      44352        0
         32 Bucket    256      40     125         496       0      62      42240        0
        malloc-128    128     260      50       28673       0     126      39680        0
           DIRHASH   1024      32       4          32       0      16      36864        0
             NAMEI   1024       0      36       12405       0      16      36864        0
        malloc-384    384      65      25         113       0      30      34560        0
      malloc-32768  32768       0       1          53       0       1      32768        0
      malloc-16384  16384       1       1          65       0       1      32768        0
       malloc-8192   8192       4       0           4       0       1      32768        0
           pcpu-64     64     455      57         455       0     254      32768        0
            socket    944      20      12        1013       0     254      30208        0
            pcpu-8      8    3292     292        3315       0     254      28672        0
         64 Bucket    512      49       7         711       0      30      28672        0
        malloc-128    128     160      57         217       0     126      27776        0
             g_bio    384       0      70        4769       0      30      26880        0
            clpbuf   2624       0      10          29       0       5      26240        0
       malloc-4096   4096       6       0           6       0       2      24576        0
         malloc-64     64     198     117        1717       0     254      20160        0
         TURNSTILE    136     122      25         122       0      62      19992        0
       Mountpoints   2752       2       5           2       0       4      19264        0
      malloc-16384  16384       1       0           1       0       1      16384        0
      malloc-16384  16384       1       0           1       0       1      16384        0
       malloc-8192   8192       2       0           2       0       1      16384        0
       malloc-2048   2048       3       5           9       0       8      16384        0
       malloc-2048   2048       3       5         216       0       8      16384        0
       malloc-1024   1024      14       2          14       0      16      16384        0
        malloc-128    128      72      52          80       0     126      15872        0
             tcpcb   1080       4      10          10       0     254      15120        0
              pipe    744       7      13         297       0      16      14880        0
        SLEEPQUEUE     88     122      38         122       0     126      14080        0
       malloc-4096   4096       1       2           4       0       2      12288        0
       malloc-2048   2048       4       2           4       0       8      12288        0
       malloc-2048   2048       4       2           5       0       8      12288        0
       malloc-1024   1024       7       5          14       0      16      12288        0
         malloc-64     64      49     140        8564       0     254      12096        0
         malloc-64     64      95      94       16234       0     254      12096        0
         malloc-32     32     245     133         353       0     254      12096        0
             Files     80      81      69        7008       0     126      12000        0
         malloc-16     16     475     275        1326       0     254      12000        0
         udp_inpcb    496       2      22          60       0     254      11904        0
       mbuf_packet    256       0      45         101       0     254      11520        0
        malloc-256    256      19      26         110       0      62      11520        0
        malloc-256    256      22      23         298       0      62      11520        0
        malloc-256    256      25      20         172       0      62      11520        0
       malloc-8192   8192       1       0           1       0       1       8192        0
       malloc-8192   8192       1       0           1       0       1       8192        0
       malloc-8192   8192       1       0           1       0       1       8192        0
       malloc-8192   8192       0       1           2       0       1       8192        0
       malloc-4096   4096       0       2          13       0       2       8192        0
       malloc-4096   4096       0       2           2       0       2       8192        0
       malloc-4096   4096       2       0           2       0       2       8192        0
       malloc-1024   1024       2       6           6       0      16       8192        0
       malloc-1024   1024       6       2           6       0      16       8192        0
       malloc-1024   1024       7       1           7       0      16       8192        0
       malloc-1024   1024       3       5           3       0      16       8192        0
        malloc-512    512       8       8           9       0      30       8192        0
           rtentry    176      11      35          14       0      62       8096        0
              PGRP     88      15      77          31       0     126       8096        0
          rl_entry     40      33     169          35       0     254       8080        0
             udpcb     32       2     250          60       0     254       8064        0
               PWD     32      11     241          95       0     254       8064        0
         malloc-64     64     116      10         144       0     254       8064        0
         malloc-64     64       4     122          39       0     254       8064        0
         malloc-64     64       3     123           7       0     254       8064        0
         malloc-32     32      29     223         174       0     254       8064        0
         malloc-32     32     156      96         925       0     254       8064        0
         malloc-32     32      44     208          74       0     254       8064        0
         malloc-32     32      17     235        4956       0     254       8064        0
         malloc-32     32      16     236         107       0     254       8064        0
         16 Bucket    144      29      27         260       0      62       8064        0
          4 Bucket     48       5     163          56       0     254       8064        0
          2 Bucket     32      45     207         578       0     254       8064        0
            ttyinq    160      15      35          45       0      62       8000        0
         malloc-16     16       1     499         174       0     254       8000        0
         malloc-16     16      23     477          80       0     254       8000        0
         malloc-16     16      37     463       27417       0     254       8000        0
         malloc-16     16       2     498         126       0     254       8000        0
          8 Bucket     80      28      72         322       0     126       8000        0
         tcp_inpcb    496       4      12          10       0     254       7936        0
        malloc-128    128      14      48         217       0     126       7936        0
        malloc-128    128       5      57          13       0     126       7936        0
              kenv    258       2      28         704       0      30       7740        0
     routing nhops    256       8      22          14       0      62       7680        0
             unpcb    256      12      18         931       0     254       7680        0
           ttyoutq    256       8      22          24       0      62       7680        0
        malloc-384    384       0      20          14       0      30       7680        0
        malloc-384    384       6      14           7       0      30       7680        0
        malloc-384    384       0      20           2       0      30       7680        0
        malloc-256    256       0      30         312       0      62       7680        0
        malloc-256    256      10      20          14       0      62       7680        0
        malloc-256    256       3      27           3       0      62       7680        0
     FPU_save_area    832       1       8           1       0      16       7488        0
            cpuset    104       8      54           8       0     126       6448        0
 epoch_record pcpu    256       4      12           4       0      62       4096        0
       malloc-4096   4096       1       0           1       0       2       4096        0
       malloc-2048   2048       2       0           2       0       8       4096        0
        malloc-512    512       1       7           1       0      30       4096        0
        malloc-512    512       1       7           1       0      30       4096        0
        malloc-512    512       1       7           1       0      30       4096        0
        malloc-512    512       2       6           2       0      30       4096        0
           pcpu-16     16       7     249           7       0     254       4096        0
         hostcache     64       1      62           1       0     254       4032        0
          syncache    168       0      24           5       0     254       4032        0
         malloc-32     32       0     126           2       0     254       4032        0
      vtnet_tx_hdr     24       1     166        6970       0     254       4008        0
         malloc-16     16       2     248           2       0     254       4000        0
         malloc-16     16       2     248           3       0     254       4000        0
             ripcb    496       1       7           1       0     254       3968        0
       UMA Slabs 1    176       6      16           6       0      62       3872        0
       L VFS Cache    320       0      12           1       0      30       3840        0
        malloc-384    384       1       9           1       0      30       3840        0
        malloc-384    384       7       3           7       0      30       3840        0
        malloc-384    384       1       9           1       0      30       3840        0
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
             KNOTE    160       0       0           0       0      62          0        0
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
      malloc-32768  32768       0       0           0       0       1          0        0
      malloc-32768  32768       0       0           0       0       1          0        0
      malloc-32768  32768       0       0           0       0       1          0        0
      malloc-32768  32768       0       0           0       0       1          0        0
      malloc-16384  16384       0       0           0       0       1          0        0
      malloc-16384  16384       0       0           0       0       1          0        0
      malloc-16384  16384       0       0           0       0       1          0        0
       malloc-8192   8192       0       0           0       0       1          0        0
       malloc-2048   2048       0       0           0       0       8          0        0
       malloc-2048   2048       0       0           0       0       8          0        0
       malloc-1024   1024       0       0           0       0      16          0        0
        malloc-512    512       0       0           0       0      30          0        0
        malloc-512    512       0       0           0       0      30          0        0
           pcpu-32     32       0       0           0       0     254          0        0
            pcpu-4      4       0       0           0       0     254          0        0
            fakepg    104       0       0           0       0     126          0        0
          UMA Hash    256       0       0           0       0      62          0        0


Syzkaller reproducer:
# {Threaded:false Collide:false Repeat:false RepeatTimes:0 Procs:1 Slowdown:1 Sandbox: Fault:false FaultCall:-1 FaultNth:0 Leak:false NetInjection:false NetDevices:false NetReset:false Cgroups:false BinfmtMisc:false CloseFDs:false KCSAN:false DevlinkPCI:false USB:false VhciInjection:false Wifi:false IEEE802154:false Sysctl:false UseTmpDir:false HandleSegv:true Repro:false Trace:false}
ioctl$DIOCGETRULE(0xffffffffffffffff, 0xcbe04407, &(0x7f0000000100)="6cd82b83437b55cf1864ffaf473e3eb23e4b06a9c3e04aff0952d4cee1b398026567c065ffa0bc68d3db314d3126aed3e32c27e7d2c7a89109c133640014923f2c3314d79dc4692225c92ada0b58cf77a3cf77fc2fb405e25e5e014e91e2cacf2d1e38cdf7f5e10b3909871bf4c5adc0083cc2e8b348f9bbf597736c6e4379ca522d5025a54d7d")
openat$ptmx(0xffffffffffffff9c, &(0x7f0000000000), 0x0, 0x0)
mprotect(&(0x7f0000000000/0xc00000)=nil, 0xc00000, 0x5)
r0 = openat$ptmx(0xffffffffffffff9c, &(0x7f0000000000), 0x1, 0x0)
ioctl$DIOCCLRIFFLAG(r0, 0xc028445a, &(0x7f0000000100)={0x10, 0x0})


C reproducer:
// autogenerated by syzkaller (https://github.com/google/syzkaller)

#define _GNU_SOURCE

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
#include <unistd.h>

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

uint64_t r[1] = {0xffffffffffffffff};

int main(void)
{
  syscall(SYS_mmap, 0x20000000ul, 0x1000000ul, 7ul, 0x1012ul, -1, 0ul);
  install_segv_handler();
  intptr_t res = 0;
  NONFAILING(memcpy(
      (void*)0x20000100,
      "\x6c\xd8\x2b\x83\x43\x7b\x55\xcf\x18\x64\xff\xaf\x47\x3e\x3e\xb2\x3e\x4b"
      "\x06\xa9\xc3\xe0\x4a\xff\x09\x52\xd4\xce\xe1\xb3\x98\x02\x65\x67\xc0\x65"
      "\xff\xa0\xbc\x68\xd3\xdb\x31\x4d\x31\x26\xae\xd3\xe3\x2c\x27\xe7\xd2\xc7"
      "\xa8\x91\x09\xc1\x33\x64\x00\x14\x92\x3f\x2c\x33\x14\xd7\x9d\xc4\x69\x22"
      "\x25\xc9\x2a\xda\x0b\x58\xcf\x77\xa3\xcf\x77\xfc\x2f\xb4\x05\xe2\x5e\x5e"
      "\x01\x4e\x91\xe2\xca\xcf\x2d\x1e\x38\xcd\xf7\xf5\xe1\x0b\x39\x09\x87\x1b"
      "\xf4\xc5\xad\xc0\x08\x3c\xc2\xe8\xb3\x48\xf9\xbb\xf5\x97\x73\x6c\x6e\x43"
      "\x79\xca\x52\x2d\x50\x25\xa5\x4d\x7d",
      135));
  syscall(SYS_ioctl, -1, 0xcbe04407ul, 0x20000100ul);
  NONFAILING(memcpy((void*)0x20000000, "/dev/pf\000", 8));
  syscall(SYS_openat, 0xffffffffffffff9cul, 0x20000000ul, 0ul, 0ul);
  syscall(SYS_mprotect, 0x20000000ul, 0xc00000ul, 5ul);
  NONFAILING(memcpy((void*)0x20000000, "/dev/pf\000", 8));
  res = syscall(SYS_openat, 0xffffffffffffff9cul, 0x20000000ul, 1ul, 0ul);
  if (res != -1)
    r[0] = res;
  NONFAILING(*(uint8_t*)0x20000100 = 0x10);
  NONFAILING(*(uint64_t*)0x20000108 = 0);
  NONFAILING(*(uint32_t*)0x20000110 = 0);
  NONFAILING(*(uint32_t*)0x20000114 = 0);
  NONFAILING(*(uint32_t*)0x20000118 = 0);
  syscall(SYS_ioctl, r[0], 0xc028445aul, 0x20000100ul);
  return 0;
}


