Syzkaller hit 'panic: ASan: Invalid access, NUM-byte read in sctp_free_assoc' bug.

login: panic: ASan: Invalid access, 4-byte read at 0xfffffe008ff14a5c, UMAUseAfterFree(fd)
cpuid = 0
time = 1630365279
KDB: stack backtrace:
db_trace_self_wrapper() at db_trace_self_wrapper+0xc7/frame 0xfffffe0054036730
kdb_backtrace() at kdb_backtrace+0xd3/frame 0xfffffe0054036890
vpanic() at vpanic+0x2c5/frame 0xfffffe0054036970
panic() at panic+0xb5/frame 0xfffffe0054036a30
__asan_load4_noabort() at __asan_load4_noabort+0x216/frame 0xfffffe0054036af0
sctp_free_assoc() at sctp_free_assoc+0x173f/frame 0xfffffe0054036c30
sctp_process_control() at sctp_process_control+0x7d28/frame 0xfffffe0054037300
sctp_common_input_processing() at sctp_common_input_processing+0xb26/frame 0xfffffe0054037560
sctp6_input_with_port() at sctp6_input_with_port+0x5a1/frame 0xfffffe0054037730
sctp6_input() at sctp6_input+0x1f/frame 0xfffffe0054037750
ip6_input() at ip6_input+0x252d/frame 0xfffffe00540379b0
swi_net() at swi_net+0x2e5/frame 0xfffffe0054037a50
ithread_loop() at ithread_loop+0x4f1/frame 0xfffffe0054037bb0
fork_exit() at fork_exit+0xd0/frame 0xfffffe0054037bf0
fork_trampoline() at fork_trampoline+0xe/frame 0xfffffe0054037bf0
--- trap 0, rip = 0, rsp = 0, rbp = 0 ---
KDB: enter: panic
[ thread pid 12 tid 100035 ]
Stopped at      kdb_enter+0x6b: movq    $0,0x28dbc7a(%rip)
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
rcx         0xf91336069f422a3b
rdx         0xdffff7c000000000
rbx                          0
rsp         0xfffffe0054036870
rbp         0xfffffe0054036890
rsi                        0x1
rdi         0xffffffff8407a840  cov_trace_pc
r8                         0x3
r9          0xfffffe00540363a8
r10                          0
r11                       0xbf
r12         0xfffffe0053e1fac0
r13         0xfffffe0054036801
r14         0xffffffff82c383a0  .str.18
r15         0xffffffff82c383a0  .str.18
rip         0xffffffff817a153b  kdb_enter+0x6b
rflags                    0x46
kdb_enter+0x6b: movq    $0,0x28dbc7a(%rip)
db> show proc
Process 12 (intr) at 0xfffffe0053deba70:
 state: NORMAL
 uid: 0  gids: 0
 parent: pid 0 at 0xffffffff8401e540
 ABI: null
 flag: 0x10000284  flag2: 0
 reaper: 0xffffffff8401e540 reapsubtree: 12
 sigparent: 20
 vmspace: 0xffffffff8401f4c0
   (map 0xffffffff8401f4c0)
   (map.pmap 0xffffffff8401f580)
   (pmap 0xffffffff8401f5e0)
 threads: 16
100010                   I                                   [swi6: task queue]
100011                   I                                   [swi6: Giant taskq]
100013                   I                                   [swi5: fast taskq]
100032                   I                                   [swi3: vm]
100033                   I                                   [swi4: clock (0)]
100034                   I                                   [swi4: clock (1)]
100035                   Run     CPU 0                       [swi1: netisr 0]
100048                   I                                   [irq40: virtio_pci0]
100049                   I                                   [irq41: virtio_pci0]
100050                   I                                   [irq42: virtio_pci0]
100053                   I                                   [irq43: virtio_pci1]
100054                   I                                   [irq44: virtio_pci1]
100055                   I                                   [irq1: atkbd0]
100056                   I                                   [irq12: psm0]
100057                   I                                   [swi0: uart uart++]
100087                   I                                   [swi1: pf send]
db> ps
  pid  ppid  pgrp   uid  state   wmesg   wchan               cmd
  778   777   775     0  RE      CPU 1                       syz-executor0841721
  777   775   775     0  R                                   syz-executor0841721
  775   773   775     0  Ss      pause   0xfffffe008ff50b20  csh
  773   727   773     0  Ss      select  0xfffffe008fa2f8c0  sshd
  752     1   752     0  Ss+     ttyin   0xfffffe00543db4b0  getty
  751     1   751     0  Ss      select  0xfffffe008fa2fc40  logger
  745     1    21     0  S+      piperd  0xfffffe008f9e75d0  logger
  744   743    21     0  S+      nanslp  0xffffffff8404a0c1  sleep
  743     1    21     0  S+      wait    0xfffffe008fa2e000  sh
  737     1   737     0  Ss      nanslp  0xffffffff8404a0c1  cron
  733     1   733    25  Ss      pause   0xfffffe008f4a45e8  sendmail
  730     1   730     0  Ss      select  0xfffffe0054214040  sendmail
  727     1   727     0  Ss      select  0xfffffe008fa2fec0  sshd
  636     1   636     0  Ss      select  0xfffffe0054214340  syslogd
  444     1   444     0  Ss      select  0xfffffe008f9def40  devd
  342     1   342    65  Ss      select  0xfffffe00542140c0  dhclient
  260     1   260     0  Ss      select  0xfffffe0054214240  dhclient
  257     1   257     0  Ss      select  0xfffffe0054236240  dhclient
   90     0     0     0  DL      pftm    0xffffffff84d14e20  [pf purge]
   27     0     0     0  DL      vlruwt  0xfffffe0062fe0538  [vnlru]
   26     0     0     0  DL      syncer  0xffffffff84172420  [syncer]
   20     0     0     0  DL      (threaded)                  [bufdaemon]
100072                   D       qsleep  0xffffffff84170120  [bufdaemon]
100073                   D       -       0xffffffff83411f80  [bufspacedaemon-0]
100085                   D       sdflush 0xfffffe0053e8f4e8  [/ worker]
   19     0     0     0  DL      psleep  0xffffffff841a5600  [vmdaemon]
   18     0     0     0  DL      (threaded)                  [pagedaemon]
100070                   D       psleep  0xffffffff84199138  [dom0]
100074                   D       launds  0xffffffff84199144  [laundry: dom0]
100075                   D       umarcl  0xffffffff81e80750  [uma]
   17     0     0     0  DL      -       0xffffffff83e011a0  [rand_harvestq]
   16     0     0     0  DL      waiting 0xffffffff8488a4a0  [sctp_iterator]
   15     0     0     0  DL      -       0xffffffff8416b340  [soaiod4]
    9     0     0     0  DL      -       0xffffffff8416b340  [soaiod3]
    8     0     0     0  DL      -       0xffffffff8416b340  [soaiod2]
    7     0     0     0  DL      -       0xffffffff8416b340  [soaiod1]
    6     0     0     0  DL      (threaded)                  [cam]
100046                   D       -       0xffffffff83c86940  [doneq0]
100047                   D       -       0xffffffff83c868c0  [async]
100069                   D       -       0xffffffff83c86740  [scanner]
   14     0     0     0  DL      seqstat 0xfffffe000791a088  [sequencer 00]
    5     0     0     0  DL      crypto_ 0xfffffe0053eb0d80  [crypto returns 1]
    4     0     0     0  DL      crypto_ 0xfffffe0053eb0d30  [crypto returns 0]
    3     0     0     0  DL      crypto_ 0xffffffff84193260  [crypto]
   13     0     0     0  DL      (threaded)                  [geom]
100037                   D       -       0xffffffff8401d640  [g_event]
100038                   D       -       0xffffffff8401d680  [g_up]
100039                   D       -       0xffffffff8401d6c0  [g_down]
    2     0     0     0  DL      (threaded)                  [KTLS]
100029                   D       -       0xfffffe00081eab00  [thr_0]
100030                   D       -       0xfffffe00081eab80  [thr_1]
100031                   D       -       0xffffffff8416c6c8  [alloc_0]
   12     0     0     0  RL      (threaded)                  [intr]
100010                   I                                   [swi6: task queue]
100011                   I                                   [swi6: Giant taskq]
100013                   I                                   [swi5: fast taskq]
100032                   I                                   [swi3: vm]
100033                   I                                   [swi4: clock (0)]
100034                   I                                   [swi4: clock (1)]
100035                   Run     CPU 0                       [swi1: netisr 0]
100048                   I                                   [irq40: virtio_pci0]
100049                   I                                   [irq41: virtio_pci0]
100050                   I                                   [irq42: virtio_pci0]
100053                   I                                   [irq43: virtio_pci1]
100054                   I                                   [irq44: virtio_pci1]
100055                   I                                   [irq1: atkbd0]
100056                   I                                   [irq12: psm0]
100057                   I                                   [swi0: uart uart++]
100087                   I                                   [swi1: pf send]
   11     0     0     0  RL      (threaded)                  [idle]
100003                   CanRun                              [idle: cpu0]
100004                   CanRun                              [idle: cpu1]
    1     0     1     0  SLs     wait    0xfffffe0053d4e538  [init]
   10     0     0     0  DL      audit_w 0xffffffff84194200  [audit]
    0     0     0     0  DLs     (threaded)                  [kernel]
100000                   D       swapin  0xffffffff8401e540  [swapper]
100005                   D       -       0xfffffe00081f3800  [if_config_tqg_0]
100006                   D       -       0xfffffe00081f3600  [softirq_0]
100007                   D       -       0xfffffe00081f3400  [softirq_1]
100008                   D       -       0xfffffe00081f3200  [if_io_tqg_0]
100009                   D       -       0xfffffe00081f3000  [if_io_tqg_1]
100012                   D       -       0xfffffe0053dea900  [thread taskq]
100014                   D       -       0xfffffe0053dea500  [in6m_free taskq]
100015                   D       -       0xfffffe0053dea300  [kqueue_ctx taskq]
100016                   D       -       0xfffffe0053dea100  [pci_hp taskq]
100017                   D       -       0xfffffe0053df4e00  [aiod_kick taskq]
100018                   D       -       0xfffffe0053df4c00  [inm_free taskq]
100019                   D       -       0xfffffe0053df4a00  [deferred_unmount ta]
100020                   D       -       0xfffffe0053df4800  [linuxkpi_irq_wq]
100021                   D       -       0xfffffe0053df4600  [linuxkpi_short_wq_0]
100022                   D       -       0xfffffe0053df4600  [linuxkpi_short_wq_1]
100023                   D       -       0xfffffe0053df4600  [linuxkpi_short_wq_2]
100024                   D       -       0xfffffe0053df4600  [linuxkpi_short_wq_3]
100025                   D       -       0xfffffe0053df4100  [linuxkpi_long_wq_0]
100026                   D       -       0xfffffe0053df4100  [linuxkpi_long_wq_1]
100027                   D       -       0xfffffe0053df4100  [linuxkpi_long_wq_2]
100028                   D       -       0xfffffe0053df4100  [linuxkpi_long_wq_3]
100036                   D       -       0xfffffe0053dfc400  [firmware taskq]
100040                   D       -       0xfffffe0053eb1e00  [crypto_0]
100041                   D       -       0xfffffe0053eb1e00  [crypto_1]
100051                   D       -       0xfffffe0054298e00  [vtnet0 rxq 0]
100052                   D       -       0xfffffe0054298d00  [vtnet0 txq 0]
100062                   D       -       0xffffffff82c3f2a1  [deadlkres]
100064                   D       -       0xfffffe0054298000  [acpi_task_0]
100065                   D       -       0xfffffe0054298000  [acpi_task_1]
100066                   D       -       0xfffffe0054298000  [acpi_task_2]
100068                   D       -       0xfffffe0053eb1700  [CAM taskq]
db> show all locks
Process 778 (syz-executor0841721) thread 0xfffffe008f9ca900 (100110)
exclusive rw pmap pv list (pmap pv list) r = 0 (0xfffffe000779c800) locked @ /root/freebsd/sys/amd64/amd64/pmap.c:8376
exclusive sleep mutex pmap (pmap) r = 0 (0xfffffe008ff59500) locked @ /root/freebsd/sys/amd64/amd64/pmap.c:8288
Process 12 (intr) thread 0xfffffe0053e1fac0 (100035)
exclusive sleep mutex sctp-send-tcb (tcbs) r = 0 (0xfffffe008ff5ec90) locked @ /root/freebsd/sys/netinet/sctp_pcb.c:4835
exclusive sleep mutex sctp-tcb (tcb) r = 0 (0xfffffe008ff5ec70) locked @ /root/freebsd/sys/netinet/sctp_pcb.c:4834
exclusive rw sctp-info (sctp-info) r = 0 (0xfffffe00081b2308) locked @ /root/freebsd/sys/netinet/sctp_pcb.c:4832
db> show malloc
              Type        InUse        MemUse     Requests
           pf_hash            5        11524K            5
         sysctloid        31442         1856K        31484
              kobj          324         1296K          484
            newblk          573         1167K          625
            devbuf         1360         1150K         1377
            linker          225         1077K          233
          vfscache            3         1025K            3
               pcb           24          539K           40
          inodedep           31          524K           70
         ufs_quota            1          512K            1
          vfs_hash            1          512K            1
           callout            2          512K            2
              intr            4          472K            4
           subproc          100          190K          837
         vnet_data            1          168K            1
           tidhash            3          141K            3
           pagedep           13          131K           20
        tfo_ccache            1          128K            1
               sem            4          106K            4
            DEVFS1           91           91K          103
               bus          966           78K         2567
            bus-sc           31           76K         1055
              vmem            3           74K            4
          mtx_pool            2           72K            2
          syncache            1           68K            1
          acpitask            1           64K            1
       ddb_capture            1           64K            1
            module          493           62K          493
            acpica          420           39K        62596
               LRO            2           33K            2
              temp           16           33K         1391
         hostcache            1           32K            1
               shm            1           32K            1
           kdtrace          155           31K          892
              umtx          242           31K          242
               msg            4           30K            4
            DEVFS3          110           28K          126
        gtaskqueue           18           26K           18
            kbdmux            5           22K            5
        DEVFS_RULE           59           21K           59
           ithread          104           19K          104
               BPF           10           18K           10
         ufs_mount            4           17K            5
              proc            3           17K            3
            KTRACE          100           13K          100
           devstat            6           13K            6
              rman          102           12K          526
            ifaddr           29           11K           30
      eventhandler          126           11K          126
              kenv           60           10K           60
              GEOM           61           10K          508
          routetbl           44           10K          142
         bmsafemap            2            9K           46
              UART           12            9K           12
               rpc            2            8K            2
             shmfd            1            8K            1
       pfs_vncache            1            8K            1
         pfs_nodes           20            8K           20
     audit_evclass          237            8K          295
         taskqueue           54            6K           54
            sglist            3            6K            3
              cred           20            5K          287
       ufs_dirhash           24            5K           24
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
            kqueue           42            3K          779
           pwddesc           41            3K          779
           uidinfo            4            3K            9
             lockf           21            3K           28
             selfd           33            3K        14213
        local_apic            1            2K            1
       fpukern_ctx            2            2K            2
          freefile           16            2K           25
         ipsec-saq            2            2K            2
           CAM DEV            1            2K            2
           session           15            2K           30
               msi           13            2K           13
            diradd           13            2K           43
          pci_link           16            2K           16
            Unitno           25            2K           45
         proc-args           34            2K          466
           acpidev           22            2K           22
            select           10            2K           57
         toponodes           10            2K           10
         CAM queue            2            2K            5
         sctp_stro            1            1K            1
           softdep            1            1K            1
            dirrem            4            1K           27
       ipsecpolicy            1            1K            1
            sahead            1            1K            1
          secasvar            1            1K            1
             clone            8            1K            8
       ether_multi           13            1K           18
       vnodemarker            2            1K           10
      NFSD session            1            1K            1
         in6_multi            9            1K            9
         newdirblk            7            1K           10
             mkdir            7            1K           20
         sctp_atcl            2            1K            2
          indirdep            3            1K            3
             nhops            6            1K            6
             mount           16            1K           89
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
            DEVFSP            5            1K           10
               osd            3            1K            9
         sctp_timw            1            1K            1
          sctp_ifn            2            1K            5
      NFSD lckfile            1            1K            1
     NFSD V4client            1            1K            1
             DEVFS            9            1K           10
               MCA            2            1K            2
               mld            2            1K            2
              igmp            2            1K            2
            vnodes            1            1K            1
              ktls            1            1K            1
          procdesc            2            1K           18
       inpcbpolicy            7            1K           71
            feeder            7            1K            7
             xform            3            1K           56
        loginclass            3            1K            7
            prison            6            1K            6
       lkpikmalloc            5            1K            6
        aesni_data            2            1K            2
         sctp_atky            3            1K            3
            apmdev            1            1K            1
          atkbddev            2            1K            2
           CAM SIM            1            1K            1
          pmchooks            1            1K            1
            soname            4            1K         2558
          filecaps            4            1K           92
          nexusdev            6            1K            6
               tun            3            1K            3
          sctp_vrf            1            1K            1
     CAM dev queue            1            1K            1
           tcpfunc            1            1K            1
              vnet            1            1K            1
          acpiintr            1            1K            1
               pmc            1            1K            1
         sctp_athm            2            1K            2
          sctp_map            2            1K            2
              cpus            2            1K            2
    vnet_data_free            1            1K            1
          CAM path            1            1K           12
           entropy            1            1K           41
           Per-cpu            1            1K            1
          freework            1            1K           21
          p1003.1b            1            1K            1
          pf_table            0            0K            0
           pf_rule            0            0K            0
           pf_altq            0            0K            0
           pf_osfp            0            0K            0
           pf_temp            0            0K            0
        sctp_mcore            0            0K            0
        sctp_socko            0            0K            0
         sctp_iter            0            0K            3
         sctp_mvrf            0            0K            0
         sctp_cpal            0            0K            0
         sctp_cmsg            0            0K            0
         sctp_stre            0            0K            0
         sctp_athi            0            0K            0
         sctp_a_it            0            0K            3
         sctp_aadr            0            0K            0
         sctp_stri            0            0K            0
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
          savedino            0            0K            9
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
          freeblks            0            0K           20
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
            statfs            0            0K          980
     namei_tracker            0            0K            1
       export_host            0            0K            0
        cl_savebuf            0            0K            3
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
               iov            0            0K         7676
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
         sysctltmp            0            0K          506
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
   mbuf_jumbo_page   4096    1088    1006       14656       0     254    8577024        0
              pbuf   2624       0     794           0       0       2    2083456        0
          BUF TRIE    144     163   11653         464       0      62    1701504        0
       malloc-4096   4096     326       2         525       0       2    1343488        0
        malloc-128    128   10343      42       10370       0     126    1329280        0
              mbuf    256    1349    1006       22726       0     254     602880        0
        malloc-512    512    1026       6        1026       0      30     528384        0
        RADIX NODE    144    2355     412       27789       0      62     398448        0
      malloc-65536  65536       6       0           6       0       1     393216        0
            lkpimm    168       1    2327           1       0      62     391104        0
          lkpicurr    168       2    2326           2       0      62     391104        0
         vmem btag     56    6572      99        6572       0     254     373576        0
       UMA Slabs 0    112    2992      29        2992       0     126     338352        0
       malloc-2048   2048     132       2         132       0       8     274432        0
         VM OBJECT    264     922      53       11104       0      30     257400        0
        256 Bucket   2048     107      15        2906       0       8     249856        0
             VNODE    448     516      33         543       0      30     245952        0
         malloc-64     64    3522      69        4263       0     254     229824        0
            THREAD   1808     112       9         112       0       8     218768        0
         malloc-16     16   13087     413       13131       0     254     216000        0
            DEVCTL   1024       0     192          92       0       0     196608        0
      malloc-65536  65536       1       2          32       0       1     196608        0
      malloc-65536  65536       1       2          70       0       1     196608        0
      malloc-65536  65536       3       0           3       0       1     196608        0
       malloc-4096   4096      42       3         779       0       2     184320        0
         UMA Zones    768     231       3         231       0      16     179712        0
         malloc-32     32    4835     205        4911       0     254     161280        0
        malloc-256    256     592      23         687       0      62     157440        0
       FFS2 dinode    256     495      30         520       0      62     134400        0
          ksiginfo    112      40    1004          70       0     126     116928        0
       malloc-1024   1024     100       8         228       0      16     110592        0
       S VFS Cache    104     973      80        1017       0     126     109512        0
         MAP ENTRY     96     810     324       36334       0     126     108864        0
         FFS inode    192     495      51         520       0      62     104832        0
      mbuf_cluster   2048      45       1          45       0     254      94208        0
          UMA Kegs    384     216       7         216       0      30      85632        0
        malloc-128    128     570      50        1066       0     126      79360        0
              PROC   1336      41      16         778       0       8      76152        0
        malloc-128    128     577      12        3042       0     126      75392        0
           VMSPACE   2544      19       8         757       0       4      68688        0
      malloc-65536  65536       1       0           1       0       1      65536        0
      malloc-32768  32768       2       0           2       0       1      65536        0
      malloc-32768  32768       0       2          53       0       1      65536        0
         malloc-64     64     882     126        2599       0     254      64512        0
         filedesc0   1072      41      15         779       0       8      60032        0
        malloc-128    128     384      50       28900       0     126      55552        0
       malloc-8192   8192       5       1          48       0       1      49152        0
        128 Bucket   1024      36      11         521       0      16      48128        0
        malloc-256    256     153      27         958       0      62      46080        0
        malloc-256    256     145      20         620       0      62      42240        0
         32 Bucket    256      46     119        1599       0      62      42240        0
            clpbuf   2624       0      16          29       0      16      41984        0
       malloc-8192   8192       5       0           5       0       1      40960        0
         64 Bucket    512      60      20        1129       0      30      40960        0
        malloc-256    256     114      36         193       0      62      38400        0
           DIRHASH   1024      32       4          32       0      16      36864        0
             NAMEI   1024       0      36       11494       0      16      36864        0
             g_bio    384       0      90        4730       0      30      34560        0
      malloc-32768  32768       1       0           1       0       1      32768        0
      malloc-32768  32768       1       0           1       0       1      32768        0
      malloc-32768  32768       1       0           1       0       1      32768        0
      malloc-16384  16384       1       1           2       0       1      32768        0
       malloc-8192   8192       4       0           4       0       1      32768        0
           pcpu-64     64     474      38         474       0     254      32768        0
        malloc-384    384      74       6          74       0      30      30720        0
       malloc-4096   4096       7       0           7       0       2      28672        0
            pcpu-8      8    3328     256        3351       0     254      28672        0
            socket    960      19       9        1005       0     254      26880        0
        malloc-384    384      62       8          70       0      30      26880        0
       malloc-8192   8192       3       0           3       0       1      24576        0
       malloc-4096   4096       4       2          11       0       2      24576        0
        malloc-384    384      30      30          81       0      30      23040        0
       malloc-4096   4096       3       2         267       0       2      20480        0
       malloc-1024   1024      18       2          21       0      16      20480        0
       malloc-1024   1024      10      10         785       0      16      20480        0
         TURNSTILE    136     122      25         122       0      62      19992        0
        malloc-128    128     108      47         630       0     126      19840        0
       Mountpoints   2752       2       5           2       0       4      19264        0
        malloc-256    256      35      40         347       0      62      19200        0
      malloc-16384  16384       1       0           1       0       1      16384        0
      malloc-16384  16384       1       0          65       0       1      16384        0
      malloc-16384  16384       1       0           1       0       1      16384        0
       malloc-8192   8192       0       2          32       0       1      16384        0
       malloc-8192   8192       2       0           2       0       1      16384        0
       malloc-8192   8192       2       0           2       0       1      16384        0
       malloc-4096   4096       1       3         982       0       2      16384        0
       malloc-2048   2048       4       4         233       0       8      16384        0
         malloc-64     64     188      64        1743       0     254      16128        0
             tcpcb   1080       4      10          10       0     254      15120        0
              pipe    744       7      13         289       0      16      14880        0
        SLEEPQUEUE     88     122      38         122       0     126      14080        0
       malloc-2048   2048       4       2           4       0       8      12288        0
       malloc-2048   2048       2       4          20       0       8      12288        0
       malloc-1024   1024       4       8          49       0      16      12288        0
         malloc-64     64     148      41       14340       0     254      12096        0
             Files     80      78      72        6440       0     126      12000        0
         malloc-16     16     453     297        1192       0     254      12000        0
         udp_inpcb    496       2      22          60       0     254      11904        0
        malloc-128    128      36      57          99       0     126      11904        0
       mbuf_packet    256       0      45         100       0     254      11520        0
        malloc-384    384      16      14          16       0      30      11520        0
         sctp_asoc   2288       1       4           1       0     254      11440        0
       malloc-4096   4096       0       2           7       0       2       8192        0
       malloc-2048   2048       1       3           7       0       8       8192        0
       malloc-1024   1024       4       4           7       0      16       8192        0
       malloc-1024   1024       3       5          24       0      16       8192        0
        malloc-512    512       2      14           2       0      30       8192        0
        malloc-512    512       0      16           7       0      30       8192        0
        malloc-512    512       2      14          39       0      30       8192        0
        malloc-512    512       2      14          11       0      30       8192        0
        malloc-512    512      11       5          11       0      30       8192        0
        sctp_raddr    736       1      10           1       0     254       8096        0
           rtentry    176      11      35          14       0      62       8096        0
              PGRP     88      15      77          30       0     126       8096        0
          rl_entry     40      31     171          31       0     254       8080        0
             udpcb     32       2     250          60       0     254       8064        0
               PWD     32      11     241          89       0     254       8064        0
         malloc-64     64      23     103        7451       0     254       8064        0
         malloc-64     64      29      97          70       0     254       8064        0
         malloc-64     64      15     111         273       0     254       8064        0
         malloc-64     64      11     115          11       0     254       8064        0
         malloc-32     32      12     240          73       0     254       8064        0
         malloc-32     32      85     167         649       0     254       8064        0
         malloc-32     32      14     238         123       0     254       8064        0
         malloc-32     32      81     171        5147       0     254       8064        0
         malloc-32     32      46     206         175       0     254       8064        0
         malloc-32     32      14     238          14       0     254       8064        0
         16 Bucket    144      31      25         193       0      62       8064        0
          4 Bucket     48       5     163          46       0     254       8064        0
          2 Bucket     32      45     207         473       0     254       8064        0
            ttyinq    160      15      35          45       0      62       8000        0
         malloc-16     16      16     484          23       0     254       8000        0
         malloc-16     16      12     488          42       0     254       8000        0
         malloc-16     16      49     451       27528       0     254       8000        0
         malloc-16     16       2     498           6       0     254       8000        0
         malloc-16     16       8     492           8       0     254       8000        0
          8 Bucket     80      27      73         300       0     126       8000        0
         tcp_inpcb    496       4      12          10       0     254       7936        0
        malloc-128    128      21      41          36       0     126       7936        0
        malloc-128    128      21      41          38       0     126       7936        0
              kenv    258       2      28         693       0      30       7740        0
     routing nhops    256       8      22          14       0      62       7680        0
             unpcb    256      11      19         922       0     254       7680        0
           ttyoutq    256       8      22          24       0      62       7680        0
        malloc-384    384       6      14           7       0      30       7680        0
        malloc-384    384       2      18         184       0      30       7680        0
        malloc-256    256       4      26          44       0      62       7680        0
        malloc-256    256      11      19          34       0      62       7680        0
        malloc-256    256       6      24           7       0      62       7680        0
     FPU_save_area    832       1       8           1       0      16       7488        0
            cpuset    104       8      54           8       0     126       6448        0
 epoch_record pcpu    256       4      12           4       0      62       4096        0
       malloc-2048   2048       0       2          12       0       8       4096        0
       malloc-2048   2048       2       0           2       0       8       4096        0
       malloc-2048   2048       1       1           1       0       8       4096        0
       malloc-1024   1024       0       4           1       0      16       4096        0
       malloc-1024   1024       3       1           3       0      16       4096        0
        malloc-512    512       0       8         139       0      30       4096        0
           pcpu-16     16       7     249           7       0     254       4096        0
sctp_stream_msg_out    112       1      35           1       0     254       4032        0
        sctp_laddr     48       0      84           3       0     254       4032        0
         hostcache     64       1      62           1       0     254       4032        0
          syncache    168       0      24           5       0     254       4032        0
         malloc-32     32      13     113          89       0     254       4032        0
      vtnet_tx_hdr     24       1     166        7047       0     254       4008        0
         malloc-16     16      11     239         120       0     254       4000        0
             ripcb    496       1       7           1       0     254       3968        0
       UMA Slabs 1    176       6      16           6       0      62       3872        0
           sctp_ep   1280       1       2           1       0     254       3840        0
       L VFS Cache    320       0      12           1       0      30       3840        0
        malloc-384    384       0      10           1       0      30       3840        0
        malloc-384    384       1       9           1       0      30       3840        0
        KMAP ENTRY     96       9      30          12       0       0       3744        0
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
   sctp_asconf_ack     48       0       0           0       0     254          0        0
       sctp_asconf     40       0       0           0       0     254          0        0
        sctp_readq    152       0       0           0       0     254          0        0
        sctp_chunk    152       0       0           0       0     254          0        0
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
           NCLNODE    592       0       0           0       0      16          0        0
        TMPFS node    224       0       0           0       0      62          0        0
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
      malloc-16384  16384       0       0           0       0       1          0        0
      malloc-16384  16384       0       0           0       0       1          0        0
      malloc-16384  16384       0       0           0       0       1          0        0
      malloc-16384  16384       0       0           0       0       1          0        0
       malloc-8192   8192       0       0           0       0       1          0        0
       malloc-4096   4096       0       0           0       0       2          0        0
        malloc-512    512       0       0           0       0      30          0        0
           pcpu-32     32       0       0           0       0     254          0        0
            pcpu-4      4       0       0           0       0     254          0        0
            fakepg    104       0       0           0       0     126          0        0
          UMA Hash    256       0       0           0       0      62          0        0


Syzkaller reproducer:
# {Threaded:false Collide:false Repeat:true RepeatTimes:0 Procs:1 Slowdown:1 Sandbox: Fault:false FaultCall:-1 FaultNth:0 Leak:false NetInjection:false NetDevices:false NetReset:false Cgroups:false BinfmtMisc:false CloseFDs:false KCSAN:false DevlinkPCI:false USB:false VhciInjection:false Wifi:false IEEE802154:false Sysctl:false UseTmpDir:false HandleSegv:false Repro:false Trace:false}
r0 = socket$inet6_sctp(0x1c, 0x1, 0x84)
sendmsg$inet6_sctp(r0, &(0x7f00000199c0)={&(0x7f0000019a00)=@in6={0x1c, 0x1c, 0x3, 0x0, @loopback}, 0x1c, &(0x7f0000000000)=[{&(0x7f00000195c0)="a3", 0x1}], 0x1}, 0x0)


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

uint64_t r[1] = {0xffffffffffffffff};

void execute_one(void)
{
  intptr_t res = 0;
  res = syscall(SYS_socket, 0x1cul, 1ul, 0x84);
  if (res != -1)
    r[0] = res;
  *(uint64_t*)0x200199c0 = 0x20019a00;
  *(uint8_t*)0x20019a00 = 0x1c;
  *(uint8_t*)0x20019a01 = 0x1c;
  *(uint16_t*)0x20019a02 = htobe16(0x4e23);
  *(uint32_t*)0x20019a04 = 0;
  *(uint64_t*)0x20019a08 = htobe64(0);
  *(uint64_t*)0x20019a10 = htobe64(1);
  *(uint32_t*)0x20019a18 = 0;
  *(uint32_t*)0x200199c8 = 0x1c;
  *(uint64_t*)0x200199d0 = 0x20000000;
  *(uint64_t*)0x20000000 = 0x200195c0;
  memset((void*)0x200195c0, 163, 1);
  *(uint64_t*)0x20000008 = 1;
  *(uint32_t*)0x200199d8 = 1;
  *(uint64_t*)0x200199e0 = 0;
  *(uint32_t*)0x200199e8 = 0;
  *(uint32_t*)0x200199ec = 0;
  syscall(SYS_sendmsg, r[0], 0x200199c0ul, 0ul);
}
int main(void)
{
  syscall(SYS_mmap, 0x20000000ul, 0x1000000ul, 7ul, 0x1012ul, -1, 0ul);
  loop();
  return 0;
}


