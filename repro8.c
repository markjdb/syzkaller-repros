Syzkaller hit 'panic: MSan: Uninitialized Variable In ADDR' bug.

login: panic: MSan: Uninitialized Variable In 0xffffffff85ad2798

cpuid = 0
time = 1620530394
KDB: stack backtrace:
db_trace_self_wrapper() at db_trace_self_wrapper+0xde/frame 0xfffffe00709a0e00
vpanic() at vpanic+0x656/frame 0xfffffe00709a0ec0
panic() at panic+0x1ad/frame 0xfffffe00709a0fc0
__msan_warning() at __msan_warning+0x139/frame 0xfffffe00709a1110
sse42_crc32c() at sse42_crc32c+0x488/frame 0xfffffe00709a1220
calculate_crc32c() at calculate_crc32c+0xf56/frame 0xfffffe00709a1340
ffs_ckhash_cg() at ffs_ckhash_cg+0x123/frame 0xfffffe00709a13b0
bufdone() at bufdone+0x1c35/frame 0xfffffe00709a14e0
g_io_deliver() at g_io_deliver+0x1578/frame 0xfffffe00709a1620
g_io_deliver() at g_io_deliver+0x1578/frame 0xfffffe00709a1760
g_io_deliver() at g_io_deliver+0x1578/frame 0xfffffe00709a18a0
g_disk_done() at g_disk_done+0x586/frame 0xfffffe00709a1950
vtblk_vq_intr() at vtblk_vq_intr+0x70b/frame 0xfffffe00709a1a00
ithread_loop() at ithread_loop+0xb9a/frame 0xfffffe00709a1b60
fork_exit() at fork_exit+0x1f7/frame 0xfffffe00709a1bf0
fork_trampoline() at fork_trampoline+0xe/frame 0xfffffe00709a1bf0
--- trap 0, rip = 0, rsp = 0, rbp = 0 ---
KDB: enter: panic
[ thread pid 12 tid 100045 ]
Stopped at      kdb_enter+0x1c7:        movq    $0x87022290,%rdi
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
rax         0xffffffff86333744
rcx                          0
rdx         0xfffff7ff87022290
rbx                          0
rsp         0xfffffe00709a0da0
rbp         0xfffffe00709a0e00
rsi         0xfffffe000e9edcb8
rdi         0xffffffff87022290  kdb_why
r8          0xfffffdff87022290
r9                         0x8
r10         0xffffffffffffffff
r11                          0
r12                          0
r13                        0x1
r14         0xfffffe0078e01fb8
r15         0xffffffff86333744
rip         0xffffffff83fc8007  kdb_enter+0x1c7
rflags                    0x46
kdb_enter+0x1c7:        movq    $0x87022290,%rdi
db> show proc
Process 12 (intr) at 0xfffffe0070b57a70:
 state: NORMAL
 uid: 0  gids: 0
 parent: pid 0 at 0xffffffff86fd57b0
 ABI: null
 flag: 0x10000284  flag2: 0
 reaper: 0xffffffff86fd57b0 reapsubtree: 12
 sigparent: 20
 vmspace: 0xffffffff86fd6430
   (map 0xffffffff86fd6430)
   (map.pmap 0xffffffff86fd64f0)
   (pmap 0xffffffff86fd6550)
 threads: 14
100009                   I                                   [swi6: task queue]
100012                   I                                   [swi6: Giant taskq]
100015                   I                                   [swi5: fast taskq]
100026                   I                                   [swi4: clock (0)]
100027                   I                                   [swi3: vm]
100028                   I                                   [swi1: netisr 0]
100039                   I                                   [irq40: virtio_pci0]
100040                   I                                   [irq41: virtio_pci0]
100041                   I                                   [irq42: virtio_pci0]
100044                   I                                   [irq43: virtio_pci1]
100045                   Run     CPU 0                       [irq44: virtio_pci1]
100046                   I                                   [irq1: atkbd0]
100047                   I                                   [irq12: psm0]
100048                   I                                   [swi0: uart uart++]
db> ps
  pid  ppid  pgrp   uid  state   wmesg   wchan               cmd
  863   719   719     0  R                                   syz-executor1636746
  720   718   720     0  Ds      biord   0xfffffe001f038c70  syz-executor1636746
  719   718   719     0  Ss      nanslp  0xffffffff86ff59e0  syz-executor1636746
  718   716   716     0  S       nanslp  0xffffffff86ff59e0  syz-executor1636746
  716   714   716     0  Ss      pause   0xfffffe00c9d1f5e8  csh
  714   641   714     0  Ss      select  0xfffffe00c9daae40  sshd
  693     1   693     0  Ss+     ttyin   0xfffffe0070eaf8b0  getty
  692   689    21     0  S+      nanslp  0xffffffff86ff59e0  sleep
  690     1    21     0  S+      piperd  0xfffffe00aed0c2e8  logger
  689     1    21     0  S+      wait    0xfffffe00c9d1fa70  sh
  645     1   645     0  Ss      nanslp  0xffffffff86ff59e0  cron
  641     1   641     0  Ss      select  0xfffffe00c9daaec0  sshd
  449     1   449     0  Ss      select  0xfffffe00aeca1340  syslogd
  378     1   378     0  Ss      select  0xfffffe00aecc7bc0  devd
  377     1   377    65  Ss      select  0xfffffe00aeca16c0  dhclient
  307     1   307     0  Ss      select  0xfffffe00aeca1040  dhclient
  304     1   304     0  Ss      select  0xfffffe00aecc7040  dhclient
   89     1    89     0  Ss      pause   0xfffffe00aed000b0  adjkerntz
   20     0     0     0  DL      -       0xffffffff870eaf5c  [soaiod4]
   19     0     0     0  DL      -       0xffffffff870eaf5c  [soaiod3]
   18     0     0     0  DL      -       0xffffffff870eaf5c  [soaiod2]
   17     0     0     0  DL      -       0xffffffff870eaf5c  [soaiod1]
   16     0     0     0  DL      syncer  0xffffffff870ee850  [syncer]
   15     0     0     0  DL      vlruwt  0xfffffe0079773000  [vnlru]
    9     0     0     0  DL      (threaded)                  [bufdaemon]
100058                   D       qsleep  0xffffffff870ed900  [bufdaemon]
100061                   D       -       0xffffffff86a0aec0  [bufspacedaemon-0]
100062                   D       -       0xffffffff86a13180  [bufspacedaemon-1]
100074                   D       sdflush 0xfffffe00aedc3ce8  [/ worker]
    8     0     0     0  DL      psleep  0xffffffff87113648  [vmdaemon]
    7     0     0     0  DL      (threaded)                  [pagedaemon]
100056                   D       psleep  0xffffffff87107ab8  [dom0]
100063                   D       launds  0xffffffff87107ac4  [laundry: dom0]
100064                   D       umarcl  0xffffffff85372d90  [uma]
    6     0     0     0  DL      -       0xffffffff86e29d78  [rand_harvestq]
    5     0     0     0  DL      (threaded)                  [cam]
100037                   D       -       0xffffffff86d01240  [doneq0]
100038                   D       -       0xffffffff86d011c0  [async]
100055                   D       -       0xffffffff86d01090  [scanner]
   14     0     0     0  DL      seqstat 0xfffffe001fb03488  [sequencer 00]
    4     0     0     0  DL      crypto_ 0xfffffe0070ce8f30  [crypto returns 0]
    3     0     0     0  DL      crypto_ 0xffffffff87104fe0  [crypto]
   13     0     0     0  DL      (threaded)                  [geom]
100030                   D       -       0xffffffff86fd5220  [g_event]
100031                   D       -       0xffffffff86fd5228  [g_up]
100032                   D       -       0xffffffff86fd5230  [g_down]
    2     0     0     0  DL      -       0xfffffe001ee4e280  [thr_0]
   12     0     0     0  RL      (threaded)                  [intr]
100009                   I                                   [swi6: task queue]
100012                   I                                   [swi6: Giant taskq]
100015                   I                                   [swi5: fast taskq]
100026                   I                                   [swi4: clock (0)]
100027                   I                                   [swi3: vm]
100028                   I                                   [swi1: netisr 0]
100039                   I                                   [irq40: virtio_pci0]
100040                   I                                   [irq41: virtio_pci0]
100041                   I                                   [irq42: virtio_pci0]
100044                   I                                   [irq43: virtio_pci1]
100045                   Run     CPU 0                       [irq44: virtio_pci1]
100046                   I                                   [irq1: atkbd0]
100047                   I                                   [irq12: psm0]
100048                   I                                   [swi0: uart uart++]
   11     0     0     0  RL                                  [idle: cpu0]
    1     0     1     0  SLs     wait    0xfffffe0070a77538  [init]
   10     0     0     0  DL      audit_w 0xffffffff871054f0  [audit]
    0     0     0     0  DLs     (threaded)                  [kernel]
100000                   D       swapin  0xffffffff86fd57b0  [swapper]
100004                   D       -       0xfffffe001ef16d00  [if_config_tqg_0]
100005                   D       -       0xfffffe001ef16c00  [softirq_0]
100006                   D       -       0xfffffe001ef16b00  [if_io_tqg_0]
100007                   D       -       0xfffffe0070b27d00  [kqueue_ctx taskq]
100008                   D       -       0xfffffe0070b27c00  [linuxkpi_irq_wq]
100010                   D       -       0xfffffe0070b27900  [in6m_free taskq]
100011                   D       -       0xfffffe0070b27800  [inm_free taskq]
100013                   D       -       0xfffffe0070b27500  [thread taskq]
100014                   D       -       0xfffffe0070b27400  [aiod_kick taskq]
100016                   D       -       0xfffffe0070b27100  [pci_hp taskq]
100017                   D       -       0xfffffe0070b27000  [linuxkpi_short_wq_0]
100018                   D       -       0xfffffe0070b27000  [linuxkpi_short_wq_1]
100019                   D       -       0xfffffe0070b27000  [linuxkpi_short_wq_2]
100020                   D       -       0xfffffe0070b27000  [linuxkpi_short_wq_3]
100021                   D       -       0xfffffe0070bc0e00  [linuxkpi_long_wq_0]
100022                   D       -       0xfffffe0070bc0e00  [linuxkpi_long_wq_1]
100023                   D       -       0xfffffe0070bc0e00  [linuxkpi_long_wq_2]
100024                   D       -       0xfffffe0070bc0e00  [linuxkpi_long_wq_3]
100029                   D       -       0xfffffe0070bc0900  [firmware taskq]
100033                   D       -       0xfffffe0070bc0700  [crypto]
100042                   D       -       0xfffffe0070e80c00  [vtnet0 rxq 0]
100043                   D       -       0xfffffe0070e80b00  [vtnet0 txq 0]
100049                   D       -       0xffffffff866dd0e0  [deadlkres]
100050                   D       -       0xfffffe0079724a00  [acpi_task_0]
100051                   D       -       0xfffffe0079724a00  [acpi_task_1]
100052                   D       -       0xfffffe0079724a00  [acpi_task_2]
100054                   D       -       0xfffffe0070bc0600  [CAM taskq]
db> show all locks
Process 720 (syz-executor1636746) thread 0xfffffe00c9cc3740 (100086)
exclusive lockmgr bufwait (bufwait) r = 0 (0xfffffe001f038cf0) locked @ /usr/home/markj/src/freebsd/sys/kern/vfs_bio.c:1687
exclusive lockmgr ufs (ufs) r = 0 (0xfffffe00c9f84230) locked @ /usr/home/markj/src/freebsd/sys/kern/vfs_cache.c:4462
db> show malloc
              Type        InUse        MemUse     Requests
             kmsan           88         2816K           88
            newblk          548         2185K          726
          vfscache            3         2049K            3
            linker          306         1981K          344
         sysctloid        29067         1714K        29106
               pcb           15         1545K           35
              kobj          329         1316K          526
            devbuf         1360         1149K         1380
          inodedep          191         1096K          212
         ufs_quota            1         1024K            1
          vfs_hash            1         1024K            1
              intr            4          472K            4
           callout            1          256K            1
           subproc           79          171K          904
         vnet_data            1          168K            1
           tidhash            3          158K            3
              SWAP            1          132K            1
           pagedep           16          132K          163
        tfo_ccache            1          128K            1
               sem            4          106K            4
            DEVFS1           92           92K          106
              vmem            3           82K            4
               bus          976           78K         2580
            bus-sc           31           76K         1058
          mtx_pool            2           72K            2
          syncache            1           68K            1
          acpitask            1           64K            1
       ddb_capture            1           64K            1
            module          503           63K          503
         pfs_nodes          151           57K          151
            dirrem          158           40K          170
            acpica          420           39K        61011
               LRO            2           33K            2
              proc            3           33K            3
              temp           18           33K         1497
         hostcache            1           32K            1
               shm            1           32K            1
               msg            4           30K            4
            DEVFS3          114           29K          132
        gtaskqueue           12           25K           12
           kdtrace          128           25K          953
         ufs_mount            5           25K            6
              umtx          176           22K          176
            kbdmux            5           22K            5
        DEVFS_RULE           56           20K           56
          freefile          142           18K          152
               BPF           10           18K           10
           ithread           98           18K           98
       pfs_vncache            6           17K            6
           devstat            8           17K            8
            KTRACE          100           13K          100
              GEOM           79           13K          662
              rman          103           12K          527
            ifaddr           30           12K           32
          routetbl           52           11K          178
              kenv           63           11K           63
      eventhandler          116           10K          116
         bmsafemap            4            9K          186
              UART           12            9K           12
               rpc            2            8K            2
             shmfd            1            8K            1
     audit_evclass          236            8K          294
       ufs_dirhash           36            8K           36
         taskqueue           51            6K           51
            sglist            3            6K            3
           uidinfo            3            5K            8
              cred           17            5K          268
             ifnet            3            5K            3
           io_apic            1            4K            1
               tty            4            4K            4
             evdev            4            4K            4
          filedesc            1            4K            1
               UMA          238            4K          238
             mount           76            4K          153
            diradd           27            4K          181
             hhook           13            4K           13
           lltable           11            4K           11
            plimit           11            3K          205
           acpisem           21            3K           21
            kqueue           39            3K          864
           pwddesc           39            3K          864
             linux           33            3K           33
       ether_multi           26            3K           36
       fpukern_ctx            2            2K            2
         ipsec-saq            2            2K            2
           CAM DEV            1            2K            2
           session           15            2K           23
         in6_multi           15            2K           15
             selfd           27            2K        11735
               msi           13            2K           13
            Unitno           27            2K           51
             lockf           15            2K           22
          pci_link           16            2K           16
           acpidev           22            2K           22
             mkdir           10            2K          306
        local_apic            1            1K            1
           softdep            1            1K            1
       ipsecpolicy            1            1K            1
            sahead            1            1K            1
          secasvar            1            1K            1
             clone            8            1K            8
       vnodemarker            2            1K            8
      NFSD session            1            1K            1
         proc-args           24            1K          421
         newdirblk            7            1K          153
            select            7            1K           23
          indirdep            3            1K            3
             nhops            6            1K            6
            ip6ndp            4            1K            5
            isadev            5            1K            5
           CAM XPT           11            1K           12
         CAM queue            2            1K            5
            crypto            4            1K            4
          in_multi            2            1K            4
              pfil            4            1K            4
              cdev            2            1K            2
 encap_export_host            8            1K            8
        CAM periph            2            1K           14
            prison           12            1K           12
               osd            3            1K           10
      NFSD lckfile            1            1K            1
     NFSD V4client            1            1K            1
             DEVFS            9            1K           10
               mld            2            1K            2
              igmp            2            1K            2
    chacha20random            1            1K            1
            vnodes            1            1K            1
           CAM SIM            1            1K            1
            feeder            7            1K            7
       inpcbpolicy            6            1K           78
        loginclass            3            1K            7
             linux            5            1K            6
            DEVFSP            2            1K            2
               MCA            1            1K            1
            apmdev            1            1K            1
          atkbddev            2            1K            2
         vm_pgdata            1            1K            1
          freework            1            1K          162
              ktls            1            1K            1
          procdesc            1            1K            2
          pmchooks            1            1K            1
            soname            4            1K         3106
          filecaps            4            1K           51
          nexusdev            6            1K            6
               tun            3            1K            3
        debugfsint            2            1K            2
        aesni_data            2            1K            2
     CAM dev queue            1            1K            1
           tcpfunc            1            1K            1
              vnet            1            1K            1
          acpiintr            1            1K            1
               pmc            1            1K            1
              cpus            2            1K            2
    vnet_data_free            1            1K            1
          CAM path            1            1K           12
           entropy            1            1K           35
           Per-cpu            1            1K            1
             cache            1            1K            1
       fdesc_mount            1            1K            1
          p1003.1b            1            1K            1
          futex wp            0            0K            0
             futex            0            0K            0
            lepoll            0            0K            0
          ktls_ocf            0            0K            0
       NFSD V4lock            0            0K            0
      NFSD V4state            0            0K            0
        madt_table            0            0K            2
          smartpqi            0            0K            0
     NFSD srvcache            0            0K            0
       msdosfs_fat            0            0K            0
     msdosfs_mount            0            0K            0
      msdosfs_node            0            0K            0
              iavf            0            0K            0
               ixl            0            0K            0
            DEVFS4            0            0K            0
            DEVFS2            0            0K            0
            gntdev            0            0K            0
       privcmd_dev            0            0K            0
        evtchn_dev            0            0K            0
        ice-resmgr            0            0K            0
         ice-osdep            0            0K            0
               ice            0            0K            0
             axgbe            0            0K            0
          xenstore            0            0K            0
         ciss_data            0            0K            0
         BACKLIGHT            0            0K            0
               xnb            0            0K            0
              xbbd            0            0K            0
               xbd            0            0K            0
           Balloon            0            0K            0
          sysmouse            0            0K            0
            vtfont            0            0K            0
           memdesc            0            0K            0
                vt            0            0K            0
          xen_intr            0            0K            0
             vtbuf            0            0K            0
           ath_hal            0            0K            0
           xen_hvm            0            0K            0
         legacydrv            0            0K            0
            qpidrv            0            0K            0
            athdev            0            0K            0
           ata_pci            0            0K            0
      dmar_idpgtbl            0            0K            0
          dmar_dom            0            0K            0
          dmar_ctx            0            0K            0
           ata_dma            0            0K            0
       ata_generic            0            0K            0
               amr            0            0K            0
              isci            0            0K            0
      iommu_dmamap            0            0K            0
            pvscsi            0            0K            0
     hyperv_socket            0            0K            0
           bxe_ilt            0            0K            0
            xenbus            0            0K            0
           scsi_da            0            0K            0
            ata_da            0            0K            0
     vm_fictitious            0            0K            0
           scsi_ch            0            0K            0
           scsi_cd            0            0K            0
       AHCI driver            0            0K            0
            USBdev            0            0K            0
               USB            0            0K            0
               agp            0            0K            0
           nvme_da            0            0K            0
 CAM I/O Scheduler            0            0K            0
           acpipwr            0            0K            0
           UMAHash            0            0K            0
         acpi_perf            0            0K            0
            twsbuf            0            0K            0
           jblocks            0            0K            0
          savedino            0            0K            0
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
          freeblks            0            0K          161
          freefrag            0            0K            0
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
             xform            0            0K            0
      twe_commands            0            0K            0
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
      twa_commands            0            0K            0
            statfs            0            0K          204
     namei_tracker            0            0K            1
       export_host            0            0K            0
        cl_savebuf            0            0K            5
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
          tempbuff            0            0K            0
            biobuf            0            0K            0
              aios            0            0K            0
               lio            0            0K            0
               acl            0            0K            0
          tempbuff            0            0K            0
          mbuf_tag            0            0K           27
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
               iov            0            0K        11872
          ioctlops            0            0K           76
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
         toponodes            0            0K            0
              sbuf            0            0K          478
        md_sectors            0            0K            0
          firmware            0            0K            0
        compressor            0            0K            0
           md_disk            0            0K            0
           malodev            0            0K            0
               LED            0            0K            0
         sysctltmp            0            0K          593
            sysctl            0            0K            1
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
         raid_data            0            0K           96
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
      NFSCL client            0            0K            0
       NFSCL deleg            0            0K            0
        NFSCL open            0            0K            0
       NFSCL owner            0            0K            0
            NFS fh            0            0K            0
           NFS req            0            0K            0
     NFSD usrgroup            0            0K            0
       NFSD string            0            0K            0
db> show uma
              Zone   Size    Used    Free    Requests  Sleeps  Bucket  Total Mem    XFree
   mbuf_jumbo_page   4096    1088     518       13814       0     254    6578176        0
      malloc-32768  32768      88       0          88       0       1    2883584        0
              pbuf   2624       0     973           0       0       4    2553152        0
          BUF TRIE    144     194   16914         459       0      62    2463552        0
       malloc-4096   4096     330       1         527       0       2    1355776        0
        malloc-128    128    9554      25        9560       0     126    1226112        0
         FFS inode   1160     525      14         677       0       8     625240        0
        malloc-512    512    1028       4        1034       0      30     528384        0
              mbuf    256    1347     528       21868       0     254     480000        0
        RADIX NODE    144    2569     225       19888       0      62     402336        0
      malloc-65536  65536       6       0           6       0       1     393216        0
            lkpimm    160       1    2324           1       0      62     372000        0
          lkpicurr    160       2    2323           2       0      62     372000        0
         vmem btag     56    6424      32        6424       0     254     361536        0
       UMA Slabs 0    112    2532      21        2532       0     126     285936        0
       malloc-2048   2048     129       1         129       0       8     266240        0
             VNODE    448     556      38         710       0      30     266112        0
      malloc-65536  65536       3       1         109       0       1     262144        0
      malloc-65536  65536       4       0           4       0       1     262144        0
         VM OBJECT    264     875      10       12781       0      30     233640        0
         malloc-64     64    3453      12        4293       0     254     221760        0
            DEVCTL   1024       0     216         114       0       0     221184        0
       malloc-4096   4096      51       1         876       0       2     212992        0
        malloc-256    256     773       7        1473       0      62     199680        0
         malloc-16     16   12080     170       12129       0     254     196000        0
      malloc-32768  32768       5       0           5       0       1     163840        0
            THREAD   1808      88       0          88       0       8     159104        0
         malloc-32     32    4291     119        4318       0     254     141120        0
       FFS2 dinode    256     525      15         677       0      62     138240        0
         UMA Zones    640     210       4         210       0      16     136960        0
      malloc-65536  65536       2       0           2       0       1     131072        0
       S VFS Cache    104     996     135        1192       0     126     117624        0
          ksiginfo    112      29    1015          42       0     126     116928        0
        256 Bucket   2048      56       0        2413       0       8     114688        0
        malloc-128    128     840      28        1850       0     126     111104        0
       malloc-1024   1024      93      11         114       0      16     106496        0
      malloc-16384  16384       6       0          78       0       1      98304        0
            clpbuf   2624       0      32          58       0      32      83968        0
          UMA Kegs    384     195       8         195       0      30      77952        0
        malloc-384    384     199       1         232       0      30      76800        0
         MAP ENTRY     96     699      99       36494       0     126      76608        0
        malloc-128    128     510      17       31487       0     126      67456        0
      malloc-65536  65536       1       0           1       0       1      65536        0
      malloc-65536  65536       1       0           1       0       1      65536        0
      malloc-32768  32768       2       0           2       0       1      65536        0
        malloc-384    384     151       9         151       0      30      61440        0
           DIRHASH   1024      54       2          54       0      16      57344        0
       malloc-8192   8192       6       1          96       0       1      57344        0
           VMSPACE   2544      19       2         845       0       4      53424        0
              PROC   1336      38       1         863       0       8      52104        0
      malloc-16384  16384       3       0           3       0       1      49152        0
      malloc-16384  16384       2       1           4       0       1      49152        0
         filedesc0   1072      39       3         864       0       8      45024        0
       malloc-8192   8192       5       0           5       0       1      40960        0
         malloc-64     64     610      20         854       0     254      40320        0
        malloc-128    128     285      25         527       0     126      39680        0
        malloc-256    256     145       5         568       0      62      38400        0
        malloc-256    256     121      14         145       0      62      34560        0
      mbuf_cluster   2048      15       1          15       0     254      32768        0
      malloc-32768  32768       0       1          52       0       1      32768        0
      malloc-32768  32768       1       0           1       0       1      32768        0
           pcpu-64     64     454      58         454       0     254      32768        0
       malloc-4096   4096       6       1         272       0       2      28672        0
            pcpu-8      8    3146     438        3158       0     254      28672        0
        malloc-256    256      85      20         275       0      62      26880        0
       malloc-4096   4096       5       1         210       0       2      24576        0
        malloc-384    384      52       8          52       0      30      23040        0
        malloc-384    384      54       6          54       0      30      23040        0
       malloc-2048   2048       9       1           9       0       8      20480        0
        128 Bucket   1024      17       2         440       0      16      19456        0
       Mountpoints   2752       6       1           6       0       4      19264        0
       malloc-8192   8192       2       0           2       0       1      16384        0
       malloc-2048   2048       6       2          62       0       8      16384        0
       malloc-1024   1024      14       2          14       0      16      16384        0
         64 Bucket    512      29       3         531       0      30      16384        0
        malloc-128    128     105      19         153       0     126      15872        0
            socket    944      14       2        1158       0     254      15104        0
         TURNSTILE    136      89      16          89       0      62      14280        0
       malloc-4096   4096       2       1          48       0       2      12288        0
       malloc-2048   2048       3       3          12       0       8      12288        0
       malloc-1024   1024       8       4         956       0      16      12288        0
       malloc-1024   1024       7       5          11       0      16      12288        0
       malloc-1024   1024       9       3           9       0      16      12288        0
         malloc-64     64     136      53        1841       0     254      12096        0
         malloc-64     64     185       4       13328       0     254      12096        0
         malloc-32     32     322      56         431       0     254      12096        0
        SLEEPQUEUE     88      89       7          89       0     126       8448        0
       malloc-8192   8192       1       0           1       0       1       8192        0
       malloc-8192   8192       1       0           1       0       1       8192        0
       malloc-4096   4096       1       1           4       0       2       8192        0
       malloc-1024   1024       4       4          15       0      16       8192        0
       malloc-1024   1024       6       2           6       0      16       8192        0
        malloc-512    512      12       4          12       0      30       8192        0
             g_bio    408       1      19        5177       0      30       8160        0
               PWD     32      14     238         244       0     254       8064        0
         malloc-64     64      85      41       11817       0     254       8064        0
         malloc-64     64     113      13         141       0     254       8064        0
             Files     80      62      38        6170       0     126       8000        0
         malloc-16     16     274     226         543       0     254       8000        0
        malloc-128    128      36      26         191       0     126       7936        0
        malloc-256    256      14      16         231       0      62       7680        0
        malloc-256    256      16      14         593       0      62       7680        0
        malloc-256    256      18      12         169       0      62       7680        0
         32 Bucket    256      21       9         353       0      62       7680        0
     FPU_save_area    832       1       8           1       0      16       7488        0
             tcpcb   1064       3       4           7       0     254       7448        0
              pipe    744       7       3         271       0      16       7440        0
             NAMEI   1024       2       2       12097       0      16       4096        0
 epoch_record pcpu    256       4      12           4       0      62       4096        0
       malloc-2048   2048       1       1           2       0       8       4096        0
       malloc-2048   2048       0       2         211       0       8       4096        0
       malloc-2048   2048       2       0           2       0       8       4096        0
       malloc-1024   1024       0       4           4       0      16       4096        0
        malloc-512    512       3       5         230       0      30       4096        0
        malloc-512    512       0       8           1       0      30       4096        0
        malloc-512    512       6       2           7       0      30       4096        0
           pcpu-16     16       7     249           7       0     254       4096        0
           rtentry    176      13      10          17       0      62       4048        0
              PGRP     88      15      31          23       0     126       4048        0
          rl_entry     40      17      84          17       0     254       4040        0
         hostcache     64       1      62           1       0     254       4032        0
          syncache    168       0      24           5       0     254       4032        0
             udpcb     32       2     124          70       0     254       4032        0
         malloc-64     64       6      57           7       0     254       4032        0
         malloc-64     64      17      46         243       0     254       4032        0
         malloc-32     32       4     122           5       0     254       4032        0
         malloc-32     32       2     124           4       0     254       4032        0
         malloc-32     32      89      37         244       0     254       4032        0
         malloc-32     32      39      87         629       0     254       4032        0
         malloc-32     32      44      82        4972       0     254       4032        0
         malloc-32     32      24     102         158       0     254       4032        0
         16 Bucket    144      14      14         166       0      62       4032        0
          4 Bucket     48       3      81          11       0     254       4032        0
          2 Bucket     32      26     100         556       0     254       4032        0
      vtnet_tx_hdr     24       1     166        7097       0     254       4008        0
            ttyinq    160      15      10          45       0      62       4000        0
         malloc-16     16       0     250           4       0     254       4000        0
         malloc-16     16      54     196          93       0     254       4000        0
         malloc-16     16      20     230          21       0     254       4000        0
         malloc-16     16     180      70         957       0     254       4000        0
         malloc-16     16      32     218       26662       0     254       4000        0
         malloc-16     16      15     235          21       0     254       4000        0
          8 Bucket     80      16      34        2441       0     126       4000        0
        malloc-128    128       6      25          12       0     126       3968        0
        malloc-128    128      11      20          70       0     126       3968        0
             ripcb    488       1       7           1       0     254       3904        0
         tcp_inpcb    488       3       5           7       0     254       3904        0
         udp_inpcb    488       2       6          70       0     254       3904        0
       UMA Slabs 1    176       6      16           6       0      62       3872        0
              kenv    258       2      13         697       0      30       3870        0
     routing nhops    256      10       5          17       0      62       3840        0
             unpcb    256       7       8        1064       0     254       3840        0
           ttyoutq    256       8       7          24       0      62       3840        0
       mbuf_packet    256       0      15          96       0     254       3840        0
        malloc-384    384       0      10          16       0      30       3840        0
        malloc-384    384       4       6         182       0      30       3840        0
        malloc-384    384       6       4           6       0      30       3840        0
        malloc-384    384       0      10           3       0      30       3840        0
        malloc-256    256      10       5         320       0      62       3840        0
        KMAP ENTRY     96      21      18          26       0       0       3744        0
              vmem   1856       1       1           1       0       8       3712        0
            cpuset    104       3      28           3       0     126       3224        0
           SMR CPU     32       3      28           3       0     254        992        0
        SMR SHARED     24       3      28           3       0     254        744        0
       FFS1 dinode    128       0       0           0       0     126          0        0
             swblk    136       0       0           0       0      62          0        0
          swpctrie    144       0       0           0       0      62          0        0
     udplite_inpcb    488       0       0           0       0     254          0        0
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
       L VFS Cache    320       0       0           0       0      30          0        0
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
            vnpbuf   2624       0       0           0       0     128          0        0
           nfspbuf   2624       0       0           0       0      32          0        0
            mdpbuf   2624       0       0           0       0       6          0        0
            swwbuf   2624       0       0           0       0      16          0        0
            swrbuf   2624       0       0           0       0      32          0        0
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
       malloc-8192   8192       0       0           0       0       1          0        0
       malloc-4096   4096       0       0           0       0       2          0        0
       malloc-4096   4096       0       0           0       0       2          0        0
       malloc-2048   2048       0       0           0       0       8          0        0
        malloc-512    512       0       0           0       0      30          0        0
        malloc-512    512       0       0           0       0      30          0        0
        malloc-512    512       0       0           0       0      30          0        0
           pcpu-32     32       0       0           0       0     254          0        0
            pcpu-4      4       0       0           0       0     254          0        0
            fakepg    104       0       0           0       0     126          0        0
          UMA Hash    256       0       0           0       0      62          0        0


Syzkaller reproducer:
# {Threaded:false Collide:false Repeat:true RepeatTimes:0 Procs:2 Slowdown:1 Sandbox:none Fault:false FaultCall:-1 FaultNth:0 Leak:false NetInjection:false NetDevices:false NetReset:false Cgroups:false BinfmtMisc:false CloseFDs:false KCSAN:false DevlinkPCI:false USB:false VhciInjection:false Wifi:false IEEE802154:false Sysctl:false UseTmpDir:true HandleSegv:false Repro:false Trace:false}
freebsd11_mknod(&(0x7f0000000000)='./file1\x00', 0xe154, 0x0)
r0 = open$dir(0x0, 0x0, 0x132)
mkdirat(r0, 0x0, 0x82)


C reproducer:
// autogenerated by syzkaller (https://github.com/google/syzkaller)

#define _GNU_SOURCE

#include <sys/types.h>

#include <dirent.h>
#include <errno.h>
#include <pwd.h>
#include <signal.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/endian.h>
#include <sys/resource.h>
#include <sys/stat.h>
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

static void use_temporary_dir(void)
{
  char tmpdir_template[] = "./syzkaller.XXXXXX";
  char* tmpdir = mkdtemp(tmpdir_template);
  if (!tmpdir)
    exit(1);
  if (chmod(tmpdir, 0777))
    exit(1);
  if (chdir(tmpdir))
    exit(1);
}

static void __attribute__((noinline)) remove_dir(const char* dir)
{
  DIR* dp = opendir(dir);
  if (dp == NULL) {
    if (errno == EACCES) {
      if (rmdir(dir))
        exit(1);
      return;
    }
    exit(1);
  }
  struct dirent* ep = 0;
  while ((ep = readdir(dp))) {
    if (strcmp(ep->d_name, ".") == 0 || strcmp(ep->d_name, "..") == 0)
      continue;
    char filename[FILENAME_MAX];
    snprintf(filename, sizeof(filename), "%s/%s", dir, ep->d_name);
    struct stat st;
    if (lstat(filename, &st))
      exit(1);
    if (S_ISDIR(st.st_mode)) {
      remove_dir(filename);
      continue;
    }
    if (unlink(filename))
      exit(1);
  }
  closedir(dp);
  if (rmdir(dir))
    exit(1);
}

static void sandbox_common()
{
  if (setsid() == -1)
    exit(1);
  struct rlimit rlim;
  rlim.rlim_cur = rlim.rlim_max = 128 << 20;
  setrlimit(RLIMIT_AS, &rlim);
  rlim.rlim_cur = rlim.rlim_max = 8 << 20;
  setrlimit(RLIMIT_MEMLOCK, &rlim);
  rlim.rlim_cur = rlim.rlim_max = 1 << 20;
  setrlimit(RLIMIT_FSIZE, &rlim);
  rlim.rlim_cur = rlim.rlim_max = 1 << 20;
  setrlimit(RLIMIT_STACK, &rlim);
  rlim.rlim_cur = rlim.rlim_max = 0;
  setrlimit(RLIMIT_CORE, &rlim);
  rlim.rlim_cur = rlim.rlim_max = 256;
  setrlimit(RLIMIT_NOFILE, &rlim);
}

static void loop();

static int do_sandbox_none(void)
{
  sandbox_common();
  loop();
  return 0;
}

static void execute_one(void);

#define WAIT_FLAGS 0

static void loop(void)
{
  int iter = 0;
  for (;; iter++) {
    char cwdbuf[32];
    sprintf(cwdbuf, "./%d", iter);
    if (mkdir(cwdbuf, 0777))
      exit(1);
    int pid = fork();
    if (pid < 0)
      exit(1);
    if (pid == 0) {
      if (chdir(cwdbuf))
        exit(1);
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
    remove_dir(cwdbuf);
  }
}

uint64_t r[1] = {0xffffffffffffffff};

void execute_one(void)
{
  intptr_t res = 0;
  memcpy((void*)0x20000000, "./file1\000", 8);
  syscall(SYS_freebsd11_mknod, 0x20000000ul, 0xe154ul, 0);
  res = syscall(SYS_open, 0ul, 0ul, 0x132ul);
  if (res != -1)
    r[0] = res;
  syscall(SYS_mkdirat, r[0], 0ul, 0x82ul);
}
int main(void)
{
  syscall(SYS_mmap, 0x20000000ul, 0x1000000ul, 7ul, 0x1012ul, -1, 0ul);
  for (procid = 0; procid < 2; procid++) {
    if (fork() == 0) {
      use_temporary_dir();
      do_sandbox_none();
    }
  }
  sleep(1000000);
  return 0;
}


