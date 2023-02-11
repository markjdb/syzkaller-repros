Syzkaller hit 'panic: in6_pcbconnect: inp is already connected' bug.

login: panic: in6_pcbconnect: inp is already connected
cpuid = 0
time = 1676005422
KDB: stack backtrace:
db_trace_self_wrapper() at db_trace_self_wrapper+0xc7/frame 0xfffffe008e6f7550
kdb_backtrace() at kdb_backtrace+0xd3/frame 0xfffffe008e6f76b0
vpanic() at vpanic+0x254/frame 0xfffffe008e6f7790
panic() at panic+0xb5/frame 0xfffffe008e6f7850
in6_pcbconnect() at in6_pcbconnect+0xb5c/frame 0xfffffe008e6f79b0
tcp6_connect() at tcp6_connect+0x140/frame 0xfffffe008e6f7a90
tcp6_usr_connect() at tcp6_usr_connect+0x3b3/frame 0xfffffe008e6f7bd0
soconnectat() at soconnectat+0x1b9/frame 0xfffffe008e6f7c30
kern_connectat() at kern_connectat+0x2d1/frame 0xfffffe008e6f7d10
sys_connect() at sys_connect+0xfb/frame 0xfffffe008e6f7d50
amd64_syscall() at amd64_syscall+0x3d7/frame 0xfffffe008e6f7f30
fast_syscall_common() at fast_syscall_common+0xf8/frame 0xfffffe008e6f7f30
--- syscall (0, FreeBSD ELF64, syscall), rip = 0x233a5a, rsp = 0x82449df88, rbp = 0x82449dfc0 ---
KDB: enter: panic
[ thread pid 837 tid 100141 ]
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
rcx         0x57aa8d83fa8c861e
rdx         0xdffff7c000000000
rbx                          0
rsp         0xfffffe008e6f7690
rbp         0xfffffe008e6f76b0
rsi                        0x1
rdi                          0
r8                         0x3
r9                  0xffffffff
r10                          0
r11                          0
r12                          0
r13         0xfffffe008ff85020
r14         0xffffffff82bf1340  .str.26
r15         0xffffffff82bf1340  .str.26
rip         0xffffffff81779cfb  kdb_enter+0x6b
rflags                    0x46
kdb_enter+0x6b: movq    $0,0x271259a(%rip)
db> show proc
Process 837 (syz-executor1301267) at 0xfffffe00542e6558:
 state: NORMAL
 uid: 0  gids: 0, 0, 5
 parent: pid 814 at 0xfffffe008f7f7008
 ABI: FreeBSD ELF64
 flag: 0x10000080  flag2: 0
 arguments: /root/syz-executor1301267891
 reaper: 0xfffffe0053dc7010 reapsubtree: 1
 sigparent: 20
 vmspace: 0xfffffe00904fa000
   (map 0xfffffe00904fa000)
   (map.pmap 0xfffffe00904fa0c0)
   (pmap 0xfffffe00904fa130)
 threads: 3
100071                   Run     CPU 1                       syz-executor1301267
100141                   Run     CPU 0                       syz-executor1301267
100142                   S       uwait   0xfffffe005428b280  syz-executor1301267
db> show routetable

Route table for AF 2 (INET):
dst <0.0.0.0> gateway <169.254.0.1> netmask <0.0.0.0> ifp <on link> ifa <169.254.0.111> flags UP,GATEWAY,STATIC
dst <127.0.0.1> gateway <on link> netmask <NULL> ifp <on link> ifa <127.0.0.1> flags UP,HOST,PINNED
dst <169.254.0.0> gateway <on link> netmask <255.255.255.0> ifp <on link> ifa <169.254.0.111> flags UP,PINNED
dst <169.254.0.111> gateway <on link> netmask <NULL> ifp <on link> ifa <127.0.0.1> flags UP,HOST,STATIC,PINNED

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
  837   814   814     0  R       (threaded)                  syz-executor1301267
100071                   Run     CPU 1                       syz-executor1301267
100141                   Run     CPU 0                       syz-executor1301267
100142                   S       uwait   0xfffffe005428b280  syz-executor1301267
  814   812   814     0  Ss      nanslp  0xffffffff83e59a00  syz-executor1301267
  812   745   812     0  Ss      select  0xfffffe0056d08cc0  sshd
  799     1   799     0  Ss+     ttyin   0xfffffe00543a90b0  getty
  794     1   794     0  Ss      select  0xfffffe0056d088c0  logger
  789     1     9     0  S+      piperd  0xfffffe008e922110  logger
  788   787     9     0  S+      nanslp  0xffffffff83e59a01  sleep
  787     1     9     0  S+      wait    0xfffffe008ff86ab0  sh
  781     1   781     0  Ss      nanslp  0xffffffff83e59a00  cron
  777     1   777    25  Ss      pause   0xfffffe00572aeb70  sendmail
  774     1   774     0  Ss      select  0xfffffe0056d08440  sendmail
  745     1   745     0  Ss      select  0xfffffe0056d087c0  sshd
  648     1   648     0  Ss      select  0xfffffe0056d080c0  syslogd
  453     1   453     0  Ss      select  0xfffffe0056d07ec0  devd
  351     1   351    65  Ss      select  0xfffffe0056d093c0  dhclient
  269     1   269     0  Ss      select  0xfffffe0056d08040  dhclient
  266     1   266     0  Ss      select  0xfffffe0056d081c0  dhclient
   94     0     0     0  DL      pftm    0xffffffff849242d0  [pf purge]
   17     0     0     0  DL      syncer  0xffffffff83f7eea0  [syncer]
   16     0     0     0  DL      vlruwt  0xfffffe00542e8ac0  [vnlru]
    8     0     0     0  DL      (threaded)                  [bufdaemon]
100063                   D       psleep  0xffffffff83f7d4a0  [bufdaemon]
100064                   D       -       0xffffffff83212180  [bufspacedaemon-0]
100076                   D       sdflush 0xfffffe0056d0e4e8  [/ worker]
    7     0     0     0  DL      psleep  0xffffffff83fb1a40  [vmdaemon]
    6     0     0     0  DL      (threaded)                  [pagedaemon]
100061                   D       psleep  0xffffffff83fa58f8  [dom0]
100065                   D       launds  0xffffffff83fa5904  [laundry: dom0]
100066                   D       umarcl  0xffffffff81ed8e60  [uma]
    5     0     0     0  DL      -       0xffffffff83c15e48  [rand_harvestq]
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
100078                   I                                   [swi1: pf send]
   11     0     0     0  RL      (threaded)                  [idle]
100003                   CanRun                              [idle: cpu0]
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
100054                   D       -       0xffffffff82bf73e1  [deadlkres]
100055                   D       -       0xfffffe00543b4300  [acpi_task_0]
100056                   D       -       0xfffffe00543b4300  [acpi_task_1]
100057                   D       -       0xfffffe00543b4300  [acpi_task_2]
100059                   D       -       0xfffffe00081f8000  [CAM taskq]
db> show all locks
Process 837 (syz-executor1301267) thread 0xfffffe008ff85020 (100141)
exclusive sleep mutex tcphash (tcphash) r = 0 (0xfffffe0053c107e0) locked @ /root/freebsd/sys/netinet/tcp_usrreq.c:1442
exclusive rw tcpinp (tcpinp) r = 0 (0xfffffe00904f6560) locked @ /root/freebsd/sys/netinet/tcp_usrreq.c:532
db> show malloc
              Type        InUse        MemUse     Requests
           pf_hash            5        11524K            5
         sysctloid        31163         1834K        31205
            linker          257         1387K          275
              kobj          327         1308K          491
            newblk          807         1226K          904
            devbuf         1357         1137K         1374
          vfscache            3         1025K            3
               pcb           17          525K           27
          inodedep           28          523K           99
         ufs_quota            1          512K            1
          vfs_hash            1          512K            1
           callout            2          512K            2
              intr            4          472K            4
           subproc           90          157K          894
           tidhash            3          141K            3
           pagedep           18          133K           33
        tfo_ccache            1          128K            1
          IP reass            1          128K            1
         vnet_data            1          112K            1
               sem            4          106K            4
            DEVFS1           92           92K          104
               bus          974           79K         3688
            bus-sc           31           76K         1058
              vmem            3           73K            3
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
            DEVFS3          111           28K          127
            kbdmux            5           28K            5
           kdtrace          133           27K          981
        gtaskqueue           18           26K           18
        DEVFS_RULE           62           22K           62
               BPF           10           18K           10
           ithread           95           18K           95
              temp           15           17K         1561
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
         bmsafemap            2            9K           92
              UART           12            9K           12
               rpc            2            8K            2
             shmfd            1            8K            1
       pfs_vncache            1            8K            1
              cred           30            8K          290
         pfs_nodes           20            8K           20
     audit_evclass          237            8K          296
         taskqueue           56            6K           56
            sglist            3            6K            3
       ufs_dirhash           24            5K           24
             ifnet            3            5K            3
               UMA          250            5K          250
           io_apic            1            4K            1
               tty            4            4K            4
          filedesc            1            4K            1
             evdev            4            4K            4
             hhook           15            4K           17
            diradd           25            4K          107
          pf_ifnet            5            3K            6
           lltable           10            3K           10
            plimit           11            3K          228
           acpisem           21            3K           21
           uidinfo            4            3K            9
             lockf           21            3K           32
            kqueue           34            3K          838
           pwddesc           34            3K          838
        local_apic            1            2K            1
       fpukern_ctx            2            2K            2
         ipsec-saq            2            2K            2
             clone            8            2K            8
           CAM DEV            1            2K            2
             selfd           31            2K        10727
           session           15            2K           31
         proc-args           51            2K         1809
               msi           13            2K           13
          pci_link           16            2K           16
            Unitno           25            2K           47
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
       ether_multi           13            1K           18
       vnodemarker            2            1K           10
      NFSD session            1            1K            1
         in6_multi            9            1K            9
          indirdep            3            1K            3
             nhops            6            1K            6
             mount           16            1K          123
            crypto            4            1K            4
            CC Mem            5            1K           33
            isadev            5            1K            5
           CAM XPT           11            1K           12
          in_multi            2            1K            3
              pfil            4            1K            4
              cdev            2            1K            2
 encap_export_host            8            1K            8
               osd            9            1K           43
            ip6ndp            3            1K            3
    chacha20random            1            1K            1
        CAM periph            2            1K           14
            ip6opt            2            1K           46
      NFSD lckfile            1            1K            1
     NFSD V4client            1            1K            1
               MCA            2            1K            2
            DEVFSP            4            1K           25
             DEVFS            9            1K           10
            dirrem            1            1K           46
       inpcbpolicy            8            1K           94
               mld            2            1K            2
              igmp            2            1K            2
            vnodes            1            1K            1
          procdesc            2            1K           20
            feeder            7            1K            7
        loginclass            3            1K            7
            prison            6            1K            6
       lkpikmalloc            5            1K            6
        aesni_data            2            1K            2
            soname            5            1K         2666
         cryptodev            2            1K          161
            apmdev            1            1K            1
          atkbddev            2            1K            2
           netlink            1            1K            1
           CAM SIM            1            1K            1
          pmchooks            1            1K            1
          filecaps            4            1K          101
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
          ktls_ocf            0            0K            0
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
            statfs            0            0K           13
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
         sysctltmp            0            0K          530
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
   mbuf_jumbo_page   4096    1088    1452       20822       0     254   10403840        0
              pbuf   2624       0     778           0       0       2    2041472        0
          BUF TRIE    144     182   11634         557       0      62    1701504        0
       malloc-4096   4096     367       3        1599       0       2    1515520        0
        malloc-128    128   10273      81       10387       0     126    1325312        0
      mbuf_cluster   2048     508       0         508       0     254    1040384        0
              mbuf    256    1347    1205       31608       0     254     653312        0
        malloc-512    512    1028      52        1036       0      30     552960        0
            socket    960      21     487        1044       0     254     487680        0
         vmem btag     56    7913     118        7913       0     254     449736        0
       UMA Slabs 0    112    3793      17        3793       0     126     426720        0
        RADIX NODE    144    2554     325       27780       0      62     414576        0
      malloc-65536  65536       6       0           6       0       1     393216        0
            lkpimm    168       1    2327           1       0      62     391104        0
          lkpicurr    168       2    2326           2       0      62     391104        0
       malloc-2048   2048     130      14         130       0       8     294912        0
        256 Bucket   2048     118      18         660       0       8     278528        0
         VM OBJECT    264     946      74       14260       0      30     269280        0
      malloc-65536  65536       3       1          72       0       1     262144        0
      malloc-65536  65536       4       0           4       0       1     262144        0
             VNODE    448     509      67         539       0      30     258048        0
         malloc-64     64    3578     265        3895       0     254     245952        0
        malloc-256    256     856      74        1005       0      62     238080        0
            THREAD   1824      98      23         142       0       8     220704        0
         malloc-16     16   13177     323       14476       0     254     216000        0
            DEVCTL   1024       0     196          94       0       0     200704        0
         UMA Zones    768     222       2         222       0      16     172032        0
         malloc-32     32    4515     399        4781       0     254     157248        0
       FFS2 dinode    256     488      82         515       0      62     145920        0
       S VFS Cache    104     971     316        1051       0     126     133848        0
      malloc-65536  65536       0       2          31       0       1     131072        0
             unpcb    256      12     498         939       0     254     130560        0
       mbuf_packet    256       0     508          85       0     254     130048        0
         MAP ENTRY     96     831     429       42601       0     126     120960        0
          ksiginfo    112      32    1012          65       0     126     116928        0
       malloc-1024   1024      97      15         109       0      16     114688        0
     FPU_save_area    832     100      35         156       0      16     112320        0
         FFS inode    192     488      79         515       0      62     108864        0
        malloc-128    128     556     219         790       0     126      99200        0
      malloc-32768  32768       3       0           3       0       1      98304        0
            clpbuf   2624       0      32          37       0      16      83968        0
          UMA Kegs    384     208       5         208       0      30      81792        0
           VMSPACE   2560      18      12         823       0       4      76800        0
              PROC   1368      33      22         837       0       8      75240        0
        128 Bucket   1024      42      25         222       0      16      68608        0
        malloc-128    128     295     232         317       0     126      67456        0
        malloc-128    128     344     183       31678       0     126      67456        0
      malloc-65536  65536       1       0           1       0       1      65536        0
      malloc-32768  32768       2       0           2       0       1      65536        0
       malloc-8192   8192       8       0          77       0       1      65536        0
         64 Bucket    512      66      38        1554       0      30      53248        0
         filedesc0   1072      34      15         838       0       8      52528        0
         malloc-64     64     616     203         831       0     254      52416        0
        malloc-128    128     299     104         809       0     126      51584        0
        malloc-256    256     115      80         140       0      62      49920        0
        malloc-256    256     151      44         532       0      62      49920        0
         32 Bucket    256      51     144        3575       0      62      49920        0
           DIRHASH   1024      33      15          33       0      16      49152        0
             NAMEI   1024       0      48       12229       0      16      49152        0
       malloc-8192   8192       6       0           6       0       1      49152        0
       malloc-1024   1024      18      30          25       0      16      49152        0
             g_bio    384       0     120        4777       0      30      46080        0
        malloc-384    384      27      93          98       0      30      46080        0
         udp_inpcb    472       2      94          60       0      30      45312        0
          syncache    168       0     264           5       0     254      44352        0
         tcp_inpcb   1312       5      28          33       0       8      43296        0
         malloc-64     64       0     567           2       0     254      36288        0
         malloc-64     64     114     453         174       0     254      36288        0
         malloc-64     64      45     522         864       0     254      36288        0
         malloc-64     64     138     429       12530       0     254      36288        0
         malloc-64     64     169     398        9399       0     254      36288        0
         malloc-64     64      33     534          69       0     254      36288        0
        malloc-128    128      10     269          18       0     126      35712        0
        malloc-128    128     156     123         760       0     126      35712        0
        malloc-128    128      46     233         108       0     126      35712        0
     routing nhops    256       8     127          14       0      62      34560        0
        malloc-384    384      59      31         240       0      30      34560        0
        malloc-384    384      63      27          63       0      30      34560        0
        malloc-256    256      22     113          83       0      62      34560        0
        malloc-256    256      52      83         438       0      62      34560        0
        malloc-256    256      35     100         655       0      62      34560        0
        malloc-256    256       6     129         416       0      62      34560        0
        malloc-256    256      58      77          97       0      62      34560        0
      malloc-32768  32768       0       1           1       0       1      32768        0
      malloc-32768  32768       0       1          48       0       1      32768        0
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
       malloc-1024   1024      11      21         901       0      16      32768        0
        malloc-512    512       3      61         175       0      30      32768        0
        malloc-512    512       8      56          15       0      30      32768        0
           pcpu-64     64     467      45         467       0     254      32768        0
            cpuset    104       7     272           7       0     126      29016        0
            pcpu-8      8    3315     269        3338       0     254      28672        0
          4 Bucket     48       5     583          53       0     254      28224        0
         TURNSTILE    136     122      67         122       0      62      25704        0
       malloc-8192   8192       1       2           3       0       1      24576        0
              PGRP     88      15     261          31       0     126      24288        0
    ertt_txseginfo     40       1     605         349       0     254      24240        0
          rl_entry     40      26     580          28       0     254      24240        0
           rtentry    168      11     133          14       0      62      24192        0
              pipe    728       6      27         289       0      16      24024        0
             Files     80      77     223        6865       0     126      24000        0
          8 Bucket     80      35     265         202       0     126      24000        0
        malloc-384    384      10      50          19       0      30      23040        0
        malloc-384    384      11      49          23       0      30      23040        0
        malloc-384    384       1      59           5       0      30      23040        0
        SLEEPQUEUE     88     122     134         122       0     126      22528        0
         hostcache     64       1     314           1       0     254      20160        0
   udp_inpcb ports     32       1     629           7       0     254      20160        0
   tcp_inpcb ports     32       3     627          25       0     254      20160        0
              ertt     72       5     275          33       0     126      20160        0
               PWD     32      11     619          95       0     254      20160        0
         malloc-32     32     248     382         331       0     254      20160        0
         malloc-32     32      57     573          82       0     254      20160        0
         malloc-32     32      31     599         100       0     254      20160        0
         malloc-32     32      40     590         592       0     254      20160        0
         malloc-32     32      30     600        5178       0     254      20160        0
         malloc-32     32      21     609         148       0     254      20160        0
         16 Bucket    144      40     100         177       0      62      20160        0
          2 Bucket     32      42     588         277       0     254      20160        0
       Mountpoints   2752       2       5           2       0       4      19264        0
           ttyoutq    256       8      67          24       0      62      19200        0
 epoch_record pcpu    256       4      60           4       0      62      16384        0
      malloc-16384  16384       1       0           1       0       1      16384        0
       malloc-8192   8192       2       0           2       0       1      16384        0
       malloc-8192   8192       2       0           2       0       1      16384        0
       malloc-8192   8192       2       0           2       0       1      16384        0
       malloc-4096   4096       3       1           5       0       2      16384        0
       malloc-4096   4096       1       3          52       0       2      16384        0
       malloc-4096   4096       1       3          16       0       2      16384        0
       malloc-4096   4096       0       4           6       0       2      16384        0
       malloc-2048   2048       2       6           2       0       8      16384        0
       malloc-1024   1024       2      14           2       0      16      16384        0
        malloc-512    512       1      31           1       0      30      16384        0
        malloc-512    512       0      32           1       0      30      16384        0
        malloc-512    512       3      29           3       0      30      16384        0
           SMR CPU     32       7     504           7       0     254      16352        0
               ipq     56       0     288         275       0     254      16128        0
             ripcb    440       1      35           1       0      30      15840        0
              kenv    258       2      58         693       0      30      15480        0
              vmem   1856       1       7           1       0       8      14848        0
        SMR SHARED     24       7     504           7       0     254      12264        0
         malloc-32     32      39     339         142       0     254      12096        0
            ttyinq    160      15      60          45       0      62      12000        0
         malloc-16     16       6     744          38       0     254      12000        0
         malloc-16     16      14     736         137       0     254      12000        0
         malloc-16     16     263     487         430       0     254      12000        0
         malloc-16     16      15     735          72       0     254      12000        0
         malloc-16     16     177     573        1870       0     254      12000        0
         malloc-16     16      28     722       27930       0     254      12000        0
         malloc-16     16      18     732          96       0     254      12000        0
       L VFS Cache    320       0      36           1       0      30      11520        0
        malloc-384    384      20      10          20       0      30      11520        0
       malloc-8192   8192       1       0           1       0       1       8192        0
       malloc-8192   8192       1       0           1       0       1       8192        0
       malloc-4096   4096       1       1           2       0       2       8192        0
       malloc-4096   4096       1       1           1       0       2       8192        0
      vtnet_tx_hdr     24       1     333        9683       0     254       8016        0
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
             swblk    136       0       0           0       0      62          0        0
          swpctrie    144       0       0           0       0      62          0        0
       FFS1 dinode    128       0       0           0       0     126          0        0
            da_ccb    544       0       0           0       0      16          0        0
           ada_ccb    272       0       0           0       0      30          0        0
tfo_ccache_entries     80       0       0           0       0     126          0        0
               tfo      4       0       0           0       0     254          0        0
          sackhole     32       0       0           0       0     254          0        0
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
# {Threaded:true Repeat:true RepeatTimes:0 Procs:1 Slowdown:1 Sandbox: SandboxArg:0 Leak:false NetInjection:false NetDevices:false NetReset:false Cgroups:false BinfmtMisc:false CloseFDs:false KCSAN:false DevlinkPCI:false NicVF:false USB:false VhciInjection:false Wifi:false IEEE802154:false Sysctl:false UseTmpDir:false HandleSegv:false Repro:false Trace:false LegacyOptions:{Collide:false Fault:false FaultCall:0 FaultNth:0}}
sendmsg(0xffffffffffffffff, &(0x7f0000000480)={&(0x7f0000000040)=@in6={0xfffffffffffffca9, 0x1c, 0x2, 0x0, @loopback}, 0x1c, 0x0, 0x0, 0x0}, 0x0)
r0 = socket$inet6_tcp(0x1c, 0x1, 0x0)
setsockopt$inet6_int(r0, 0x29, 0x30, &(0x7f0000000040)=0x1c1c, 0x707a5d49) (async)
sendto$inet6(r0, 0x0, 0x0, 0x0, &(0x7f0000000000)={0x1c, 0x1c, 0x1, 0x0, @rand_addr="feffffffffffffff00953a00000028a6"}, 0x1c) (async)
connect$inet6(r0, &(0x7f0000000080)={0x1c, 0x1c, 0x0, 0x9, @empty, 0x1}, 0x1c)


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
  for (call = 0; call < 5; call++) {
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
      if (call == 2 || call == 3)
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
    *(uint64_t*)0x20000480 = 0x20000040;
    *(uint8_t*)0x20000040 = 0xa9;
    *(uint8_t*)0x20000041 = 0x1c;
    *(uint16_t*)0x20000042 = htobe16(0x4e22);
    *(uint32_t*)0x20000044 = 0;
    *(uint64_t*)0x20000048 = htobe64(0);
    *(uint64_t*)0x20000050 = htobe64(1);
    *(uint32_t*)0x20000058 = 0;
    *(uint32_t*)0x20000488 = 0x1c;
    *(uint64_t*)0x20000490 = 0;
    *(uint64_t*)0x20000498 = 0;
    *(uint64_t*)0x200004a0 = 0;
    *(uint64_t*)0x200004a8 = 0;
    *(uint32_t*)0x200004b0 = 0;
    syscall(SYS_sendmsg, -1, 0x20000480ul, 0ul);
    break;
  case 1:
    res = syscall(SYS_socket, 0x1cul, 1ul, 0);
    if (res != -1)
      r[0] = res;
    break;
  case 2:
    *(uint32_t*)0x20000040 = 0x1c1c;
    syscall(SYS_setsockopt, r[0], 0x29, 0x30, 0x20000040ul, 0x707a5d49ul);
    break;
  case 3:
    *(uint8_t*)0x20000000 = 0x1c;
    *(uint8_t*)0x20000001 = 0x1c;
    *(uint16_t*)0x20000002 = htobe16(0x4e21);
    *(uint32_t*)0x20000004 = 0;
    memcpy((void*)0x20000008,
           "\xfe\xff\xff\xff\xff\xff\xff\xff\x00\x95\x3a\x00\x00\x00\x28\xa6",
           16);
    *(uint32_t*)0x20000018 = 0;
    syscall(SYS_sendto, r[0], 0ul, 0ul, 0ul, 0x20000000ul, 0x1cul);
    break;
  case 4:
    *(uint8_t*)0x20000080 = 0x1c;
    *(uint8_t*)0x20000081 = 0x1c;
    *(uint16_t*)0x20000082 = htobe16(0x4e20);
    *(uint32_t*)0x20000084 = 9;
    memset((void*)0x20000088, 0, 16);
    *(uint32_t*)0x20000098 = 1;
    syscall(SYS_connect, r[0], 0x20000080ul, 0x1cul);
    break;
  }
}
int main(void)
{
  syscall(SYS_mmap, 0x20000000ul, 0x1000000ul, 7ul, 0x1012ul, -1, 0ul);
  loop();
  return 0;
}


