Syzkaller hit 'panic: lock ADDR is not initialized' bug.

login: panic: lock 0xfffffe00571adb38 is not initialized
cpuid = 0
time = 1643571568
KDB: stack backtrace:
db_trace_self_wrapper() at db_trace_self_wrapper+0xc7/frame 0xfffffe008e70e870
kdb_backtrace() at kdb_backtrace+0xd3/frame 0xfffffe008e70e9d0
vpanic() at vpanic+0x2b8/frame 0xfffffe008e70eab0
panic() at panic+0xb5/frame 0xfffffe008e70eb80
lock_destroy() at lock_destroy+0x7a/frame 0xfffffe008e70ebb0
pf_krule_free() at pf_krule_free+0xe8/frame 0xfffffe008e70ebd0
pfioctl() at pfioctl+0xc146/frame 0xfffffe008e710650
devfs_ioctl() at devfs_ioctl+0x22a/frame 0xfffffe008e710730
vn_ioctl() at vn_ioctl+0x215/frame 0xfffffe008e710a80
devfs_ioctl_f() at devfs_ioctl_f+0x71/frame 0xfffffe008e710ad0
kern_ioctl() at kern_ioctl+0x62e/frame 0xfffffe008e710bd0
sys_ioctl() at sys_ioctl+0x3b6/frame 0xfffffe008e710d50
amd64_syscall() at amd64_syscall+0x3dc/frame 0xfffffe008e710f30
fast_syscall_common() at fast_syscall_common+0xf8/frame 0xfffffe008e710f30
--- syscall (0, FreeBSD ELF64, nosys), rip = 0x23390a, rsp = 0x8207b7b48, rbp = 0x8207b7b90 ---
KDB: enter: panic
[ thread pid 818 tid 100101 ]
Stopped at      kdb_enter+0x6b: movq    $0,0x28f10ca(%rip)
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
rcx         0xcd71490d713c1146
rdx         0xdffff7c000000000
rbx                          0
rsp         0xfffffe008e70e9b0
rbp         0xfffffe008e70e9d0
rsi                        0x1
rdi                          0
r8                         0x3
r9          0xfffffe008e70e4e8
r10                          0
r11         0xfffffe0090443510
r12         0xfffffe0090443000
r13         0xfffffe008e70ea01
r14         0xffffffff82c2a740  .str.18
r15         0xffffffff82c2a740  .str.18
rip         0xffffffff81778deb  kdb_enter+0x6b
rflags                    0x46
kdb_enter+0x6b: movq    $0,0x28f10ca(%rip)
db> show proc
Process 818 (syz-executor8288024) at 0xfffffe009009d548:
 state: NORMAL
 uid: 0  gids: 0, 0, 5
 parent: pid 816 at 0xfffffe00542c7000
 ABI: FreeBSD ELF64
 flag: 0x10000000  flag2: 0
 arguments: /root/syz-executor828802449
 reaper: 0xfffffe0053dd7000 reapsubtree: 1
 sigparent: 20
 vmspace: 0xfffffe0053dea9f8
   (map 0xfffffe0053dea9f8)
   (map.pmap 0xfffffe0053deaab8)
   (pmap 0xfffffe0053deab20)
 threads: 1
100101                   Run     CPU 0                       syz-executor8288024
db> ps
  pid  ppid  pgrp   uid  state   wmesg   wchan               cmd
  818   816   814     0  R       CPU 0                       syz-executor8288024
  816   814   814     0  S       nanslp  0xffffffff84036dc1  syz-executor8288024
  814   812   814     0  Ss      pause   0xfffffe009009db40  csh
  812   729   812     0  Rs      CPU 1                       sshd
  801     1   801     0  Ss+     ttyin   0xfffffe0056ce3cb0  getty
  795     1   795     0  Ss      select  0xfffffe005428bd40  logger
  788     1     9     0  S+      piperd  0xfffffe007437a8b8  logger
  787   786     9     0  S+      nanslp  0xffffffff84036dc1  sleep
  786     1     9     0  S+      wait    0xfffffe008fe6f548  sh
  782     1   782    25  Ss      pause   0xfffffe008fe6bb40  sendmail
  779     1   779     0  Ss      select  0xfffffe005428b7c0  sendmail
  733     1   733     0  Ss      nanslp  0xffffffff84036dc0  cron
  729     1   729     0  Ss      select  0xfffffe005428b740  sshd
  640     1   640     0  Ss      select  0xfffffe005428ba40  syslogd
  443     1   443     0  Ss      select  0xfffffe005428b8c0  devd
  346     1   346    65  Ss      select  0xfffffe005428b840  dhclient
  264     1   264     0  Ss      select  0xfffffe005428b9c0  dhclient
  261     1   261     0  Ss      select  0xfffffe005428c340  dhclient
   89     0     0     0  DL      pftm    0xffffffff8491e570  [pf purge]
   19     0     0     0  DL      syncer  0xffffffff8415f1a0  [syncer]
   18     0     0     0  DL      vlruwt  0xfffffe00542c7a90  [vnlru]
    8     0     0     0  DL      (threaded)                  [bufdaemon]
100064                   D       psleep  0xffffffff8415cea0  [bufdaemon]
100067                   D       -       0xffffffff83411f80  [bufspacedaemon-0]
100078                   D       sdflush 0xfffffe00542fb0e8  [/ worker]
    7     0     0     0  DL      psleep  0xffffffff841924c0  [vmdaemon]
    6     0     0     0  DL      (threaded)                  [pagedaemon]
100062                   D       psleep  0xffffffff84185fb8  [dom0]
100065                   D       launds  0xffffffff84185fc4  [laundry: dom0]
100066                   D       umarcl  0xffffffff81e79420  [uma]
    5     0     0     0  DL      -       0xffffffff83ded068  [rand_harvestq]
    4     0     0     0  DL      (threaded)                  [cam]
100043                   D       -       0xffffffff83c89c40  [doneq0]
100044                   D       -       0xffffffff83c89bc0  [async]
100061                   D       -       0xffffffff83c89a40  [scanner]
   14     0     0     0  DL      seqstat 0xfffffe005420e888  [sequencer 00]
    3     0     0     0  DL      (threaded)                  [crypto]
100039                   D       crypto_ 0xffffffff841800e0  [crypto]
100040                   D       crypto_ 0xfffffe0053f87030  [crypto returns 0]
100041                   D       crypto_ 0xfffffe0053f87080  [crypto returns 1]
   13     0     0     0  DL      (threaded)                  [geom]
100034                   D       -       0xffffffff84009ee0  [g_event]
100035                   D       -       0xffffffff84009f20  [g_up]
100036                   D       -       0xffffffff84009f60  [g_down]
    2     0     0     0  WL      (threaded)                  [clock]
100030                   I                                   [clock (0)]
100031                   I                                   [clock (1)]
   12     0     0     0  WL      (threaded)                  [intr]
100010                   I                                   [swi6: Giant taskq]
100015                   I                                   [swi5: fast taskq]
100020                   I                                   [swi6: task queue]
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
100079                   I                                   [swi1: pf send]
   11     0     0     0  RL      (threaded)                  [idle]
100003                   CanRun                              [idle: cpu0]
100004                   CanRun                              [idle: cpu1]
    1     0     1     0  SLs     wait    0xfffffe0053dd7000  [init]
   10     0     0     0  DL      audit_w 0xffffffff84181080  [audit]
    0     0     0     0  DLs     (threaded)                  [kernel]
100000                   D       swapin  0xffffffff8400ade0  [swapper]
100005                   D       -       0xfffffe000817c000  [if_io_tqg_0]
100006                   D       -       0xfffffe000817be00  [if_io_tqg_1]
100007                   D       -       0xfffffe000817bd00  [if_config_tqg_0]
100008                   D       -       0xfffffe000817bc00  [softirq_0]
100009                   D       -       0xfffffe000817bb00  [softirq_1]
100011                   D       -       0xfffffe000817b900  [aiod_kick taskq]
100012                   D       -       0xfffffe000817b800  [inm_free taskq]
100013                   D       -       0xfffffe000817b700  [deferred_unmount ta]
100014                   D       -       0xfffffe000817b600  [thread taskq]
100016                   D       -       0xfffffe000817b400  [kqueue_ctx taskq]
100017                   D       -       0xfffffe000817b300  [linuxkpi_irq_wq]
100018                   D       -       0xfffffe000817b200  [pci_hp taskq]
100019                   D       -       0xfffffe000817b100  [in6m_free taskq]
100021                   D       -       0xfffffe000817ae00  [linuxkpi_short_wq_0]
100022                   D       -       0xfffffe000817ae00  [linuxkpi_short_wq_1]
100023                   D       -       0xfffffe000817ae00  [linuxkpi_short_wq_2]
100024                   D       -       0xfffffe000817ae00  [linuxkpi_short_wq_3]
100025                   D       -       0xfffffe000817ad00  [linuxkpi_long_wq_0]
100026                   D       -       0xfffffe000817ad00  [linuxkpi_long_wq_1]
100027                   D       -       0xfffffe000817ad00  [linuxkpi_long_wq_2]
100028                   D       -       0xfffffe000817ad00  [linuxkpi_long_wq_3]
100033                   D       -       0xfffffe000817ac00  [firmware taskq]
100037                   D       -       0xfffffe000817a100  [crypto_0]
100038                   D       -       0xfffffe000817a100  [crypto_1]
100048                   D       -       0xfffffe000817a800  [vtnet0 rxq 0]
100049                   D       -       0xfffffe000817a900  [vtnet0 txq 0]
100055                   D       -       0xffffffff82c31680  [deadlkres]
100057                   D       -       0xfffffe0056c89900  [acpi_task_0]
100058                   D       -       0xfffffe0056c89900  [acpi_task_1]
100059                   D       -       0xfffffe0056c89900  [acpi_task_2]
100060                   D       -       0xfffffe0008179900  [CAM taskq]
db> show all locks
Process 812 (sshd) thread 0xfffffe008fe77020 (100098)
exclusive rw tcpinp (tcpinp) r = 0 (0xfffffe008ffea010) locked @ /root/freebsd/sys/netinet/tcp_usrreq.c:1007
exclusive sx so_snd_sx (so_snd_sx) r = 0 (0xfffffe00743c4140) locked @ /root/freebsd/sys/kern/uipc_socket.c:4176
db> show malloc
              Type        InUse        MemUse     Requests
           pf_hash            5        11524K            5
         sysctloid        31631         1861K        31673
              kobj          319         1276K          479
            newblk          734         1208K          769
            linker          234         1207K          247
            devbuf         1356         1134K         1373
          vfscache            3         1025K            3
          inodedep           63          536K           99
         ufs_quota            1          512K            1
          vfs_hash            1          512K            1
           callout            2          512K            2
              intr            4          472K            4
               pcb           13          393K           23
         vnet_data            1          168K            1
           subproc           84          159K          868
           tidhash            3          141K            3
           pagedep           22          134K           33
        tfo_ccache            1          128K            1
               sem            4          106K            4
            DEVFS1           91           91K          103
               bus          950           77K         2542
            bus-sc           31           76K         1046
              vmem            3           74K            4
          mtx_pool            2           72K            2
          syncache            1           68K            1
          acpitask            1           64K            1
       ddb_capture            1           64K            1
            module          487           61K          487
            acpica          420           39K        63467
               LRO            2           33K            2
         hostcache            1           32K            1
               shm            1           32K            1
              umtx          242           31K          242
               msg            4           30K            4
           kdtrace          137           28K          921
            DEVFS3          110           28K          126
        gtaskqueue           18           26K           18
            kbdmux            5           22K            5
        DEVFS_RULE           59           21K           59
               BPF           10           18K           10
           ithread           98           18K           98
              temp           15           17K         1519
         ufs_mount            4           17K            5
              proc            3           17K            3
            KTRACE          100           13K          100
           devstat            6           13K            6
              rman          102           12K          526
            ifaddr           29           11K           30
      eventhandler          122           11K          122
              GEOM           61           10K          508
              kenv           59           10K           59
          routetbl           44           10K          142
         bmsafemap            2            9K           92
              UART           12            9K           12
               rpc            2            8K            2
             shmfd            1            8K            1
       pfs_vncache            1            8K            1
              cred           30            8K          290
         pfs_nodes           20            8K           20
     audit_evclass          237            8K          296
         taskqueue           56            6K           56
            diradd           46            6K          107
            sglist            3            6K            3
       ufs_dirhash           24            5K           24
               UMA          254            5K          254
             ifnet            3            5K            3
           pf_rule            2            4K            2
           io_apic            1            4K            1
               tty            4            4K            4
          ioctlops            1            4K           79
             evdev            4            4K            4
          filedesc            1            4K            1
             hhook           15            4K           17
          pf_ifnet            5            3K            6
           lltable           10            3K           10
            plimit           11            3K          228
           acpisem           21            3K           21
           uidinfo            4            3K            9
             lockf           21            3K           32
            kqueue           35            3K          819
           pwddesc           35            3K          819
        local_apic            1            2K            1
       fpukern_ctx            2            2K            2
         ipsec-saq            2            2K            2
           CAM DEV            1            2K            2
           session           15            2K           31
         proc-args           53            2K         1757
               msi           13            2K           13
             selfd           26            2K        11990
          pci_link           16            2K           16
            Unitno           25            2K           45
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
            dirrem            2            1K           46
          in_multi            2            1K            3
              pfil            4            1K            4
              cdev            2            1K            2
 encap_export_host            8            1K            8
               osd            8            1K           20
            ip6ndp            3            1K            3
    chacha20random            1            1K            1
        CAM periph            2            1K           14
            DEVFSP            5            1K           22
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
          freework            1            1K           26
     CAM dev queue            1            1K            1
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
         ciss_data            0            0K            0
         BACKLIGHT            0            0K            0
     vm_fictitious            0            0K            0
               xnb            0            0K            0
              xbbd            0            0K            0
               xbd            0            0K            0
           Balloon            0            0K            0
          sysmouse            0            0K            0
            vtfont            0            0K            0
                vt            0            0K            0
             vtbuf            0            0K            0
           ath_hal            0            0K            0
            athdev            0            0K            0
           ata_pci            0            0K            0
           UMAHash            0            0K            0
           ata_dma            0            0K            0
       ata_generic            0            0K            0
         vm_pgdata            0            0K            0
           jblocks            0            0K            0
          savedino            0            0K           24
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
           scsi_da            0            0K            0
            pvscsi            0            0K            0
            ata_da            0            0K            0
           scsi_ch            0            0K            0
           scsi_cd            0            0K            0
       AHCI driver            0            0K            0
               agp            0            0K            0
            USBdev            0            0K            0
               USB            0            0K            0
           nvme_da            0            0K            0
          ktls_ocf            0            0K            0
 CAM I/O Scheduler            0            0K            0
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
           acpipwr            0            0K            0
            statfs            0            0K         1092
     namei_tracker            0            0K            2
       export_host            0            0K            0
        cl_savebuf            0            0K            6
         acpi_perf            0            0K            0
         acpicmbat            0            0K            0
            twsbuf            0            0K            0
      twe_commands            0            0K            0
       tcp_log_dev            0            0K            0
      midi buffers            0            0K            0
             mixer            0            0K            0
              ac97            0            0K            0
             hdacc            0            0K            0
              hdac            0            0K            0
              hdaa            0            0K            0
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
               iov            0            0K         7886
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
db> show uma
              Zone   Size    Used    Free    Requests  Sleeps  Bucket  Total Mem    XFree
   mbuf_jumbo_page   4096    1088    1198       16932       0     254    9363456        0
              pbuf   2624       0     778           0       0       2    2041472        0
          BUF TRIE    144     184   11632         522       0      62    1701504        0
        malloc-128    128   10473     129       10539       0     126    1357056        0
       malloc-4096   4096     319       1         480       0       2    1310720        0
      mbuf_cluster   2048     508       0         508       0     254    1040384        0
              mbuf    256    1348    1204       26265       0     254     653312        0
             tcpcb   1096       4     507          10       0     254     560056        0
        malloc-512    512    1035      45        1207       0      30     552960        0
            socket    960      20     488        1013       0     254     487680        0
      malloc-65536  65536       6       1          75       0       1     458752        0
         vmem btag     56    7774     113        7774       0     254     441672        0
        RADIX NODE    144    2520     471       28181       0      62     430704        0
       UMA Slabs 0    112    3541      17        3541       0     126     398496        0
            lkpimm    168       1    2327           1       0      62     391104        0
          lkpicurr    168       2    2326           2       0      62     391104        0
        256 Bucket   2048     122      24         635       0       8     299008        0
       malloc-2048   2048     132      12         165       0       8     294912        0
         VM OBJECT    264     987      63       14024       0      30     277200        0
        malloc-256    256     966      99        1718       0      62     272640        0
             VNODE    448     524      79         554       0      30     270144        0
         malloc-64     64    3639     456        4434       0     254     262080        0
            THREAD   1808     101      20         101       0       8     218768        0
         malloc-16     16   13333     167       13379       0     254     216000        0
            DEVCTL   1024       0     192          93       0       0     196608        0
         UMA Zones    768     226       3         226       0      16     175872        0
       FFS2 dinode    256     502     128         529       0      62     161280        0
         malloc-32     32    4535     379        4642       0     254     157248        0
       malloc-4096   4096      36       2         820       0       2     155648        0
      malloc-65536  65536       2       0           2       0       1     131072        0
      malloc-65536  65536       2       0           2       0       1     131072        0
      malloc-65536  65536       2       0           2       0       1     131072        0
      malloc-65536  65536       0       2          31       0       1     131072        0
             unpcb    256      12     498         931       0     254     130560        0
       mbuf_packet    256       0     508          90       0     254     130048        0
       S VFS Cache    104     997     173        1077       0     126     121680        0
         FFS inode    192     502     128         529       0      62     120960        0
         MAP ENTRY     96     864     396       41715       0     126     120960        0
          ksiginfo    112      36    1008          67       0     126     116928        0
       malloc-1024   1024     101      11         292       0      16     114688        0
     FPU_save_area    832     103      32         117       0      16     112320        0
          syncache    168       0     528           5       0     254      88704        0
        128 Bucket   1024      39      44         205       0      16      84992        0
            clpbuf   2624       0      32          31       0      16      83968        0
        malloc-128    128     517     134        3080       0     126      83328        0
          UMA Kegs    384     212       1         212       0      30      81792        0
       malloc-8192   8192       7       2          80       0       1      73728        0
        malloc-128    128     337     190         522       0     126      67456        0
      malloc-65536  65536       1       0           1       0       1      65536        0
      malloc-32768  32768       2       0           2       0       1      65536        0
      malloc-32768  32768       2       0           2       0       1      65536        0
              PROC   1352      34      14         818       0       8      64896        0
           VMSPACE   2552      19       5         804       0       4      61248        0
         64 Bucket    512      63      41        1598       0      30      53248        0
         filedesc0   1072      35      14         819       0       8      52528        0
         malloc-64     64     653     166         944       0     254      52416        0
         malloc-64     64     257     562        3388       0     254      52416        0
        malloc-128    128     257     146       28946       0     126      51584        0
        malloc-128    128     251     152         749       0     126      51584        0
        malloc-256    256     107      88         307       0      62      49920        0
         32 Bucket    256      54     141        4789       0      62      49920        0
           DIRHASH   1024      32      16          32       0      16      49152        0
             NAMEI   1024       0      48       12405       0      16      49152        0
       malloc-1024   1024      19      29          22       0      16      49152        0
       malloc-8192   8192       3       2           5       0       1      40960        0
         udp_inpcb    424       2      88          60       0      30      38160        0
         malloc-64     64      18     549        7866       0     254      36288        0
         malloc-64     64     112     455         145       0     254      36288        0
         malloc-64     64      35     532       12021       0     254      36288        0
         malloc-64     64       3     564           6       0     254      36288        0
         malloc-64     64       4     563          37       0     254      36288        0
        malloc-128    128     152     127         753       0     126      35712        0
        malloc-128    128     136     143         216       0     126      35712        0
     routing nhops    256       8     127          14       0      62      34560        0
             g_bio    384       0      90        4622       0      30      34560        0
           ttyoutq    256       8     127          24       0      62      34560        0
        malloc-384    384      49      41          51       0      30      34560        0
        malloc-384    384      81       9         260       0      30      34560        0
        malloc-384    384      62      28          98       0      30      34560        0
        malloc-256    256      13     122         265       0      62      34560        0
        malloc-256    256       7     128          13       0      62      34560        0
        malloc-256    256      60      75         607       0      62      34560        0
        malloc-256    256       2     133           5       0      62      34560        0
        malloc-256    256      61      74         196       0      62      34560        0
        malloc-256    256       6     129          44       0      62      34560        0
      malloc-32768  32768       0       1           1       0       1      32768        0
      malloc-32768  32768       0       1          48       0       1      32768        0
      malloc-32768  32768       1       0           1       0       1      32768        0
      malloc-16384  16384       2       0           2       0       1      32768        0
       malloc-8192   8192       4       0           4       0       1      32768        0
       malloc-4096   4096       7       1           7       0       2      32768        0
       malloc-4096   4096       6       2          11       0       2      32768        0
       malloc-2048   2048       4      12           4       0       8      32768        0
       malloc-2048   2048       4      12          10       0       8      32768        0
       malloc-2048   2048       4      12         217       0       8      32768        0
       malloc-2048   2048       1      15          18       0       8      32768        0
       malloc-1024   1024       8      24          12       0      16      32768        0
       malloc-1024   1024       3      29           3       0      16      32768        0
       malloc-1024   1024       7      25           7       0      16      32768        0
       malloc-1024   1024       0      32         858       0      16      32768        0
        malloc-512    512       3      61           9       0      30      32768        0
        malloc-512    512       2      62           9       0      30      32768        0
           pcpu-64     64     456      56         456       0     254      32768        0
            cpuset    104       7     272           7       0     126      29016        0
            pcpu-8      8    3327     257        3358       0     254      28672        0
         malloc-32     32     257     625        5332       0     254      28224        0
          4 Bucket     48       5     583          47       0     254      28224        0
         tcp_inpcb    424       4      59          10       0      30      26712        0
              pipe    744       7      28         297       0      16      26040        0
         TURNSTILE    136     122      67         122       0      62      25704        0
       malloc-8192   8192       3       0           3       0       1      24576        0
       malloc-8192   8192       3       0           3       0       1      24576        0
       malloc-4096   4096       2       4         320       0       2      24576        0
           rtentry    176      11     127          14       0      62      24288        0
              PGRP     88      15     261          31       0     126      24288        0
    ertt_txseginfo     40       1     605         307       0     254      24240        0
          rl_entry     40      29     577          31       0     254      24240        0
             Files     80      80     220        7008       0     126      24000        0
          8 Bucket     80      28     272         198       0     126      24000        0
        malloc-384    384       6      54           7       0      30      23040        0
        malloc-384    384       4      56          12       0      30      23040        0
        malloc-384    384       0      60          14       0      30      23040        0
        SLEEPQUEUE     88     122     134         122       0     126      22528        0
         hostcache     64       1     314           1       0     254      20160        0
             udpcb     32       2     628          60       0     254      20160        0
   tcp_inpcb ports     32       2     628           2       0     254      20160        0
   udp_inpcb ports     32       1     629           7       0     254      20160        0
              ertt     72       4     276          10       0     126      20160        0
               PWD     32      11     619          95       0     254      20160        0
         malloc-32     32      34     596         275       0     254      20160        0
         malloc-32     32      60     570         105       0     254      20160        0
         malloc-32     32     107     523         768       0     254      20160        0
         malloc-32     32      22     608          34       0     254      20160        0
         malloc-32     32       6     624           8       0     254      20160        0
         malloc-32     32      13     617          66       0     254      20160        0
         16 Bucket    144      38     102         169       0      62      20160        0
          2 Bucket     32      45     585         271       0     254      20160        0
            ttyinq    160      15     110          45       0      62      20000        0
       Mountpoints   2752       2       5           2       0       4      19264        0
 epoch_record pcpu    256       4      60           4       0      62      16384        0
      malloc-16384  16384       0       1          64       0       1      16384        0
      malloc-16384  16384       1       0           1       0       1      16384        0
       malloc-4096   4096       1       3           4       0       2      16384        0
       malloc-4096   4096       0       4        1092       0       2      16384        0
       malloc-4096   4096       3       1           4       0       2      16384        0
       malloc-2048   2048       2       6           2       0       8      16384        0
       malloc-2048   2048       1       7           1       0       8      16384        0
       malloc-1024   1024       1      15           1       0      16      16384        0
       malloc-1024   1024       2      14           2       0      16      16384        0
        malloc-512    512       0      32           1       0      30      16384        0
        malloc-512    512       1      31           3       0      30      16384        0
        malloc-512    512       2      30           2       0      30      16384        0
           SMR CPU     32       7     504           7       0     254      16352        0
               ipq     56       0     288           3       0     254      16128        0
         malloc-16     16     475     525        1292       0     254      16000        0
              kenv    258       2      58         707       0      30      15480        0
             ripcb    424       1      35           1       0      30      15264        0
              vmem   1856       1       7           1       0       8      14848        0
        SMR SHARED     24       7     504           7       0     254      12264        0
         malloc-16     16      18     732        1469       0     254      12000        0
         malloc-16     16      23     727         147       0     254      12000        0
         malloc-16     16       7     743           8       0     254      12000        0
         malloc-16     16      34     716       27661       0     254      12000        0
         malloc-16     16       1     749           2       0     254      12000        0
         malloc-16     16       8     742          36       0     254      12000        0
       L VFS Cache    320       0      36           1       0      30      11520        0
        malloc-384    384       1      29           1       0      30      11520        0
        malloc-384    384       9      21           9       0      30      11520        0
       malloc-8192   8192       1       0           1       0       1       8192        0
      vtnet_tx_hdr     24       1     333        8259       0     254       8016        0
           pcpu-16     16       7     249           7       0     254       4096        0
       UMA Slabs 1    176       6      16           6       0      62       3872        0
        KMAP ENTRY     96      12      27          15       0       0       3744        0
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
tfo_ccache_entries     80       0       0           0       0     126          0        0
               tfo      4       0       0           0       0     254          0        0
          sackhole     32       0       0           0       0     254          0        0
             tcptw     72       0       0           0       0     254          0        0
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
           NCLNODE    608       0       0           0       0      16          0        0
        TMPFS node    224       0       0           0       0      62          0        0
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
      malloc-16384  16384       0       0           0       0       1          0        0
      malloc-16384  16384       0       0           0       0       1          0        0
       malloc-8192   8192       0       0           0       0       1          0        0
       malloc-8192   8192       0       0           0       0       1          0        0
       malloc-2048   2048       0       0           0       0       8          0        0
        malloc-512    512       0       0           0       0      30          0        0
        malloc-512    512       0       0           0       0      30          0        0
        malloc-128    128       0       0           0       0     126          0        0
           pcpu-32     32       0       0           0       0     254          0        0
            pcpu-4      4       0       0           0       0     254          0        0
            fakepg    104       0       0           0       0     126          0        0
          UMA Hash    256       0       0           0       0      62          0        0


Syzkaller reproducer:
# {Threaded:false Collide:false Repeat:true RepeatTimes:0 Procs:1 Slowdown:1 Sandbox: Leak:false NetInjection:false NetDevices:false NetReset:false Cgroups:false BinfmtMisc:false CloseFDs:false KCSAN:false DevlinkPCI:false USB:false VhciInjection:false Wifi:false IEEE802154:false Sysctl:false UseTmpDir:false HandleSegv:false Repro:false Trace:false LegacyOptions:{Fault:false FaultCall:0 FaultNth:0}}
r0 = openat$ptmx(0xffffffffffffff9c, &(0x7f0000000100), 0x1, 0x0)
ioctl$MDIOCQUERY(0xffffffffffffffff, 0xc1c06d02, &(0x7f0000000140)={0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0})
ioctl$DIOCCHANGERULE(r0, 0xcbe0441a, &(0x7f0000000140))


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
      if (current_time_ms() - start < 5000)
        continue;
      kill_and_wait(pid, &status);
      break;
    }
  }
}

uint64_t r[1] = {0xffffffffffffffff};

void execute_one(void)
{
  intptr_t res = 0;
  memcpy((void*)0x20000100, "/dev/pf\000", 8);
  res = syscall(SYS_openat, 0xffffffffffffff9cul, 0x20000100ul, 1ul, 0ul);
  if (res != -1)
    r[0] = res;
  *(uint32_t*)0x20000140 = 1;
  *(uint32_t*)0x20000144 = 0;
  *(uint32_t*)0x20000148 = 0;
  *(uint64_t*)0x20000150 = 0;
  *(uint64_t*)0x20000158 = 0;
  *(uint32_t*)0x20000160 = 0;
  *(uint32_t*)0x20000164 = 0;
  *(uint64_t*)0x20000168 = 0;
  *(uint32_t*)0x20000170 = 0;
  *(uint32_t*)0x20000174 = 0;
  *(uint64_t*)0x20000178 = 0;
  *(uint32_t*)0x20000180 = 0;
  *(uint32_t*)0x20000184 = 0;
  *(uint32_t*)0x20000188 = 0;
  *(uint32_t*)0x2000018c = 0;
  *(uint32_t*)0x20000190 = 0;
  *(uint32_t*)0x20000194 = 0;
  *(uint32_t*)0x20000198 = 0;
  *(uint32_t*)0x2000019c = 0;
  *(uint32_t*)0x200001a0 = 0;
  *(uint32_t*)0x200001a4 = 0;
  *(uint32_t*)0x200001a8 = 0;
  *(uint32_t*)0x200001ac = 0;
  *(uint32_t*)0x200001b0 = 0;
  *(uint32_t*)0x200001b4 = 0;
  *(uint32_t*)0x200001b8 = 0;
  *(uint32_t*)0x200001bc = 0;
  *(uint32_t*)0x200001c0 = 0;
  *(uint32_t*)0x200001c4 = 0;
  *(uint32_t*)0x200001c8 = 0;
  *(uint32_t*)0x200001cc = 0;
  *(uint32_t*)0x200001d0 = 0;
  *(uint32_t*)0x200001d4 = 0;
  *(uint32_t*)0x200001d8 = 0;
  *(uint32_t*)0x200001dc = 0;
  *(uint32_t*)0x200001e0 = 0;
  *(uint32_t*)0x200001e4 = 0;
  *(uint32_t*)0x200001e8 = 0;
  *(uint32_t*)0x200001ec = 0;
  *(uint32_t*)0x200001f0 = 0;
  *(uint32_t*)0x200001f4 = 0;
  *(uint32_t*)0x200001f8 = 0;
  *(uint32_t*)0x200001fc = 0;
  *(uint32_t*)0x20000200 = 0;
  *(uint32_t*)0x20000204 = 0;
  *(uint32_t*)0x20000208 = 0;
  *(uint32_t*)0x2000020c = 0;
  *(uint32_t*)0x20000210 = 0;
  *(uint32_t*)0x20000214 = 0;
  *(uint32_t*)0x20000218 = 0;
  *(uint32_t*)0x2000021c = 0;
  *(uint32_t*)0x20000220 = 0;
  *(uint32_t*)0x20000224 = 0;
  *(uint32_t*)0x20000228 = 0;
  *(uint32_t*)0x2000022c = 0;
  *(uint32_t*)0x20000230 = 0;
  *(uint32_t*)0x20000234 = 0;
  *(uint32_t*)0x20000238 = 0;
  *(uint32_t*)0x2000023c = 0;
  *(uint32_t*)0x20000240 = 0;
  *(uint32_t*)0x20000244 = 0;
  *(uint32_t*)0x20000248 = 0;
  *(uint32_t*)0x2000024c = 0;
  *(uint32_t*)0x20000250 = 0;
  *(uint32_t*)0x20000254 = 0;
  *(uint32_t*)0x20000258 = 0;
  *(uint32_t*)0x2000025c = 0;
  *(uint32_t*)0x20000260 = 0;
  *(uint32_t*)0x20000264 = 0;
  *(uint32_t*)0x20000268 = 0;
  *(uint32_t*)0x2000026c = 0;
  *(uint32_t*)0x20000270 = 0;
  *(uint32_t*)0x20000274 = 0;
  *(uint32_t*)0x20000278 = 0;
  *(uint32_t*)0x2000027c = 0;
  *(uint32_t*)0x20000280 = 0;
  *(uint32_t*)0x20000284 = 0;
  *(uint32_t*)0x20000288 = 0;
  *(uint32_t*)0x2000028c = 0;
  *(uint32_t*)0x20000290 = 0;
  *(uint32_t*)0x20000294 = 0;
  *(uint32_t*)0x20000298 = 0;
  *(uint32_t*)0x2000029c = 0;
  *(uint32_t*)0x200002a0 = 0;
  *(uint32_t*)0x200002a4 = 0;
  *(uint32_t*)0x200002a8 = 0;
  *(uint32_t*)0x200002ac = 0;
  *(uint32_t*)0x200002b0 = 0;
  *(uint32_t*)0x200002b4 = 0;
  *(uint32_t*)0x200002b8 = 0;
  *(uint32_t*)0x200002bc = 0;
  *(uint32_t*)0x200002c0 = 0;
  *(uint32_t*)0x200002c4 = 0;
  *(uint32_t*)0x200002c8 = 0;
  *(uint32_t*)0x200002cc = 0;
  *(uint32_t*)0x200002d0 = 0;
  *(uint32_t*)0x200002d4 = 0;
  *(uint32_t*)0x200002d8 = 0;
  *(uint32_t*)0x200002dc = 0;
  *(uint32_t*)0x200002e0 = 0;
  *(uint32_t*)0x200002e4 = 0;
  *(uint32_t*)0x200002e8 = 0;
  *(uint32_t*)0x200002ec = 0;
  *(uint32_t*)0x200002f0 = 0;
  *(uint32_t*)0x200002f4 = 0;
  *(uint32_t*)0x200002f8 = 0;
  *(uint32_t*)0x200002fc = 0;
  syscall(SYS_ioctl, -1, 0xc1c06d02ul, 0x20000140ul);
  syscall(SYS_ioctl, r[0], 0xcbe0441aul, 0x20000140ul);
}
int main(void)
{
  syscall(SYS_mmap, 0x20000000ul, 0x1000000ul, 7ul, 0x1012ul, -1, 0ul);
  loop();
  return 0;
}


