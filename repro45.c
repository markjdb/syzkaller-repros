Syzkaller hit 'panic: wrong offset -NUM for sectorsize NUM' bug.

login: panic: wrong offset -31233 for sectorsize 512
cpuid = 1
time = 1629672276
KDB: stack backtrace:
db_trace_self_wrapper() at db_trace_self_wrapper+0x47/frame 0xfffffe00516a8750
vpanic() at vpanic+0x1cc/frame 0xfffffe00516a87b0
panic() at panic+0x43/frame 0xfffffe00516a8810
g_io_request() at g_io_request+0x5be/frame 0xfffffe00516a8860
g_read_data() at g_read_data+0xc1/frame 0xfffffe00516a88a0
g_raid_md_taste_promise() at g_raid_md_taste_promise+0x193/frame 0xfffffe00516a89c0
g_raid_taste() at g_raid_taste+0x248/frame 0xfffffe00516a8a20
g_resize_provider_event() at g_resize_provider_event+0x2b0/frame 0xfffffe00516a8a60
g_run_events() at g_run_events+0x14b/frame 0xfffffe00516a8ab0
fork_exit() at fork_exit+0xb3/frame 0xfffffe00516a8af0
fork_trampoline() at fork_trampoline+0xe/frame 0xfffffe00516a8af0
--- trap 0, rip = 0, rsp = 0, rbp = 0 ---
KDB: enter: panic
[ thread pid 13 tid 100037 ]
Stopped at      kdb_enter+0x67: movq    $0,0x1633f2e(%rip)
db> 
db> ~
Unrecognized input; use "help" to list available commands
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
rdx         0xffffffff81a2377d
rbx                          0
rsp         0xfffffe00516a8730
rbp         0xfffffe00516a8750
rsi                        0x1
rdi                          0
r8                           0
r9          0x8080808080808080
r10         0xfffffe00516a8620
r11              0x1ffaefff59c
r12         0xffffffff82267d00  ddb_dbbe
r13         0xffffffff81a23200
r14         0xffffffff81a73f35
r15         0xffffffff81a73f35
rip         0xffffffff81136cd7  kdb_enter+0x67
rflags                    0x86
kdb_enter+0x67: movq    $0,0x1633f2e(%rip)
db> show proc
Process 13 (geom) at 0xfffff8000357d000:
 state: NORMAL
 uid: 0  gids: 0
 parent: pid 0 at 0xffffffff8271e110
 ABI: null
 flag: 0x10000284  flag2: 0
 reaper: 0xffffffff8271e110 reapsubtree: 13
 sigparent: 20
 vmspace: 0xffffffff8271ed90
   (map 0xffffffff8271ed90)
   (map.pmap 0xffffffff8271ee50)
   (pmap 0xffffffff8271eeb0)
 threads: 3
100037                   Run     CPU 1                       [g_event]
100038                   D       -       0xffffffff8271db78  [g_up]
100039                   D       -       0xffffffff8271db80  [g_down]
db> ps
  pid  ppid  pgrp   uid  state   wmesg   wchan               cmd
  830     0     0     0  DL      mdwait  0xfffff800038b0000  [md0]
  829   827   827     0  D       g_waiti 0xffffffff8271daa0  syz-executor7597632
  827   825   827     0  Ss      pause   0xfffff80003def0b0  csh
  825   735   825     0  Ss      select  0xfffff800294124c0  sshd
  797     1   797     0  Ss+     ttyin   0xfffff80003840cb0  getty
  793     1   793     0  Ss      select  0xfffff80029412840  logger
  787     1    22     0  S+      piperd  0xfffff8002946a2e8  logger
  786   785    22     0  S+      nanslp  0xffffffff8273e360  sleep
  785     1    22     0  S+      wait    0xfffff80029414000  sh
  781     1   781    25  Ss      pause   0xfffff80029362b20  sendmail
  778     1   778     0  Ss      select  0xfffff80003e9f7c0  sendmail
  739     1   739     0  Ss      nanslp  0xffffffff8273e361  cron
  735     1   735     0  Ss      select  0xfffff80003e9f940  sshd
  646     1   646     0  Rs      CPU 0                       syslogd
  449     1   449     0  Rs                                  devd
  352     1   352    65  Ss      select  0xfffff80029412cc0  dhclient
  270     1   270     0  Ss      select  0xfffff80003ecb9c0  dhclient
  267     1   267     0  Ss      select  0xfffff80003e9fac0  dhclient
   95     0     0     0  DL      pftm    0xffffffff82f19520  [pf purge]
   21     0     0     0  DL      syncer  0xffffffff8282f140  [syncer]
   20     0     0     0  DL      vlruwt  0xfffff80003b3c538  [vnlru]
   19     0     0     0  DL      (threaded)                  [bufdaemon]
100071                   D       qsleep  0xffffffff8282e1b0  [bufdaemon]
100074                   D       -       0xffffffff8220af40  [bufspacedaemon-0]
100085                   D       sdflush 0xfffff800038ab0e8  [/ worker]
   18     0     0     0  DL      psleep  0xffffffff82853ec8  [vmdaemon]
   17     0     0     0  DL      (threaded)                  [pagedaemon]
100069                   D       psleep  0xffffffff82848338  [dom0]
100072                   D       launds  0xffffffff82848344  [laundry: dom0]
100073                   D       umarcl  0xffffffff815c5ba0  [uma]
   16     0     0     0  DL      -       0xffffffff825726d8  [rand_harvestq]
   15     0     0     0  DL      -       0xffffffff8282b6dc  [soaiod4]
    9     0     0     0  DL      -       0xffffffff8282b6dc  [soaiod3]
    8     0     0     0  DL      -       0xffffffff8282b6dc  [soaiod2]
    7     0     0     0  DL      -       0xffffffff8282b6dc  [soaiod1]
    6     0     0     0  DL      (threaded)                  [cam]
100046                   D       -       0xffffffff82449dc0  [doneq0]
100047                   D       -       0xffffffff82449d40  [async]
100068                   D       -       0xffffffff82449c10  [scanner]
   14     0     0     0  DL      seqstat 0xfffff800036e9488  [sequencer 00]
    5     0     0     0  DL      crypto_ 0xfffff800033ffc80  [crypto returns 1]
    4     0     0     0  DL      crypto_ 0xfffff800033ffc30  [crypto returns 0]
    3     0     0     0  DL      crypto_ 0xffffffff82845860  [crypto]
   13     0     0     0  RL      (threaded)                  [geom]
100037                   Run     CPU 1                       [g_event]
100038                   D       -       0xffffffff8271db78  [g_up]
100039                   D       -       0xffffffff8271db80  [g_down]
    2     0     0     0  DL      (threaded)                  [KTLS]
100029                   D       -       0xfffff80003579000  [thr_0]
100030                   D       -       0xfffff80003579080  [thr_1]
100031                   D       -       0xffffffff8282be38  [alloc_0]
   12     0     0     0  WL      (threaded)                  [intr]
100010                   I                                   [swi5: fast taskq]
100015                   I                                   [swi6: task queue]
100019                   I                                   [swi6: Giant taskq]
100032                   I                                   [swi3: vm]
100033                   I                                   [swi1: netisr 0]
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
100087                   I                                   [swi1: pf send]
   11     0     0     0  RL      (threaded)                  [idle]
100003                   CanRun                              [idle: cpu0]
100004                   CanRun                              [idle: cpu1]
    1     0     1     0  SLs     wait    0xfffff8000352e538  [init]
   10     0     0     0  DL      audit_w 0xffffffff82845d70  [audit]
    0     0     0     0  DLs     (threaded)                  [kernel]
100000                   D       swapin  0xffffffff8271e110  [swapper]
100005                   D       -       0xfffff8000357fe00  [softirq_0]
100006                   D       -       0xfffff8000357fd00  [softirq_1]
100007                   D       -       0xfffff8000357fc00  [if_io_tqg_0]
100008                   D       -       0xfffff8000357fb00  [if_io_tqg_1]
100009                   D       -       0xfffff8000357fa00  [if_config_tqg_0]
100011                   D       -       0xfffff800033fbb00  [kqueue_ctx taskq]
100012                   D       -       0xfffff800033fba00  [in6m_free taskq]
100013                   D       -       0xfffff800033fb900  [pci_hp taskq]
100014                   D       -       0xfffff800033fb800  [aiod_kick taskq]
100016                   D       -       0xfffff800033fb600  [inm_free taskq]
100017                   D       -       0xfffff800033fb500  [deferred_unmount ta]
100018                   D       -       0xfffff800033fb400  [linuxkpi_irq_wq]
100020                   D       -       0xfffff800033fb200  [thread taskq]
100021                   D       -       0xfffff800033fb100  [linuxkpi_short_wq_0]
100022                   D       -       0xfffff800033fb100  [linuxkpi_short_wq_1]
100023                   D       -       0xfffff800033fb100  [linuxkpi_short_wq_2]
100024                   D       -       0xfffff800033fb100  [linuxkpi_short_wq_3]
100025                   D       -       0xfffff800033fb000  [linuxkpi_long_wq_0]
100026                   D       -       0xfffff800033fb000  [linuxkpi_long_wq_1]
100027                   D       -       0xfffff800033fb000  [linuxkpi_long_wq_2]
100028                   D       -       0xfffff800033fb000  [linuxkpi_long_wq_3]
100036                   D       -       0xfffff8000355be00  [firmware taskq]
100040                   D       -       0xfffff8000355bc00  [crypto_0]
100041                   D       -       0xfffff8000355bc00  [crypto_1]
100051                   D       -       0xfffff800037b3e00  [vtnet0 rxq 0]
100052                   D       -       0xfffff800037b3d00  [vtnet0 txq 0]
100062                   D       -       0xffffffff81e204e0  [deadlkres]
100064                   D       -       0xfffff800037b3b00  [acpi_task_0]
100065                   D       -       0xfffff800037b3b00  [acpi_task_1]
100066                   D       -       0xfffff800037b3b00  [acpi_task_2]
100067                   D       -       0xfffff8000355ba00  [CAM taskq]
db> show all locks
db> show malloc
              Type        InUse        MemUse     Requests
           pf_hash            5        11524K            5
         sysctloid        30416         1795K        30458
              kobj          325         1300K          494
            newblk          612         1177K          670
            devbuf         1360         1152K         1378
          vfscache            3         1025K            3
            linker          227          632K          240
          inodedep           61          535K          101
         ufs_quota            1          512K            1
          vfs_hash            1          512K            1
           callout            2          512K            2
              intr            4          472K            4
               pcb           16          393K           32
           subproc           90          183K          880
         vnet_data            1          168K            1
           tidhash            3          141K            3
           pagedep           22          134K           34
        tfo_ccache            1          128K            1
               sem            4          106K            4
            DEVFS1           92           92K          104
               bus          966           78K         2577
            bus-sc           31           76K         1061
          mtx_pool            2           72K            2
          syncache            1           68K            1
          acpitask            1           64K            1
       ddb_capture            1           64K            1
            module          492           62K          492
            acpica          420           39K        62949
               LRO            2           33K            2
         hostcache            1           32K            1
               shm            1           32K            1
               msg            4           30K            4
           kdtrace          146           29K          936
            DEVFS3          111           28K          127
              umtx          220           28K          220
        gtaskqueue           18           26K           18
            kbdmux            5           22K            5
        DEVFS_RULE           59           21K           59
           ithread          104           19K          104
               BPF           10           18K           10
              temp           15           17K         1543
         ufs_mount            4           17K            5
              proc            3           17K            3
              GEOM           73           14K          561
              vmem            3           13K            3
            KTRACE          100           13K          100
           devstat            6           13K            6
              rman          102           12K          526
            ifaddr           29           11K           30
      eventhandler          125           11K          125
              kenv           59           10K           59
          routetbl           44           10K          142
         bmsafemap            2            9K           94
              UART           12            9K           12
               rpc            2            8K            2
             shmfd            1            8K            1
       pfs_vncache            1            8K            1
         pfs_nodes           20            8K           20
     audit_evclass          237            8K          295
            diradd           47            6K          109
         taskqueue           54            6K           54
            sglist            3            6K            3
              cred           20            5K          299
       ufs_dirhash           24            5K           24
             ifnet            3            5K            3
               UMA          250            5K          250
           io_apic            1            4K            1
       fpukern_ctx            2            4K            2
               tty            4            4K            4
           md_disk            1            4K            1
             evdev            4            4K            4
          filedesc            1            4K            1
             hhook           13            4K           13
          pf_ifnet            5            3K            6
           lltable           10            3K           10
            plimit           11            3K          243
           acpisem           21            3K           21
            kqueue           41            3K          831
           pwddesc           41            3K          831
           uidinfo            4            3K           10
             lockf           21            3K           32
        local_apic            1            2K            1
         ipsec-saq            2            2K            2
           CAM DEV            1            2K            2
           session           15            2K           32
               msi           13            2K           13
             selfd           25            2K        12117
          pci_link           16            2K           16
            Unitno           25            2K           45
         proc-args           34            2K          514
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
           CAM SIM            1            1K            1
          pmchooks            1            1K            1
            soname            4            1K         2578
          filecaps            4            1K          105
          nexusdev            6            1K            6
               tun            3            1K            3
     CAM dev queue            1            1K            1
           tcpfunc            1            1K            1
              vnet            1            1K            1
          acpiintr            1            1K            1
               pmc            1            1K            1
              cpus            2            1K            2
    vnet_data_free            1            1K            1
          CAM path            1            1K           12
           entropy            1            1K           56
           Per-cpu            1            1K            1
         raid_data            1            1K           79
          freework            1            1K           26
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
          savedino            0            0K            0
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
            statfs            0            0K         1104
     namei_tracker            0            0K            2
       export_host            0            0K            0
        cl_savebuf            0            0K            5
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
               iov            0            0K         7873
          ioctlops            0            0K           77
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
              sbuf            0            0K          378
          firmware            0            0K            0
        compressor            0            0K            0
           malodev            0            0K            0
              SWAP            0            0K            0
               LED            0            0K            0
         sysctltmp            0            0K          543
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
   mbuf_jumbo_page   4096    1088    1137       14606       0     254    9113600        0
              pbuf   2624       0     794           0       0       2    2083456        0
          BUF TRIE    144     168   13328         438       0      62    1943424        0
       malloc-4096   4096     366       2        1325       0       2    1507328        0
        malloc-128    128   10726      31       10819       0     126    1376896        0
              mbuf    256    1348    1097       22607       0     254     625920        0
        malloc-512    512    1027      13        1027       0      30     532480        0
            lkpimm    168       1    2327           1       0      62     391104        0
          lkpicurr    168       2    2326           2       0      62     391104        0
       UMA Slabs 0    112    3116      13        3116       0     126     350448        0
        RADIX NODE    144    1985     252       28994       0      62     322128        0
       malloc-2048   2048     133       1         133       0       8     274432        0
      malloc-65536  65536       4       0           4       0       1     262144        0
      malloc-65536  65536       2       2          71       0       1     262144        0
         VM OBJECT    264     929      61       11959       0      30     261360        0
             VNODE    448     527      40         557       0      30     254016        0
        256 Bucket   2048     102      18        2818       0       8     245760        0
         malloc-64     64    3458     133        5068       0     254     229824        0
         malloc-16     16   12645     105       12692       0     254     204000        0
            THREAD   1808     104       6         104       0       8     198880        0
            DEVCTL   1024       0     192          96       0       0     196608        0
        malloc-256    256     665      10         827       0      62     172800        0
         UMA Zones    768     222       2         222       0      16     172032        0
         malloc-32     32    4441      95        4482       0     254     145152        0
       FFS2 dinode    256     505      20         532       0      62     134400        0
      malloc-65536  65536       0       2          31       0       1     131072        0
      malloc-65536  65536       2       0           2       0       1     131072        0
          ksiginfo    112      32    1012          64       0     126     116928        0
       S VFS Cache    104    1002      90        1083       0     126     113568        0
         MAP ENTRY     96     803     331       39094       0     126     108864        0
       malloc-1024   1024     100       4         112       0      16     106496        0
         FFS inode    192     505      41         532       0      62     104832        0
      malloc-32768  32768       3       0           3       0       1      98304        0
      malloc-32768  32768       2       1           3       0       1      98304        0
         vmem btag     56    1504      68        1504       0     254      88032        0
       malloc-8192   8192       7       3          47       0       1      81920        0
          UMA Kegs    384     207       6         207       0      30      81792        0
           VMSPACE   2544      18       9         809       0       4      68688        0
      mbuf_cluster   2048      30       2          30       0     254      65536        0
      malloc-65536  65536       1       0           1       0       1      65536        0
      malloc-65536  65536       1       0           1       0       1      65536        0
              PROC   1336      40       8         830       0       8      64128        0
         filedesc0   1072      41      15         831       0       8      60032        0
        128 Bucket   1024      36      19         517       0      16      56320        0
        malloc-128    128     326      46         498       0     126      47616        0
         32 Bucket    256      48     132        3297       0      62      46080        0
             g_bio    384       1     109        4783       0      30      42240        0
            clpbuf   2624       0      16          25       0      16      41984        0
       malloc-4096   4096      10       0          10       0       2      40960        0
         malloc-64     64     479     151       13044       0     254      40320        0
        malloc-128    128     267      43       28679       0     126      39680        0
        malloc-256    256     118      32         361       0      62      38400        0
           DIRHASH   1024      32       4          32       0      16      36864        0
             NAMEI   1024       0      36       12531       0      16      36864        0
         64 Bucket    512      56      16        1187       0      30      36864        0
        malloc-384    384      60      30         100       0      30      34560        0
        malloc-256    256     118      17         119       0      62      34560        0
      malloc-32768  32768       1       0           1       0       1      32768        0
      malloc-32768  32768       0       1          52       0       1      32768        0
      malloc-16384  16384       2       0           2       0       1      32768        0
       malloc-8192   8192       4       0           4       0       1      32768        0
           pcpu-64     64     454      58         454       0     254      32768        0
            pcpu-8      8    3292     292        3315       0     254      28672        0
         malloc-64     64     365      76        7954       0     254      28224        0
        malloc-128    128     161      56         260       0     126      27776        0
        malloc-384    384      51      19          59       0      30      26880        0
            socket    944      20       8        1014       0     254      26432        0
       malloc-8192   8192       3       0           5       0       1      24576        0
       malloc-1024   1024      17       7          20       0      16      24576        0
        malloc-128    128     129      57         571       0     126      23808        0
        malloc-384    384      57       3          57       0      30      23040        0
        malloc-256    256      72      18         830       0      62      23040        0
       malloc-4096   4096       3       2           9       0       2      20480        0
       malloc-2048   2048       4       6          10       0       8      20480        0
         malloc-64     64     193     122        1767       0     254      20160        0
         TURNSTILE    136     111      36         111       0      62      19992        0
       Mountpoints   2752       2       5           2       0       4      19264        0
        malloc-256    256      50      25         381       0      62      19200        0
        malloc-256    256      52      23         175       0      62      19200        0
      malloc-16384  16384       1       0           1       0       1      16384        0
      malloc-16384  16384       1       0           1       0       1      16384        0
      malloc-16384  16384       0       1          64       0       1      16384        0
       malloc-8192   8192       2       0           2       0       1      16384        0
       malloc-8192   8192       2       0          43       0       1      16384        0
       malloc-4096   4096       3       1         304       0       2      16384        0
       malloc-1024   1024       6      10         883       0      16      16384        0
         malloc-32     32     299     205        1167       0     254      16128        0
             tcpcb   1080       4      10          10       0     254      15120        0
              pipe    744       7      13         300       0      16      14880        0
       malloc-4096   4096       3       0           7       0       2      12288        0
       malloc-4096   4096       1       2           5       0       2      12288        0
       malloc-4096   4096       1       2        1105       0       2      12288        0
       malloc-2048   2048       4       2          17       0       8      12288        0
       malloc-2048   2048       3       3          21       0       8      12288        0
         malloc-64     64     133      56        1003       0     254      12096        0
             Files     80      82      68        7071       0     126      12000        0
         udp_inpcb    496       2      22          60       0     254      11904        0
        malloc-128    128      60      33         767       0     126      11904        0
        malloc-384    384      20      10         200       0      30      11520        0
        SLEEPQUEUE     88     111      17         111       0     126      11264        0
       malloc-8192   8192       1       0           1       0       1       8192        0
       malloc-2048   2048       4       0           4       0       8       8192        0
       malloc-2048   2048       3       1           3       0       8       8192        0
       malloc-2048   2048       0       4         213       0       8       8192        0
       malloc-1024   1024       3       5          52       0      16       8192        0
       malloc-1024   1024       3       5           3       0      16       8192        0
       malloc-1024   1024       1       7         113       0      16       8192        0
       malloc-1024   1024       7       1           7       0      16       8192        0
       malloc-1024   1024       2       6          23       0      16       8192        0
        malloc-512    512       2      14          18       0      30       8192        0
        malloc-512    512       2      14          39       0      30       8192        0
        malloc-512    512       8       8           8       0      30       8192        0
        malloc-512    512       1      15           3       0      30       8192        0
           rtentry    176      11      35          14       0      62       8096        0
              PGRP     88      15      77          32       0     126       8096        0
          rl_entry     40      27     175          29       0     254       8080        0
             udpcb     32       2     250          60       0     254       8064        0
               PWD     32      11     241          97       0     254       8064        0
         malloc-64     64      20     106          43       0     254       8064        0
         malloc-64     64       9     117          37       0     254       8064        0
         malloc-64     64      33      93          33       0     254       8064        0
         malloc-32     32      73     179          99       0     254       8064        0
         malloc-32     32      40     212          79       0     254       8064        0
         malloc-32     32      17     235          27       0     254       8064        0
         malloc-32     32      39     213          90       0     254       8064        0
         malloc-32     32      40     212        5169       0     254       8064        0
         16 Bucket    144      35      21         198       0      62       8064        0
          4 Bucket     48       5     163          54       0     254       8064        0
          2 Bucket     32      45     207         469       0     254       8064        0
         malloc-16     16      19     481         199       0     254       8000        0
         malloc-16     16      43     457         264       0     254       8000        0
         malloc-16     16     181     319         938       0     254       8000        0
         malloc-16     16       7     493           7       0     254       8000        0
         malloc-16     16     253     247         253       0     254       8000        0
         malloc-16     16      25     475       27445       0     254       8000        0
          8 Bucket     80      31      69         248       0     126       8000        0
         tcp_inpcb    496       4      12          10       0     254       7936        0
        malloc-128    128      23      39        2494       0     126       7936        0
              kenv    258       2      28         704       0      30       7740        0
     routing nhops    256       8      22          14       0      62       7680        0
             unpcb    256      12      18         932       0     254       7680        0
       mbuf_packet    256       1      29         105       0     254       7680        0
        malloc-384    384      14       6          16       0      30       7680        0
        malloc-384    384       7      13           8       0      30       7680        0
        malloc-384    384       0      20          14       0      30       7680        0
        malloc-256    256       4      26          95       0      62       7680        0
        malloc-256    256      20      10         304       0      62       7680        0
     FPU_save_area   1088       1       6           1       0       8       7616        0
            cpuset    104       8      54           8       0     126       6448        0
 epoch_record pcpu    256       4      12           4       0      62       4096        0
       malloc-2048   2048       0       2          16       0       8       4096        0
        malloc-512    512       1       7         156       0      30       4096        0
        malloc-512    512       1       7           1       0      30       4096        0
        malloc-512    512       0       8           1       0      30       4096        0
           pcpu-16     16       7     249           7       0     254       4096        0
         hostcache     64       1      62           1       0     254       4032        0
          syncache    168       0      24           5       0     254       4032        0
         malloc-32     32      13     113          38       0     254       4032        0
      vtnet_tx_hdr     24       1     166        6983       0     254       4008        0
            ttyinq    160      15      10          45       0      62       4000        0
         malloc-16     16      21     229          53       0     254       4000        0
             ripcb    496       1       7           1       0     254       3968        0
        malloc-128    128      20      11          80       0     126       3968        0
       UMA Slabs 1    176       6      16           6       0      62       3872        0
       L VFS Cache    320       0      12           1       0      30       3840        0
           ttyoutq    256       8       7          24       0      62       3840        0
        KMAP ENTRY     96      11      28          13       0       0       3744        0
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
       malloc-4096   4096       0       0           0       0       2          0        0
        malloc-384    384       0       0           0       0      30          0        0
           pcpu-32     32       0       0           0       0     254          0        0
            pcpu-4      4       0       0           0       0     254          0        0
            fakepg    104       0       0           0       0     126          0        0
          UMA Hash    256       0       0           0       0      62          0        0


Syzkaller reproducer:
# {Threaded:false Collide:false Repeat:false RepeatTimes:0 Procs:1 Slowdown:1 Sandbox: Fault:false FaultCall:-1 FaultNth:0 Leak:false NetInjection:false NetDevices:false NetReset:false Cgroups:false BinfmtMisc:false CloseFDs:false KCSAN:false DevlinkPCI:false USB:false VhciInjection:false Wifi:false IEEE802154:false Sysctl:false UseTmpDir:false HandleSegv:false Repro:false Trace:false}
open(&(0x7f0000001d40)='./file0\x00', 0x200, 0x0)
r0 = openat$md(0xffffffffffffff9c, &(0x7f0000000040), 0x0, 0x0)
ioctl$MDIOCATTACH(r0, 0xc1c06d00, &(0x7f00000000c0)={0x0, 0x0, 0x2, &(0x7f0000000000)='./file0\x00', 0x3b0b, 0x0, 0x5, 0x0, 0x0, 0x0, 0x0})
r1 = openat$md(0xffffffffffffff9c, &(0x7f0000000040), 0x0, 0x0)
ioctl$MDIOCRESIZE(r1, 0xc1c06d04, &(0x7f0000000300)={0x0, 0x0, 0x0, 0x0, 0x3ff, 0x0, 0x20, 0x0, 0x0, 0x0, 0x0, [0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x400000, 0x0, 0x0, 0x0, 0x0, 0x3, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xfffffffd, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2000002, 0x0, 0x0, 0x0, 0x0, 0xffffffff]})


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

uint64_t r[2] = {0xffffffffffffffff, 0xffffffffffffffff};

int main(void)
{
  syscall(SYS_mmap, 0x20000000ul, 0x1000000ul, 7ul, 0x1012ul, -1, 0ul);
  intptr_t res = 0;
  memcpy((void*)0x20001d40, "./file0\000", 8);
  syscall(SYS_open, 0x20001d40ul, 0x200ul, 0ul);
  memcpy((void*)0x20000040, "/dev/mdctl\000", 11);
  res = syscall(SYS_openat, 0xffffffffffffff9cul, 0x20000040ul, 0ul, 0ul);
  if (res != -1)
    r[0] = res;
  *(uint32_t*)0x200000c0 = 0;
  *(uint32_t*)0x200000c4 = 0;
  *(uint32_t*)0x200000c8 = 2;
  *(uint64_t*)0x200000d0 = 0x20000000;
  memcpy((void*)0x20000000, "./file0\000", 8);
  *(uint64_t*)0x200000d8 = 0x3b0b;
  *(uint32_t*)0x200000e0 = 0;
  *(uint32_t*)0x200000e4 = 5;
  *(uint64_t*)0x200000e8 = 0;
  *(uint32_t*)0x200000f0 = 0;
  *(uint32_t*)0x200000f4 = 0;
  *(uint64_t*)0x200000f8 = 0;
  *(uint32_t*)0x20000100 = 0;
  *(uint32_t*)0x20000104 = 0;
  *(uint32_t*)0x20000108 = 0;
  *(uint32_t*)0x2000010c = 0;
  *(uint32_t*)0x20000110 = 0;
  *(uint32_t*)0x20000114 = 0;
  *(uint32_t*)0x20000118 = 0;
  *(uint32_t*)0x2000011c = 0;
  *(uint32_t*)0x20000120 = 0;
  *(uint32_t*)0x20000124 = 0;
  *(uint32_t*)0x20000128 = 0;
  *(uint32_t*)0x2000012c = 0;
  *(uint32_t*)0x20000130 = 0;
  *(uint32_t*)0x20000134 = 0;
  *(uint32_t*)0x20000138 = 0;
  *(uint32_t*)0x2000013c = 0;
  *(uint32_t*)0x20000140 = 0;
  *(uint32_t*)0x20000144 = 0;
  *(uint32_t*)0x20000148 = 0;
  *(uint32_t*)0x2000014c = 0;
  *(uint32_t*)0x20000150 = 0;
  *(uint32_t*)0x20000154 = 0;
  *(uint32_t*)0x20000158 = 0;
  *(uint32_t*)0x2000015c = 0;
  *(uint32_t*)0x20000160 = 0;
  *(uint32_t*)0x20000164 = 0;
  *(uint32_t*)0x20000168 = 0;
  *(uint32_t*)0x2000016c = 0;
  *(uint32_t*)0x20000170 = 0;
  *(uint32_t*)0x20000174 = 0;
  *(uint32_t*)0x20000178 = 0;
  *(uint32_t*)0x2000017c = 0;
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
  syscall(SYS_ioctl, r[0], 0xc1c06d00ul, 0x200000c0ul);
  memcpy((void*)0x20000040, "/dev/mdctl\000", 11);
  res = syscall(SYS_openat, 0xffffffffffffff9cul, 0x20000040ul, 0ul, 0ul);
  if (res != -1)
    r[1] = res;
  *(uint32_t*)0x20000300 = 0;
  *(uint32_t*)0x20000304 = 0;
  *(uint32_t*)0x20000308 = 0;
  *(uint64_t*)0x20000310 = 0;
  *(uint64_t*)0x20000318 = 0x3ff;
  *(uint32_t*)0x20000320 = 0;
  *(uint32_t*)0x20000324 = 0x20;
  *(uint64_t*)0x20000328 = 0;
  *(uint32_t*)0x20000330 = 0;
  *(uint32_t*)0x20000334 = 0;
  *(uint64_t*)0x20000338 = 0;
  *(uint32_t*)0x20000340 = 0;
  *(uint32_t*)0x20000344 = 0;
  *(uint32_t*)0x20000348 = 0;
  *(uint32_t*)0x2000034c = 0;
  *(uint32_t*)0x20000350 = 0;
  *(uint32_t*)0x20000354 = 0;
  *(uint32_t*)0x20000358 = 0;
  *(uint32_t*)0x2000035c = 0;
  *(uint32_t*)0x20000360 = 0;
  *(uint32_t*)0x20000364 = 0;
  *(uint32_t*)0x20000368 = 0x400000;
  *(uint32_t*)0x2000036c = 0;
  *(uint32_t*)0x20000370 = 0;
  *(uint32_t*)0x20000374 = 0;
  *(uint32_t*)0x20000378 = 0;
  *(uint32_t*)0x2000037c = 3;
  *(uint32_t*)0x20000380 = 0;
  *(uint32_t*)0x20000384 = 0;
  *(uint32_t*)0x20000388 = 0;
  *(uint32_t*)0x2000038c = 0;
  *(uint32_t*)0x20000390 = 0;
  *(uint32_t*)0x20000394 = 0;
  *(uint32_t*)0x20000398 = 0;
  *(uint32_t*)0x2000039c = 0;
  *(uint32_t*)0x200003a0 = 0;
  *(uint32_t*)0x200003a4 = 0;
  *(uint32_t*)0x200003a8 = 0;
  *(uint32_t*)0x200003ac = 0;
  *(uint32_t*)0x200003b0 = 0;
  *(uint32_t*)0x200003b4 = 0;
  *(uint32_t*)0x200003b8 = 0x2000;
  *(uint32_t*)0x200003bc = 0;
  *(uint32_t*)0x200003c0 = 0;
  *(uint32_t*)0x200003c4 = 0;
  *(uint32_t*)0x200003c8 = 0;
  *(uint32_t*)0x200003cc = 0;
  *(uint32_t*)0x200003d0 = 0;
  *(uint32_t*)0x200003d4 = 0;
  *(uint32_t*)0x200003d8 = 0xfffffffd;
  *(uint32_t*)0x200003dc = 0;
  *(uint32_t*)0x200003e0 = 0;
  *(uint32_t*)0x200003e4 = 0;
  *(uint32_t*)0x200003e8 = 0;
  *(uint32_t*)0x200003ec = 0;
  *(uint32_t*)0x200003f0 = 0;
  *(uint32_t*)0x200003f4 = 0;
  *(uint32_t*)0x200003f8 = 0;
  *(uint32_t*)0x200003fc = 0;
  *(uint32_t*)0x20000400 = 0;
  *(uint32_t*)0x20000404 = 0;
  *(uint32_t*)0x20000408 = 0;
  *(uint32_t*)0x2000040c = 0;
  *(uint32_t*)0x20000410 = 0;
  *(uint32_t*)0x20000414 = 0;
  *(uint32_t*)0x20000418 = 0;
  *(uint32_t*)0x2000041c = 0;
  *(uint32_t*)0x20000420 = 6;
  *(uint32_t*)0x20000424 = 0;
  *(uint32_t*)0x20000428 = 0;
  *(uint32_t*)0x2000042c = 0;
  *(uint32_t*)0x20000430 = 0;
  *(uint32_t*)0x20000434 = 0;
  *(uint32_t*)0x20000438 = 0;
  *(uint32_t*)0x2000043c = 0;
  *(uint32_t*)0x20000440 = 0;
  *(uint32_t*)0x20000444 = 0;
  *(uint32_t*)0x20000448 = 0;
  *(uint32_t*)0x2000044c = 0;
  *(uint32_t*)0x20000450 = 0;
  *(uint32_t*)0x20000454 = 0x2000002;
  *(uint32_t*)0x20000458 = 0;
  *(uint32_t*)0x2000045c = 0;
  *(uint32_t*)0x20000460 = 0;
  *(uint32_t*)0x20000464 = 0;
  *(uint32_t*)0x20000468 = -1;
  *(uint32_t*)0x2000046c = 0;
  *(uint32_t*)0x20000470 = 0;
  *(uint32_t*)0x20000474 = 0;
  *(uint32_t*)0x20000478 = 0;
  *(uint32_t*)0x2000047c = 0;
  *(uint32_t*)0x20000480 = 0;
  *(uint32_t*)0x20000484 = 0;
  *(uint32_t*)0x20000488 = 0;
  *(uint32_t*)0x2000048c = 0;
  *(uint32_t*)0x20000490 = 0;
  *(uint32_t*)0x20000494 = 0;
  *(uint32_t*)0x20000498 = 0;
  *(uint32_t*)0x2000049c = 0;
  *(uint32_t*)0x200004a0 = 0;
  *(uint32_t*)0x200004a4 = 0;
  *(uint32_t*)0x200004a8 = 0;
  *(uint32_t*)0x200004ac = 0;
  *(uint32_t*)0x200004b0 = 0;
  *(uint32_t*)0x200004b4 = 0;
  *(uint32_t*)0x200004b8 = 0;
  *(uint32_t*)0x200004bc = 0;
  syscall(SYS_ioctl, r[1], 0xc1c06d04ul, 0x20000300ul);
  return 0;
}


