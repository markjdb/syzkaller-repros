Syzkaller hit 'Fatal trap NUM: page fault in pf_krule_global_RB_INSERT' bug.

Fatal trap 12: page fault while in kernel mode
cpuid = 1; apic id = 01
fault virtual address	= 0x0
fault code		= supervisor read data, page not present
instruction pointer	= 0x20:0xffffffff84765b14
stack pointer	        = 0x28:0xfffffe0053fa0290
frame pointer	        = 0x28:0xfffffe0053fa02d0
code segment		= base 0x0, limit 0xfffff, type 0x1b
			= DPL 0, pres 1, long 1, def32 0, gran 1
processor eflags	= interrupt enabled, resume, IOPL = 0
current process		= 817 (syz-executor4080110)
trap number		= 12
panic: page fault
cpuid = 1
time = 1653583379
KDB: stack backtrace:
db_trace_self_wrapper() at db_trace_self_wrapper+0xc7/frame 0xfffffe0053f9fa90
kdb_backtrace() at kdb_backtrace+0xd3/frame 0xfffffe0053f9fbf0
vpanic() at vpanic+0x2b8/frame 0xfffffe0053f9fcd0
panic() at panic+0xb5/frame 0xfffffe0053f9fd90
trap_fatal() at trap_fatal+0x6a4/frame 0xfffffe0053f9fe90
trap_pfault() at trap_pfault+0x186/frame 0xfffffe0053f9ffd0
trap() at trap+0x5b0/frame 0xfffffe0053fa01c0
calltrap() at calltrap+0x8/frame 0xfffffe0053fa01c0
--- trap 0xc, rip = 0xffffffff84765b14, rsp = 0xfffffe0053fa0290, rbp = 0xfffffe0053fa02d0 ---
pf_krule_global_RB_INSERT() at pf_krule_global_RB_INSERT+0x24/frame 0xfffffe0053fa02d0
pfioctl() at pfioctl+0xc2e1/frame 0xfffffe0053fa1670
devfs_ioctl() at devfs_ioctl+0x22a/frame 0xfffffe0053fa1750
vn_ioctl() at vn_ioctl+0x215/frame 0xfffffe0053fa1aa0
devfs_ioctl_f() at devfs_ioctl_f+0x71/frame 0xfffffe0053fa1af0
kern_ioctl() at kern_ioctl+0x631/frame 0xfffffe0053fa1bf0
sys_ioctl() at sys_ioctl+0x31f/frame 0xfffffe0053fa1d50
amd64_syscall() at amd64_syscall+0x3d6/frame 0xfffffe0053fa1f30
fast_syscall_common() at fast_syscall_common+0xf8/frame 0xfffffe0053fa1f30
--- syscall (0, FreeBSD ELF64, nosys), rip = 0x233aaa, rsp = 0x820b897e8, rbp = 0x820b89830 ---
KDB: enter: panic
[ thread pid 817 tid 100097 ]
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
rcx         0x76a3722af7437af2
rdx         0xdffff7c000000000
rbx                          0
rsp         0xfffffe0053f9fbd0
rbp         0xfffffe0053f9fbf0
rsi                        0x1
rdi                          0
r8                         0x3
r9                  0xffffffff
r10                          0
r11                          0
r12         0xfffffe008fedc000
r13         0xfffffe0053f9fc01
r14         0xffffffff82b99700  .str.26
r15         0xffffffff82b99700  .str.26
rip         0xffffffff8176c2fb  kdb_enter+0x6b
rflags                    0x46
kdb_enter+0x6b: movq    $0,0x26fa89a(%rip)
db> show proc
Process 817 (syz-executor4080110) at 0xfffffe008feda548:
 state: NORMAL
 uid: 0  gids: 0, 0, 5
 parent: pid 815 at 0xfffffe008fedb000
 ABI: FreeBSD ELF64
 flag: 0x10000000  flag2: 0
 arguments: /root/syz-executor4080110454
 reaper: 0xfffffe0053dda000 reapsubtree: 1
 sigparent: 20
 vmspace: 0xfffffe008feab9f8
   (map 0xfffffe008feab9f8)
   (map.pmap 0xfffffe008feabab8)
   (pmap 0xfffffe008feabb20)
 threads: 1
100097                   Run     CPU 1                       syz-executor4080110
db> ps
  pid  ppid  pgrp   uid  state   wmesg   wchan               cmd
  818   816   814     0  R       CPU 0                       syz-executor4080110
  817   815   814     0  R       CPU 1                       syz-executor4080110
  816   814   814     0  R                                   syz-executor4080110
  815   814   814     0  R                                   syz-executor4080110
  814   812   814     0  Ss      nanslp  0xffffffff83e34240  syz-executor4080110
  812   745   812     0  Ss      select  0xfffffe00542ac140  sshd
  799     1   799     0  Ss+     ttyin   0xfffffe0056d114b0  getty
  795     1   795     0  Ss      select  0xfffffe00542abe40  logger
  789     1     9     0  S+      piperd  0xfffffe0075b985d0  logger
  788   787     9     0  S+      nanslp  0xffffffff83e34241  sleep
  787     1     9     0  S+      wait    0xfffffe008e8f5000  sh
  781     1   781     0  Ss      nanslp  0xffffffff83e34241  cron
  777     1   777    25  Ss      pause   0xfffffe00542e45f8  sendmail
  774     1   774     0  Ss      select  0xfffffe00542acb40  sendmail
  745     1   745     0  Ss      select  0xfffffe00542ac9c0  sshd
  648     1   648     0  Ss      select  0xfffffe00542ac240  syslogd
  453     1   453     0  Ss      select  0xfffffe00542ac340  devd
  351     1   351    65  Ss      select  0xfffffe00542ac440  dhclient
  269     1   269     0  Ss      select  0xfffffe00542abf40  dhclient
  266     1   266     0  Ss      select  0xfffffe00542ac0c0  dhclient
   94     0     0     0  RL                                  [pf purge]
   21     0     0     0  DL      syncer  0xffffffff83f59a20  [syncer]
   20     0     0     0  DL      vlruwt  0xfffffe00542e5a90  [vnlru]
    8     0     0     0  DL      (threaded)                  [bufdaemon]
100063                   D       psleep  0xffffffff83f58040  [bufdaemon]
100066                   D       -       0xffffffff83211f80  [bufspacedaemon-0]
100077                   D       sdflush 0xfffffe008e906ce8  [/ worker]
    7     0     0     0  DL      psleep  0xffffffff83f88e40  [vmdaemon]
    6     0     0     0  DL      (threaded)                  [pagedaemon]
100061                   D       psleep  0xffffffff83f7ccf8  [dom0]
100064                   D       launds  0xffffffff83f7cd04  [laundry: dom0]
100065                   D       umarcl  0xffffffff81e89f70  [uma]
    5     0     0     0  RL                                  [rand_harvestq]
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
100079                   I                                   [swi1: pf send]
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
Process 817 (syz-executor4080110) thread 0xfffffe008fedc000 (100097)
exclusive rm pf rulesets (pf rulesets) r = 0 (0xffffffff847e0760) locked @ /root/freebsd/sys/netpfil/pf/pf_ioctl.c:3436
exclusive sx pf config (pf config) r = 0 (0xffffffff847e0580) locked @ /root/freebsd/sys/netpfil/pf/pf_ioctl.c:3435
db> show malloc
              Type        InUse        MemUse     Requests
           pf_hash            5        11524K            5
         sysctloid        31631         1861K        31673
            linker          256         1363K          274
              kobj          325         1300K          488
            newblk          568         1166K          664
            devbuf         1356         1134K         1373
          vfscache            3         1025K            3
          inodedep           49          530K           99
         ufs_quota            1          512K            1
          vfs_hash            1          512K            1
           callout            2          512K            2
              intr            4          472K            4
               pcb           13          393K           23
         vnet_data            1          168K            1
           subproc           86          167K          868
           tidhash            3          141K            3
           pagedep           22          134K           33
        tfo_ccache            1          128K            1
               sem            4          106K            4
            DEVFS1           92           92K          104
               bus          969           78K         3701
            bus-sc           31           76K         1066
              vmem            3           73K            3
          mtx_pool            2           72K            2
          syncache            1           68K            1
          acpitask            1           64K            1
       ddb_capture            1           64K            1
            module          497           63K          497
            acpica          420           39K        63353
               LRO            2           33K            2
         hostcache            1           32K            1
               shm            1           32K            1
               msg            4           30K            4
            DEVFS3          111           28K          127
              umtx          220           28K          220
           kdtrace          135           27K          917
        gtaskqueue           18           26K           18
        DEVFS_RULE           62           22K           62
            kbdmux            5           22K            5
               BPF           10           18K           10
           ithread           95           18K           95
              temp           15           17K         1561
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
         bmsafemap            2            9K           92
              UART           12            9K           12
               rpc            2            8K            2
             shmfd            1            8K            1
          ioctlops            2            8K           82
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
          filedesc            1            4K            1
             evdev            4            4K            4
             hhook           15            4K           17
          pf_ifnet            5            3K            6
           lltable           10            3K           10
            plimit           11            3K          228
           acpisem           21            3K           21
           uidinfo            4            3K            9
            kqueue           37            3K          819
           pwddesc           37            3K          819
             lockf           21            3K           32
        local_apic            1            2K            1
       fpukern_ctx            2            2K            2
         ipsec-saq            2            2K            2
           CAM DEV            1            2K            2
             selfd           31            2K         8049
           session           15            2K           31
         proc-args           54            2K         1786
               msi           13            2K           13
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
               osd            8            1K           20
            ip6ndp            3            1K            3
    chacha20random            1            1K            1
        CAM periph            2            1K           14
      NFSD lckfile            1            1K            1
     NFSD V4client            1            1K            1
               MCA            2            1K            2
            DEVFSP            4            1K           25
             DEVFS            9            1K           10
            dirrem            1            1K           46
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
               iov            0            0K         7784
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
           NFS FHA            0            0K            0
         newnfsmnt            0            0K            0
  newnfsclient_req            0            0K            0
   NFSCL layrecall            0            0K            0
     NFSCL session            0            0K            0
     NFSCL sockreq            0            0K            0
     NFSCL devinfo            0            0K            0
db> show uma
              Zone   Size    Used    Free    Requests  Sleeps  Bucket  Total Mem    XFree
   mbuf_jumbo_page   4096    1088    1198       14527       0     254    9363456        0
              pbuf   2624       0     794           0       0       2    2083456        0
          BUF TRIE    144     165   11679         430       0      62    1705536        0
        malloc-128    128   10465     137       10543       0     126    1357056        0
       malloc-4096   4096     325       3         490       0       2    1343488        0
              mbuf    256    1346    1460       22415       0     254     718336        0
             tcpcb   1104       4     507          10       0     254     564144        0
        malloc-512    512    1026      54        1198       0      30     552960        0
      mbuf_cluster   2048     254       0         254       0     254     520192        0
            socket    960      20     488        1021       0     254     487680        0
      malloc-65536  65536       6       1          75       0       1     458752        0
         vmem btag     56    7590      81        7590       0     254     429576        0
        RADIX NODE    144    2407     332       27392       0      62     394416        0
            lkpimm    168       1    2327           1       0      62     391104        0
          lkpicurr    168       2    2326           2       0      62     391104        0
       UMA Slabs 0    112    3414       0        3414       0     126     382368        0
       malloc-2048   2048     130      14         162       0       8     294912        0
        256 Bucket   2048     124      16         627       0       8     286720        0
         VM OBJECT    264     962      58       13982       0      30     269280        0
             VNODE    448     510      66         540       0      30     258048        0
         malloc-64     64    3668     175        4458       0     254     245952        0
        malloc-256    256     782     148        1233       0      62     238080        0
         malloc-16     16   13348     152       13396       0     254     216000        0
            DEVCTL   1024       0     196          94       0       0     200704        0
            THREAD   1808      97      13          97       0       8     198880        0
      malloc-65536  65536       3       0           3       0       1     196608        0
       malloc-4096   4096      43       1         831       0       2     180224        0
         UMA Zones    768     226       3         226       0      16     175872        0
         malloc-32     32    4539     375        4601       0     254     157248        0
       FFS2 dinode    256     488      82         515       0      62     145920        0
      malloc-65536  65536       2       0           2       0       1     131072        0
      malloc-65536  65536       0       2          31       0       1     131072        0
             unpcb    256      12     498         939       0     254     130560        0
       S VFS Cache    104     971     199        1051       0     126     121680        0
         MAP ENTRY     96     846     414       41188       0     126     120960        0
          ksiginfo    112      33    1011          65       0     126     116928        0
       malloc-1024   1024     101      11         273       0      16     114688        0
         FFS inode    192     488      79         515       0      62     108864        0
        malloc-128    128     515     260        3009       0     126      99200        0
      malloc-32768  32768       3       0           3       0       1      98304        0
     FPU_save_area    832      99      18         111       0      16      97344        0
          UMA Kegs    384     212       1         212       0      30      81792        0
        128 Bucket   1024      41      26         213       0      16      68608        0
        malloc-128    128     329     198         552       0     126      67456        0
      malloc-65536  65536       1       0           1       0       1      65536        0
      malloc-65536  65536       1       0           1       0       1      65536        0
       malloc-8192   8192       7       1          80       0       1      65536        0
       mbuf_packet    256       0     254          70       0     254      65024        0
              PROC   1352      36      12         818       0       8      64896        0
           VMSPACE   2552      21       3         804       0       4      61248        0
         64 Bucket    512      62      42        1596       0      30      53248        0
         filedesc0   1072      37      12         819       0       8      52528        0
         malloc-64     64     623     196         919       0     254      52416        0
        malloc-128    128     256     147       28898       0     126      51584        0
        malloc-128    128     232     171         743       0     126      51584        0
        malloc-256    256     151      44         156       0      62      49920        0
         32 Bucket    256      55     140        2237       0      62      49920        0
           DIRHASH   1024      33      15          33       0      16      49152        0
             NAMEI   1024       0      48       12225       0      16      49152        0
        malloc-384    384      50      70         120       0      30      46080        0
          syncache    168       0     264           5       0     254      44352        0
            clpbuf   2624       0      16          29       0      16      41984        0
       malloc-8192   8192       4       1           6       0       1      40960        0
         udp_inpcb    424       2      88          60       0      30      38160        0
         malloc-64     64       8     559        7469       0     254      36288        0
         malloc-64     64     123     444         162       0     254      36288        0
         malloc-64     64      82     485        8942       0     254      36288        0
         malloc-64     64     176     391        1695       0     254      36288        0
         malloc-64     64      51     516        1140       0     254      36288        0
         malloc-64     64      10     557          25       0     254      36288        0
        malloc-128    128     164     115         768       0     126      35712        0
        malloc-128    128     127     152         167       0     126      35712        0
        malloc-128    128      41     238         143       0     126      35712        0
     routing nhops    256       8     127          14       0      62      34560        0
             g_bio    384       0      90        4656       0      30      34560        0
           ttyoutq    256       8     127          24       0      62      34560        0
        malloc-384    384      64      26         243       0      30      34560        0
        malloc-384    384      49      41          49       0      30      34560        0
        malloc-256    256       0     135         243       0      62      34560        0
        malloc-256    256      11     124          20       0      62      34560        0
        malloc-256    256      45      90         612       0      62      34560        0
        malloc-256    256      19     116         110       0      62      34560        0
        malloc-256    256      38      97         635       0      62      34560        0
        malloc-256    256       4     131          43       0      62      34560        0
      malloc-32768  32768       1       0           1       0       1      32768        0
      malloc-32768  32768       0       1           1       0       1      32768        0
      malloc-32768  32768       0       1          48       0       1      32768        0
      malloc-32768  32768       1       0           1       0       1      32768        0
      malloc-32768  32768       1       0           1       0       1      32768        0
       malloc-8192   8192       4       0           4       0       1      32768        0
       malloc-2048   2048       3      13          11       0       8      32768        0
       malloc-2048   2048       3      13         216       0       8      32768        0
       malloc-2048   2048       4      12           4       0       8      32768        0
       malloc-2048   2048       3      13          21       0       8      32768        0
       malloc-1024   1024       4      28           4       0      16      32768        0
       malloc-1024   1024      16      16          27       0      16      32768        0
       malloc-1024   1024       2      30           2       0      16      32768        0
       malloc-1024   1024       7      25          25       0      16      32768        0
       malloc-1024   1024       6      26         895       0      16      32768        0
        malloc-512    512      11      53          19       0      30      32768        0
        malloc-512    512       2      62           2       0      30      32768        0
        malloc-512    512       2      62           9       0      30      32768        0
           pcpu-64     64     463      49         463       0     254      32768        0
            pcpu-8      8    3342     754        3365       0     254      32768        0
            cpuset    104       7     272           7       0     126      29016        0
         malloc-32     32     259     623        5278       0     254      28224        0
          4 Bucket     48       5     583          54       0     254      28224        0
         tcp_inpcb    424       4      59          10       0      30      26712        0
              pipe    744       6      29         289       0      16      26040        0
         TURNSTILE    136     111      78         111       0      62      25704        0
       malloc-8192   8192       3       0           3       0       1      24576        0
       malloc-4096   4096       3       3         322       0       2      24576        0
       malloc-4096   4096       5       1           5       0       2      24576        0
           rtentry    176      11     127          14       0      62      24288        0
              PGRP     88      15     261          31       0     126      24288        0
    ertt_txseginfo     40       0     606         257       0     254      24240        0
          rl_entry     40      22     584          24       0     254      24240        0
             Files     80      78     222        6843       0     126      24000        0
          8 Bucket     80      28     272         170       0     126      24000        0
        malloc-384    384       0      60           2       0      30      23040        0
        malloc-384    384      26      34          27       0      30      23040        0
        malloc-384    384       1      59           3       0      30      23040        0
        SLEEPQUEUE     88     111     145         111       0     126      22528        0
         hostcache     64       1     314           1       0     254      20160        0
             udpcb     32       2     628          60       0     254      20160        0
   tcp_inpcb ports     32       2     628           2       0     254      20160        0
   udp_inpcb ports     32       1     629           7       0     254      20160        0
              ertt     72       4     276          10       0     126      20160        0
               PWD     32      11     619          95       0     254      20160        0
         malloc-32     32       4     626           9       0     254      20160        0
         malloc-32     32      78     552         203       0     254      20160        0
         malloc-32     32      81     549         793       0     254      20160        0
         malloc-32     32      19     611          21       0     254      20160        0
         malloc-32     32      48     582         320       0     254      20160        0
         malloc-32     32      13     617          38       0     254      20160        0
         16 Bucket    144      38     102         155       0      62      20160        0
          2 Bucket     32      44     586         268       0     254      20160        0
            ttyinq    160      15     110          45       0      62      20000        0
       Mountpoints   2752       2       5           2       0       4      19264        0
 epoch_record pcpu    256       4      60           4       0      62      16384        0
      malloc-16384  16384       0       1          64       0       1      16384        0
      malloc-16384  16384       1       0           1       0       1      16384        0
      malloc-16384  16384       1       0           1       0       1      16384        0
      malloc-16384  16384       1       0           1       0       1      16384        0
       malloc-8192   8192       2       0           2       0       1      16384        0
       malloc-4096   4096       1       3           4       0       2      16384        0
       malloc-4096   4096       2       2          15       0       2      16384        0
       malloc-4096   4096       4       0           4       0       2      16384        0
       malloc-2048   2048       1       7           1       0       8      16384        0
       malloc-2048   2048       4       4           4       0       8      16384        0
       malloc-1024   1024       1      15           1       0      16      16384        0
       malloc-1024   1024       7       9           7       0      16      16384        0
        malloc-512    512       0      32           1       0      30      16384        0
        malloc-512    512       2      30           2       0      30      16384        0
           SMR CPU     32       7     504           7       0     254      16352        0
               ipq     56       0     288          24       0     254      16128        0
         malloc-16     16     451     549        2334       0     254      16000        0
              kenv    258       2      58         702       0      30      15480        0
             ripcb    424       1      35           1       0      30      15264        0
              vmem   1856       1       7           1       0       8      14848        0
        SMR SHARED     24       7     504           7       0     254      12264        0
         malloc-16     16       1     749         174       0     254      12000        0
         malloc-16     16      16     734         139       0     254      12000        0
         malloc-16     16      16     734          74       0     254      12000        0
         malloc-16     16      44     706       27620       0     254      12000        0
         malloc-16     16      16     734        1306       0     254      12000        0
         malloc-16     16       9     741          39       0     254      12000        0
       L VFS Cache    320       0      36           1       0      30      11520        0
        malloc-384    384       1      29           1       0      30      11520        0
        malloc-384    384      13      17          13       0      30      11520        0
       malloc-8192   8192       1       0           1       0       1       8192        0
       malloc-8192   8192       1       0           1       0       1       8192        0
       malloc-4096   4096       1       1           1       0       2       8192        0
      vtnet_tx_hdr     24       1     333        6910       0     254       8016        0
           pcpu-16     16       7     249           7       0     254       4096        0
       UMA Slabs 1    176       8      14           8       0      62       3872        0
        KMAP ENTRY     96      14      25          16       0       0       3744        0
            pcpu-4      4       3     509           3       0     254       2048        0
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
# {Threaded:false Repeat:true RepeatTimes:0 Procs:2 Slowdown:1 Sandbox: Leak:false NetInjection:false NetDevices:false NetReset:false Cgroups:false BinfmtMisc:false CloseFDs:false KCSAN:false DevlinkPCI:false USB:false VhciInjection:false Wifi:false IEEE802154:false Sysctl:false UseTmpDir:false HandleSegv:false Repro:false Trace:false LegacyOptions:{Collide:false Fault:false FaultCall:0 FaultNth:0}}
r0 = openat$ptmx(0xffffffffffffff9c, &(0x7f0000001640), 0x101, 0x0)
ioctl$DIOCRTSTADDRS(0xffffffffffffffff, 0xc4504449, &(0x7f0000001040)={{"c84fb2dcdb03f4b31124ae09b24d5f2ad4f145ba81e72ae57be098ff502ab50ff4e98d0f5c99ec8405d57b379f95b82e936254d65193a684497de742d0bac85b019bd5fa6550cd181cbd9e21e896edd558b5d4f545905887e0f244734665501cec48e045d506c54c8bbbfb5144a9e4ea7c46cf4e3b869f67692b9bfca41665cd4489bf28facd312b70ebe56feedbd5dbe6105c0eb8ef09da04df8bf1bc86bf21f2b0822a6f0d4894c198ff2243909e205489d367065597b7d903f8cac436d117bfe6a50605ae2d18c3deeb4350796d1c06390ba6069cdc13ff0acb6f6ef7c735f4dc239bb8c3395004d351bdb19c7a047a3b2b8bf20b4de728f6295786459d7c7a19876a57c47373e4f77672593abd555dba03a8baa3656902e3fb2a16d27f36d045788730c15119af575ef44280b5b16a8e30c41c1db225ea552aa6b02a6c708bbd972f7025912b1c1442a9688591134105e6e2fa695321c28101fc86a4af76745797a079d434acd31cc1e53f1a2aa24e189d691526f8ece212cae4455aedb97850c6731002c83b98c23e63a6ef44f7090334778eea9965fc7b19c76b22f5f14eca42697beb7a992c864353b05b7bfec1952de0a0d8f5e0268b900dd7f170cc39302aea784c4a8192f3e52c0054d11856349ab29ccd355721f81bfe29400c2f8d6f9b78b05195cb3c0b68b2856a02f4ebf843b2a73f64678c909c2e0360b418c1d9352d08ad21e44eafefe0a0bf2e9470eeca993a2224232c16ed2cbc14fc45a8f201d46d7e686cd818fca3c9be6861aa51983a714d1436388fb3ae9462f7e9c4c9ae91cbc6be2270106b389ec932048a79e8f4a8ed326d289b0f65dbba015a63f4e2c2e6ef1d6545718ab449e6cf8367ba111887a3baaf8c6c1c120ff52a1f8bdc28f90202abfec25d496a7afd88801ccc261707b68711b980050e1d6f4a4693defd9ac85b03b6229a9c025d59f74ea623c088fad4725a8b71fa8ab801776746a2db03e76525809b22ddd5b6bcdcec12087e657017b4b4ac2df08942652216a2165c9580cdf9a54307670ad9fe1cf23fe97e5467ba2b99aac7fd2539448cf5a46e23b2bfefd325ff8cb3e0bea18108a194403b83a065fbe7477ab31671d7ed7b16f4d047683be701175a3da62a31037eb39808704a916776a3886a9a90f45d3dcdec51feab9e180a894d654b0f667125ef55a09d18ade7199968f27e3c46ac1e11e340b91c6117649f0e68a0980f5e14679c9c654b592049419ba187c91c9fc9df4141dad9bc6906eb615e93c4a794adbca14517b4279553ec04fa95e66d143eb3fc963d99e2a426fb296d93af828b4c7ac1f8031c7dc537249722a60ccf6ca53dc3395c2e8046764d573aa5e3a4c580e30bf129e05207926606222fa475543cd87b8f6839534c77ea909778865d2b19d68deb801a32f5215dced32dcfef6b", "f93fe2535820ee1aad80b4424d8bd24fc38bb4d0fab1909a8bd12f6dba38cc7f"}, 0x0, 0x0, 0x0, 0x2})
ioctl$DIOCCHANGERULE(r0, 0xcbe0441a, &(0x7f0000001480))


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

uint64_t r[1] = {0xffffffffffffffff};

void execute_one(void)
{
  intptr_t res = 0;
  memcpy((void*)0x20001640, "/dev/pf\000", 8);
  res = syscall(SYS_openat, 0xffffffffffffff9cul, 0x20001640ul, 0x101ul, 0ul);
  if (res != -1)
    r[0] = res;
  memcpy(
      (void*)0x20001040,
      "\xc8\x4f\xb2\xdc\xdb\x03\xf4\xb3\x11\x24\xae\x09\xb2\x4d\x5f\x2a\xd4\xf1"
      "\x45\xba\x81\xe7\x2a\xe5\x7b\xe0\x98\xff\x50\x2a\xb5\x0f\xf4\xe9\x8d\x0f"
      "\x5c\x99\xec\x84\x05\xd5\x7b\x37\x9f\x95\xb8\x2e\x93\x62\x54\xd6\x51\x93"
      "\xa6\x84\x49\x7d\xe7\x42\xd0\xba\xc8\x5b\x01\x9b\xd5\xfa\x65\x50\xcd\x18"
      "\x1c\xbd\x9e\x21\xe8\x96\xed\xd5\x58\xb5\xd4\xf5\x45\x90\x58\x87\xe0\xf2"
      "\x44\x73\x46\x65\x50\x1c\xec\x48\xe0\x45\xd5\x06\xc5\x4c\x8b\xbb\xfb\x51"
      "\x44\xa9\xe4\xea\x7c\x46\xcf\x4e\x3b\x86\x9f\x67\x69\x2b\x9b\xfc\xa4\x16"
      "\x65\xcd\x44\x89\xbf\x28\xfa\xcd\x31\x2b\x70\xeb\xe5\x6f\xee\xdb\xd5\xdb"
      "\xe6\x10\x5c\x0e\xb8\xef\x09\xda\x04\xdf\x8b\xf1\xbc\x86\xbf\x21\xf2\xb0"
      "\x82\x2a\x6f\x0d\x48\x94\xc1\x98\xff\x22\x43\x90\x9e\x20\x54\x89\xd3\x67"
      "\x06\x55\x97\xb7\xd9\x03\xf8\xca\xc4\x36\xd1\x17\xbf\xe6\xa5\x06\x05\xae"
      "\x2d\x18\xc3\xde\xeb\x43\x50\x79\x6d\x1c\x06\x39\x0b\xa6\x06\x9c\xdc\x13"
      "\xff\x0a\xcb\x6f\x6e\xf7\xc7\x35\xf4\xdc\x23\x9b\xb8\xc3\x39\x50\x04\xd3"
      "\x51\xbd\xb1\x9c\x7a\x04\x7a\x3b\x2b\x8b\xf2\x0b\x4d\xe7\x28\xf6\x29\x57"
      "\x86\x45\x9d\x7c\x7a\x19\x87\x6a\x57\xc4\x73\x73\xe4\xf7\x76\x72\x59\x3a"
      "\xbd\x55\x5d\xba\x03\xa8\xba\xa3\x65\x69\x02\xe3\xfb\x2a\x16\xd2\x7f\x36"
      "\xd0\x45\x78\x87\x30\xc1\x51\x19\xaf\x57\x5e\xf4\x42\x80\xb5\xb1\x6a\x8e"
      "\x30\xc4\x1c\x1d\xb2\x25\xea\x55\x2a\xa6\xb0\x2a\x6c\x70\x8b\xbd\x97\x2f"
      "\x70\x25\x91\x2b\x1c\x14\x42\xa9\x68\x85\x91\x13\x41\x05\xe6\xe2\xfa\x69"
      "\x53\x21\xc2\x81\x01\xfc\x86\xa4\xaf\x76\x74\x57\x97\xa0\x79\xd4\x34\xac"
      "\xd3\x1c\xc1\xe5\x3f\x1a\x2a\xa2\x4e\x18\x9d\x69\x15\x26\xf8\xec\xe2\x12"
      "\xca\xe4\x45\x5a\xed\xb9\x78\x50\xc6\x73\x10\x02\xc8\x3b\x98\xc2\x3e\x63"
      "\xa6\xef\x44\xf7\x09\x03\x34\x77\x8e\xea\x99\x65\xfc\x7b\x19\xc7\x6b\x22"
      "\xf5\xf1\x4e\xca\x42\x69\x7b\xeb\x7a\x99\x2c\x86\x43\x53\xb0\x5b\x7b\xfe"
      "\xc1\x95\x2d\xe0\xa0\xd8\xf5\xe0\x26\x8b\x90\x0d\xd7\xf1\x70\xcc\x39\x30"
      "\x2a\xea\x78\x4c\x4a\x81\x92\xf3\xe5\x2c\x00\x54\xd1\x18\x56\x34\x9a\xb2"
      "\x9c\xcd\x35\x57\x21\xf8\x1b\xfe\x29\x40\x0c\x2f\x8d\x6f\x9b\x78\xb0\x51"
      "\x95\xcb\x3c\x0b\x68\xb2\x85\x6a\x02\xf4\xeb\xf8\x43\xb2\xa7\x3f\x64\x67"
      "\x8c\x90\x9c\x2e\x03\x60\xb4\x18\xc1\xd9\x35\x2d\x08\xad\x21\xe4\x4e\xaf"
      "\xef\xe0\xa0\xbf\x2e\x94\x70\xee\xca\x99\x3a\x22\x24\x23\x2c\x16\xed\x2c"
      "\xbc\x14\xfc\x45\xa8\xf2\x01\xd4\x6d\x7e\x68\x6c\xd8\x18\xfc\xa3\xc9\xbe"
      "\x68\x61\xaa\x51\x98\x3a\x71\x4d\x14\x36\x38\x8f\xb3\xae\x94\x62\xf7\xe9"
      "\xc4\xc9\xae\x91\xcb\xc6\xbe\x22\x70\x10\x6b\x38\x9e\xc9\x32\x04\x8a\x79"
      "\xe8\xf4\xa8\xed\x32\x6d\x28\x9b\x0f\x65\xdb\xba\x01\x5a\x63\xf4\xe2\xc2"
      "\xe6\xef\x1d\x65\x45\x71\x8a\xb4\x49\xe6\xcf\x83\x67\xba\x11\x18\x87\xa3"
      "\xba\xaf\x8c\x6c\x1c\x12\x0f\xf5\x2a\x1f\x8b\xdc\x28\xf9\x02\x02\xab\xfe"
      "\xc2\x5d\x49\x6a\x7a\xfd\x88\x80\x1c\xcc\x26\x17\x07\xb6\x87\x11\xb9\x80"
      "\x05\x0e\x1d\x6f\x4a\x46\x93\xde\xfd\x9a\xc8\x5b\x03\xb6\x22\x9a\x9c\x02"
      "\x5d\x59\xf7\x4e\xa6\x23\xc0\x88\xfa\xd4\x72\x5a\x8b\x71\xfa\x8a\xb8\x01"
      "\x77\x67\x46\xa2\xdb\x03\xe7\x65\x25\x80\x9b\x22\xdd\xd5\xb6\xbc\xdc\xec"
      "\x12\x08\x7e\x65\x70\x17\xb4\xb4\xac\x2d\xf0\x89\x42\x65\x22\x16\xa2\x16"
      "\x5c\x95\x80\xcd\xf9\xa5\x43\x07\x67\x0a\xd9\xfe\x1c\xf2\x3f\xe9\x7e\x54"
      "\x67\xba\x2b\x99\xaa\xc7\xfd\x25\x39\x44\x8c\xf5\xa4\x6e\x23\xb2\xbf\xef"
      "\xd3\x25\xff\x8c\xb3\xe0\xbe\xa1\x81\x08\xa1\x94\x40\x3b\x83\xa0\x65\xfb"
      "\xe7\x47\x7a\xb3\x16\x71\xd7\xed\x7b\x16\xf4\xd0\x47\x68\x3b\xe7\x01\x17"
      "\x5a\x3d\xa6\x2a\x31\x03\x7e\xb3\x98\x08\x70\x4a\x91\x67\x76\xa3\x88\x6a"
      "\x9a\x90\xf4\x5d\x3d\xcd\xec\x51\xfe\xab\x9e\x18\x0a\x89\x4d\x65\x4b\x0f"
      "\x66\x71\x25\xef\x55\xa0\x9d\x18\xad\xe7\x19\x99\x68\xf2\x7e\x3c\x46\xac"
      "\x1e\x11\xe3\x40\xb9\x1c\x61\x17\x64\x9f\x0e\x68\xa0\x98\x0f\x5e\x14\x67"
      "\x9c\x9c\x65\x4b\x59\x20\x49\x41\x9b\xa1\x87\xc9\x1c\x9f\xc9\xdf\x41\x41"
      "\xda\xd9\xbc\x69\x06\xeb\x61\x5e\x93\xc4\xa7\x94\xad\xbc\xa1\x45\x17\xb4"
      "\x27\x95\x53\xec\x04\xfa\x95\xe6\x6d\x14\x3e\xb3\xfc\x96\x3d\x99\xe2\xa4"
      "\x26\xfb\x29\x6d\x93\xaf\x82\x8b\x4c\x7a\xc1\xf8\x03\x1c\x7d\xc5\x37\x24"
      "\x97\x22\xa6\x0c\xcf\x6c\xa5\x3d\xc3\x39\x5c\x2e\x80\x46\x76\x4d\x57\x3a"
      "\xa5\xe3\xa4\xc5\x80\xe3\x0b\xf1\x29\xe0\x52\x07\x92\x66\x06\x22\x2f\xa4"
      "\x75\x54\x3c\xd8\x7b\x8f\x68\x39\x53\x4c\x77\xea\x90\x97\x78\x86\x5d\x2b"
      "\x19\xd6\x8d\xeb\x80\x1a\x32\xf5\x21\x5d\xce\xd3\x2d\xcf\xef\x6b",
      1024);
  memcpy((void*)0x20001440,
         "\xf9\x3f\xe2\x53\x58\x20\xee\x1a\xad\x80\xb4\x42\x4d\x8b\xd2\x4f\xc3"
         "\x8b\xb4\xd0\xfa\xb1\x90\x9a\x8b\xd1\x2f\x6d\xba\x38\xcc\x7f",
         32);
  *(uint32_t*)0x20001460 = 0;
  *(uint8_t*)0x20001464 = 0;
  *(uint64_t*)0x20001468 = 0;
  *(uint64_t*)0x20001470 = 0;
  *(uint64_t*)0x20001478 = 0;
  *(uint64_t*)0x20001480 = 2;
  *(uint64_t*)0x20001488 = 0;
  *(uint64_t*)0x20001490 = 0;
  *(uint64_t*)0x20001498 = 0;
  *(uint64_t*)0x200014a0 = 0;
  *(uint32_t*)0x200014a8 = 0;
  syscall(SYS_ioctl, -1, 0xc4504449ul, 0x20001040ul);
  syscall(SYS_ioctl, r[0], 0xcbe0441aul, 0x20001480ul);
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


