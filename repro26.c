Syzkaller hit 'panic: KMSAN: Uninitialized malloc memory in copyout():arg1, offset 96/104, addr ADDR, from ip6_ctloutput+0x65f6' bug.

login: panic: KMSAN: Uninitialized malloc memory in copyout():arg1, offset 96/104, addr 0xfffffe003af2ad60, from ip6_ctloutput+0x65f6
cpuid = 0
time = 1627284921
KDB: stack backtrace:
db_trace_self_wrapper() at db_trace_self_wrapper+0xde/frame 0xfffffe001a6d79f0
vpanic() at vpanic+0x639/frame 0xfffffe001a6d7ab0
panic() at panic+0x1b3/frame 0xfffffe001a6d7bc0
kmsan_report_hook() at kmsan_report_hook+0x2f6/frame 0xfffffe001a6d7d40
kmsan_copyout() at kmsan_copyout+0x1f1/frame 0xfffffe001a6d7d70
sooptcopyout() at sooptcopyout+0x206/frame 0xfffffe001a6d7e10
ip6_ctloutput() at ip6_ctloutput+0x85a4/frame 0xfffffe001a6d8790
sogetopt() at sogetopt+0x18a7/frame 0xfffffe001a6d88a0
kern_getsockopt() at kern_getsockopt+0x561/frame 0xfffffe001a6d8980
sys_getsockopt() at sys_getsockopt+0x293/frame 0xfffffe001a6d8a10
amd64_syscall() at amd64_syscall+0xa4e/frame 0xfffffe001a6d8bf0
fast_syscall_common() at fast_syscall_common+0x104/frame 0xfffffe001a6d8bf0
--- syscall (0, FreeBSD ELF64, nosys), rip = 0x2332ea, rsp = 0x7fffffffea68, rbp = 0x7fffffffea80 ---
KDB: enter: panic
[ thread pid 824 tid 100102 ]
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
rax         0xffffffff8632f0bc
rcx                          0
rdx         0xffffffff8702b000  msan_dummy_orig
rbx                          0
rsp         0xfffffe001a6d7990
rbp         0xfffffe001a6d79f0
rsi                        0x1
rdi         0xffffffff87024010  kdb_why
r8                           0
r9                           0
r10                          0
r11                          0
r12                          0
r13         0xffffffff87028e01  msan_thread0+0x3e01
r14         0xffffffff87028ec8  dummy_tls
r15         0xffffffff8632f0bc
rip         0xffffffff83f97477  kdb_enter+0x1c7
rflags                    0x46
kdb_enter+0x1c7:        movq    $0x87024010,%rdi
db> show proc
Process 824 (syz-executor5097734) at 0xfffffe003b3ea000:
 state: NORMAL
 uid: 0  gids: 0, 0, 5
 parent: pid 822 at 0xfffffe003b3ea538
 ABI: FreeBSD ELF64
 flag: 0x10004000  flag2: 0
 arguments: /root/syz-executor509773476
 reaper: 0xfffffe0011383538 reapsubtree: 1
 sigparent: 20
 vmspace: 0xfffffe003ae083e0
   (map 0xfffffe003ae083e0)
   (map.pmap 0xfffffe003ae084a0)
   (pmap 0xfffffe003ae08500)
 threads: 1
100102                   Run     CPU 0                       syz-executor5097734
db> ps
  pid  ppid  pgrp   uid  state   wmesg   wchan               cmd
  824   822   822     0  R       CPU 0                       syz-executor5097734
  822   820   822     0  Ss      pause   0xfffffe003b3ea5e8  csh
  820   781   820     0  Ss      select  0xfffffe001137d040  sshd
  797     1   797     0  Ss+     ttyin   0xfffffe001aadacb0  getty
  794     1   794     0  Ss      select  0xfffffe001a96b3c0  logger
  788     1    22     0  S+      piperd  0xfffffe0039c37000  logger
  787   786    22     0  S+      nanslp  0xffffffff86ff77a1  sleep
  786     1    22     0  S+      wait    0xfffffe001f9f3538  sh
  781     1   781     0  Ss      select  0xfffffe001a96b4c0  sshd
  758     1   758    25  Ss      pause   0xfffffe003ae455e8  sendmail
  755     1   755     0  Ss      select  0xfffffe001a96b540  sendmail
  726     1   726     0  Ss      nanslp  0xffffffff86ff77a0  cron
  646     1   646     0  Ss      select  0xfffffe001a96b940  syslogd
  448     1   448     0  Ss      select  0xfffffe001a96bb40  devd
  352     1   352    65  Ss      select  0xfffffe001a96b9c0  dhclient
  270     1   270     0  Ss      select  0xfffffe001137d6c0  dhclient
  267     1   267     0  Ss      select  0xfffffe001137d7c0  dhclient
  102     0     0     0  DL      pftm    0xffffffff87731b30  [pf purge]
   21     0     0     0  DL      syncer  0xffffffff870ee800  [syncer]
   20     0     0     0  DL      vlruwt  0xfffffe001f832000  [vnlru]
   19     0     0     0  DL      (threaded)                  [bufdaemon]
100070                   D       qsleep  0xffffffff870ed8a0  [bufdaemon]
100073                   D       -       0xffffffff86a0af80  [bufspacedaemon-0]
100085                   D       sdflush 0xfffffe0010b194e8  [/ worker]
   18     0     0     0  DL      psleep  0xffffffff87113588  [vmdaemon]
   17     0     0     0  DL      (threaded)                  [pagedaemon]
100068                   D       psleep  0xffffffff871079f8  [dom0]
100074                   D       launds  0xffffffff87107a04  [laundry: dom0]
100075                   D       umarcl  0xffffffff85369b10  [uma]
   16     0     0     0  DL      -       0xffffffff86e2bb58  [rand_harvestq]
   15     0     0     0  DL      -       0xffffffff870eaf5c  [soaiod4]
    9     0     0     0  DL      -       0xffffffff870eaf5c  [soaiod3]
    8     0     0     0  DL      -       0xffffffff870eaf5c  [soaiod2]
    7     0     0     0  DL      -       0xffffffff870eaf5c  [soaiod1]
    6     0     0     0  DL      (threaded)                  [cam]
100045                   D       -       0xffffffff86d03240  [doneq0]
100046                   D       -       0xffffffff86d031c0  [async]
100067                   D       -       0xffffffff86d03090  [scanner]
   14     0     0     0  DL      seqstat 0xfffffe001a58b488  [sequencer 00]
    5     0     0     0  DL      crypto_ 0xfffffe001a4c3c80  [crypto returns 1]
    4     0     0     0  DL      crypto_ 0xfffffe001a4c3c30  [crypto returns 0]
    3     0     0     0  DL      crypto_ 0xffffffff87104f20  [crypto]
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
100087                   I                                   [swi1: pf send]
   11     0     0     0  RL      (threaded)                  [idle]
100003                   CanRun                              [idle: cpu0]
100004                   Run     CPU 1                       [idle: cpu1]
    1     0     1     0  SLs     wait    0xfffffe0011383538  [init]
   10     0     0     0  DL      audit_w 0xffffffff87105430  [audit]
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
100059                   D       -       0xffffffff866d75f1  [deadlkres]
100063                   D       -       0xfffffe001a93b500  [acpi_task_0]
100064                   D       -       0xfffffe001a93b500  [acpi_task_1]
100065                   D       -       0xfffffe001a93b500  [acpi_task_2]
100066                   D       -       0xfffffe001a4d9700  [CAM taskq]
db> show all locks
db> show malloc
              Type        InUse        MemUse     Requests
           pf_hash            5        11524K            5
         sysctloid        30404         1794K        30446
             kmsan          102         1632K          102
            linker          227         1500K          240
              kobj          323         1292K          483
            newblk          633         1182K          668
            devbuf         1360         1150K         1377
          vfscache            3         1025K            3
               pcb           16          777K           32
          inodedep           62          535K           99
         ufs_quota            1          512K            1
          vfs_hash            1          512K            1
           callout            2          512K            2
              intr            4          472K            4
           subproc           89          179K          874
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
            acpica          420           39K        61577
               LRO            2           33K            2
              proc            3           33K            3
         hostcache            1           32K            1
               shm            1           32K            1
               msg            4           30K            4
           kdtrace          143           29K          928
            DEVFS3          110           28K          126
              umtx          220           28K          220
        gtaskqueue           18           26K           18
            kbdmux            5           22K            5
        DEVFS_RULE           59           21K           59
           ithread          104           19K          104
               BPF           10           18K           10
              temp           16           17K         1527
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
            diradd           46            6K          107
         taskqueue           54            6K           54
            sglist            3            6K            3
              cred           20            5K          300
       ufs_dirhash           24            5K           24
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
            plimit           11            3K          243
           acpisem           21            3K           21
            kqueue           40            3K          825
           pwddesc           40            3K          825
             lockf           22            3K           36
             selfd           33            3K        15411
        local_apic            1            2K            1
         ipsec-saq            2            2K            2
           CAM DEV            1            2K            2
           session           15            2K           32
               msi           13            2K           13
          pci_link           16            2K           16
            Unitno           25            2K           45
         proc-args           34            2K          505
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
       vnodemarker            2            1K            8
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
            ip6opt            2            1K            2
    chacha20random            1            1K            1
        CAM periph            2            1K           14
            DEVFSP            5            1K           22
               osd            3            1K            9
      NFSD lckfile            1            1K            1
     NFSD V4client            1            1K            1
             DEVFS            9            1K           10
               MCA            2            1K            2
            dirrem            1            1K           46
       inpcbpolicy            8            1K           72
               mld            2            1K            2
              igmp            2            1K            2
            vnodes            1            1K            1
              ktls            1            1K            1
          procdesc            2            1K           20
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
            soname            4            1K         2570
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
          savedino            0            0K           13
          sentinel            0            0K            0
            jfsync            0            0K            0
            jtrunc            0            0K            0
             sbdep            0            0K            2
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
               iov            0            0K         7856
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
              sbuf            0            0K          356
           md_disk            0            0K            0
          firmware            0            0K            0
        compressor            0            0K            0
           malodev            0            0K            0
              SWAP            0            0K            0
               LED            0            0K            0
         sysctltmp            0            0K          532
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
   mbuf_jumbo_page   4096    1088    1047       14455       0     254    8744960        0
      malloc-16384  16384     105       0         105       0       1    1720320        0
        malloc-128    128   10763      25       10826       0     126    1380864        0
       malloc-4096   4096     323       1         483       0       2    1327104        0
          BUF TRIE    144     176    8980         443       0      62    1318464        0
              pbuf   2624       0     264           0       0       2     692736        0
              mbuf    256    1347    1173       22344       0     254     645120        0
        malloc-512    512    1026      14        1034       0      30     532480        0
      malloc-65536  65536       6       1          37       0       1     458752        0
         vmem btag     56    7352     111        7352       0     254     417928        0
        RADIX NODE    144    2376     390       28570       0      62     398304        0
          lkpicurr    160       2    2348           2       0      62     376000        0
            lkpimm    160       1    2324           1       0      62     372000        0
       UMA Slabs 0    112    3113      16        3113       0     126     350448        0
       malloc-2048   2048     136       8         160       0       8     294912        0
         VM OBJECT    264     906      69       11758       0      30     257400        0
             VNODE    448     526      41         556       0      30     254016        0
        256 Bucket   2048     100      16        2962       0       8     237568        0
         malloc-64     64    3374      28        3430       0     254     217728        0
         malloc-16     16   12635     115       12683       0     254     204000        0
            THREAD   1808     102       8         102       0       8     198880        0
            DEVCTL   1024       0     192          93       0       0     196608        0
      malloc-65536  65536       3       0           3       0       1     196608        0
       malloc-4096   4096      40       4         829       0       2     180224        0
        malloc-256    256     652      23        1194       0      62     172800        0
         UMA Zones    768     222       2         222       0      16     172032        0
         malloc-32     32    4679     109        4821       0     254     153216        0
       FFS2 dinode    256     505      20         532       0      62     134400        0
      malloc-65536  65536       1       1          70       0       1     131072        0
      malloc-65536  65536       2       0           2       0       1     131072        0
      malloc-32768  32768       2       2           4       0       1     131072        0
          ksiginfo    112      31    1013          62       0     126     116928        0
       malloc-8192   8192      11       3          14       0       1     114688        0
       malloc-1024   1024     101      11         229       0      16     114688        0
       S VFS Cache    104     995      97        1075       0     126     113568        0
         MAP ENTRY     96     776     358       37115       0     126     108864        0
         FFS inode    192     505      41         532       0      62     104832        0
          UMA Kegs    384     207       6         207       0      30      81792        0
         malloc-64     64     983     151       17674       0     254      72576        0
        128 Bucket   1024      45      22         691       0      16      68608        0
      mbuf_cluster   2048      30       2          30       0     254      65536        0
      malloc-32768  32768       2       0          54       0       1      65536        0
              PROC   1336      39       9         824       0       8      64128        0
        malloc-256    256     224      16         471       0      62      61440        0
           VMSPACE   2544      18       6         804       0       4      61056        0
         filedesc0   1072      40      16         825       0       8      60032        0
        malloc-128    128     374      60        3643       0     126      55552        0
        malloc-128    128     348      55       28257       0     126      51584        0
        malloc-384    384     111      19         150       0      30      49920        0
            clpbuf   2624       0      15          27       0       5      39360        0
         32 Bucket    256      37     113         483       0      62      38400        0
           DIRHASH   1024      32       4          32       0      16      36864        0
             NAMEI   1024       0      36       12410       0      16      36864        0
        malloc-256    256     107      28         573       0      62      34560        0
            socket    944      21      15        1015       0     254      33984        0
      malloc-32768  32768       1       0           1       0       1      32768        0
      malloc-32768  32768       1       0           1       0       1      32768        0
      malloc-16384  16384       2       0           2       0       1      32768        0
           pcpu-64     64     455      57         455       0     254      32768        0
       malloc-4096   4096       6       1           8       0       2      28672        0
            pcpu-8      8    3293     291        3316       0     254      28672        0
         64 Bucket    512      52       4         717       0      30      28672        0
         malloc-64     64     259     182        3329       0     254      28224        0
             g_bio    384       0      70        4611       0      30      26880        0
       malloc-4096   4096       4       2         274       0       2      24576        0
        malloc-128    128     149      37         580       0     126      23808        0
        malloc-384    384      54       6          54       0      30      23040        0
        malloc-256    256      84       6         316       0      62      23040        0
       malloc-1024   1024      14       6         879       0      16      20480        0
         TURNSTILE    136     111      36         111       0      62      19992        0
       Mountpoints   2752       2       5           2       0       4      19264        0
        malloc-256    256      29      46         401       0      62      19200        0
      malloc-16384  16384       1       0           1       0       1      16384        0
      malloc-16384  16384       1       0          65       0       1      16384        0
       malloc-8192   8192       0       2          32       0       1      16384        0
       malloc-8192   8192       2       0           2       0       1      16384        0
       malloc-8192   8192       2       0          43       0       1      16384        0
       malloc-8192   8192       2       0           2       0       1      16384        0
       malloc-4096   4096       4       0           5       0       2      16384        0
       malloc-2048   2048       5       3         232       0       8      16384        0
        malloc-384    384      17      23          25       0      30      15360        0
             tcpcb   1080       4      10          10       0     254      15120        0
              pipe    744       7      13         299       0      16      14880        0
        SLEEPQUEUE     88     111      49         111       0     126      14080        0
       malloc-4096   4096       1       2          14       0       2      12288        0
       malloc-1024   1024       4       8          21       0      16      12288        0
       malloc-1024   1024       9       3           9       0      16      12288        0
             Files     80      80      70        6999       0     126      12000        0
         udp_inpcb    496       3      21          61       0     254      11904        0
        malloc-128    128      44      49         165       0     126      11904        0
             unpcb    256      12      33         932       0     254      11520        0
        malloc-256    256       1      44         104       0      62      11520        0
       malloc-4096   4096       2       0           2       0       2       8192        0
       malloc-4096   4096       2       0          39       0       2       8192        0
       malloc-1024   1024       4       4          53       0      16       8192        0
       malloc-1024   1024       4       4           4       0      16       8192        0
        malloc-512    512      10       6          16       0      30       8192        0
           rtentry    176      11      35          14       0      62       8096        0
              PGRP     88      15      77          32       0     126       8096        0
          rl_entry     40      26     176          28       0     254       8080        0
             udpcb     32       3     249          61       0     254       8064        0
               PWD     32      11     241          97       0     254       8064        0
         malloc-64     64      23     103        7632       0     254       8064        0
         malloc-64     64      34      92          51       0     254       8064        0
         malloc-64     64       5     121           9       0     254       8064        0
         malloc-64     64       8     118           9       0     254       8064        0
         malloc-64     64       7     119          29       0     254       8064        0
         malloc-32     32      62     190         226       0     254       8064        0
         malloc-32     32     122     130         878       0     254       8064        0
         malloc-32     32      29     223        4971       0     254       8064        0
         malloc-32     32      48     204          50       0     254       8064        0
         malloc-32     32      13     239          43       0     254       8064        0
         16 Bucket    144      31      25        1889       0      62       8064        0
          4 Bucket     48       5     163          50       0     254       8064        0
          2 Bucket     32      40     212         568       0     254       8064        0
         malloc-16     16      21     479         176       0     254       8000        0
         malloc-16     16      13     487          53       0     254       8000        0
         malloc-16     16     450      50        1318       0     254       8000        0
         malloc-16     16      37     463       26957       0     254       8000        0
         malloc-16     16      16     484          19       0     254       8000        0
          8 Bucket     80      27      73         328       0     126       8000        0
         tcp_inpcb    496       4      12          10       0     254       7936        0
        malloc-128    128      16      46          22       0     126       7936        0
        malloc-128    128       1      61           8       0     126       7936        0
        malloc-128    128      12      50          13       0     126       7936        0
              kenv    258       2      28         704       0      30       7740        0
     routing nhops    256       8      22          14       0      62       7680        0
       mbuf_packet    256       0      30         102       0     254       7680        0
        malloc-384    384      20       0          20       0      30       7680        0
        malloc-384    384       8      12           9       0      30       7680        0
        malloc-384    384       0      20         194       0      30       7680        0
        malloc-256    256      16      14          16       0      62       7680        0
     FPU_save_area    832       1       8           1       0      16       7488        0
            cpuset    104       7      55           7       0     126       6448        0
 epoch_record pcpu    256       4      12           4       0      62       4096        0
       malloc-2048   2048       1       1          13       0       8       4096        0
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
         malloc-32     32       9     117          47       0     254       4032        0
         malloc-32     32       0     126           2       0     254       4032        0
      vtnet_tx_hdr     24       1     166        6872       0     254       4008        0
            ttyinq    160      15      10          45       0      62       4000        0
         malloc-16     16       4     246           5       0     254       4000        0
         malloc-16     16       7     243           7       0     254       4000        0
             ripcb    496       1       7           1       0     254       3968        0
       UMA Slabs 1    176       6      16           6       0      62       3872        0
       L VFS Cache    320       0      12           1       0      30       3840        0
           ttyoutq    256       8       7          24       0      62       3840        0
        malloc-256    256       1      14           1       0      62       3840        0
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
           ada_ccb    272       0       0           0       0      30          0        0
            da_ccb    544       0       0           0       0      16          0        0
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
    IPsec SA lft_c     16       0       0           0       0     254          0        0
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
# {Threaded:false Collide:false Repeat:false RepeatTimes:0 Procs:1 Slowdown:1 Sandbox: Fault:false FaultCall:-1 FaultNth:0 Leak:false NetInjection:false NetDevices:false NetReset:false Cgroups:false BinfmtMisc:false CloseFDs:false KCSAN:false DevlinkPCI:false USB:false VhciInjection:false Wifi:false IEEE802154:false Sysctl:false UseTmpDir:false HandleSegv:false Repro:false Trace:false}
r0 = socket$inet6_udp(0x1c, 0x2, 0x0)
setsockopt$inet6_IPV6_RTHDR(r0, 0x29, 0x33, &(0x7f0000000080)=ANY=[@ANYBLOB="590c000600e30000f76a6e725cd38492e09cff0e0000d3a900000000000000008000000000000000000000000013bb0000000000000000000000ffe5000001ff020000000000000000000000008001749e94eda655302aade5fc249c4bc6bd000000000000000000"], 0x68)
getsockopt$inet6_buf(r0, 0x29, 0x33, &(0x7f0000000180)=""/224, &(0x7f0000000280)=0xe0)


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
  res = syscall(SYS_socket, 0x1cul, 2ul, 0);
  if (res != -1)
    r[0] = res;
  memcpy(
      (void*)0x20000080,
      "\x59\x0c\x00\x06\x00\xe3\x00\x00\xf7\x6a\x6e\x72\x5c\xd3\x84\x92\xe0\x9c"
      "\xff\x0e\x00\x00\xd3\xa9\x00\x00\x00\x00\x00\x00\x00\x00\x80\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x13\xbb\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\xff\xe5\x00\x00\x01\xff\x02\x00\x00\x00\x00\x00\x00\x00"
      "\x00\x00\x00\x00\x00\x80\x01\x74\x9e\x94\xed\xa6\x55\x30\x2a\xad\xe5\xfc"
      "\x24\x9c\x4b\xc6\xbd\x00\x00\x00\x00\x00\x00\x00\x00\x00",
      104);
  syscall(SYS_setsockopt, r[0], 0x29, 0x33, 0x20000080ul, 0x68ul);
  *(uint32_t*)0x20000280 = 0xe0;
  syscall(SYS_getsockopt, r[0], 0x29, 0x33, 0x20000180ul, 0x20000280ul);
  return 0;
}


