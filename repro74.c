Syzkaller hit 'panic: refcount ADDR wraparound' bug.

login: panic: refcount 0xfffff80003ef8b44 wraparound
cpuid = 0
time = 1644186105
KDB: stack backtrace:
db_trace_self_wrapper() at db_trace_self_wrapper+0x47/frame 0xfffffe00517c5b40
vpanic() at vpanic+0x1c7/frame 0xfffffe00517c5ba0
panic() at panic+0x43/frame 0xfffffe00517c5c00
_refcount_update_saturated() at _refcount_update_saturated+0x15/frame 0xfffffe00517c5c10
closef() at closef+0x2da/frame 0xfffffe00517c5ca0
fdescfree() at fdescfree+0x6f2/frame 0xfffffe00517c5d70
exit1() at exit1+0x6c8/frame 0xfffffe00517c5de0
sys_exit() at sys_exit+0xd/frame 0xfffffe00517c5df0
amd64_syscall() at amd64_syscall+0x217/frame 0xfffffe00517c5f30
fast_syscall_common() at fast_syscall_common+0xf8/frame 0xfffffe00517c5f30
--- syscall (1, FreeBSD ELF64, sys_exit), rip = 0x2340da, rsp = 0x820336f68, rbp = 0x820336f80 ---
KDB: enter: panic
[ thread pid 818 tid 100094 ]
Stopped at      kdb_enter+0x67: movq    $0,0x1632ebe(%rip)
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
rcx                       0x80
rdx         0xffffffff819f6943
rbx                          0
rsp         0xfffffe00517c5b20
rbp         0xfffffe00517c5b40
rsi                        0x1
rdi                          0
r8                           0
r9          0x8080808080808080
r10         0xfffffe00517c5a00
r11              0x1ffaefff59c
r12         0xffffffff82267db0  ddb_dbbe
r13                          0
r14         0xffffffff81a8d222
r15         0xffffffff81a8d222
rip         0xffffffff81125847  kdb_enter+0x67
rflags                    0x82
kdb_enter+0x67: movq    $0,0x1632ebe(%rip)
db> show proc
Process 818 (syz-executor9080807) at 0xfffff80007a29000:
 state: NORMAL
 uid: 0  gids: 0, 0, 5
 parent: pid 816 at 0xfffff80003f58000
 ABI: FreeBSD ELF64
 flag: 0x10002000  flag2: 0
 arguments: /root/syz-executor908080725
 reaper: 0xfffff80003600000 reapsubtree: 1
 sigparent: 20
 vmspace: 0xfffffe00881f09f8
   (map 0xfffffe00881f09f8)
   (map.pmap 0xfffffe00881f0ab8)
   (pmap 0xfffffe00881f0b20)
 threads: 1
100094                   Run     CPU 0                       syz-executor9080807
db> ps
  pid  ppid  pgrp   uid  state   wmesg   wchan               cmd
  818   816   818     0  REs     CPU 0                       syz-executor9080807
  817   815   817     0  Rs      CPU 1                       syz-executor9080807
  816   814   814     0  S       nanslp  0xffffffff8272bea0  syz-executor9080807
  815   814   814     0  S       nanslp  0xffffffff8272bea1  syz-executor9080807
  814   812   814     0  Ss      nanslp  0xffffffff8272bea0  syz-executor9080807
  812   745   812     0  Ss      select  0xfffff80003498840  sshd
  799     1   799     0  Ss+     ttyin   0xfffff800039d40b0  getty
  795     1   795     0  Ss      select  0xfffff800034984c0  logger
  789     1    16     0  S+      piperd  0xfffff80003f778b8  logger
  788   787    16     0  S+      nanslp  0xffffffff8272bea1  sleep
  787     1    16     0  S+      wait    0xfffff80003f68000  sh
  781     1   781     0  Ss      nanslp  0xffffffff8272bea1  cron
  777     1   777    25  Ss      pause   0xfffff8000727bb40  sendmail
  774     1   774     0  Ss      select  0xfffff80003687f40  sendmail
  745     1   745     0  Ss      select  0xfffff80003499ec0  sshd
  648     1   648     0  Ss      select  0xfffff80003498d40  syslogd
  453     1   453     0  Ss      select  0xfffff800037022c0  devd
  351     1   351    65  Ss      select  0xfffff80003499840  dhclient
  269     1   269     0  Ss      select  0xfffff80003499c40  dhclient
  266     1   266     0  Ss      select  0xfffff800037026c0  dhclient
   94     0     0     0  DL      pftm    0xffffffff82f1e950  [pf purge]
   15     0     0     0  DL      vlruwt  0xfffff80003cc8000  [vnlru]
    9     0     0     0  DL      syncer  0xffffffff8281ccb0  [syncer]
    8     0     0     0  DL      (threaded)                  [bufdaemon]
100064                   D       psleep  0xffffffff8281bcd0  [bufdaemon]
100065                   D       -       0xffffffff8220af40  [bufspacedaemon-0]
100080                   D       sdflush 0xfffff80003f6ece8  [/ worker]
    7     0     0     0  DL      psleep  0xffffffff82841a10  [vmdaemon]
    6     0     0     0  DL      (threaded)                  [pagedaemon]
100062                   D       psleep  0xffffffff82835e78  [dom0]
100066                   D       launds  0xffffffff82835e84  [laundry: dom0]
100067                   D       umarcl  0xffffffff815e0ee0  [uma]
    5     0     0     0  DL      -       0xffffffff8255f8f8  [rand_harvestq]
    4     0     0     0  DL      (threaded)                  [cam]
100043                   D       -       0xffffffff824496c0  [doneq0]
100044                   D       -       0xffffffff82449640  [async]
100061                   D       -       0xffffffff82449510  [scanner]
   14     0     0     0  DL      seqstat 0xfffff8000372c088  [sequencer 00]
    3     0     0     0  DL      (threaded)                  [crypto]
100039                   D       crypto_ 0xffffffff828333a0  [crypto]
100040                   D       crypto_ 0xfffff8000375d030  [crypto returns 0]
100041                   D       crypto_ 0xfffff8000375d080  [crypto returns 1]
   13     0     0     0  DL      (threaded)                  [geom]
100034                   D       -       0xffffffff8270b610  [g_event]
100035                   D       -       0xffffffff8270b618  [g_up]
100036                   D       -       0xffffffff8270b620  [g_down]
    2     0     0     0  WL      (threaded)                  [clock]
100030                   I                                   [clock (0)]
100031                   I                                   [clock (1)]
   12     0     0     0  WL      (threaded)                  [intr]
100010                   I                                   [swi6: task queue]
100011                   I                                   [swi6: Giant taskq]
100016                   I                                   [swi5: fast taskq]
100029                   I                                   [swi1: netisr 0]
100032                   I                                   [swi3: busdma]
100045                   I                                   [irq40: virtio_pci0]
100046                   I                                   [irq41: virtio_pci0]
100047                   I                                   [irq42: virtio_pci0]
100050                   I                                   [irq43: virtio_pci1]
100051                   I                                   [irq44: virtio_pci1]
100052                   I                                   [irq1: atkbd0]
100053                   I                                   [irq12: psm0]
100054                   I                                   [swi0: uart uart++]
100082                   I                                   [swi1: pf send]
   11     0     0     0  RL      (threaded)                  [idle]
100003                   CanRun                              [idle: cpu0]
100004                   CanRun                              [idle: cpu1]
    1     0     1     0  SLs     wait    0xfffff80003600000  [init]
   10     0     0     0  DL      audit_w 0xffffffff828338b0  [audit]
    0     0     0     0  DLs     (threaded)                  [kernel]
100000                   D       swapin  0xffffffff8270bb90  [swapper]
100005                   D       -       0xfffff80003494800  [softirq_0]
100006                   D       -       0xfffff80003494600  [softirq_1]
100007                   D       -       0xfffff80003494400  [if_io_tqg_0]
100008                   D       -       0xfffff80003494200  [if_io_tqg_1]
100009                   D       -       0xfffff80003494000  [if_config_tqg_0]
100012                   D       -       0xfffff8000345fd00  [aiod_kick taskq]
100013                   D       -       0xfffff8000345fc00  [inm_free taskq]
100014                   D       -       0xfffff8000345fb00  [deferred_unmount ta]
100015                   D       -       0xfffff8000345fa00  [thread taskq]
100017                   D       -       0xfffff8000345f800  [kqueue_ctx taskq]
100018                   D       -       0xfffff8000345f700  [linuxkpi_irq_wq]
100019                   D       -       0xfffff8000345f600  [pci_hp taskq]
100020                   D       -       0xfffff8000345f500  [in6m_free taskq]
100021                   D       -       0xfffff8000345f400  [linuxkpi_short_wq_0]
100022                   D       -       0xfffff8000345f400  [linuxkpi_short_wq_1]
100023                   D       -       0xfffff8000345f400  [linuxkpi_short_wq_2]
100024                   D       -       0xfffff8000345f400  [linuxkpi_short_wq_3]
100025                   D       -       0xfffff8000345f300  [linuxkpi_long_wq_0]
100026                   D       -       0xfffff8000345f300  [linuxkpi_long_wq_1]
100027                   D       -       0xfffff8000345f300  [linuxkpi_long_wq_2]
100028                   D       -       0xfffff8000345f300  [linuxkpi_long_wq_3]
100033                   D       -       0xfffff80003694300  [firmware taskq]
100037                   D       -       0xfffff80003694100  [crypto_0]
100038                   D       -       0xfffff80003694100  [crypto_1]
100048                   D       -       0xfffff80003697400  [vtnet0 rxq 0]
100049                   D       -       0xfffff80003697300  [vtnet0 txq 0]
100055                   D       -       0xffffffff81e38560  [deadlkres]
100056                   D       -       0xfffff80003460600  [acpi_task_0]
100057                   D       -       0xfffff80003460600  [acpi_task_1]
100058                   D       -       0xfffff80003460600  [acpi_task_2]
100060                   D       -       0xfffff80003695e00  [CAM taskq]
db> show all locks
Process 817 (syz-executor9080807) thread 0xfffffe0051a1a1e0 (100077)
exclusive lockmgr bufwait (bufwait) r = 0 (0xfffffe0003871de0) locked @ /root/freebsd/sys/kern/vfs_bio.c:3984
exclusive lockmgr ufs (ufs) r = 0 (0xfffff80007be3af0) locked @ /root/freebsd/sys/kern/vfs_subr.c:3235
db> show malloc
              Type        InUse        MemUse     Requests
           pf_hash            5        11524K            5
         sysctloid        31631         1861K        31673
              kobj          323         1292K          485
            newblk          631         1182K          666
            devbuf         1356         1134K         1373
          vfscache            3         1025K            3
            linker          249          685K          267
          inodedep           65          536K          102
         ufs_quota            1          512K            1
          vfs_hash            1          512K            1
           callout            2          512K            2
              intr            4          472K            4
               pcb           13          393K           23
         vnet_data            1          168K            1
           subproc           86          167K          868
           tidhash            3          141K            3
           pagedep           24          134K           35
        tfo_ccache            1          128K            1
               sem            4          106K            4
            DEVFS1           92           92K          104
               bus          961           78K         2550
            bus-sc           31           76K         1044
          mtx_pool            2           72K            2
          syncache            1           68K            1
          acpitask            1           64K            1
       ddb_capture            1           64K            1
            module          494           62K          494
            acpica          420           39K        62999
               LRO            2           33K            2
         hostcache            1           32K            1
               shm            1           32K            1
               msg            4           30K            4
            DEVFS3          111           28K          127
              umtx          220           28K          220
           kdtrace          137           28K          919
        gtaskqueue           18           26K           18
        DEVFS_RULE           62           22K           62
            kbdmux            5           22K            5
               BPF           10           18K           10
           ithread           98           18K           98
              temp           15           17K         1561
         ufs_mount            4           17K            5
              proc            3           17K            3
              vmem            3           13K            3
            KTRACE          100           13K          100
           devstat            6           13K            6
              rman          102           12K          526
            ifaddr           29           11K           30
      eventhandler          125           11K          125
              GEOM           61           11K          508
              kenv           59           10K           59
          routetbl           44           10K          142
         bmsafemap            2            9K           94
              UART           12            9K           12
           filemon            1            8K            2
               rpc            2            8K            2
             shmfd            1            8K            1
       pfs_vncache            1            8K            1
              cred           30            8K          290
         pfs_nodes           20            8K           20
     audit_evclass          237            8K          296
            diradd           48            6K          109
         taskqueue           56            6K           56
            sglist            3            6K            3
       ufs_dirhash           24            5K           24
               UMA          254            5K          254
             ifnet            3            5K            3
           io_apic            1            4K            1
               tty            4            4K            4
             evdev            4            4K            4
          filedesc            1            4K            1
             hhook           15            4K           17
          pf_ifnet            5            3K            6
           lltable           10            3K           10
            plimit           11            3K          228
           acpisem           21            3K           21
           uidinfo            4            3K            9
            kqueue           37            3K          819
           pwddesc           36            3K          819
             lockf           21            3K           32
           session           17            3K           33
        local_apic            1            2K            1
       fpukern_ctx            2            2K            2
         ipsec-saq            2            2K            2
           CAM DEV            1            2K            2
             selfd           31            2K         7693
         proc-args           54            2K         1787
               msi           13            2K           13
          pci_link           16            2K           16
             mkdir           12            2K           34
            Unitno           25            2K           45
           acpidev           22            2K           22
         newdirblk           10            2K           17
            select           10            2K           61
         toponodes           10            2K           10
         CAM queue            2            2K            5
           softdep            1            1K            1
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
            dirrem            2            1K           46
          in_multi            2            1K            3
              pfil            4            1K            4
              cdev            2            1K            2
 encap_export_host            8            1K            8
               osd            8            1K           20
            ip6ndp            3            1K            3
    chacha20random            1            1K            1
        CAM periph            2            1K           14
            DEVFSP            5            1K           27
      NFSD lckfile            1            1K            1
     NFSD V4client            1            1K            1
             DEVFS            9            1K           10
               MCA            2            1K            2
               mld            2            1K            2
            CC Mem            4            1K           10
              igmp            2            1K            2
            vnodes            1            1K            1
          procdesc            2            1K           20
       inpcbpolicy            7            1K           71
            feeder            7            1K            7
        loginclass            3            1K            7
            prison            6            1K            6
       lkpikmalloc            5            1K            6
        aesni_data            2            1K            2
         cryptodev            2            1K          161
            apmdev            1            1K            1
          atkbddev            2            1K            2
          freefile            1            1K           27
           CAM SIM            1            1K            1
          pmchooks            1            1K            1
            soname            4            1K         2597
          filecaps            4            1K          101
          nexusdev            6            1K            6
               tun            3            1K            3
          freework            1            1K           26
     CAM dev queue            1            1K            1
           tcpfunc            1            1K            1
              vnet            1            1K            1
          acpiintr            1            1K            1
               pmc            1            1K            1
              cpus            2            1K            2
    vnet_data_free            1            1K            1
          CAM path            1            1K           12
           entropy            1            1K           66
           Per-cpu            1            1K            1
          p1003.1b            1            1K            1
          pf_table            0            0K            0
           pf_rule            0            0K            0
           pf_altq            0            0K            0
           pf_osfp            0            0K            0
           pf_temp            0            0K            0
       NEWdirectio            0            0K            0
        NEWNFSnode            0            0K            0
        madt_table            0            0K            2
          smartpqi            0            0K            0
         NFSCL lck            0            0K            0
      NFSCL lckown            0            0K            0
      NFSCL client            0            0K            0
               ixl            0            0K            0
       NFSCL deleg            0            0K            0
        NFSCL open            0            0K            0
       NFSCL owner            0            0K            0
            NFS fh            0            0K            0
           NFS req            0            0K            0
     NFSD usrgroup            0            0K            0
       NFSD string            0            0K            0
        ice-resmgr            0            0K            0
         ice-osdep            0            0K            0
               ice            0            0K            0
              iavf            0            0K            0
             axgbe            0            0K            0
       NFSD V4lock            0            0K            0
      NFSD V4state            0            0K            0
     NFSD srvcache            0            0K            0
       msdosfs_fat            0            0K            0
     msdosfs_mount            0            0K            0
      msdosfs_node            0            0K            0
           memdesc            0            0K            0
          xen_intr            0            0K            0
            DEVFS4            0            0K            0
           xen_hvm            0            0K            0
         legacydrv            0            0K            0
            bounce            0            0K            0
            busdma            0            0K            0
            qpidrv            0            0K            0
      dmar_idpgtbl            0            0K            0
          dmar_dom            0            0K            0
          dmar_ctx            0            0K            0
            DEVFS2            0            0K            0
            gntdev            0            0K            0
       privcmd_dev            0            0K            0
              isci            0            0K            0
      iommu_dmamap            0            0K            0
     hyperv_socket            0            0K            0
           bxe_ilt            0            0K            0
        evtchn_dev            0            0K            0
            xenbus            0            0K            0
          xenstore            0            0K            0
         scsi_pass            0            0K            0
         ciss_data            0            0K            0
     vm_fictitious            0            0K            0
               xnb            0            0K            0
              xbbd            0            0K            0
               xbd            0            0K            0
           Balloon            0            0K            0
          sysmouse            0            0K            0
            vtfont            0            0K            0
                vt            0            0K            0
             vtbuf            0            0K            0
         BACKLIGHT            0            0K            0
           ath_hal            0            0K            0
            athdev            0            0K            0
           UMAHash            0            0K            0
           ata_pci            0            0K            0
           ata_dma            0            0K            0
         vm_pgdata            0            0K            0
           jblocks            0            0K            0
          savedino            0            0K           24
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
       ata_generic            0            0K            0
            pvscsi            0            0K            0
           scsi_da            0            0K            0
            ata_da            0            0K            0
           scsi_ch            0            0K            0
           scsi_cd            0            0K            0
       AHCI driver            0            0K            0
            USBdev            0            0K            0
               USB            0            0K            0
               agp            0            0K            0
          ktls_ocf            0            0K            0
           nvme_da            0            0K            0
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
 CAM I/O Scheduler            0            0K            0
            statfs            0            0K           13
     namei_tracker            0            0K            2
       export_host            0            0K            0
        cl_savebuf            0            0K            6
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
               PUC            0            0K            0
          ppbusdev            0            0K            0
            biobuf            0            0K            0
              aios            0            0K            0
               lio            0            0K            0
               acl            0            0K            0
agtiapi_MemAlloc malloc            0            0K            0
          mbuf_tag            0            0K           16
              ktls            0            0K            0
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
          mpt_user            0            0K            0
          mps_user            0            0K            0
              accf            0            0K            0
               pts            0            0K            0
               iov            0            0K         7764
          ioctlops            0            0K           78
           eventfd            0            0K            0
           Witness            0            0K            0
          terminal            0            0K            0
             stack            0            0K            0
            MPSSAS            0            0K            0
               mps            0            0K            0
          mpr_user            0            0K            0
            MPRSAS            0            0K            0
               mpr            0            0K            0
            mfibuf            0            0K            0
              sbuf            0            0K          364
        md_sectors            0            0K            0
          firmware            0            0K            0
        compressor            0            0K            0
           md_disk            0            0K            0
              SWAP            0            0K            0
           malodev            0            0K            0
               LED            0            0K            0
         sysctltmp            0            0K          530
            sysctl            0            0K           34
              ekcd            0            0K            0
            dumper            0            0K            0
          sendfile            0            0K            0
              rctl            0            0K            0
          ix_sriov            0            0K            0
        aacraidcam            0            0K            0
                ix            0            0K            0
            ipsbuf            0            0K            0
             cache            0            0K            0
       aacraid_buf            0            0K            0
          kcovinfo            0            0K            0
      prison_racct            0            0K            0
       Fail Points            0            0K            0
             sigio            0            0K            1
filedesc_to_leader            0            0K            0
               pwd            0            0K            0
       tty console            0            0K            0
            aaccam            0            0K            0
            aacbuf            0            0K            0
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
db> show uma
              Zone   Size    Used    Free    Requests  Sleeps  Bucket  Total Mem    XFree
   mbuf_jumbo_page   4096    1088    1198       14389       0     254    9363456        0
              pbuf   2624       0     794           0       0       2    2083456        0
          BUF TRIE    144     163   13333         429       0      62    1943424        0
      mbuf_cluster   2048     508     254         508       0     254    1560576        0
       malloc-4096   4096     365       1        1309       0       2    1499136        0
        malloc-128    128   10700     150       10807       0     126    1388800        0
              mbuf    256    1346    1206       22194       0     254     653312        0
             tcpcb   1096       4     507          10       0     254     560056        0
        malloc-512    512    1026      30        1026       0      30     540672        0
            socket    960      20     488        1021       0     254     487680        0
       UMA Slabs 0    112    3698       4        3698       0     126     414624        0
            lkpimm    168       1    2327           1       0      62     391104        0
          lkpicurr    168       2    2326           2       0      62     391104        0
        RADIX NODE    144    1959     222       26516       0      62     314064        0
        256 Bucket   2048     123      23         345       0       8     299008        0
       malloc-2048   2048     131      13         131       0       8     294912        0
         malloc-64     64    3862     485        4072       0     254     278208        0
         VM OBJECT    264     964      56       13958       0      30     269280        0
      malloc-65536  65536       4       0           4       0       1     262144        0
             VNODE    448     512      64         542       0      30     258048        0
        malloc-256    256     814      56        1550       0      62     222720        0
         malloc-16     16   13520     230       14292       0     254     220000        0
            DEVCTL   1024       0     196          94       0       0     200704        0
            THREAD   1808      99      11          99       0       8     198880        0
      malloc-65536  65536       2       1          71       0       1     196608        0
         UMA Zones    768     226       3         226       0      16     175872        0
         malloc-32     32    4563     351        5183       0     254     157248        0
       FFS2 dinode    256     490      80         517       0      62     145920        0
      malloc-65536  65536       2       0           2       0       1     131072        0
      malloc-65536  65536       0       2          31       0       1     131072        0
             unpcb    256      12     498         939       0     254     130560        0
       mbuf_packet    256       0     508          70       0     254     130048        0
       S VFS Cache    104     973     197        1053       0     126     121680        0
         MAP ENTRY     96     846     414       41177       0     126     120960        0
          ksiginfo    112      34    1010          66       0     126     116928        0
        malloc-128    128     618     281        3197       0     126     115072        0
       malloc-1024   1024      97      15         109       0      16     114688        0
         FFS inode    192     490      77         517       0      62     108864        0
         vmem btag     56    1583     205        1583       0     254     100128        0
      malloc-32768  32768       3       0           3       0       1      98304        0
     FPU_save_area    832     101      16         112       0      16      97344        0
        128 Bucket   1024      42      41         214       0      16      84992        0
          UMA Kegs    384     212       1         212       0      30      81792        0
        malloc-128    128     293     234         795       0     126      67456        0
      malloc-65536  65536       1       0           1       0       1      65536        0
      malloc-65536  65536       1       0           1       0       1      65536        0
              PROC   1352      36      12         818       0       8      64896        0
           VMSPACE   2552      21       3         804       0       4      61248        0
         64 Bucket    512      65      39        1465       0      30      53248        0
         filedesc0   1072      37      12         819       0       8      52528        0
        malloc-128    128     228     175       28680       0     126      51584        0
        malloc-256    256     159      36         722       0      62      49920        0
         32 Bucket    256      53     142        2500       0      62      49920        0
             NAMEI   1024       1      47       12230       0      16      49152        0
       malloc-8192   8192       6       0          47       0       1      49152        0
           pcpu-64     64     457     311         457       0     254      49152        0
             g_bio    384       0     120        4639       0      30      46080        0
          syncache    168       0     264           5       0     254      44352        0
            clpbuf   2624       0      16          23       0      16      41984        0
       malloc-8192   8192       4       1           5       0       1      40960        0
       malloc-4096   4096       7       3           9       0       2      40960        0
         udp_inpcb    424       2      88          60       0      30      38160        0
         malloc-64     64      56     511         356       0     254      36288        0
         malloc-64     64     163     404        7661       0     254      36288        0
         malloc-64     64      83     484        8593       0     254      36288        0
         malloc-64     64      89     478        1711       0     254      36288        0
         malloc-64     64     281     286         286       0     254      36288        0
         malloc-64     64     170     397        1704       0     254      36288        0
         malloc-64     64      33     534          66       0     254      36288        0
        malloc-128    128      34     245         130       0     126      35712        0
        malloc-128    128     105     174         710       0     126      35712        0
        malloc-128    128      90     189         245       0     126      35712        0
        malloc-128    128      66     213          71       0     126      35712        0
     routing nhops    256       8     127          14       0      62      34560        0
        malloc-384    384      57      33          57       0      30      34560        0
        malloc-384    384      68      22         125       0      30      34560        0
        malloc-384    384      63      27          64       0      30      34560        0
        malloc-256    256      26     109          49       0      62      34560        0
        malloc-256    256       9     126         238       0      62      34560        0
        malloc-256    256      27     108         234       0      62      34560        0
        malloc-256    256       8     127           8       0      62      34560        0
        malloc-256    256      11     124         151       0      62      34560        0
        malloc-256    256      67      68         106       0      62      34560        0
           DIRHASH   1024      32       0          32       0      16      32768        0
      malloc-32768  32768       1       0           1       0       1      32768        0
      malloc-32768  32768       0       1           1       0       1      32768        0
      malloc-32768  32768       1       0           1       0       1      32768        0
      malloc-32768  32768       1       0          49       0       1      32768        0
      malloc-16384  16384       2       0           2       0       1      32768        0
       malloc-8192   8192       3       1           5       0       1      32768        0
       malloc-2048   2048       4      12           4       0       8      32768        0
       malloc-2048   2048       2      14          15       0       8      32768        0
       malloc-2048   2048       2      14           8       0       8      32768        0
       malloc-2048   2048       5      11           5       0       8      32768        0
       malloc-2048   2048       1      15         214       0       8      32768        0
       malloc-2048   2048       2      14          19       0       8      32768        0
       malloc-1024   1024       1      31           5       0      16      32768        0
       malloc-1024   1024      12      20          12       0      16      32768        0
       malloc-1024   1024       6      26          52       0      16      32768        0
       malloc-1024   1024      14      18          21       0      16      32768        0
       malloc-1024   1024       3      29         128       0      16      32768        0
       malloc-1024   1024       9      23           9       0      16      32768        0
       malloc-1024   1024       1      31         890       0      16      32768        0
        malloc-512    512       2      62         149       0      30      32768        0
        malloc-512    512       5      59          38       0      30      32768        0
        malloc-512    512       4      60           4       0      30      32768        0
        malloc-512    512       0      64           7       0      30      32768        0
            cpuset    104       7     272           7       0     126      29016        0
            pcpu-8      8    3319     265        3342       0     254      28672        0
          4 Bucket     48       5     583          52       0     254      28224        0
         tcp_inpcb    424       4      59          10       0      30      26712        0
              pipe    744       6      29         289       0      16      26040        0
         TURNSTILE    136     111      78         111       0      62      25704        0
       malloc-8192   8192       1       2          33       0       1      24576        0
       malloc-8192   8192       3       0           3       0       1      24576        0
       malloc-4096   4096       4       2           8       0       2      24576        0
       malloc-4096   4096       2       4         330       0       2      24576        0
           rtentry    176      11     127          14       0      62      24288        0
              PGRP     88      17     259          33       0     126      24288        0
    ertt_txseginfo     40       0     606         230       0     254      24240        0
          rl_entry     40      28     578          30       0     254      24240        0
             Files     80      78     222        6845       0     126      24000        0
          8 Bucket     80      33     267         116       0     126      24000        0
        malloc-384    384       7      53           9       0      30      23040        0
        malloc-384    384       1      59           3       0      30      23040        0
        SLEEPQUEUE     88     111     145         111       0     126      22528        0
         hostcache     64       1     314           1       0     254      20160        0
             udpcb     32       2     628          60       0     254      20160        0
   udp_inpcb ports     32       1     629           7       0     254      20160        0
              ertt     72       4     276          10       0     126      20160        0
               PWD     32      11     619          95       0     254      20160        0
         malloc-32     32      31     599         200       0     254      20160        0
         malloc-32     32      82     548         135       0     254      20160        0
         malloc-32     32      18     612          96       0     254      20160        0
         malloc-32     32      31     599          97       0     254      20160        0
         malloc-32     32      32     598         117       0     254      20160        0
         malloc-32     32     261     369        5360       0     254      20160        0
         malloc-32     32      18     612          41       0     254      20160        0
         16 Bucket    144      39     101         154       0      62      20160        0
          2 Bucket     32      47     583         270       0     254      20160        0
       Mountpoints   2752       2       5           2       0       4      19264        0
           ttyoutq    256       8      67          24       0      62      19200        0
 epoch_record pcpu    256       4      60           4       0      62      16384        0
      malloc-16384  16384       1       0           1       0       1      16384        0
      malloc-16384  16384       1       0           1       0       1      16384        0
      malloc-16384  16384       0       1          64       0       1      16384        0
      malloc-16384  16384       1       0           1       0       1      16384        0
       malloc-8192   8192       2       0           2       0       1      16384        0
       malloc-4096   4096       2       2           2       0       2      16384        0
       malloc-4096   4096       1       3           3       0       2      16384        0
       malloc-4096   4096       0       4           6       0       2      16384        0
       malloc-2048   2048       0       8          20       0       8      16384        0
        malloc-512    512       8      24           9       0      30      16384        0
           SMR CPU     32       7     504           7       0     254      16352        0
              kenv    258       2      58         707       0      30      15480        0
             ripcb    424       1      35           1       0      30      15264        0
              vmem   1856       1       7           1       0       8      14848        0
        SMR SHARED     24       7     504           7       0     254      12264        0
   tcp_inpcb ports     32       2     376           2       0     254      12096        0
            ttyinq    160      15      60          45       0      62      12000        0
         malloc-16     16      26     724        1327       0     254      12000        0
         malloc-16     16      15     735         208       0     254      12000        0
         malloc-16     16      29     721         168       0     254      12000        0
         malloc-16     16      21     729          31       0     254      12000        0
         malloc-16     16      12     738          17       0     254      12000        0
         malloc-16     16     268     482       27712       0     254      12000        0
         malloc-16     16       9     741          40       0     254      12000        0
       L VFS Cache    320       0      36           1       0      30      11520        0
        malloc-384    384      20      10         199       0      30      11520        0
        malloc-384    384       1      29           1       0      30      11520        0
       malloc-8192   8192       1       0           1       0       1       8192        0
       malloc-4096   4096       0       2           1       0       2       8192        0
      vtnet_tx_hdr     24       1     333        6854       0     254       8016        0
           pcpu-16     16       7     249           7       0     254       4096        0
       UMA Slabs 1    176       6      16           6       0      62       3872        0
        KMAP ENTRY     96      14      25          15       0       0       3744        0
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
tfo_ccache_entries     80       0       0           0       0     126          0        0
               tfo      4       0       0           0       0     254          0        0
          sackhole     32       0       0           0       0     254          0        0
             tcptw     72       0       0           0       0     254          0        0
               ipq     56       0       0           0       0     254          0        0
      tcp_log_node    120       0       0           0       0     126          0        0
    tcp_log_bucket    176       0       0           0       0      62          0        0
           tcp_log    416       0       0           0       0     254          0        0
          tcpreass     48       0       0           0       0     254          0        0
       ripcb ports     32       0       0           0       0     254          0        0
udplite_inpcb ports     32       0       0           0       0     254          0        0
     udplite_inpcb    424       0       0           0       0      30          0        0
    IPsec SA lft_c     16       0       0           0       0     254          0        0
             KNOTE    160       0       0           0       0      62          0        0
            itimer    352       0       0           0       0      30          0        0
            AIOLIO    272       0       0           0       0      30          0        0
             AIOCB    552       0       0           0       0      16          0        0
              AIOP     32       0       0           0       0     254          0        0
               AIO    208       0       0           0       0      62          0        0
        TMPFS node    224       0       0           0       0      62          0        0
           NCLNODE    608       0       0           0       0      16          0        0
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
      malloc-65536  65536       0       0           0       0       1          0        0
      malloc-32768  32768       0       0           0       0       1          0        0
      malloc-32768  32768       0       0           0       0       1          0        0
      malloc-32768  32768       0       0           0       0       1          0        0
      malloc-16384  16384       0       0           0       0       1          0        0
      malloc-16384  16384       0       0           0       0       1          0        0
      malloc-16384  16384       0       0           0       0       1          0        0
       malloc-8192   8192       0       0           0       0       1          0        0
        malloc-512    512       0       0           0       0      30          0        0
        malloc-512    512       0       0           0       0      30          0        0
        malloc-384    384       0       0           0       0      30          0        0
           pcpu-32     32       0       0           0       0     254          0        0
            pcpu-4      4       0       0           0       0     254          0        0
            fakepg    104       0       0           0       0     126          0        0
          UMA Hash    256       0       0           0       0      62          0        0


Syzkaller reproducer:
# {Threaded:false Repeat:true RepeatTimes:0 Procs:2 Slowdown:1 Sandbox: Leak:false NetInjection:false NetDevices:false NetReset:false Cgroups:false BinfmtMisc:false CloseFDs:false KCSAN:false DevlinkPCI:false USB:false VhciInjection:false Wifi:false IEEE802154:false Sysctl:false UseTmpDir:false HandleSegv:false Repro:false Trace:false LegacyOptions:{Collide:false Fault:false FaultCall:0 FaultNth:0}}
r0 = openat$filemon(0xffffffffffffff9c, &(0x7f0000000000), 0x0, 0x0)
r1 = setsid()
ioctl$FILEMON_SET_PID(r0, 0xc0045302, &(0x7f0000000100)=r1)
mkdirat(0xffffffffffffff9c, &(0x7f0000000040)='./file0\x00', 0x0)
r2 = open$dir(&(0x7f0000000080)='./file0\x00', 0x400000, 0x0)
mkdirat(r2, &(0x7f00000000c0)='./file0\x00', 0x0)
openat(r2, &(0x7f0000000100)='./file0\x00', 0x0, 0x0)


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
      if (current_time_ms() - start < 5000)
        continue;
      kill_and_wait(pid, &status);
      break;
    }
  }
}

uint64_t r[3] = {0xffffffffffffffff, 0x0, 0xffffffffffffffff};

void execute_one(void)
{
  intptr_t res = 0;
  memcpy((void*)0x20000000, "/dev/filemon\000", 13);
  res = syscall(SYS_openat, 0xffffffffffffff9cul, 0x20000000ul, 0ul, 0ul);
  if (res != -1)
    r[0] = res;
  res = syscall(SYS_setsid);
  if (res != -1)
    r[1] = res;
  *(uint32_t*)0x20000100 = r[1];
  syscall(SYS_ioctl, r[0], 0xc0045302ul, 0x20000100ul);
  memcpy((void*)0x20000040, "./file0\000", 8);
  syscall(SYS_mkdirat, 0xffffff9c, 0x20000040ul, 0ul);
  memcpy((void*)0x20000080, "./file0\000", 8);
  res = syscall(SYS_open, 0x20000080ul, 0x400000ul, 0ul);
  if (res != -1)
    r[2] = res;
  memcpy((void*)0x200000c0, "./file0\000", 8);
  syscall(SYS_mkdirat, r[2], 0x200000c0ul, 0ul);
  memcpy((void*)0x20000100, "./file0\000", 8);
  syscall(SYS_openat, r[2], 0x20000100ul, 0ul, 0ul);
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


