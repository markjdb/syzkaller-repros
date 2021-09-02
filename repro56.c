Syzkaller hit 'panic: MSan: Uninitialized UMA memory from m_get2+0x221' bug.

login: panic: MSan: Uninitialized UMA memory from m_get2+0x221
cpuid = 1
time = 1630617978
KDB: stack backtrace:
db_trace_self_wrapper() at db_trace_self_wrapper+0xde/frame 0xfffffe001aadeee0
vpanic() at vpanic+0x639/frame 0xfffffe001aadefa0
panic() at panic+0x1b3/frame 0xfffffe001aadf0b0
__msan_warning() at __msan_warning+0x255/frame 0xfffffe001aadf200
uipc_send() at uipc_send+0x949/frame 0xfffffe001aadf400
sosend_generic() at sosend_generic+0x27f4/frame 0xfffffe001aadf680
sosend() at sosend+0x2f2/frame 0xfffffe001aadf760
kern_sendit() at kern_sendit+0xeb8/frame 0xfffffe001aadf8a0
sendit() at sendit+0x9a6/frame 0xfffffe001aadf970
sys_sendmsg() at sys_sendmsg+0x2b3/frame 0xfffffe001aadfa10
amd64_syscall() at amd64_syscall+0xa4e/frame 0xfffffe001aadfbf0
fast_syscall_common() at fast_syscall_common+0xf8/frame 0xfffffe001aadfbf0
--- syscall (0, FreeBSD ELF64, nosys), rip = 0x23324a, rsp = 0x7fffffffea68, rbp = 0x7fffffffea80 ---
KDB: enter: panic
[ thread pid 823 tid 100103 ]
Stopped at      kdb_enter+0x1c7:        movq    $0x87434090,%rdi
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
rax         0xffffffff8668669e
rcx                          0
rdx         0xffffffff8743c000  msan_dummy_orig
rbx                          0
rsp         0xfffffe001aadee80
rbp         0xfffffe001aadeee0
rsi                        0x1
rdi         0xffffffff87434090  kdb_why
r8                           0
r9                           0
r10                          0
r11                          0
r12                          0
r13         0xffffffff87438e01  msan_thread0+0x3e01
r14         0xffffffff87438ec8  dummy_tls
r15         0xffffffff8668669e
rip         0xffffffff83fc5967  kdb_enter+0x1c7
rflags                    0x46
kdb_enter+0x1c7:        movq    $0x87434090,%rdi
db> show proc
Process 823 (syz-executor3740282) at 0xfffffe003b238000:
 state: NORMAL
 uid: 0  gids: 0, 0, 5
 parent: pid 821 at 0xfffffe003b420a70
 ABI: FreeBSD ELF64
 flag: 0x10004000  flag2: 0
 arguments: /root/syz-executor374028296
 reaper: 0xfffffe0011389538 reapsubtree: 1
 sigparent: 20
 vmspace: 0xfffffe0039a7d9f0
   (map 0xfffffe0039a7d9f0)
   (map.pmap 0xfffffe0039a7dab0)
   (pmap 0xfffffe0039a7db10)
 threads: 1
100103                   Run     CPU 1                       syz-executor3740282
db> ps
  pid  ppid  pgrp   uid  state   wmesg   wchan               cmd
  823   821   821     0  R       CPU 1                       syz-executor3740282
  821   819   821     0  Ss      pause   0xfffffe003b420b20  csh
  819   736   819     0  Ss      select  0xfffffe003af3ca40  sshd
  798     1   798     0  Ss+     ttyin   0xfffffe001a8ed4b0  getty
  794     1   794     0  Ss      select  0xfffffe003af3cd40  logger
  788     1    23     0  S+      piperd  0xfffffe003aeda5d0  logger
  787   786    23     0  S+      nanslp  0xffffffff874077e0  sleep
  786     1    23     0  S+      wait    0xfffffe001f9b4000  sh
  782     1   782    25  Ss      pause   0xfffffe003aebeb20  sendmail
  779     1   779     0  Ss      select  0xfffffe003af3cdc0  sendmail
  740     1   740     0  Ss      nanslp  0xffffffff874077e1  cron
  736     1   736     0  Ss      select  0xfffffe001a7330c0  sshd
  647     1   647     0  Ss      select  0xfffffe001a710140  syslogd
  450     1   450     0  Ss      select  0xfffffe003ae8ce40  devd
  353     1   353    65  Ss      select  0xfffffe003ae8cec0  dhclient
  271     1   271     0  Ss      select  0xfffffe001a710240  dhclient
  268     1   268     0  Ss      select  0xfffffe001a733340  dhclient
   96     0     0     0  DL      pftm    0xffffffff87b31b30  [pf purge]
   22     0     0     0  DL      syncer  0xffffffff87501230  [syncer]
   21     0     0     0  DL      vlruwt  0xfffffe001f864000  [vnlru]
   20     0     0     0  DL      (threaded)                  [bufdaemon]
100072                   D       qsleep  0xffffffff87500230  [bufdaemon]
100073                   D       -       0xffffffff86e0af80  [bufspacedaemon-0]
100086                   D       sdflush 0xfffffe001a9050e8  [/ worker]
   19     0     0     0  DL      psleep  0xffffffff87526008  [vmdaemon]
   18     0     0     0  DL      (threaded)                  [pagedaemon]
100070                   D       psleep  0xffffffff8751a478  [dom0]
100076                   D       launds  0xffffffff8751a484  [laundry: dom0]
100077                   D       umarcl  0xffffffff856b8980  [uma]
   17     0     0     0  DL      -       0xffffffff8723bb58  [rand_harvestq]
   16     0     0     0  DL      waiting 0xffffffff87503980  [sctp_iterator]
   15     0     0     0  DL      -       0xffffffff874fd75c  [soaiod4]
    9     0     0     0  DL      -       0xffffffff874fd75c  [soaiod3]
    8     0     0     0  DL      -       0xffffffff874fd75c  [soaiod2]
    7     0     0     0  DL      -       0xffffffff874fd75c  [soaiod1]
    6     0     0     0  DL      (threaded)                  [cam]
100046                   D       -       0xffffffff87113240  [doneq0]
100047                   D       -       0xffffffff871131c0  [async]
100069                   D       -       0xffffffff87113090  [scanner]
   14     0     0     0  DL      seqstat 0xfffffe0010b1a088  [sequencer 00]
    5     0     0     0  DL      crypto_ 0xfffffe001a59ed80  [crypto returns 1]
    4     0     0     0  DL      crypto_ 0xfffffe001a59ed30  [crypto returns 0]
    3     0     0     0  DL      crypto_ 0xffffffff875179a0  [crypto]
   13     0     0     0  DL      (threaded)                  [geom]
100037                   D       -       0xffffffff873e6ff0  [g_event]
100038                   D       -       0xffffffff873e6ff8  [g_up]
100039                   D       -       0xffffffff873e7000  [g_down]
    2     0     0     0  DL      (threaded)                  [KTLS]
100029                   D       -       0xfffffe0011243b00  [thr_0]
100030                   D       -       0xfffffe0011243b80  [thr_1]
100031                   D       -       0xffffffff874fdeb8  [alloc_0]
   12     0     0     0  WL      (threaded)                  [intr]
100016                   I                                   [swi6: task queue]
100017                   I                                   [swi6: Giant taskq]
100020                   I                                   [swi5: fast taskq]
100032                   I                                   [swi4: clock (0)]
100033                   I                                   [swi4: clock (1)]
100034                   I                                   [swi3: vm]
100035                   I                                   [swi1: netisr 0]
100048                   I                                   [irq40: virtio_pci0]
100049                   I                                   [irq41: virtio_pci0]
100050                   I                                   [irq42: virtio_pci0]
100053                   I                                   [irq43: virtio_pci1]
100054                   I                                   [irq44: virtio_pci1]
100055                   I                                   [irq1: atkbd0]
100056                   I                                   [irq12: psm0]
100057                   I                                   [swi0: uart uart++]
100088                   I                                   [swi1: pf send]
   11     0     0     0  RL      (threaded)                  [idle]
100003                   Run     CPU 0                       [idle: cpu0]
100004                   CanRun                              [idle: cpu1]
    1     0     1     0  SLs     wait    0xfffffe0011389538  [init]
   10     0     0     0  DL      audit_w 0xffffffff87517eb0  [audit]
    0     0     0     0  DLs     (threaded)                  [kernel]
100000                   D       swapin  0xffffffff873e7590  [swapper]
100005                   D       -       0xfffffe001124d800  [if_config_tqg_0]
100006                   D       -       0xfffffe001124d600  [softirq_0]
100007                   D       -       0xfffffe001124d400  [softirq_1]
100008                   D       -       0xfffffe001124d200  [if_io_tqg_0]
100009                   D       -       0xfffffe001124d000  [if_io_tqg_1]
100010                   D       -       0xfffffe00113ffd00  [pci_hp taskq]
100011                   D       -       0xfffffe00113ffb00  [kqueue_ctx taskq]
100012                   D       -       0xfffffe00113ff900  [in6m_free taskq]
100013                   D       -       0xfffffe00113ff700  [aiod_kick taskq]
100014                   D       -       0xfffffe00113ff500  [inm_free taskq]
100015                   D       -       0xfffffe00113ff300  [deferred_unmount ta]
100018                   D       -       0xfffffe001a470c00  [linuxkpi_irq_wq]
100019                   D       -       0xfffffe001a470a00  [thread taskq]
100021                   D       -       0xfffffe001a470600  [linuxkpi_short_wq_0]
100022                   D       -       0xfffffe001a470600  [linuxkpi_short_wq_1]
100023                   D       -       0xfffffe001a470600  [linuxkpi_short_wq_2]
100024                   D       -       0xfffffe001a470600  [linuxkpi_short_wq_3]
100025                   D       -       0xfffffe001a470100  [linuxkpi_long_wq_0]
100026                   D       -       0xfffffe001a470100  [linuxkpi_long_wq_1]
100027                   D       -       0xfffffe001a470100  [linuxkpi_long_wq_2]
100028                   D       -       0xfffffe001a470100  [linuxkpi_long_wq_3]
100036                   D       -       0xfffffe001a49e400  [firmware taskq]
100040                   D       -       0xfffffe001a59fe00  [crypto_0]
100041                   D       -       0xfffffe001a59fe00  [crypto_1]
100051                   D       -       0xfffffe001a795e00  [vtnet0 rxq 0]
100052                   D       -       0xfffffe001a795d00  [vtnet0 txq 0]
100062                   D       -       0xffffffff86a2fd41  [deadlkres]
100065                   D       -       0xfffffe001f883e00  [acpi_task_0]
100066                   D       -       0xfffffe001f883e00  [acpi_task_1]
100067                   D       -       0xfffffe001f883e00  [acpi_task_2]
100068                   D       -       0xfffffe001a59f700  [CAM taskq]
db> show all locks
Process 823 (syz-executor3740282) thread 0xfffffe003af4b720 (100103)
shared sx filedesc structure (filedesc structure) r = 0 (0xfffffe0039a5c940) locked @ /root/freebsd/sys/kern/uipc_usrreq.c:2270
exclusive sx so_snd_sx (so_snd_sx) r = 0 (0xfffffe003b428c80) locked @ /root/freebsd/sys/kern/uipc_socket.c:4149
db> show malloc
              Type        InUse        MemUse     Requests
           pf_hash            5        11524K            5
         sysctloid        31442         1856K        31484
             kmsan          104         1664K          104
            linker          227         1504K          240
              kobj          324         1296K          484
            newblk          612         1177K          671
            devbuf         1360         1150K         1377
          vfscache            3         1025K            3
               pcb           22          921K           38
          inodedep           62          535K           99
         ufs_quota            1          512K            1
          vfs_hash            1          512K            1
           callout            2          512K            2
              intr            4          472K            4
           subproc           93          184K          876
         vnet_data            1          168K            1
           tidhash            3          158K            3
           pagedep           22          134K           33
        tfo_ccache            1          128K            1
               sem            4          106K            4
            DEVFS1           91           91K          103
              vmem            3           84K            5
               bus          967           78K         2573
            bus-sc           31           76K         1060
          mtx_pool            2           72K            2
          syncache            1           68K            1
          acpitask            1           64K            1
       ddb_capture            1           64K            1
            module          492           62K          492
            acpica          420           39K        62761
               LRO            2           33K            2
              proc            3           33K            3
         hostcache            1           32K            1
               shm            1           32K            1
               msg            4           30K            4
           kdtrace          146           29K          929
            DEVFS3          110           28K          126
              umtx          220           28K          220
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
      eventhandler          126           11K          126
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
               UMA          259            5K          259
             ifnet            3            5K            3
           io_apic            1            4K            1
               tty            4            4K            4
             evdev            4            4K            4
          filedesc            1            4K            1
             hhook           13            4K           13
          pf_ifnet            5            3K            6
           lltable           10            3K           10
            plimit           11            3K          228
           acpisem           21            3K           21
            kqueue           41            3K          824
           pwddesc           41            3K          824
             lockf           21            3K           32
             selfd           33            3K        14318
        local_apic            1            2K            1
       fpukern_ctx            2            2K            2
         ipsec-saq            2            2K            2
           CAM DEV            1            2K            2
           session           15            2K           31
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
       vnodemarker            2            1K           10
      NFSD session            1            1K            1
         in6_multi            9            1K            9
          indirdep            3            1K            3
             nhops            6            1K            6
             mount           16            1K          123
            crypto            4            1K            4
            isadev            5            1K            5
           CAM XPT           11            1K           12
          sctp_ifa            4            1K            5
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
          sctp_ifn            2            1K            5
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
          sctp_vrf            1            1K            1
              vnet            1            1K            1
          acpiintr            1            1K            1
               pmc            1            1K            1
              cpus            2            1K            2
    vnet_data_free            1            1K            1
          CAM path            1            1K           12
           entropy            1            1K           55
           Per-cpu            1            1K            1
          freework            1            1K           26
               iov            1            1K         7791
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
        sctp_mcore            0            0K            0
        sctp_socko            0            0K            0
         sctp_iter            0            0K            3
         sctp_mvrf            0            0K            0
         sctp_timw            0            0K            0
         sctp_cpal            0            0K            0
         sctp_cmsg            0            0K            0
         sctp_stre            0            0K            0
         sctp_athi            0            0K            0
         sctp_athm            0            0K            0
         sctp_atky            0            0K            0
         sctp_atcl            0            0K            0
         sctp_a_it            0            0K            3
         sctp_aadr            0            0K            0
         sctp_stro            0            0K            0
         sctp_stri            0            0K            0
          sctp_map            0            0K            0
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
            statfs            0            0K         1092
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
         NFSCL lck            0            0K            0
      NFSCL lckown            0            0K            0
db> show uma
              Zone   Size    Used    Free    Requests  Sleeps  Bucket  Total Mem    XFree
   mbuf_jumbo_page   4096    1088     965       14561       0     254    8409088        0
      malloc-16384  16384     105       0         169       0       1    1720320        0
       malloc-4096   4096     326       2         525       0       2    1343488        0
        malloc-128    128   10343      42       10371       0     126    1329280        0
          BUF TRIE    144     171    8985         457       0      62    1318464        0
              pbuf   2624       0     269           0       0       2     705856        0
              mbuf    256    1349    1036       22401       0     254     610560        0
        malloc-512    512    1025       7        1025       0      30     528384        0
         vmem btag     56    7329     134        7329       0     254     417928        0
        RADIX NODE    144    2395     343       28962       0      62     394272        0
      malloc-65536  65536       6       0           6       0       1     393216        0
            lkpimm    168       1    2327           1       0      62     391104        0
          lkpicurr    168       2    2326           2       0      62     391104        0
       UMA Slabs 0    112    3050       7        3050       0     126     342384        0
       malloc-2048   2048     134       2         134       0       8     278528        0
         VM OBJECT    264     924      51       11805       0      30     257400        0
             VNODE    448     523      35         553       0      30     249984        0
        256 Bucket   2048     104      16        2872       0       8     245760        0
         malloc-64     64    3521      70        4308       0     254     229824        0
         malloc-16     16   13087     413       13131       0     254     216000        0
            THREAD   1808     104       6         104       0       8     198880        0
            DEVCTL   1024       0     192          93       0       0     196608        0
      malloc-65536  65536       1       2          32       0       1     196608        0
      malloc-65536  65536       1       2          70       0       1     196608        0
      malloc-65536  65536       3       0           3       0       1     196608        0
       malloc-4096   4096      41       3         824       0       2     180224        0
         UMA Zones    768     231       3         231       0      16     179712        0
        malloc-256    256     640      20         748       0      62     168960        0
         malloc-32     32    4835      79        4911       0     254     157248        0
       FFS2 dinode    256     502      23         529       0      62     134400        0
       S VFS Cache    104     997     134        1077       0     126     117624        0
          ksiginfo    112      32    1012          64       0     126     116928        0
         FFS inode    192     502      65         529       0      62     108864        0
         MAP ENTRY     96     799     335       38624       0     126     108864        0
       malloc-1024   1024      99       5         229       0      16     106496        0
        malloc-128    128     603      79        1186       0     126      87296        0
          UMA Kegs    384     216       7         216       0      30      85632        0
        malloc-128    128     558      31        3034       0     126      75392        0
        128 Bucket   1024      44      23         701       0      16      68608        0
              PROC   1336      40      11         823       0       8      68136        0
      mbuf_cluster   2048      30       2          30       0     254      65536        0
      malloc-65536  65536       1       0           1       0       1      65536        0
      malloc-32768  32768       2       0           2       0       1      65536        0
      malloc-32768  32768       0       2          53       0       1      65536        0
         malloc-64     64     882     126        2703       0     254      64512        0
           VMSPACE   2544      18       6         802       0       4      61056        0
         filedesc0   1072      41      15         824       0       8      60032        0
       malloc-8192   8192       7       0           7       0       1      57344        0
        malloc-128    128     384      50       28987       0     126      55552        0
       malloc-8192   8192       5       1          48       0       1      49152        0
        malloc-256    256     143      37         613       0      62      46080        0
        malloc-256    256     145      20         976       0      62      42240        0
         32 Bucket    256      44     106         904       0      62      38400        0
           DIRHASH   1024      32       4          32       0      16      36864        0
             NAMEI   1024       0      36       12409       0      16      36864        0
           pcpu-64     64     475     101         475       0     254      36864        0
            socket    960      21      15        1014       0     254      34560        0
        malloc-256    256     109      26         258       0      62      34560        0
      malloc-32768  32768       1       0           1       0       1      32768        0
      malloc-32768  32768       0       1           1       0       1      32768        0
      malloc-32768  32768       1       0           1       0       1      32768        0
      malloc-32768  32768       1       0           1       0       1      32768        0
      malloc-32768  32768       1       0           1       0       1      32768        0
      malloc-16384  16384       2       0           2       0       1      32768        0
      malloc-16384  16384       2       0           2       0       1      32768        0
             g_bio    384       0      80        4773       0      30      30720        0
        malloc-384    384      74       6          74       0      30      30720        0
        malloc-384    384      61      19         110       0      30      30720        0
       malloc-4096   4096       7       0           7       0       2      28672        0
            pcpu-8      8    3331     253        3354       0     254      28672        0
         64 Bucket    512      52       4         723       0      30      28672        0
        malloc-384    384      56      14          64       0      30      26880        0
            clpbuf   2624       0      10          29       0       5      26240        0
       malloc-8192   8192       2       1           3       0       1      24576        0
       malloc-8192   8192       3       0           3       0       1      24576        0
       malloc-1024   1024      18       6          22       0      16      24576        0
       malloc-4096   4096       3       2        1096       0       2      20480        0
       malloc-4096   4096       4       1           8       0       2      20480        0
        malloc-128    128     109      46         640       0     126      19840        0
       Mountpoints   2752       2       5           2       0       4      19264        0
        malloc-256    256      35      40         351       0      62      19200        0
         TURNSTILE    136     111      15         111       0      62      17136        0
      malloc-16384  16384       1       0           1       0       1      16384        0
      malloc-16384  16384       1       0           1       0       1      16384        0
       malloc-8192   8192       0       2          32       0       1      16384        0
       malloc-8192   8192       2       0           2       0       1      16384        0
       malloc-4096   4096       3       1         267       0       2      16384        0
       malloc-2048   2048       3       5         232       0       8      16384        0
       malloc-1024   1024      10       6         868       0      16      16384        0
         malloc-64     64     148     104       14445       0     254      16128        0
         malloc-64     64     187      65        1755       0     254      16128        0
             tcpcb   1080       4      10          10       0     254      15120        0
              pipe    744       7      13         297       0      16      14880        0
        SLEEPQUEUE     88     111      49         111       0     126      14080        0
       malloc-2048   2048       2       4          20       0       8      12288        0
       malloc-2048   2048       1       5           7       0       8      12288        0
       malloc-1024   1024       4       8          49       0      16      12288        0
         malloc-64     64      15     174         288       0     254      12096        0
             Files     80      80      70        7008       0     126      12000        0
         udp_inpcb    496       2      22          60       0     254      11904        0
        malloc-128    128      36      57          99       0     126      11904        0
       malloc-4096   4096       0       2           6       0       2       8192        0
       malloc-2048   2048       3       1           3       0       8       8192        0
       malloc-1024   1024       4       4           7       0      16       8192        0
       malloc-1024   1024       2       6          24       0      16       8192        0
       malloc-1024   1024       4       4           4       0      16       8192        0
        malloc-512    512       0      16           7       0      30       8192        0
        malloc-512    512       2      14          39       0      30       8192        0
        malloc-512    512       2      14          11       0      30       8192        0
        malloc-512    512      10       6          10       0      30       8192        0
           rtentry    176      11      35          14       0      62       8096        0
              PGRP     88      15      77          31       0     126       8096        0
          rl_entry     40      24     178          26       0     254       8080        0
             udpcb     32       2     250          60       0     254       8064        0
               PWD     32      11     241          95       0     254       8064        0
         malloc-64     64      23     103        7575       0     254       8064        0
         malloc-64     64      29      97          74       0     254       8064        0
         malloc-64     64      11     115          11       0     254       8064        0
         malloc-32     32      12     240          79       0     254       8064        0
         malloc-32     32      87     165         656       0     254       8064        0
         malloc-32     32      14     238         123       0     254       8064        0
         malloc-32     32      78     174        5154       0     254       8064        0
         malloc-32     32      46     206         186       0     254       8064        0
         malloc-32     32      14     238          14       0     254       8064        0
         16 Bucket    144      32      24         350       0      62       8064        0
          4 Bucket     48       5     163          49       0     254       8064        0
          2 Bucket     32      46     206         574       0     254       8064        0
         malloc-16     16      12     488         150       0     254       8000        0
         malloc-16     16      16     484          22       0     254       8000        0
         malloc-16     16     451      49        1216       0     254       8000        0
         malloc-16     16      12     488          43       0     254       8000        0
         malloc-16     16      45     455       27600       0     254       8000        0
         malloc-16     16       2     498           7       0     254       8000        0
         malloc-16     16       8     492           8       0     254       8000        0
          8 Bucket     80      31      69         330       0     126       8000        0
         tcp_inpcb    496       4      12          10       0     254       7936        0
        malloc-128    128       6      56          44       0     126       7936        0
        malloc-128    128      21      41          40       0     126       7936        0
              kenv    258       2      28         699       0      30       7740        0
     routing nhops    256       8      22          14       0      62       7680        0
             unpcb    256      13      17         932       0     254       7680        0
       mbuf_packet    256       0      30         101       0     254       7680        0
        malloc-384    384      15       5          15       0      30       7680        0
        malloc-384    384       6      14           7       0      30       7680        0
        malloc-384    384       0      20         185       0      30       7680        0
        malloc-256    256       4      26          54       0      62       7680        0
        malloc-256    256      11      19          37       0      62       7680        0
     FPU_save_area    832       1       8           1       0      16       7488        0
            cpuset    104       8      54           8       0     126       6448        0
 epoch_record pcpu    256       4      12           4       0      62       4096        0
       malloc-2048   2048       0       2          12       0       8       4096        0
       malloc-2048   2048       2       0           2       0       8       4096        0
       malloc-2048   2048       1       1           1       0       8       4096        0
        malloc-512    512       0       8         139       0      30       4096        0
        malloc-512    512       2       6           2       0      30       4096        0
           pcpu-16     16       7     249           7       0     254       4096        0
        sctp_laddr     48       0      84           3       0     254       4032        0
         hostcache     64       1      62           1       0     254       4032        0
          syncache    168       0      24           5       0     254       4032        0
         malloc-32     32      13     113         147       0     254       4032        0
      vtnet_tx_hdr     24       1     166        6861       0     254       4008        0
            ttyinq    160      15      10          45       0      62       4000        0
             ripcb    496       1       7           1       0     254       3968        0
       UMA Slabs 1    176       6      16           6       0      62       3872        0
       L VFS Cache    320       0      12           1       0      30       3840        0
           ttyoutq    256       8       7          24       0      62       3840        0
        malloc-384    384       0      10           2       0      30       3840        0
        malloc-384    384       1       9           1       0      30       3840        0
        malloc-256    256       6       9           7       0      62       3840        0
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
   sctp_asconf_ack     48       0       0           0       0     254          0        0
       sctp_asconf     40       0       0           0       0     254          0        0
sctp_stream_msg_out    112       0       0           0       0     254          0        0
        sctp_readq    152       0       0           0       0     254          0        0
        sctp_chunk    152       0       0           0       0     254          0        0
        sctp_raddr    736       0       0           0       0     254          0        0
         sctp_asoc   2288       0       0           0       0     254          0        0
           sctp_ep   1280       0       0           0       0     254          0        0
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
      malloc-16384  16384       0       0           0       0       1          0        0
      malloc-16384  16384       0       0           0       0       1          0        0
      malloc-16384  16384       0       0           0       0       1          0        0
       malloc-8192   8192       0       0           0       0       1          0        0
       malloc-8192   8192       0       0           0       0       1          0        0
       malloc-4096   4096       0       0           0       0       2          0        0
       malloc-1024   1024       0       0           0       0      16          0        0
        malloc-512    512       0       0           0       0      30          0        0
           pcpu-32     32       0       0           0       0     254          0        0
            pcpu-4      4       0       0           0       0     254          0        0
            fakepg    104       0       0           0       0     126          0        0
          UMA Hash    256       0       0           0       0      62          0        0


Syzkaller reproducer:
# {Threaded:false Collide:false Repeat:false RepeatTimes:0 Procs:1 Slowdown:1 Sandbox: Fault:false FaultCall:-1 FaultNth:0 Leak:false NetInjection:false NetDevices:false NetReset:false Cgroups:false BinfmtMisc:false CloseFDs:false KCSAN:false DevlinkPCI:false USB:false VhciInjection:false Wifi:false IEEE802154:false Sysctl:false UseTmpDir:false HandleSegv:false Repro:false Trace:false}
r0 = socket$unix(0x1, 0x5, 0x0)
sendmsg$unix(r0, &(0x7f00000000c0)={0x0, 0x0, 0x0, 0x0, &(0x7f0000000080)=ANY=[@ANYBLOB="0c000000ffff000001"], 0x10}, 0x0)


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
  res = syscall(SYS_socket, 1ul, 5ul, 0);
  if (res != -1)
    r[0] = res;
  *(uint64_t*)0x200000c0 = 0;
  *(uint32_t*)0x200000c8 = 0;
  *(uint64_t*)0x200000d0 = 0;
  *(uint64_t*)0x200000d8 = 0;
  *(uint64_t*)0x200000e0 = 0x20000080;
  memcpy((void*)0x20000080, "\x0c\x00\x00\x00\xff\xff\x00\x00\x01", 9);
  *(uint64_t*)0x200000e8 = 0x10;
  *(uint32_t*)0x200000f0 = 0;
  syscall(SYS_sendmsg, r[0], 0x200000c0ul, 0ul);
  return 0;
}


