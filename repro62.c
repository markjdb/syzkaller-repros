Syzkaller hit 'panic: AEAD without a separate IV' bug.

login: panic: AEAD without a separate IV
cpuid = 1
time = 1632792686
KDB: stack backtrace:
db_trace_self_wrapper() at db_trace_self_wrapper+0xc7/frame 0xfffffe0053f4b070
kdb_backtrace() at kdb_backtrace+0xd3/frame 0xfffffe0053f4b1d0
vpanic() at vpanic+0x2c5/frame 0xfffffe0053f4b2b0
panic() at panic+0xb5/frame 0xfffffe0053f4b380
crp_sanity() at crp_sanity+0xbc9/frame 0xfffffe0053f4b3e0
crypto_dispatch() at crypto_dispatch+0x1a/frame 0xfffffe0053f4b410
crypto_ioctl() at crypto_ioctl+0x32ff/frame 0xfffffe0053f4b650
devfs_ioctl() at devfs_ioctl+0x22a/frame 0xfffffe0053f4b730
vn_ioctl() at vn_ioctl+0x215/frame 0xfffffe0053f4ba80
devfs_ioctl_f() at devfs_ioctl_f+0x71/frame 0xfffffe0053f4bad0
kern_ioctl() at kern_ioctl+0x62e/frame 0xfffffe0053f4bbd0
sys_ioctl() at sys_ioctl+0x3b6/frame 0xfffffe0053f4bd50
amd64_syscall() at amd64_syscall+0x3de/frame 0xfffffe0053f4bf30
fast_syscall_common() at fast_syscall_common+0xf8/frame 0xfffffe0053f4bf30
--- syscall (0, FreeBSD ELF64, nosys), rip = 0x23332a, rsp = 0x7fffffffea68, rbp = 0x7fffffffea80 ---
KDB: enter: panic
[ thread pid 824 tid 100084 ]
Stopped at      kdb_enter+0x6b: movq    $0,0x28d3aca(%rip)
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
rcx         0x67022ac0b398fb06
rdx         0xdffff7c000000000
rbx                          0
rsp         0xfffffe0053f4b1b0
rbp         0xfffffe0053f4b1d0
rsi                        0x1
rdi                          0
r8                         0x3
r9          0xfffffe0053f4ace8
r10                          0
r11         0xfffffe00667b6c30
r12         0xfffffe00667b6720
r13         0xfffffe0053f4b201
r14         0xffffffff82c4a5e0  .str.18
r15         0xffffffff82c4a5e0  .str.18
rip         0xffffffff817aba6b  kdb_enter+0x6b
rflags                    0x46
kdb_enter+0x6b: movq    $0,0x28d3aca(%rip)
db> show proc
Process 824 (syz-executor3452553) at 0xfffffe008e62b538:
 state: NORMAL
 uid: 0  gids: 0, 0, 5
 parent: pid 822 at 0xfffffe00667d3538
 ABI: FreeBSD ELF64
 flag: 0x10004000  flag2: 0
 arguments: /root/syz-executor345255302
 reaper: 0xfffffe0053d51538 reapsubtree: 1
 sigparent: 20
 vmspace: 0xfffffe008fabc000
   (map 0xfffffe008fabc000)
   (map.pmap 0xfffffe008fabc0c0)
   (pmap 0xfffffe008fabc120)
 threads: 1
100084                   Run     CPU 1                       syz-executor3452553
db> ps
  pid  ppid  pgrp   uid  state   wmesg   wchan               cmd
  824   822   822     0  R       CPU 1                       syz-executor3452553
  822   820   822     0  Ss      pause   0xfffffe00667d35e8  csh
  820   735   820     0  Rs      CPU 0                       sshd
  797     1   797     0  Ss+     ttyin   0xfffffe00543fd0b0  getty
  793     1   793     0  Ss      select  0xfffffe008fa32140  logger
  787     1    22     0  S+      piperd  0xfffffe00667c4000  logger
  786   785    22     0  S+      nanslp  0xffffffff8404c480  sleep
  785     1    22     0  S+      wait    0xfffffe008f995000  sh
  781     1   781    25  Ss      pause   0xfffffe008fa6f5e8  sendmail
  778     1   778     0  Ss      select  0xfffffe008fa32340  sendmail
  739     1   739     0  Ss      nanslp  0xffffffff8404c481  cron
  735     1   735     0  Ss      select  0xfffffe0057018dc0  sshd
  646     1   646     0  Ss      select  0xfffffe008e627040  syslogd
  449     1   449     0  Ss      select  0xfffffe008e6277c0  devd
  352     1   352    65  Ss      select  0xfffffe0057018e40  dhclient
  270     1   270     0  Ss      select  0xfffffe008e627a40  dhclient
  267     1   267     0  Ss      select  0xfffffe0057018bc0  dhclient
   95     0     0     0  DL      pftm    0xffffffff8491e1f0  [pf purge]
   21     0     0     0  DL      syncer  0xffffffff841747a0  [syncer]
   20     0     0     0  DL      vlruwt  0xfffffe005713b538  [vnlru]
   19     0     0     0  DL      (threaded)                  [bufdaemon]
100071                   D       qsleep  0xffffffff841724a0  [bufdaemon]
100074                   D       -       0xffffffff83411f80  [bufspacedaemon-0]
100085                   D       sdflush 0xfffffe00543e28e8  [/ worker]
   18     0     0     0  DL      psleep  0xffffffff841a7980  [vmdaemon]
   17     0     0     0  DL      (threaded)                  [pagedaemon]
100069                   D       psleep  0xffffffff8419b4b8  [dom0]
100075                   D       launds  0xffffffff8419b4c4  [laundry: dom0]
100076                   D       umarcl  0xffffffff81e8f430  [uma]
   16     0     0     0  DL      -       0xffffffff83e02b20  [rand_harvestq]
   15     0     0     0  DL      -       0xffffffff8416d6c0  [soaiod4]
    9     0     0     0  DL      -       0xffffffff8416d6c0  [soaiod3]
    8     0     0     0  DL      -       0xffffffff8416d6c0  [soaiod2]
    7     0     0     0  DL      -       0xffffffff8416d6c0  [soaiod1]
    6     0     0     0  DL      (threaded)                  [cam]
100046                   D       -       0xffffffff83c883c0  [doneq0]
100047                   D       -       0xffffffff83c88340  [async]
100068                   D       -       0xffffffff83c881c0  [scanner]
   14     0     0     0  DL      seqstat 0xfffffe00540b7888  [sequencer 00]
    5     0     0     0  DL      crypto_ 0xfffffe00540d9d80  [crypto returns 1]
    4     0     0     0  DL      crypto_ 0xfffffe00540d9d30  [crypto returns 0]
    3     0     0     0  DL      crypto_ 0xffffffff841955e0  [crypto]
   13     0     0     0  DL      (threaded)                  [geom]
100037                   D       -       0xffffffff8401fa00  [g_event]
100038                   D       -       0xffffffff8401fa40  [g_up]
100039                   D       -       0xffffffff8401fa80  [g_down]
    2     0     0     0  DL      (threaded)                  [KTLS]
100029                   D       -       0xfffffe0053c09d00  [thr_0]
100030                   D       -       0xfffffe0053c09d80  [thr_1]
100031                   D       -       0xffffffff8416ea48  [alloc_0]
   12     0     0     0  WL      (threaded)                  [intr]
100010                   I                                   [swi5: fast taskq]
100018                   I                                   [swi6: task queue]
100019                   I                                   [swi6: Giant taskq]
100032                   I                                   [swi1: netisr 0]
100033                   I                                   [swi3: vm]
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
100086                   I                                   [swi1: pf send]
   11     0     0     0  RL      (threaded)                  [idle]
100003                   CanRun                              [idle: cpu0]
100004                   CanRun                              [idle: cpu1]
    1     0     1     0  SLs     wait    0xfffffe0053d51538  [init]
   10     0     0     0  DL      audit_w 0xffffffff84196580  [audit]
    0     0     0     0  DLs     (threaded)                  [kernel]
100000                   D       swapin  0xffffffff84020900  [swapper]
100005                   D       -       0xfffffe0053c0b900  [if_io_tqg_0]
100006                   D       -       0xfffffe0053c0b700  [if_io_tqg_1]
100007                   D       -       0xfffffe0053c0b500  [if_config_tqg_0]
100008                   D       -       0xfffffe0053c0b300  [softirq_0]
100009                   D       -       0xfffffe0053c0b100  [softirq_1]
100011                   D       -       0xfffffe0053df3c00  [in6m_free taskq]
100012                   D       -       0xfffffe0053df3a00  [kqueue_ctx taskq]
100013                   D       -       0xfffffe0053df3800  [pci_hp taskq]
100014                   D       -       0xfffffe0053df3600  [aiod_kick taskq]
100015                   D       -       0xfffffe0053df3400  [inm_free taskq]
100016                   D       -       0xfffffe0053df3200  [deferred_unmount ta]
100017                   D       -       0xfffffe0053df3000  [linuxkpi_irq_wq]
100020                   D       -       0xfffffe0053dfe900  [thread taskq]
100021                   D       -       0xfffffe0053dfe700  [linuxkpi_short_wq_0]
100022                   D       -       0xfffffe0053dfe700  [linuxkpi_short_wq_1]
100023                   D       -       0xfffffe0053dfe700  [linuxkpi_short_wq_2]
100024                   D       -       0xfffffe0053dfe700  [linuxkpi_short_wq_3]
100025                   D       -       0xfffffe0053dfe200  [linuxkpi_long_wq_0]
100026                   D       -       0xfffffe0053dfe200  [linuxkpi_long_wq_1]
100027                   D       -       0xfffffe0053dfe200  [linuxkpi_long_wq_2]
100028                   D       -       0xfffffe0053dfe200  [linuxkpi_long_wq_3]
100036                   D       -       0xfffffe0054009500  [firmware taskq]
100040                   D       -       0xfffffe00540dae00  [crypto_0]
100041                   D       -       0xfffffe00540dae00  [crypto_1]
100051                   D       -       0xfffffe0054251500  [vtnet0 rxq 0]
100052                   D       -       0xfffffe0054251400  [vtnet0 txq 0]
100062                   D       -       0xffffffff82c51480  [deadlkres]
100064                   D       -       0xfffffe0056c0fb00  [acpi_task_0]
100065                   D       -       0xfffffe0056c0fb00  [acpi_task_1]
100066                   D       -       0xfffffe0056c0fb00  [acpi_task_2]
100067                   D       -       0xfffffe00540da600  [CAM taskq]
db> show all locks
Process 820 (sshd) thread 0xfffffe00667b7560 (100082)
exclusive sleep mutex vtnet0-tx0 (vtnet0-tx0) r = 0 (0xfffffe0054285d00) locked @ /root/freebsd/sys/dev/virtio/network/if_vtnet.c:2744
exclusive rw tcpinp (tcpinp) r = 0 (0xfffffe008fa447e0) locked @ /root/freebsd/sys/netinet/tcp_usrreq.c:1018
exclusive sx so_snd_sx (so_snd_sx) r = 0 (0xfffffe008fa6c500) locked @ /root/freebsd/sys/kern/uipc_socket.c:4157
db> show malloc
              Type        InUse        MemUse     Requests
           pf_hash            5        11524K            5
         sysctloid        31142         1832K        31184
              kobj          323         1292K          479
            newblk          734         1208K          769
            linker          232         1193K          245
            devbuf         1356         1136K         1373
          vfscache            3         1025K            3
          inodedep           62          535K           99
         ufs_quota            1          512K            1
          vfs_hash            1          512K            1
           callout            2          512K            2
              intr            4          472K            4
               pcb           16          393K           32
           subproc           89          179K          874
         vnet_data            1          168K            1
           tidhash            3          141K            3
           pagedep           22          134K           33
        tfo_ccache            1          128K            1
               sem            4          106K            4
            DEVFS1           91           91K          103
               bus          963           77K         2574
            bus-sc           31           76K         1066
              vmem            3           73K            3
          mtx_pool            2           72K            2
          syncache            1           68K            1
          acpitask            1           64K            1
       ddb_capture            1           64K            1
            module          491           62K          491
            acpica          420           39K        63114
               LRO            2           33K            2
         hostcache            1           32K            1
               shm            1           32K            1
               msg            4           30K            4
           kdtrace          146           29K          931
            DEVFS3          110           28K          126
              umtx          220           28K          220
        gtaskqueue           18           26K           18
            kbdmux            5           22K            5
        DEVFS_RULE           59           21K           59
           ithread          104           19K          104
               BPF           10           18K           10
              temp           15           17K         1525
         ufs_mount            4           17K            5
              proc            3           17K            3
            KTRACE          100           13K          100
           devstat            6           13K            6
              rman          102           12K          526
            ifaddr           29           11K           30
      eventhandler          125           11K          125
              GEOM           61           10K          502
              kenv           59           10K           59
          routetbl           44           10K          142
         bmsafemap            2            9K           92
              UART           12            9K           12
               rpc            2            8K            2
             shmfd            1            8K            1
       pfs_vncache            1            8K            1
         pfs_nodes           20            8K           20
     audit_evclass          237            8K          295
            diradd           46            6K          107
         taskqueue           54            6K           54
            sglist            3            6K            3
              cred           20            5K          298
       ufs_dirhash           24            5K           24
             ifnet            3            5K            3
               UMA          250            5K          250
           io_apic            1            4K            1
       fpukern_ctx            2            4K            2
               tty            4            4K            4
             evdev            4            4K            4
          filedesc            1            4K            1
             hhook           13            4K           13
          pf_ifnet            5            3K            6
           lltable           10            3K           10
            plimit           11            3K          243
           acpisem           21            3K           21
            kqueue           40            3K          825
           pwddesc           40            3K          825
             xform            8            3K          145
           uidinfo            4            3K            9
             lockf           21            3K           32
        local_apic            1            2K            1
         ipsec-saq            2            2K            2
           CAM DEV            1            2K            2
           session           15            2K           32
               msi           13            2K           13
            crypto            5            2K            5
             selfd           26            2K        13947
          pci_link           16            2K           16
            Unitno           25            2K           45
         proc-args           34            2K          506
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
            isadev            5            1K            5
           CAM XPT           11            1K           12
            dirrem            2            1K           46
          in_multi            2            1K            3
              pfil            4            1K            4
              cdev            2            1K            2
 encap_export_host            8            1K            8
            DEVFSP            6            1K           23
            ip6ndp            3            1K            3
    chacha20random            1            1K            1
        CAM periph            2            1K           14
               osd            3            1K            9
      NFSD lckfile            1            1K            1
     NFSD V4client            1            1K            1
             DEVFS            9            1K           10
               MCA            2            1K            2
               mld            2            1K            2
              igmp            2            1K            2
            vnodes            1            1K            1
              ktls            1            1K            1
          procdesc            2            1K           20
       inpcbpolicy            7            1K           71
            feeder            7            1K            7
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
          freework            1            1K           26
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
           pf_rule            0            0K            0
           pf_altq            0            0K            0
           pf_osfp            0            0K            0
           pf_temp            0            0K            0
      NFSCL lckown            0            0K            0
      NFSCL client            0            0K            0
        madt_table            0            0K            2
          smartpqi            0            0K            0
       NFSCL deleg            0            0K            0
        NFSCL open            0            0K            0
       NFSCL owner            0            0K            0
            NFS fh            0            0K            0
           NFS req            0            0K            0
     NFSD usrgroup            0            0K            0
       NFSD string            0            0K            0
              iavf            0            0K            0
               ixl            0            0K            0
       NFSD V4lock            0            0K            0
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
           memdesc            0            0K            0
        evtchn_dev            0            0K            0
          xen_intr            0            0K            0
          xenstore            0            0K            0
         ciss_data            0            0K            0
           xen_hvm            0            0K            0
         legacydrv            0            0K            0
            qpidrv            0            0K            0
         BACKLIGHT            0            0K            0
               xnb            0            0K            0
      dmar_idpgtbl            0            0K            0
          dmar_dom            0            0K            0
          dmar_ctx            0            0K            0
              xbbd            0            0K            0
               xbd            0            0K            0
           Balloon            0            0K            0
              isci            0            0K            0
      iommu_dmamap            0            0K            0
     hyperv_socket            0            0K            0
           bxe_ilt            0            0K            0
          sysmouse            0            0K            0
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
            statfs            0            0K         1096
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
               iov            0            0K         7905
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
db> show uma
              Zone   Size    Used    Free    Requests  Sleeps  Bucket  Total Mem    XFree
   mbuf_jumbo_page   4096    1088    1033       16856       0     254    8687616        0
              pbuf   2624       0     794           0       0       2    2083456        0
          BUF TRIE    144     185   11631         508       0      62    1701504        0
       malloc-4096   4096     364       3        1305       0       2    1503232        0
        malloc-128    128   10527      44       10586       0     126    1353088        0
              mbuf    256    1347    1068       26093       0     254     618240        0
        malloc-512    512    1027       5        1027       0      30     528384        0
        RADIX NODE    144    2396     343       29392       0      62     394416        0
      malloc-65536  65536       6       0           6       0       1     393216        0
            lkpimm    168       1    2327           1       0      62     391104        0
          lkpicurr    168       2    2326           2       0      62     391104        0
         vmem btag     56    6574      97        6574       0     254     373576        0
       UMA Slabs 0    112    3005      16        3005       0     126     338352        0
       malloc-2048   2048     133       1         133       0       8     274432        0
        malloc-256    256    1025      10        1766       0      62     264960        0
      malloc-65536  65536       2       2          33       0       1     262144        0
      malloc-65536  65536       2       2          71       0       1     262144        0
         VM OBJECT    264     926      64       11878       0      30     261360        0
         malloc-64     64    3906      63        5692       0     254     254016        0
             VNODE    448     523      35         553       0      30     249984        0
        256 Bucket   2048     102      16        2927       0       8     241664        0
         malloc-16     16   13319     181       14112       0     254     216000        0
            THREAD   1808     105       5         105       0       8     198880        0
            DEVCTL   1024       0     192          93       0       0     196608        0
         UMA Zones    768     222       2         222       0      16     172032        0
         malloc-32     32    4740      48        5439       0     254     153216        0
       FFS2 dinode    256     502      23         529       0      62     134400        0
      malloc-65536  65536       2       0           2       0       1     131072        0
        malloc-128    128     941      51        4380       0     126     126976        0
     FPU_save_area   1088     107       5         123       0       8     121856        0
       S VFS Cache    104     997     134        1077       0     126     117624        0
          ksiginfo    112      33    1011          65       0     126     116928        0
       malloc-1024   1024     104       8         116       0      16     114688        0
         MAP ENTRY     96     803     373       38828       0     126     112896        0
         FFS inode    192     502      44         529       0      62     104832        0
      malloc-32768  32768       2       1           3       0       1      98304        0
          UMA Kegs    384     207       6         207       0      30      81792        0
           VMSPACE   2544      18       9         804       0       4      68688        0
      mbuf_cluster   2048      30       2          30       0     254      65536        0
      malloc-65536  65536       1       0           1       0       1      65536        0
       malloc-8192   8192       8       0          49       0       1      65536        0
              PROC   1336      39       9         824       0       8      64128        0
         filedesc0   1072      40      16         825       0       8      60032        0
        malloc-384    384     122      28         161       0      30      57600        0
       malloc-8192   8192       6       1           8       0       1      57344        0
        128 Bucket   1024      37      14         529       0      16      52224        0
       malloc-8192   8192       4       2          36       0       1      49152        0
         32 Bucket    256      43     122        3791       0      62      42240        0
            clpbuf   2624       0      16          31       0      16      41984        0
         64 Bucket    512      59      21        1189       0      30      40960        0
        malloc-128    128     271      39       28797       0     126      39680        0
           DIRHASH   1024      32       4          32       0      16      36864        0
             NAMEI   1024       0      36       12441       0      16      36864        0
             g_bio    384       0      90        4741       0      30      34560        0
      malloc-32768  32768       1       0           1       0       1      32768        0
      malloc-32768  32768       1       0           1       0       1      32768        0
      malloc-32768  32768       1       0          53       0       1      32768        0
      malloc-16384  16384       1       1          65       0       1      32768        0
           pcpu-64     64     454      58         454       0     254      32768        0
            socket    960      20      12        1014       0     254      30720        0
            pcpu-8      8    3295     289        3318       0     254      28672        0
       malloc-4096   4096       4       2           6       0       2      24576        0
        malloc-384    384      51       9          71       0      30      23040        0
        malloc-256    256      57      33         220       0      62      23040        0
       malloc-4096   4096       5       0           5       0       2      20480        0
         malloc-64     64     198     117       21757       0     254      20160        0
         malloc-64     64     198     117         256       0     254      20160        0
         TURNSTILE    136     111      36         111       0      62      19992        0
       Mountpoints   2752       2       5           2       0       4      19264        0
        malloc-256    256      46      29         227       0      62      19200        0
      malloc-16384  16384       1       0           1       0       1      16384        0
      malloc-16384  16384       1       0           1       0       1      16384        0
       malloc-8192   8192       2       0           2       0       1      16384        0
       malloc-4096   4096       4       0           4       0       2      16384        0
       malloc-4096   4096       2       2           9       0       2      16384        0
       malloc-4096   4096       2       2        1400       0       2      16384        0
       malloc-2048   2048       2       6           8       0       8      16384        0
       malloc-2048   2048       4       4          34       0       8      16384        0
       malloc-1024   1024      10       6         916       0      16      16384        0
         malloc-64     64     173      79        1731       0     254      16128        0
        malloc-128    128      64      60         179       0     126      15872        0
        malloc-256    256      27      33         361       0      62      15360        0
             tcpcb   1080       4      10          10       0     254      15120        0
              pipe    744       7      13         299       0      16      14880        0
       malloc-2048   2048       4       2          24       0       8      12288        0
       malloc-2048   2048       1       5         214       0       8      12288        0
       malloc-1024   1024       5       7          12       0      16      12288        0
       malloc-1024   1024       9       3           9       0      16      12288        0
         malloc-64     64      80     109         897       0     254      12096        0
             Files     80      80      70        7030       0     126      12000        0
         udp_inpcb    496       2      22          60       0     254      11904        0
        malloc-128    128      64      29          70       0     126      11904        0
        malloc-384    384      20      10         199       0      30      11520        0
        malloc-384    384      14      16          15       0      30      11520        0
        malloc-256    256      18      27         103       0      62      11520        0
        malloc-256    256      24      21         256       0      62      11520        0
        SLEEPQUEUE     88     111      17         111       0     126      11264        0
       malloc-8192   8192       1       0           1       0       1       8192        0
       malloc-8192   8192       1       0           1       0       1       8192        0
       malloc-4096   4096       1       1           2       0       2       8192        0
       malloc-4096   4096       0       2           2       0       2       8192        0
       malloc-2048   2048       3       1           3       0       8       8192        0
       malloc-1024   1024       4       4           8       0      16       8192        0
       malloc-1024   1024       4       4         135       0      16       8192        0
        malloc-512    512       0      16         144       0      30       8192        0
        malloc-512    512       5      11          48       0      30       8192        0
        malloc-512    512       8       8           8       0      30       8192        0
           rtentry    176      11      35          14       0      62       8096        0
              PGRP     88      15      77          32       0     126       8096        0
          rl_entry     40      28     174          30       0     254       8080        0
             udpcb     32       2     250          60       0     254       8064        0
               PWD     32      11     241          96       0     254       8064        0
         malloc-64     64      40      86         313       0     254       8064        0
         malloc-64     64       6     120          10       0     254       8064        0
         malloc-64     64      88      38         131       0     254       8064        0
         malloc-32     32      41     211         202       0     254       8064        0
         malloc-32     32      24     228          38       0     254       8064        0
         malloc-32     32       7     245          40       0     254       8064        0
         malloc-32     32      21     231         160       0     254       8064        0
         malloc-32     32      58     194        5130       0     254       8064        0
         malloc-32     32      11     241          43       0     254       8064        0
         16 Bucket    144      31      25         198       0      62       8064        0
          4 Bucket     48       6     162          54       0     254       8064        0
          2 Bucket     32      42     210         473       0     254       8064        0
      vtnet_tx_hdr     24       1     333        8182       0     254       8016        0
            ttyinq    160      15      35          45       0      62       8000        0
         malloc-16     16       0     500           5       0     254       8000        0
         malloc-16     16      26     474         154       0     254       8000        0
         malloc-16     16      35     465         192       0     254       8000        0
         malloc-16     16       5     495          12       0     254       8000        0
         malloc-16     16       9     491         175       0     254       8000        0
         malloc-16     16     278     222       27733       0     254       8000        0
          8 Bucket     80      28      72         320       0     126       8000        0
         tcp_inpcb    496       4      12          10       0     254       7936        0
        malloc-128    128      40      22         171       0     126       7936        0
        malloc-128    128      27      35          42       0     126       7936        0
        malloc-128    128      16      46         239       0     126       7936        0
              kenv    258       2      28         709       0      30       7740        0
     routing nhops    256       8      22          14       0      62       7680        0
             unpcb    256      12      18         932       0     254       7680        0
           ttyoutq    256       8      22          24       0      62       7680        0
       mbuf_packet    256       0      30         101       0     254       7680        0
        malloc-384    384       2      18           2       0      30       7680        0
        malloc-384    384       1      19           3       0      30       7680        0
        malloc-256    256      19      11         255       0      62       7680        0
            cpuset    104       8      54           8       0     126       6448        0
 epoch_record pcpu    256       4      12           4       0      62       4096        0
       malloc-2048   2048       2       0           2       0       8       4096        0
       malloc-1024   1024       2       2           2       0      16       4096        0
       malloc-1024   1024       1       3           1       0      16       4096        0
        malloc-512    512       0       8           1       0      30       4096        0
        malloc-512    512       3       5           3       0      30       4096        0
           pcpu-16     16       7     249           7       0     254       4096        0
         hostcache     64       1      62           1       0     254       4032        0
          syncache    168       0      24           5       0     254       4032        0
         malloc-32     32      61      65         104       0     254       4032        0
         malloc-16     16       2     248           3       0     254       4000        0
             ripcb    496       1       7           1       0     254       3968        0
           cryptop    280       1      13           1       0      30       3920        0
       UMA Slabs 1    176       6      16           6       0      62       3872        0
       L VFS Cache    320       0      12           1       0      30       3840        0
        malloc-384    384       1       9           1       0      30       3840        0
        malloc-256    256       2      13           2       0      62       3840        0
        KMAP ENTRY     96      12      27          15       0       0       3744        0
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
        malloc-384    384       0       0           0       0      30          0        0
           pcpu-32     32       0       0           0       0     254          0        0
            pcpu-4      4       0       0           0       0     254          0        0
            fakepg    104       0       0           0       0     126          0        0
          UMA Hash    256       0       0           0       0      62          0        0


Syzkaller reproducer:
# {Threaded:false Collide:false Repeat:false RepeatTimes:0 Procs:1 Slowdown:1 Sandbox: Leak:false NetInjection:false NetDevices:false NetReset:false Cgroups:false BinfmtMisc:false CloseFDs:false KCSAN:false DevlinkPCI:false USB:false VhciInjection:false Wifi:false IEEE802154:false Sysctl:false UseTmpDir:false HandleSegv:false Repro:false Trace:false LegacyOptions:{Fault:false FaultCall:0 FaultNth:0}}
r0 = openat$crypto(0xffffffffffffff9c, &(0x7f0000000000), 0x0, 0x0)
ioctl$CIOCGSESSION2(r0, 0xc040636a, &(0x7f0000000200)={0x19, 0x0, 0x10, &(0x7f0000000240)="00c383e946c00ebb0857aec20de856c0", 0x0, 0x0, 0x0, 0x5d3d7c9})
ioctl$CIOCCRYPT(r0, 0xc0306367, &(0x7f00000002c0)={0x0, 0x1, 0x0, 0x401, &(0x7f0000000040), 0x0, 0x0, 0x0})


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
  memcpy((void*)0x20000000, "/dev/crypto\000", 12);
  res = syscall(SYS_openat, 0xffffffffffffff9cul, 0x20000000ul, 0ul, 0ul);
  if (res != -1)
    r[0] = res;
  *(uint32_t*)0x20000200 = 0x19;
  *(uint32_t*)0x20000204 = 0;
  *(uint32_t*)0x20000208 = 0x10;
  *(uint64_t*)0x20000210 = 0x20000240;
  memcpy((void*)0x20000240,
         "\x00\xc3\x83\xe9\x46\xc0\x0e\xbb\x08\x57\xae\xc2\x0d\xe8\x56\xc0",
         16);
  *(uint32_t*)0x20000218 = 0;
  *(uint64_t*)0x20000220 = 0;
  *(uint32_t*)0x20000228 = 0;
  *(uint32_t*)0x2000022c = 0x5d3d7c9;
  *(uint32_t*)0x20000230 = 0;
  *(uint32_t*)0x20000234 = 0;
  *(uint32_t*)0x20000238 = 0;
  *(uint32_t*)0x2000023c = 0;
  syscall(SYS_ioctl, r[0], 0xc040636aul, 0x20000200ul);
  *(uint32_t*)0x200002c0 = 0;
  *(uint16_t*)0x200002c4 = 1;
  *(uint16_t*)0x200002c6 = 0;
  *(uint32_t*)0x200002c8 = 0x401;
  *(uint64_t*)0x200002d0 = 0x20000040;
  *(uint64_t*)0x200002d8 = 0;
  *(uint64_t*)0x200002e0 = 0;
  *(uint64_t*)0x200002e8 = 0;
  syscall(SYS_ioctl, r[0], 0xc0306367ul, 0x200002c0ul);
  return 0;
}


