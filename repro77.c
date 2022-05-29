Syzkaller hit 'panic: kernel_mount NULL ma->v' bug.

login: panic: kernel_mount NULL ma->v
cpuid = 1
time = 1653740203
KDB: stack backtrace:
db_trace_self_wrapper() at db_trace_self_wrapper+0xc7/frame 0xfffffe008e7855b0
kdb_backtrace() at kdb_backtrace+0xd3/frame 0xfffffe008e785710
vpanic() at vpanic+0x2b8/frame 0xfffffe008e7857f0
panic() at panic+0xb5/frame 0xfffffe008e7858b0
kernel_mount() at kernel_mount+0x27c/frame 0xfffffe008e7859b0
msdosfs_cmount() at msdosfs_cmount+0x369/frame 0xfffffe008e785c70
sys_mount() at sys_mount+0x3b5/frame 0xfffffe008e785d50
amd64_syscall() at amd64_syscall+0x3d6/frame 0xfffffe008e785f30
fast_syscall_common() at fast_syscall_common+0xf8/frame 0xfffffe008e785f30
--- syscall (0, FreeBSD ELF64, nosys), rip = 0x23392a, rsp = 0x8240c3f88, rbp = 0x8240c3fc0 ---
KDB: enter: panic
[ thread pid 7532 tid 113532 ]
Stopped at      kdb_enter+0x6b: movq    $0,0x26fa89a(%rip)
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
rcx         0xbfa17c0037d15680
rdx         0xdffff7c000000000
rbx                          0
rsp         0xfffffe008e7856f0
rbp         0xfffffe008e785710
rsi                        0x1
rdi                          0
r8                         0x3
r9                  0xffffffff
r10                          0
r11         0xfffffe0090566fd0
r12         0xfffffe0090566ac0
r13         0xfffffe008e785701
r14         0xffffffff82b99700  .str.26
r15         0xffffffff82b99700  .str.26
rip         0xffffffff8176c2fb  kdb_enter+0x6b
rflags                    0x46
kdb_enter+0x6b: movq    $0,0x26fa89a(%rip)
db> show proc
Process 7532 (syz-executor1430153) at 0xfffffe0072996548:
 state: NORMAL
 uid: 0  gids: 0, 0, 5
 parent: pid 816 at 0xfffffe0090435000
 ABI: FreeBSD ELF64
 flag: 0x10000080  flag2: 0
 arguments: /root/syz-executor1430153543
 reaper: 0xfffffe0053dda000 reapsubtree: 1
 sigparent: 20
 vmspace: 0xfffffe008ff593f0
   (map 0xfffffe008ff593f0)
   (map.pmap 0xfffffe008ff594b0)
   (pmap 0xfffffe008ff59518)
 threads: 3
100094                   RunQ                                syz-executor1430153
113532                   Run     CPU 1                       syz-executor1430153
113533                   Run     CPU 0                       syz-executor1430153
db> ps
  pid  ppid  pgrp   uid  state   wmesg   wchan               cmd
 7532   816   816     0  R       (threaded)                  syz-executor1430153
100094                   RunQ                                syz-executor1430153
113532                   Run     CPU 1                       syz-executor1430153
113533                   Run     CPU 0                       syz-executor1430153
  816   814   816     0  Ss      nanslp  0xffffffff83e34241  syz-executor1430153
  814   745   814     0  Ss      select  0xfffffe00542ac340  sshd
  799     1   799     0  Ss+     ttyin   0xfffffe0056d114b0  getty
  781     1   781     0  Ss      nanslp  0xffffffff83e34241  cron
  777     1   777    25  Ss      pause   0xfffffe008fe825f8  sendmail
  774     1   774     0  Ss      select  0xfffffe00542abf40  sendmail
  745     1   745     0  Ss      select  0xfffffe00542ad040  sshd
  648     1   648     0  Ss      select  0xfffffe00542acbc0  syslogd
  453     1   453     0  Ss      select  0xfffffe00542abdc0  devd
  351     1   351    65  Ss      select  0xfffffe0054315cc0  dhclient
  269     1   269     0  Ss      select  0xfffffe00542ac1c0  dhclient
  266     1   266     0  Ss      select  0xfffffe00542ad3c0  dhclient
   94     0     0     0  DL      pftm    0xffffffff84724530  [pf purge]
   22     0     0     0  DL      syncer  0xffffffff83f59a20  [syncer]
   21     0     0     0  DL      vlruwt  0xfffffe0057277000  [vnlru]
    8     0     0     0  DL      (threaded)                  [bufdaemon]
100063                   D       psleep  0xffffffff83f58040  [bufdaemon]
100064                   D       -       0xffffffff83211f80  [bufspacedaemon-0]
100075                   D       sdflush 0xfffffe00572e7ce8  [/ worker]
    7     0     0     0  DL      psleep  0xffffffff83f88e40  [vmdaemon]
    6     0     0     0  DL      (threaded)                  [pagedaemon]
100061                   D       psleep  0xffffffff83f7ccf8  [dom0]
100065                   D       launds  0xffffffff83f7cd04  [laundry: dom0]
100066                   D       umarcl  0xffffffff81e89f70  [uma]
    5     0     0     0  DL      -       0xffffffff83bf0828  [rand_harvestq]
    4     0     0     0  DL      (threaded)                  [cam]
100042                   D       -       0xffffffff83a937c0  [doneq0]
100043                   D       -       0xffffffff83a93740  [async]
100060                   D       -       0xffffffff83a935c0  [scanner]
   14     0     0     0  DL      seqstat 0xfffffe0054218888  [sequencer 00]
    3     0     0     0  DL      (threaded)                  [crypto]
100038                   D       crypto_ 0xffffffff83f785a0  [crypto]
100039                   D       crypto_ 0xfffffe005409e430  [crypto returns 0]
100040                   D       crypto_ 0xfffffe005409e480  [crypto returns 1]
   13     0     0     0  DL      (threaded)                  [geom]
100033                   D       -       0xffffffff83e09800  [g_event]
100034                   D       -       0xffffffff83e09820  [g_up]
100035                   D       -       0xffffffff83e09840  [g_down]
    2     0     0     0  WL      (threaded)                  [clock]
100030                   I                                   [clock (0)]
100031                   I                                   [clock (1)]
   12     0     0     0  WL      (threaded)                  [intr]
100014                   I                                   [swi6: task queue]
100015                   I                                   [swi6: Giant taskq]
100020                   I                                   [swi5: fast taskq]
100029                   I                                   [swi1: netisr 0]
100044                   I                                   [irq40: virtio_pci0]
100045                   I                                   [irq41: virtio_pci0]
100046                   I                                   [irq42: virtio_pci0]
100049                   I                                   [irq43: virtio_pci1]
100050                   I                                   [irq44: virtio_pci1]
100051                   I                                   [irq1: atkbd0]
100052                   I                                   [irq12: psm0]
100053                   I                                   [swi0: uart uart++]
100078                   I                                   [swi1: pf send]
   11     0     0     0  RL      (threaded)                  [idle]
100003                   CanRun                              [idle: cpu0]
100004                   CanRun                              [idle: cpu1]
    1     0     1     0  SLs     wait    0xfffffe0053dda000  [init]
   10     0     0     0  DL      audit_w 0xffffffff83f79060  [audit]
    0     0     0     0  DLs     (threaded)                  [kernel]
100000                   D       swapin  0xffffffff83e0a200  [swapper]
100005                   D       -       0xfffffe0054081100  [if_io_tqg_0]
100006                   D       -       0xfffffe0054081000  [if_io_tqg_1]
100007                   D       -       0xfffffe0054080e00  [if_config_tqg_0]
100008                   D       -       0xfffffe0054080d00  [softirq_0]
100009                   D       -       0xfffffe0054080c00  [softirq_1]
100010                   D       -       0xfffffe00081eb000  [kqueue_ctx taskq]
100011                   D       -       0xfffffe00081eae00  [pci_hp taskq]
100012                   D       -       0xfffffe00081ead00  [linuxkpi_irq_wq]
100013                   D       -       0xfffffe00081eac00  [in6m_free taskq]
100016                   D       -       0xfffffe00081ea900  [aiod_kick taskq]
100017                   D       -       0xfffffe00081ea800  [inm_free taskq]
100018                   D       -       0xfffffe00081ea700  [deferred_unmount ta]
100019                   D       -       0xfffffe00081ea600  [thread taskq]
100021                   D       -       0xfffffe00081ea400  [linuxkpi_short_wq_0]
100022                   D       -       0xfffffe00081ea400  [linuxkpi_short_wq_1]
100023                   D       -       0xfffffe00081ea400  [linuxkpi_short_wq_2]
100024                   D       -       0xfffffe00081ea400  [linuxkpi_short_wq_3]
100025                   D       -       0xfffffe00081ea300  [linuxkpi_long_wq_0]
100026                   D       -       0xfffffe00081ea300  [linuxkpi_long_wq_1]
100027                   D       -       0xfffffe00081ea300  [linuxkpi_long_wq_2]
100028                   D       -       0xfffffe00081ea300  [linuxkpi_long_wq_3]
100032                   D       -       0xfffffe00081ea200  [firmware taskq]
100036                   D       -       0xfffffe00081ea100  [crypto_0]
100037                   D       -       0xfffffe00081ea100  [crypto_1]
100047                   D       -       0xfffffe00543a6300  [vtnet0 rxq 0]
100048                   D       -       0xfffffe00543a6200  [vtnet0 txq 0]
100054                   D       -       0xffffffff82b9f4e1  [deadlkres]
100055                   D       -       0xfffffe00543a5800  [acpi_task_0]
100056                   D       -       0xfffffe00543a5800  [acpi_task_1]
100057                   D       -       0xfffffe00543a5800  [acpi_task_2]
100059                   D       -       0xfffffe00081ea000  [CAM taskq]
db> show all locks
db> show malloc
              Type        InUse        MemUse     Requests
           pf_hash            5        11524K            5
         sysctloid        31631         1861K        31673
            linker          256         1363K          274
              kobj          325         1300K          488
            devbuf         1356         1134K         1373
            newblk          143         1060K          662
          vfscache            3         1025K            3
          inodedep            2          513K          101
         ufs_quota            1          512K            1
          vfs_hash            1          512K            1
           callout            2          512K            2
              intr            4          472K            4
               pcb           13          393K           23
         vnet_data            1          168K            1
           tidhash            3          141K            3
           subproc           79          139K         7582
           pagedep            2          129K           34
        tfo_ccache            1          128K            1
               sem            4          106K            4
            DEVFS1           92           92K          104
              vmem            3           81K            5
               bus          969           78K         3701
            bus-sc           31           76K         1066
          mtx_pool            2           72K            2
          syncache            1           68K            1
          acpitask            1           64K            1
       ddb_capture            1           64K            1
            module          497           63K          497
            acpica          420           39K        63353
               LRO            2           33K            2
              umtx          264           33K          264
         hostcache            1           32K            1
               shm            1           32K            1
               msg            4           30K            4
           kdtrace          136           29K        21067
            DEVFS3          111           28K          127
        gtaskqueue           18           26K           18
        DEVFS_RULE           62           22K           62
            kbdmux            5           22K            5
               BPF           10           18K           10
           ithread           95           18K           95
              temp           15           17K         8289
         ufs_mount            4           17K            5
              proc            3           17K            3
            KTRACE          100           13K          100
           devstat            6           13K            6
              rman          102           12K          526
      eventhandler          127           11K          127
            ifaddr           29           11K           30
              GEOM           61           11K          508
              kenv           59           10K           59
          routetbl           44           10K          142
              UART           12            9K           12
               rpc            2            8K            2
         bmsafemap            1            8K           92
             shmfd            1            8K            1
       pfs_vncache            1            8K            1
         pfs_nodes           20            8K           20
     audit_evclass          237            8K          296
              cred           28            7K          300
         taskqueue           56            6K           56
            sglist            3            6K            3
       ufs_dirhash           24            5K           24
               UMA          254            5K          254
             ifnet            3            5K            3
           io_apic            1            4K            1
               tty            4            4K            4
          filedesc            1            4K            1
             evdev            4            4K            4
             hhook           15            4K           17
          pf_ifnet            5            3K            6
           lltable           10            3K           10
           acpisem           21            3K           21
            plimit           10            3K          243
           uidinfo            4            3K           10
             lockf           22            3K           36
        local_apic            1            2K            1
       fpukern_ctx            2            2K            2
         ipsec-saq            2            2K            2
           CAM DEV            1            2K            2
            kqueue           30            2K         7533
           pwddesc           30            2K         7533
             selfd           27            2K        68608
               msi           13            2K           13
           session           13            2K           32
         proc-args           43            2K         8533
          pci_link           16            2K           16
            Unitno           25            2K           45
           acpidev           22            2K           22
         toponodes           10            2K           10
         CAM queue            2            2K            5
           softdep            1            1K            1
       ipsecpolicy            1            1K            1
            sahead            1            1K            1
          secasvar            1            1K            1
             clone            8            1K            8
       ether_multi           13            1K           18
       vnodemarker            2            1K           18
            select            8            1K           61
      NFSD session            1            1K            1
         in6_multi            9            1K            9
             mount           18            1K       302300
             nhops            6            1K            6
            crypto            4            1K            4
            isadev            5            1K            5
           CAM XPT           11            1K           12
          in_multi            2            1K            3
              pfil            4            1K            4
              cdev            2            1K            2
 encap_export_host            8            1K            8
               osd            8            1K           20
            ip6ndp            3            1K            3
    chacha20random            1            1K            1
        CAM periph            2            1K           14
      NFSD lckfile            1            1K            1
     NFSD V4client            1            1K            1
               MCA            2            1K            2
            DEVFSP            4            1K           25
             DEVFS            9            1K           10
          indirdep            1            1K            3
               mld            2            1K            2
            CC Mem            4            1K           10
              igmp            2            1K            2
            vnodes            1            1K            1
       inpcbpolicy            7            1K           71
            feeder            7            1K            7
        loginclass            3            1K            7
            prison            6            1K            6
       lkpikmalloc            5            1K            6
        aesni_data            2            1K            2
         cryptodev            2            1K          161
            apmdev            1            1K            1
          atkbddev            2            1K            2
            diradd            1            1K          107
           CAM SIM            1            1K            1
          procdesc            1            1K           20
          pmchooks            1            1K            1
            soname            4            1K         2599
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
     NFSCL flayout            0            0K            0
      NFSCL layout            0            0K            0
        madt_table            0            0K            2
          smartpqi            0            0K            0
     NFSD rollback            0            0K            0
      NFSCL diroff            0            0K            0
       NEWdirectio            0            0K            0
               ixl            0            0K            0
        NEWNFSnode            0            0K            0
         NFSCL lck            0            0K            0
      NFSCL lckown            0            0K            0
      NFSCL client            0            0K            0
       NFSCL deleg            0            0K            0
        NFSCL open            0            0K            0
       NFSCL owner            0            0K            0
        ice-resmgr            0            0K            0
         ice-osdep            0            0K            0
               ice            0            0K            0
              iavf            0            0K            0
             axgbe            0            0K            0
            NFS fh            0            0K            0
           NFS req            0            0K            0
     NFSD usrgroup            0            0K            0
       NFSD string            0            0K            0
       NFSD V4lock            0            0K            0
      NFSD V4state            0            0K            0
     NFSD srvcache            0            0K            0
           memdesc            0            0K            0
       msdosfs_fat            0            0K            0
          xen_intr            0            0K            0
     msdosfs_mount            0            0K            0
      msdosfs_node            0            0K            0
           xen_hvm            0            0K            0
         legacydrv            0            0K            0
            bounce            0            0K            0
            busdma            0            0K            0
            qpidrv            0            0K            0
      dmar_idpgtbl            0            0K            0
          dmar_dom            0            0K            0
          dmar_ctx            0            0K            0
            DEVFS4            0            0K            0
              isci            0            0K            0
      iommu_dmamap            0            0K            0
     hyperv_socket            0            0K            0
           bxe_ilt            0            0K            0
            xenbus            0            0K            0
            DEVFS2            0            0K            0
            gntdev            0            0K            0
       privcmd_dev            0            0K            0
     vm_fictitious            0            0K            0
        evtchn_dev            0            0K            0
          xenstore            0            0K            0
         scsi_pass            0            0K            0
         ciss_data            0            0K            0
               xnb            0            0K            0
          xen_acpi            0            0K            0
              xbbd            0            0K            0
               xbd            0            0K            0
           Balloon            0            0K            0
          sysmouse            0            0K            0
            vtfont            0            0K            0
           UMAHash            0            0K            0
                vt            0            0K            0
             vtbuf            0            0K            0
         vm_pgdata            0            0K            0
           jblocks            0            0K            0
          savedino            0            0K           18
          sentinel            0            0K            0
            jfsync            0            0K            0
            jtrunc            0            0K            0
             sbdep            0            0K            7
           jsegdep            0            0K            0
              jseg            0            0K            0
         jfreefrag            0            0K            0
          jfreeblk            0            0K            0
           jnewblk            0            0K            0
            jmvref            0            0K            0
           jremref            0            0K            0
           jaddref            0            0K            0
           freedep            0            0K            0
         newdirblk            0            0K           15
            dirrem            0            0K           46
             mkdir            0            0K           30
          freefile            0            0K           28
          freeblks            0            0K           25
          freefrag            0            0K            5
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
          ktls_ocf            0            0K            0
               agp            0            0K            0
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
            statfs            0            0K           14
     namei_tracker            0            0K            2
       export_host            0            0K            0
        cl_savebuf            0            0K            5
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
              aios            0            0K            0
               lio            0            0K            0
               acl            0            0K            0
          mbuf_tag            0            0K           16
              ktls            0            0K            0
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
               iov            0            0K         7789
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
              sbuf            0            0K        54084
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
           NFS FHA            0            0K            0
         newnfsmnt            0            0K            0
  newnfsclient_req            0            0K            0
   NFSCL layrecall            0            0K            0
     NFSCL session            0            0K            0
     NFSCL sockreq            0            0K            0
     NFSCL devinfo            0            0K            0
db> show uma
              Zone   Size    Used    Free    Requests  Sleeps  Bucket  Total Mem    XFree
   mbuf_jumbo_page   4096    1088    1452       17986       0     254   10403840        0
              pbuf   2624       0     778           0       0       2    2041472        0
          BUF TRIE    144     162   11682         470       0      62    1705536        0
        malloc-128    128   10420     182       10544       0     126    1357056        0
       malloc-4096   4096     325       3         490       0       2    1343488        0
      mbuf_cluster   2048     508       0         508       0     254    1040384        0
              mbuf    256    1346    1206       39322       0     254     653312        0
             tcpcb   1104       4     507          10       0     254     564144        0
        malloc-512    512    1026      54        1198       0      30     552960        0
            socket    960      18     490        1022       0     254     487680        0
      malloc-65536  65536       6       1          75       0       1     458752        0
         vmem btag     56    8065     110        8065       0     254     457800        0
       UMA Slabs 0    112    3823      23        3823       0     126     430752        0
            lkpimm    168       1    2327           1       0      62     391104        0
          lkpicurr    168       2    2326           2       0      62     391104        0
        RADIX NODE    144    2346     337      161655       0      62     386352        0
        256 Bucket   2048     132      20         677       0       8     311296        0
       malloc-2048   2048     130      14         162       0       8     294912        0
         VM OBJECT    264     876     144      108022       0      30     269280        0
         malloc-64     64    3661     434       11172       0     254     262080        0
             VNODE    448     512      64         543       0      30     258048        0
            THREAD   1808     105      27       13533       0       8     238656        0
         malloc-16     16   13348     402       13396       0     254     220000        0
            DEVCTL   1024       0     196          94       0       0     200704        0
      malloc-65536  65536       3       0           3       0       1     196608        0
        malloc-256    256     336     414        1241       0      62     192000        0
       malloc-4096   4096      36       8        7545       0       2     180224        0
         UMA Zones    768     226       3         226       0      16     175872        0
         malloc-32     32    4539     375        4601       0     254     157248        0
       FFS2 dinode    256     491      79         519       0      62     145920        0
      malloc-65536  65536       2       0           2       0       1     131072        0
      malloc-65536  65536       0       2          31       0       1     131072        0
             unpcb    256      10     500         940       0     254     130560        0
       mbuf_packet    256       0     508          70       0     254     130048        0
       S VFS Cache    104     978     192        1059       0     126     121680        0
         MAP ENTRY     96     690     570      168962       0     126     120960        0
     FPU_save_area    832     107      37       13551       0      16     119808        0
          ksiginfo    112      39    1005          75       0     126     116928        0
       malloc-1024   1024     101      11         273       0      16     114688        0
         FFS inode    192     491      76         519       0      62     108864        0
        malloc-128    128     515     260        3010       0     126      99200        0
      malloc-32768  32768       3       0           3       0       1      98304        0
        128 Bucket   1024      46      37         296       0      16      84992        0
            clpbuf   2624       0      32          29       0      16      83968        0
          UMA Kegs    384     212       1         212       0      30      81792        0
        malloc-256    256     159     156       13592       0      62      80640        0
           VMSPACE   2552      14      16        7518       0       4      76560        0
         64 Bucket    512      77      59        4816       0      30      69632        0
        malloc-128    128     318     209         551       0     126      67456        0
      malloc-65536  65536       1       0           1       0       1      65536        0
      malloc-65536  65536       1       0           1       0       1      65536        0
      malloc-32768  32768       0       2          49       0       1      65536        0
         32 Bucket    256      64     191        1183       0      62      65280        0
              PROC   1352      29      19        7532       0       8      64896        0
       malloc-8192   8192       6       1          80       0       1      57344        0
         filedesc0   1072      30      19        7533       0       8      52528        0
         malloc-64     64     623     196         919       0     254      52416        0
         malloc-64     64      71     748      170225       0     254      52416        0
        malloc-128    128     253     150       28899       0     126      51584        0
        malloc-128    128     276     127         795       0     126      51584        0
           DIRHASH   1024      33      15          33       0      16      49152        0
             NAMEI   1024       0      48       12292       0      16      49152        0
       malloc-8192   8192       4       2           6       0       1      49152        0
           pcpu-64     64     463     305         463       0     254      49152        0
             g_bio    384       0     120        5012       0      30      46080        0
          syncache    168       0     264           5       0     254      44352        0
         udp_inpcb    424       2      88          60       0      30      38160        0
         malloc-64     64       8     559        7492       0     254      36288        0
         malloc-64     64     123     444         162       0     254      36288        0
         malloc-64     64     176     391        1695       0     254      36288        0
         malloc-64     64      42     525        7879       0     254      36288        0
         malloc-64     64      10     557          25       0     254      36288        0
        malloc-128    128     165     114       27631       0     126      35712        0
        malloc-128    128     127     152        6882       0     126      35712        0
        malloc-128    128      33     246         143       0     126      35712        0
     routing nhops    256       8     127          14       0      62      34560        0
        malloc-384    384      64      26         243       0      30      34560        0
        malloc-384    384       3      87        6837       0      30      34560        0
        malloc-256    256       0     135         225       0      62      34560        0
        malloc-256    256      11     124          20       0      62      34560        0
        malloc-256    256      42      93       14067       0      62      34560        0
        malloc-256    256      19     116         110       0      62      34560        0
        malloc-256    256      35     100         636       0      62      34560        0
        malloc-256    256       4     131          43       0      62      34560        0
      malloc-32768  32768       1       0           1       0       1      32768        0
      malloc-32768  32768       0       1           1       0       1      32768        0
      malloc-32768  32768       1       0           1       0       1      32768        0
      malloc-32768  32768       1       0           1       0       1      32768        0
      malloc-16384  16384       1       1          65       0       1      32768        0
       malloc-8192   8192       4       0           4       0       1      32768        0
       malloc-2048   2048       3      13           9       0       8      32768        0
       malloc-2048   2048       3      13         216       0       8      32768        0
       malloc-2048   2048       4      12           4       0       8      32768        0
       malloc-2048   2048       3      13          21       0       8      32768        0
       malloc-1024   1024       4      28           4       0      16      32768        0
       malloc-1024   1024      16      16          27       0      16      32768        0
       malloc-1024   1024       2      30           2       0      16      32768        0
       malloc-1024   1024       7      25          25       0      16      32768        0
       malloc-1024   1024       6      26         903       0      16      32768        0
        malloc-512    512      11      53          27       0      30      32768        0
        malloc-512    512       0      64        6716       0      30      32768        0
        malloc-512    512       2      62           2       0      30      32768        0
        malloc-512    512       2      62           2       0      30      32768        0
        malloc-512    512       2      62           9       0      30      32768        0
            pcpu-8      8    3326     770        3349       0     254      32768        0
    ertt_txseginfo     40       0     808        6975       0     254      32320        0
          8 Bucket     80      30     370         664       0     126      32000        0
            cpuset    104       7     272           7       0     126      29016        0
         malloc-32     32     259     623        5278       0     254      28224        0
         16 Bucket    144      44     152         530       0      62      28224        0
          4 Bucket     48       6     582         336       0     254      28224        0
         tcp_inpcb    424       4      59          10       0      30      26712        0
              pipe    744       5      30         291       0      16      26040        0
         TURNSTILE    136     133      56         133       0      62      25704        0
       malloc-8192   8192       3       0           3       0       1      24576        0
       malloc-4096   4096       3       3         322       0       2      24576        0
       malloc-4096   4096       5       1           5       0       2      24576        0
           rtentry    176      11     127          14       0      62      24288        0
              PGRP     88      13     263          32       0     126      24288        0
          rl_entry     40      28     578          30       0     254      24240        0
             Files     80      68     232        6878       0     126      24000        0
        malloc-384    384      26      34          27       0      30      23040        0
        malloc-384    384       1      59           3       0      30      23040        0
        malloc-384    384      13      47          13       0      30      23040        0
        malloc-384    384      49      11          49       0      30      23040        0
        SLEEPQUEUE     88     133     123         133       0     126      22528        0
         hostcache     64       1     314           1       0     254      20160        0
             udpcb     32       2     628          60       0     254      20160        0
   udp_inpcb ports     32       1     629           7       0     254      20160        0
              ertt     72       4     276          10       0     126      20160        0
               PWD     32      11     619          97       0     254      20160        0
         malloc-32     32       4     626           9       0     254      20160        0
         malloc-32     32      78     552         203       0     254      20160        0
         malloc-32     32      78     552         793       0     254      20160        0
         malloc-32     32      21     609       20168       0     254      20160        0
         malloc-32     32      43     587        7036       0     254      20160        0
         malloc-32     32      13     617          38       0     254      20160        0
          2 Bucket     32      52     578         285       0     254      20160        0
       Mountpoints   2752       2       5           2       0       4      19264        0
           ttyoutq    256       8      67          24       0      62      19200        0
 epoch_record pcpu    256       4      60           4       0      62      16384        0
      malloc-16384  16384       1       0           1       0       1      16384        0
      malloc-16384  16384       1       0           1       0       1      16384        0
      malloc-16384  16384       1       0           1       0       1      16384        0
       malloc-8192   8192       2       0           2       0       1      16384        0
       malloc-4096   4096       1       3           4       0       2      16384        0
       malloc-4096   4096       0       4          14       0       2      16384        0
       malloc-4096   4096       4       0           4       0       2      16384        0
       malloc-2048   2048       1       7           1       0       8      16384        0
       malloc-2048   2048       2       6           2       0       8      16384        0
       malloc-1024   1024       1      15           1       0      16      16384        0
       malloc-1024   1024       7       9           7       0      16      16384        0
           SMR CPU     32       7     504           7       0     254      16352        0
               ipq     56       0     288           5       0     254      16128        0
         malloc-16     16     451     549        2334       0     254      16000        0
              kenv    258       2      58         702       0      30      15480        0
             ripcb    424       1      35           1       0      30      15264        0
              vmem   1856       1       7           1       0       8      14848        0
        SMR SHARED     24       7     504           7       0     254      12264        0
   tcp_inpcb ports     32       2     376           2       0     254      12096        0
            ttyinq    160      15      60          45       0      62      12000        0
         malloc-16     16       1     749         175       0     254      12000        0
         malloc-16     16      16     734       26999       0     254      12000        0
         malloc-16     16      16     734      154519       0     254      12000        0
         malloc-16     16      44     706       27620       0     254      12000        0
         malloc-16     16      12     738        1312       0     254      12000        0
         malloc-16     16       9     741        6755       0     254      12000        0
       L VFS Cache    320       0      36           1       0      30      11520        0
        malloc-384    384       0      30           2       0      30      11520        0
        malloc-384    384       1      29           1       0      30      11520        0
       malloc-8192   8192       1       0           1       0       1       8192        0
       malloc-8192   8192       1       0           1       0       1       8192        0
       malloc-4096   4096       1       1           1       0       2       8192        0
      vtnet_tx_hdr     24       1     333       13642       0     254       8016        0
           pcpu-16     16       7     249           7       0     254       4096        0
       UMA Slabs 1    176       8      14           8       0      62       3872        0
        KMAP ENTRY     96      14      25          16       0       0       3744        0
            pcpu-4      4       1     511           1       0     254       2048        0
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
           ada_ccb    272       0       0           0       0      30          0        0
            da_ccb    544       0       0           0       0      16          0        0
             swblk    136       0       0           0       0      62          0        0
          swpctrie    144       0       0           0       0      62          0        0
       FFS1 dinode    128       0       0           0       0     126          0        0
tfo_ccache_entries     80       0       0           0       0     126          0        0
               tfo      4       0       0           0       0     254          0        0
          sackhole     32       0       0           0       0     254          0        0
             tcptw     72       0       0           0       0     254          0        0
   tcp_log_id_node    120       0       0           0       0     126          0        0
 tcp_log_id_bucket    176       0       0           0       0      62          0        0
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
      malloc-16384  16384       0       0           0       0       1          0        0
      malloc-16384  16384       0       0           0       0       1          0        0
      malloc-16384  16384       0       0           0       0       1          0        0
      malloc-16384  16384       0       0           0       0       1          0        0
       malloc-8192   8192       0       0           0       0       1          0        0
       malloc-2048   2048       0       0           0       0       8          0        0
        malloc-512    512       0       0           0       0      30          0        0
        malloc-512    512       0       0           0       0      30          0        0
           pcpu-32     32       0       0           0       0     254          0        0
            fakepg    104       0       0           0       0     126          0        0
          UMA Hash    256       0       0           0       0      62          0        0


Syzkaller reproducer:
# {Threaded:true Repeat:true RepeatTimes:0 Procs:1 Slowdown:1 Sandbox: Leak:false NetInjection:false NetDevices:false NetReset:false Cgroups:false BinfmtMisc:false CloseFDs:false KCSAN:false DevlinkPCI:false USB:false VhciInjection:false Wifi:false IEEE802154:false Sysctl:false UseTmpDir:false HandleSegv:false Repro:false Trace:false LegacyOptions:{Collide:false Fault:false FaultCall:0 FaultNth:0}}
mount(&(0x7f0000000000)='msdosfs\x00', 0x0, 0x0, &(0x7f00000000c0)) (async)
ioctl$CIOCGSESSION2(0xffffffffffffffff, 0xc040636a, &(0x7f0000000180)={0xb, 0x0, 0x10, &(0x7f0000000000)="875fa46e2a027a06397dceb555614b6c", 0x0, 0x0, 0x0, 0x358f1b98})


C reproducer:
// autogenerated by syzkaller (https://github.com/google/syzkaller)

#define _GNU_SOURCE

#include <sys/types.h>

#include <errno.h>
#include <pthread.h>
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
  for (call = 0; call < 2; call++) {
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
      if (call == 0)
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

void execute_call(int call)
{
  switch (call) {
  case 0:
    memcpy((void*)0x20000000, "msdosfs\000", 8);
    syscall(SYS_mount, 0x20000000ul, 0ul, 0ul, 0x200000c0ul);
    break;
  case 1:
    *(uint32_t*)0x20000180 = 0xb;
    *(uint32_t*)0x20000184 = 0;
    *(uint32_t*)0x20000188 = 0x10;
    *(uint64_t*)0x20000190 = 0x20000000;
    memcpy((void*)0x20000000,
           "\x87\x5f\xa4\x6e\x2a\x02\x7a\x06\x39\x7d\xce\xb5\x55\x61\x4b\x6c",
           16);
    *(uint32_t*)0x20000198 = 0;
    *(uint64_t*)0x200001a0 = 0;
    *(uint32_t*)0x200001a8 = 0;
    *(uint32_t*)0x200001ac = 0x358f1b98;
    *(uint32_t*)0x200001b0 = 0;
    *(uint32_t*)0x200001b4 = 0;
    *(uint32_t*)0x200001b8 = 0;
    *(uint32_t*)0x200001bc = 0;
    syscall(SYS_ioctl, -1, 0xc040636aul, 0x20000180ul);
    break;
  }
}
int main(void)
{
  syscall(SYS_mmap, 0x20000000ul, 0x1000000ul, 7ul, 0x1012ul, -1, 0ul);
  loop();
  return 0;
}


