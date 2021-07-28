Syzkaller hit 'panic: KMSAN: Uninitialized malloc memory from vfs_buildopts+0xbab' bug.

login: panic: KMSAN: Uninitialized malloc memory from vfs_buildopts+0xbab
cpuid = 0
time = 1627323241
KDB: stack backtrace:
db_trace_self_wrapper() at db_trace_self_wrapper+0xde/frame 0xfffffe001a622450
vpanic() at vpanic+0x639/frame 0xfffffe001a622510
panic() at panic+0x1b3/frame 0xfffffe001a622620
__msan_warning() at __msan_warning+0x264/frame 0xfffffe001a622770
g_raid_md_taste_sii() at g_raid_md_taste_sii+0xd04/frame 0xfffffe001a622910
g_raid_taste() at g_raid_taste+0xadb/frame 0xfffffe001a622a10
g_new_provider_event() at g_new_provider_event+0x74a/frame 0xfffffe001a622aa0
g_run_events() at g_run_events+0x9b2/frame 0xfffffe001a622b60
fork_exit() at fork_exit+0x21e/frame 0xfffffe001a622bf0
fork_trampoline() at fork_trampoline+0xe/frame 0xfffffe001a622bf0
--- trap 0, rip = 0, rsp = 0, rbp = 0 ---
KDB: enter: panic
[ thread pid 13 tid 100036 ]
Stopped at      kdb_enter+0x1c7:        movq    $0x87024010,%rdi
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
rax         0xffffffff8632f0bc
rcx                          0
rdx         0xffffffff8702b000  msan_dummy_orig
rbx                          0
rsp         0xfffffe001a6223f0
rbp         0xfffffe001a622450
rsi                        0x1
rdi         0xffffffff87024010  kdb_why
r8                           0
r9                           0
r10                          0
r11                          0
r12                          0
r13         0xffffffff87028e01  msan_thread0+0x3e01
r14         0xffffffff87028ec8  dummy_tls
r15         0xffffffff8632f0bc
rip         0xffffffff83f97477  kdb_enter+0x1c7
rflags                    0x46
kdb_enter+0x1c7:        movq    $0x87024010,%rdi
db> show proc
Process 13 (geom) at 0xfffffe001a44a000:
 state: NORMAL
 uid: 0  gids: 0
 parent: pid 0 at 0xffffffff86fd7570
 ABI: null
 flag: 0x10000284  flag2: 0
 reaper: 0xffffffff86fd7570 reapsubtree: 13
 sigparent: 20
 vmspace: 0xffffffff86fd81f0
   (map 0xffffffff86fd81f0)
   (map.pmap 0xffffffff86fd82b0)
   (pmap 0xffffffff86fd8310)
 threads: 3
100036                   Run     CPU 0                       [g_event]
100037                   D       -       0xffffffff86fd6fe8  [g_up]
100038                   D       -       0xffffffff86fd6ff0  [g_down]
db> ps
  pid  ppid  pgrp   uid  state   wmesg   wchan               cmd
  836     0     0     0  DL      mdwait  0xfffffe003b346000  [md5]
  835   833   829     0  R       (threaded)                  syz-executor1307031
100084                   RunQ                                syz-executor1307031
100104                   RunQ                                syz-executor1307031
  834   832   829     0  R       (threaded)                  syz-executor1307031
100077                   Run     CPU 1                       syz-executor1307031
100103                   D       g_waiti 0xffffffff86fd6f10  syz-executor1307031
  833   831   829     0  S       nanslp  0xffffffff86ff77a1  syz-executor1307031
  832   831   829     0  S       nanslp  0xffffffff86ff77a1  syz-executor1307031
  831   829   829     0  S       nanslp  0xffffffff86ff77a0  syz-executor1307031
  829   827   829     0  Ss      pause   0xfffffe003a9195e8  csh
  827   781   827     0  Ss      select  0xfffffe001a90bd40  sshd
  797     1   797     0  Ss+     ttyin   0xfffffe001aaeccb0  getty
  781     1   781     0  Ss      select  0xfffffe001a90bb40  sshd
  758     1   758    25  Ss      pause   0xfffffe003aebcb20  sendmail
  755     1   755     0  Ss      select  0xfffffe003ae8ef40  sendmail
  726     1   726     0  Ss      nanslp  0xffffffff86ff77a1  cron
  646     1   646     0  Ss      select  0xfffffe001a9254c0  syslogd
  448     1   448     0  Ss      select  0xfffffe001a9250c0  devd
  352     1   352    65  Ss      select  0xfffffe001a925140  dhclient
  270     1   270     0  Ss      select  0xfffffe001a8fd040  dhclient
  267     1   267     0  Ss      select  0xfffffe001a9253c0  dhclient
  102     0     0     0  DL      pftm    0xffffffff87731b30  [pf purge]
   21     0     0     0  DL      syncer  0xffffffff870ee800  [syncer]
   20     0     0     0  DL      vlruwt  0xfffffe001f851538  [vnlru]
   19     0     0     0  RL      (threaded)                  [bufdaemon]
100070                   RunQ                                [bufdaemon]
100071                   D       -       0xffffffff86a0af80  [bufspacedaemon-0]
100085                   D       sdflush 0xfffffe001a9074e8  [/ worker]
   18     0     0     0  DL      psleep  0xffffffff87113588  [vmdaemon]
   17     0     0     0  DL      (threaded)                  [pagedaemon]
100068                   D       psleep  0xffffffff871079f8  [dom0]
100072                   D       launds  0xffffffff87107a04  [laundry: dom0]
100073                   D       umarcl  0xffffffff85369b10  [uma]
   16     0     0     0  DL      -       0xffffffff86e2bb58  [rand_harvestq]
   15     0     0     0  DL      -       0xffffffff870eaf5c  [soaiod4]
    9     0     0     0  DL      -       0xffffffff870eaf5c  [soaiod3]
    8     0     0     0  DL      -       0xffffffff870eaf5c  [soaiod2]
    7     0     0     0  DL      -       0xffffffff870eaf5c  [soaiod1]
    6     0     0     0  DL      (threaded)                  [cam]
100045                   D       -       0xffffffff86d03240  [doneq0]
100046                   D       -       0xffffffff86d031c0  [async]
100067                   D       -       0xffffffff86d03090  [scanner]
   14     0     0     0  DL      seqstat 0xfffffe0010b19088  [sequencer 00]
    5     0     0     0  DL      crypto_ 0xfffffe001a4bec80  [crypto returns 1]
    4     0     0     0  DL      crypto_ 0xfffffe001a4bec30  [crypto returns 0]
    3     0     0     0  DL      crypto_ 0xffffffff87104f20  [crypto]
   13     0     0     0  RL      (threaded)                  [geom]
100036                   Run     CPU 0                       [g_event]
100037                   D       -       0xffffffff86fd6fe8  [g_up]
100038                   D       -       0xffffffff86fd6ff0  [g_down]
    2     0     0     0  DL      (threaded)                  [KTLS]
100029                   D       -       0xfffffe001a4bee00  [thr_0]
100030                   D       -       0xfffffe001a4bee80  [thr_1]
   12     0     0     0  WL      (threaded)                  [intr]
100010                   I                                   [swi5: fast taskq]
100018                   I                                   [swi6: task queue]
100019                   I                                   [swi6: Giant taskq]
100031                   I                                   [swi1: netisr 0]
100032                   I                                   [swi4: clock (0)]
100033                   I                                   [swi4: clock (1)]
100034                   I                                   [swi3: vm]
100047                   I                                   [irq40: virtio_pci0]
100048                   I                                   [irq41: virtio_pci0]
100049                   I                                   [irq42: virtio_pci0]
100052                   I                                   [irq43: virtio_pci1]
100053                   I                                   [irq44: virtio_pci1]
100054                   I                                   [irq1: atkbd0]
100055                   I                                   [irq12: psm0]
100056                   I                                   [swi0: uart uart++]
100087                   I                                   [swi1: pf send]
   11     0     0     0  RL      (threaded)                  [idle]
100003                   CanRun                              [idle: cpu0]
100004                   CanRun                              [idle: cpu1]
    1     0     1     0  SLs     wait    0xfffffe0011383538  [init]
   10     0     0     0  DL      audit_w 0xffffffff87105430  [audit]
    0     0     0     0  DLs     (threaded)                  [kernel]
100000                   D       swapin  0xffffffff86fd7570  [swapper]
100005                   D       -       0xfffffe001123ec00  [if_io_tqg_0]
100006                   D       -       0xfffffe001123eb00  [if_io_tqg_1]
100007                   D       -       0xfffffe001123ea00  [if_config_tqg_0]
100008                   D       -       0xfffffe001123e900  [softirq_0]
100009                   D       -       0xfffffe001123e800  [softirq_1]
100011                   D       -       0xfffffe00113efa00  [in6m_free taskq]
100012                   D       -       0xfffffe00113ef900  [pci_hp taskq]
100013                   D       -       0xfffffe00113ef800  [aiod_kick taskq]
100014                   D       -       0xfffffe00113ef700  [kqueue_ctx taskq]
100015                   D       -       0xfffffe00113ef600  [inm_free taskq]
100016                   D       -       0xfffffe00113ef500  [deferred_unmount ta]
100017                   D       -       0xfffffe00113ef400  [linuxkpi_irq_wq]
100020                   D       -       0xfffffe001a47be00  [thread taskq]
100021                   D       -       0xfffffe001a47bd00  [linuxkpi_short_wq_0]
100022                   D       -       0xfffffe001a47bd00  [linuxkpi_short_wq_1]
100023                   D       -       0xfffffe001a47bd00  [linuxkpi_short_wq_2]
100024                   D       -       0xfffffe001a47bd00  [linuxkpi_short_wq_3]
100025                   D       -       0xfffffe001a47bc00  [linuxkpi_long_wq_0]
100026                   D       -       0xfffffe001a47bc00  [linuxkpi_long_wq_1]
100027                   D       -       0xfffffe001a47bc00  [linuxkpi_long_wq_2]
100028                   D       -       0xfffffe001a47bc00  [linuxkpi_long_wq_3]
100035                   D       -       0xfffffe001a47b600  [firmware taskq]
100039                   D       -       0xfffffe001a47b500  [crypto_0]
100040                   D       -       0xfffffe001a47b500  [crypto_1]
100050                   D       -       0xfffffe001a942600  [vtnet0 rxq 0]
100051                   D       -       0xfffffe001a942500  [vtnet0 txq 0]
100060                   D       -       0xffffffff866d75f0  [deadlkres]
100063                   D       -       0xfffffe001aaedd00  [acpi_task_0]
100064                   D       -       0xfffffe001aaedd00  [acpi_task_1]
100065                   D       -       0xfffffe001aaedd00  [acpi_task_2]
100066                   D       -       0xfffffe001a47b400  [CAM taskq]
db> show all locks
db> show malloc
              Type        InUse        MemUse     Requests
           pf_hash            5        11524K            5
         sysctloid        30518         1801K        30560
             kmsan          104         1664K          104
            linker          227         1500K          240
              kobj          324         1296K          484
            devbuf         1360         1150K         1377
            newblk          150         1062K          674
          vfscache            3         1025K            3
               pcb           16          777K           32
          inodedep            7          515K          105
         ufs_quota            1          512K            1
          vfs_hash            1          512K            1
           callout            2          512K            2
              intr            4          472K            4
           subproc           90          183K          886
         vnet_data            1          168K            1
           tidhash            3          158K            3
           pagedep            6          130K           39
        tfo_ccache            1          128K            1
               sem            4          106K            4
            DEVFS1           91           91K          103
              vmem            3           84K            5
               bus          965           77K         2576
            bus-sc           31           76K         1061
          mtx_pool            2           72K            2
          syncache            1           68K            1
          acpitask            1           64K            1
       ddb_capture            1           64K            1
            module          491           62K          491
            acpica          420           39K        61577
               LRO            2           33K            2
              proc            3           33K            3
         hostcache            1           32K            1
               shm            1           32K            1
               msg            4           30K            4
           kdtrace          146           29K          942
            DEVFS3          110           28K          126
              umtx          220           28K          220
        gtaskqueue           18           26K           18
            kbdmux            5           22K            5
        DEVFS_RULE           59           21K           59
           ithread          104           19K          104
               BPF           10           18K           10
              temp           15           17K         1553
         ufs_mount            4           17K            5
       pfs_vncache            1           16K            1
            KTRACE          100           13K          100
           devstat            6           13K            6
              rman          103           12K          527
              GEOM           69           12K          516
            ifaddr           29           11K           30
      eventhandler          125           11K          125
              kenv           59           10K           59
          routetbl           44           10K          142
         bmsafemap            3            9K           97
              UART           12            9K           12
               rpc            2            8K            2
             shmfd            1            8K            1
         pfs_nodes           20            8K           20
     audit_evclass          236            8K          294
         taskqueue           54            6K           54
            sglist            3            6K            3
       ufs_dirhash           24            5K           24
              cred           18            5K          309
           uidinfo            4            5K           11
             ifnet            3            5K            3
               UMA          251            5K          251
           md_disk            2            5K            2
           io_apic            1            4K            1
               tty            4            4K            4
        md_sectors            1            4K            1
             evdev            4            4K            4
          filedesc            1            4K            1
             hhook           13            4K           13
          pf_ifnet            5            3K            6
       fpukern_ctx            3            3K            3
            plimit           12            3K          270
           lltable           10            3K           10
           acpisem           21            3K           21
            kqueue           41            3K          837
           pwddesc           41            3K          837
             lockf           22            3K           36
        local_apic            1            2K            1
         ipsec-saq            2            2K            2
           CAM DEV            1            2K            2
             selfd           29            2K        18323
               msi           13            2K           13
           session           13            2K           33
            Unitno           27            2K           47
          pci_link           16            2K           16
           acpidev           22            2K           22
         toponodes           10            2K           10
         proc-args           30            2K          595
         CAM queue            2            2K            5
           softdep            1            1K            1
             mkdir            8            1K           38
       ipsecpolicy            1            1K            1
            sahead            1            1K            1
          secasvar            1            1K            1
             clone            8            1K            8
       ether_multi           13            1K           18
       vnodemarker            2            1K           34
            select            8            1K           61
      NFSD session            1            1K            1
         in6_multi            9            1K            9
             nhops            6            1K            6
             mount           16            1K          123
            diradd            5            1K          112
            crypto            4            1K            4
            isadev            5            1K            5
           CAM XPT           11            1K           12
         newdirblk            4            1K           19
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
          indirdep            1            1K            3
               mld            2            1K            2
              igmp            2            1K            2
            vnodes            1            1K            1
              ktls            1            1K            1
         raid_data            1            1K           73
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
          procdesc            1            1K           20
          pmchooks            1            1K            1
            soname            4            1K         2572
          nexusdev            6            1K            6
               tun            3            1K            3
     CAM dev queue            1            1K            1
           tcpfunc            1            1K            1
              vnet            1            1K            1
          acpiintr            1            1K            1
               pmc            1            1K            1
              cpus            2            1K            2
          freework            1            1K           26
    vnet_data_free            1            1K            1
          CAM path            1            1K           12
           entropy            1            1K           58
           Per-cpu            1            1K            1
          p1003.1b            1            1K            1
          filecaps            1            1K          105
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
          savedino            0            0K           16
          sentinel            0            0K            0
            jfsync            0            0K            0
            jtrunc            0            0K            0
             sbdep            0            0K            6
           jsegdep            0            0K            0
              jseg            0            0K            0
         jfreefrag            0            0K            0
          jfreeblk            0            0K            0
           jnewblk            0            0K            0
            jmvref            0            0K            0
           jremref            0            0K            0
           jaddref            0            0K            0
           freedep            0            0K            0
            dirrem            0            0K           46
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
            statfs            0            0K           15
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
               iov            0            0K         7950
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
              sbuf            0            0K          362
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
   mbuf_jumbo_page   4096    1088     859       14738       0     254    7974912        0
      malloc-16384  16384     107       0         107       0       1    1753088        0
        malloc-128    128   10760      28       10869       0     126    1380864        0
       malloc-4096   4096     324       0         484       0       2    1327104        0
          BUF TRIE    144     172    8984         488       0      62    1318464        0
              pbuf   2624       0     264           0       0       2     692736        0
              mbuf    256    1346     979       22834       0     254     595200        0
        malloc-512    512    1026      14        1034       0      30     532480        0
      malloc-65536  65536       6       1          37       0       1     458752        0
         vmem btag     56    7145     102        7145       0     254     405832        0
        RADIX NODE    144    2291     447       29280       0      62     394272        0
            lkpimm    160       1    2324           1       0      62     372000        0
          lkpicurr    160       2    2323           2       0      62     372000        0
       UMA Slabs 0    112    2938      11        2938       0     126     330288        0
       malloc-2048   2048     136       8         160       0       8     294912        0
             VNODE    448     533      43         564       0      30     258048        0
         VM OBJECT    264     887      73       11939       0      30     253440        0
        256 Bucket   2048     102      16        2742       0       8     241664        0
         malloc-64     64    3387      78        3443       0     254     221760        0
         malloc-16     16   12683     317       12732       0     254     208000        0
            THREAD   1808     104       6         104       0       8     198880        0
            DEVCTL   1024       0     192          93       0       0     196608        0
      malloc-65536  65536       3       0           3       0       1     196608        0
      malloc-65536  65536       1       2          70       0       1     196608        0
       malloc-4096   4096      41       3         841       0       2     180224        0
         UMA Zones    768     223       1         223       0      16     172032        0
         malloc-32     32    4691      97        4839       0     254     153216        0
       FFS2 dinode    256     511      14         539       0      62     134400        0
        malloc-256    256     167     358        1201       0      62     134400        0
      malloc-65536  65536       2       0           2       0       1     131072        0
      malloc-32768  32768       2       2           4       0       1     131072        0
       S VFS Cache    104    1007     124        1088       0     126     117624        0
          ksiginfo    112      31    1013          76       0     126     116928        0
       malloc-1024   1024     101       7         229       0      16     110592        0
       malloc-8192   8192      11       2          14       0       1     106496        0
         FFS inode    192     511      35         539       0      62     104832        0
         MAP ENTRY     96     723     369       37614       0     126     104832        0
          UMA Kegs    384     208       5         208       0      30      81792        0
        128 Bucket   1024      47      32         693       0      16      80896        0
         malloc-64     64     978      93       20682       0     254      68544        0
      mbuf_cluster   2048      30       2          30       0     254      65536        0
      malloc-32768  32768       2       0          54       0       1      65536        0
              PROC   1336      40       8         836       0       8      64128        0
        malloc-256    256     226      14         473       0      62      61440        0
           VMSPACE   2544      18       6         815       0       4      61056        0
         filedesc0   1072      41      15         837       0       8      60032        0
        malloc-128    128     373      61        3656       0     126      55552        0
        malloc-128    128     346      57       28265       0     126      51584        0
        malloc-384    384      56      64         156       0      30      46080        0
            clpbuf   2624       0      15          29       0       5      39360        0
         32 Bucket    256      41     109         531       0      62      38400        0
             NAMEI   1024       0      36       12604       0      16      36864        0
           DIRHASH   1024      32       0          32       0      16      32768        0
      malloc-32768  32768       1       0           1       0       1      32768        0
      malloc-32768  32768       1       0           1       0       1      32768        0
      malloc-16384  16384       2       0           2       0       1      32768        0
       malloc-4096   4096       6       2           9       0       2      32768        0
           pcpu-64     64     455      57         455       0     254      32768        0
         64 Bucket    512      55       9         720       0      30      32768        0
        malloc-256    256      87      33         587       0      62      30720        0
            pcpu-8      8    3297     287        3320       0     254      28672        0
             g_bio    384       0      70        5059       0      30      26880        0
        malloc-384    384      54      16          54       0      30      26880        0
        malloc-256    256      85      20         343       0      62      26880        0
       malloc-4096   4096       4       2         274       0       2      24576        0
         malloc-64     64     261     117        3353       0     254      24192        0
        malloc-128    128     145      41         584       0     126      23808        0
            socket    944      18       6        1015       0     254      22656        0
       malloc-2048   2048       5       5         232       0       8      20480        0
       malloc-1024   1024      14       6         897       0      16      20480        0
       Mountpoints   2752       2       5           2       0       4      19264        0
         TURNSTILE    136     111      15         111       0      62      17136        0
      malloc-16384  16384       1       0           1       0       1      16384        0
      malloc-16384  16384       1       0          65       0       1      16384        0
       malloc-8192   8192       0       2          32       0       1      16384        0
       malloc-8192   8192       2       0           2       0       1      16384        0
       malloc-8192   8192       2       0          43       0       1      16384        0
       malloc-8192   8192       2       0           2       0       1      16384        0
       malloc-4096   4096       4       0           5       0       2      16384        0
        malloc-256    256      34      26         408       0      62      15360        0
             tcpcb   1080       4      10          10       0     254      15120        0
        SLEEPQUEUE     88     111      49         111       0     126      14080        0
       malloc-4096   4096       1       2          16       0       2      12288        0
       malloc-4096   4096       3       0           3       0       2      12288        0
       malloc-4096   4096       3       0          40       0       2      12288        0
       malloc-1024   1024       4       8          21       0      16      12288        0
       malloc-1024   1024       9       3           9       0      16      12288        0
             Files     80      75      75        7079       0     126      12000        0
         malloc-16     16     451     299        1323       0     254      12000        0
        malloc-128    128      42      51         167       0     126      11904        0
        malloc-384    384      17      13          25       0      30      11520        0
              pipe    744       7       8         303       0      16      11160        0
       malloc-2048   2048       1       3          13       0       8       8192        0
       malloc-1024   1024       4       4          53       0      16       8192        0
       malloc-1024   1024       4       4           4       0      16       8192        0
       malloc-1024   1024       2       6           3       0      16       8192        0
       malloc-1024   1024       4       4           4       0      16       8192        0
        malloc-512    512      10       6          42       0      30       8192        0
        malloc-512    512       3      13          42       0      30       8192        0
           rtentry    176      11      35          14       0      62       8096        0
              PGRP     88      13      79          33       0     126       8096        0
          rl_entry     40      26     176          28       0     254       8080        0
             udpcb     32       2     250          60       0     254       8064        0
               PWD     32      15     237         103       0     254       8064        0
         malloc-64     64      23     103        7724       0     254       8064        0
         malloc-64     64      34      92          51       0     254       8064        0
         malloc-64     64       5     121           9       0     254       8064        0
         malloc-64     64       8     118           9       0     254       8064        0
         malloc-64     64       7     119          31       0     254       8064        0
         malloc-32     32      63     189         227       0     254       8064        0
         malloc-32     32     120     132         882       0     254       8064        0
         malloc-32     32      30     222        4972       0     254       8064        0
         malloc-32     32      48     204          50       0     254       8064        0
         malloc-32     32      13     239          43       0     254       8064        0
         16 Bucket    144      33      23        1523       0      62       8064        0
          4 Bucket     48       5     163          50       0     254       8064        0
          2 Bucket     32      41     211         572       0     254       8064        0
      vtnet_tx_hdr     24       1     333        7013       0     254       8016        0
            ttyinq    160      15      35          45       0      62       8000        0
         malloc-16     16      24     476         179       0     254       8000        0
         malloc-16     16      13     487          53       0     254       8000        0
         malloc-16     16      37     463       26957       0     254       8000        0
         malloc-16     16       4     496           5       0     254       8000        0
         malloc-16     16      16     484          19       0     254       8000        0
         malloc-16     16       7     493           7       0     254       8000        0
          8 Bucket     80      27      73         331       0     126       8000        0
         tcp_inpcb    496       4      12          10       0     254       7936        0
         udp_inpcb    496       2      14          60       0     254       7936        0
        malloc-128    128      16      46          23       0     126       7936        0
        malloc-128    128      11      51          12       0     126       7936        0
              kenv    258       2      28         704       0      30       7740        0
     routing nhops    256       8      22          14       0      62       7680        0
             unpcb    256      10      20         933       0     254       7680        0
           ttyoutq    256       8      22          24       0      62       7680        0
       mbuf_packet    256       0      30         103       0     254       7680        0
        malloc-384    384      20       0          20       0      30       7680        0
        malloc-384    384       8      12           9       0      30       7680        0
        malloc-384    384       0      20         194       0      30       7680        0
        malloc-256    256       2      28         112       0      62       7680        0
     FPU_save_area    832       1       8           1       0      16       7488        0
            cpuset    104       7      55           7       0     126       6448        0
 epoch_record pcpu    256       4      12           4       0      62       4096        0
       malloc-2048   2048       2       0           2       0       8       4096        0
       malloc-2048   2048       1       1           1       0       8       4096        0
       malloc-2048   2048       1       1           1       0       8       4096        0
        malloc-512    512       0       8         139       0      30       4096        0
        malloc-512    512       2       6           2       0      30       4096        0
           pcpu-16     16       7     249           7       0     254       4096        0
         hostcache     64       1      62           1       0     254       4032        0
          syncache    168       0      24           5       0     254       4032        0
               ipq     56       0      72           5       0     254       4032        0
         malloc-32     32       9     117          47       0     254       4032        0
         malloc-32     32       0     126           2       0     254       4032        0
             ripcb    496       1       7           1       0     254       3968        0
        malloc-128    128       1      30          12       0     126       3968        0
       UMA Slabs 1    176       6      16           6       0      62       3872        0
       L VFS Cache    320       0      12           1       0      30       3840        0
        malloc-256    256       1      14           1       0      62       3840        0
        malloc-256    256      15       0          15       0      62       3840        0
        KMAP ENTRY     96      11      28          12       0       0       3744        0
              vmem   1856       1       1           1       0       8       3712        0
           SMR CPU     32       3      60           3       0     254       2016        0
        SMR SHARED     24       3      60           3       0     254       1512        0
               md5      4       0       0           0       0     254          0        0
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
           ada_ccb    272       0       0           0       0      30          0        0
            da_ccb    544       0       0           0       0      16          0        0
       FFS1 dinode    128       0       0           0       0     126          0        0
             swblk    136       0       0           0       0      62          0        0
          swpctrie    144       0       0           0       0      62          0        0
     udplite_inpcb    496       0       0           0       0     254          0        0
      tcp_log_node    120       0       0           0       0     126          0        0
    tcp_log_bucket    176       0       0           0       0      62          0        0
           tcp_log    416       0       0           0       0     254          0        0
          tcpreass     48       0       0           0       0     254          0        0
tfo_ccache_entries     80       0       0           0       0     126          0        0
               tfo      4       0       0           0       0     254          0        0
          sackhole     32       0       0           0       0     254          0        0
             tcptw     88       0       0           0       0     254          0        0
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
       malloc-8192   8192       0       0           0       0       1          0        0
       malloc-2048   2048       0       0           0       0       8          0        0
       malloc-2048   2048       0       0           0       0       8          0        0
        malloc-512    512       0       0           0       0      30          0        0
        malloc-512    512       0       0           0       0      30          0        0
        malloc-512    512       0       0           0       0      30          0        0
        malloc-384    384       0       0           0       0      30          0        0
        malloc-384    384       0       0           0       0      30          0        0
           pcpu-32     32       0       0           0       0     254          0        0
            pcpu-4      4       0       0           0       0     254          0        0
            fakepg    104       0       0           0       0     126          0        0
          UMA Hash    256       0       0           0       0      62          0        0


Syzkaller reproducer:
# {Threaded:true Collide:true Repeat:true RepeatTimes:0 Procs:2 Slowdown:1 Sandbox:none Fault:false FaultCall:-1 FaultNth:0 Leak:false NetInjection:false NetDevices:false NetReset:false Cgroups:false BinfmtMisc:false CloseFDs:false KCSAN:false DevlinkPCI:false USB:false VhciInjection:false Wifi:false IEEE802154:false Sysctl:false UseTmpDir:true HandleSegv:false Repro:false Trace:false}
r0 = openat$md(0xffffffffffffff9c, &(0x7f00000001c0), 0x0, 0x0)
freebsd10_pipe(&(0x7f0000000000)={<r1=>0xffffffffffffffff})
ioctl$MDIOCATTACH(r1, 0xc1c06d00, &(0x7f0000000200)={0xb7, 0x5, 0x1, &(0x7f0000000080)='./file0\x00', 0x81, 0x4, 0x2, 0x200, 0x327, 0x4, &(0x7f00000000c0)='/dev/mdctl\x00', [0x8001, 0x5, 0x7, 0x9, 0x2, 0x236d5710, 0x0, 0x3, 0xfffffffc, 0xa55, 0x81, 0x3, 0x10001, 0x0, 0x9, 0x7, 0x0, 0x200, 0x2, 0x0, 0x8, 0x8, 0x5, 0x2, 0x737ab064, 0x40, 0x6, 0x3, 0x7fffffff, 0x5, 0xfffffff8, 0x5, 0x2, 0x8, 0x7fffffff, 0x3f, 0x6, 0x0, 0x40ca, 0x8000, 0xffffffff, 0x1, 0x2, 0x5, 0x6, 0x8, 0x5, 0x6, 0x9, 0xfffffff7, 0x80000001, 0x6b, 0x0, 0x5, 0x3f, 0x800, 0x30, 0x0, 0x9, 0xc3, 0x4cec, 0x0, 0x5, 0x3, 0xfff, 0x6, 0xffffffff, 0x5, 0x8, 0x9, 0x4, 0x7ff, 0x7, 0x1, 0x1, 0x9, 0x5, 0x1f80, 0x1, 0x3, 0xc000, 0x3, 0x10000, 0xd68, 0x5, 0x401, 0x4, 0x8c, 0x1000, 0x3f, 0x5, 0x7, 0x9, 0x5, 0x800, 0x7f]})
ioctl$MDIOCATTACH(r0, 0xc1c06d00, &(0x7f0000000480)={0x0, 0x5, 0x0, 0x0, 0x5, 0x4, 0x0, 0x3642, 0x7fb05745, 0xc945, &(0x7f0000000040)='/dev/mdctl\x00', [0x1ff, 0xfffffffc, 0xff, 0x6914, 0x9, 0x6, 0x0, 0xfffffff7, 0x1fc0, 0x9, 0xb5d, 0x7, 0x20, 0x80, 0x20, 0x1000, 0x80, 0xfffffffc, 0x2, 0x7ff, 0x3, 0x6, 0x5d, 0x9, 0x8001, 0x6, 0x9, 0x10001, 0x9, 0xd411, 0x100, 0xa9, 0x9, 0x3, 0x3, 0xf8, 0x6, 0x4, 0x0, 0x7, 0x46, 0x9, 0x8000, 0x2, 0x10000, 0x80000000, 0xfffff000, 0x8, 0x8, 0x0, 0x7fff, 0x0, 0xffffff4b, 0x8, 0x3ff, 0x2, 0xfffffff9, 0xfc, 0x101, 0x4, 0xa8ee, 0x100, 0x5, 0x3, 0x7, 0xcf4, 0x1, 0xfffffffb, 0x80000001, 0x0, 0x1000, 0x1, 0x8eda, 0x3, 0x1f, 0x800, 0x8, 0x3ff, 0x9, 0x6c8, 0x80000001, 0x10000, 0x5, 0x3, 0x7, 0x2, 0x1, 0x2, 0x9, 0x4, 0x40, 0x3, 0x9, 0x7, 0x6, 0x80000000]})


C reproducer:
// autogenerated by syzkaller (https://github.com/google/syzkaller)

#define _GNU_SOURCE

#include <sys/types.h>

#include <dirent.h>
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

static void sandbox_common()
{
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
  int collide = 0;
again:
  for (call = 0; call < 4; call++) {
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
      if (collide && (call % 2) == 0)
        break;
      event_timedwait(&th->done, 50);
      break;
    }
  }
  for (i = 0; i < 100 && __atomic_load_n(&running, __ATOMIC_RELAXED); i++)
    sleep_ms(1);
  if (!collide) {
    collide = 1;
    goto again;
  }
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

uint64_t r[2] = {0xffffffffffffffff, 0xffffffffffffffff};

void execute_call(int call)
{
  intptr_t res = 0;
  switch (call) {
  case 0:
    memcpy((void*)0x200001c0, "/dev/mdctl\000", 11);
    res = syscall(SYS_openat, 0xffffffffffffff9cul, 0x200001c0ul, 0ul, 0ul);
    if (res != -1)
      r[0] = res;
    break;
  case 1:
    res = syscall(SYS_freebsd10_pipe, 0x20000000ul);
    if (res != -1)
      r[1] = *(uint32_t*)0x20000000;
    break;
  case 2:
    *(uint32_t*)0x20000200 = 0xb7;
    *(uint32_t*)0x20000204 = 5;
    *(uint32_t*)0x20000208 = 1;
    *(uint64_t*)0x20000210 = 0x20000080;
    memcpy((void*)0x20000080, "./file0\000", 8);
    *(uint64_t*)0x20000218 = 0x81;
    *(uint32_t*)0x20000220 = 4;
    *(uint32_t*)0x20000224 = 2;
    *(uint64_t*)0x20000228 = 0x200;
    *(uint32_t*)0x20000230 = 0x327;
    *(uint32_t*)0x20000234 = 4;
    *(uint64_t*)0x20000238 = 0x200000c0;
    memcpy((void*)0x200000c0, "/dev/mdctl\000", 11);
    *(uint32_t*)0x20000240 = 0x8001;
    *(uint32_t*)0x20000244 = 5;
    *(uint32_t*)0x20000248 = 7;
    *(uint32_t*)0x2000024c = 9;
    *(uint32_t*)0x20000250 = 2;
    *(uint32_t*)0x20000254 = 0x236d5710;
    *(uint32_t*)0x20000258 = 0;
    *(uint32_t*)0x2000025c = 3;
    *(uint32_t*)0x20000260 = 0xfffffffc;
    *(uint32_t*)0x20000264 = 0xa55;
    *(uint32_t*)0x20000268 = 0x81;
    *(uint32_t*)0x2000026c = 3;
    *(uint32_t*)0x20000270 = 0x10001;
    *(uint32_t*)0x20000274 = 0;
    *(uint32_t*)0x20000278 = 9;
    *(uint32_t*)0x2000027c = 7;
    *(uint32_t*)0x20000280 = 0;
    *(uint32_t*)0x20000284 = 0x200;
    *(uint32_t*)0x20000288 = 2;
    *(uint32_t*)0x2000028c = 0;
    *(uint32_t*)0x20000290 = 8;
    *(uint32_t*)0x20000294 = 8;
    *(uint32_t*)0x20000298 = 5;
    *(uint32_t*)0x2000029c = 2;
    *(uint32_t*)0x200002a0 = 0x737ab064;
    *(uint32_t*)0x200002a4 = 0x40;
    *(uint32_t*)0x200002a8 = 6;
    *(uint32_t*)0x200002ac = 3;
    *(uint32_t*)0x200002b0 = 0x7fffffff;
    *(uint32_t*)0x200002b4 = 5;
    *(uint32_t*)0x200002b8 = 0xfffffff8;
    *(uint32_t*)0x200002bc = 5;
    *(uint32_t*)0x200002c0 = 2;
    *(uint32_t*)0x200002c4 = 8;
    *(uint32_t*)0x200002c8 = 0x7fffffff;
    *(uint32_t*)0x200002cc = 0x3f;
    *(uint32_t*)0x200002d0 = 6;
    *(uint32_t*)0x200002d4 = 0;
    *(uint32_t*)0x200002d8 = 0x40ca;
    *(uint32_t*)0x200002dc = 0x8000;
    *(uint32_t*)0x200002e0 = -1;
    *(uint32_t*)0x200002e4 = 1;
    *(uint32_t*)0x200002e8 = 2;
    *(uint32_t*)0x200002ec = 5;
    *(uint32_t*)0x200002f0 = 6;
    *(uint32_t*)0x200002f4 = 8;
    *(uint32_t*)0x200002f8 = 5;
    *(uint32_t*)0x200002fc = 6;
    *(uint32_t*)0x20000300 = 9;
    *(uint32_t*)0x20000304 = 0xfffffff7;
    *(uint32_t*)0x20000308 = 0x80000001;
    *(uint32_t*)0x2000030c = 0x6b;
    *(uint32_t*)0x20000310 = 0;
    *(uint32_t*)0x20000314 = 5;
    *(uint32_t*)0x20000318 = 0x3f;
    *(uint32_t*)0x2000031c = 0x800;
    *(uint32_t*)0x20000320 = 0x30;
    *(uint32_t*)0x20000324 = 0;
    *(uint32_t*)0x20000328 = 9;
    *(uint32_t*)0x2000032c = 0xc3;
    *(uint32_t*)0x20000330 = 0x4cec;
    *(uint32_t*)0x20000334 = 0;
    *(uint32_t*)0x20000338 = 5;
    *(uint32_t*)0x2000033c = 3;
    *(uint32_t*)0x20000340 = 0xfff;
    *(uint32_t*)0x20000344 = 6;
    *(uint32_t*)0x20000348 = -1;
    *(uint32_t*)0x2000034c = 5;
    *(uint32_t*)0x20000350 = 8;
    *(uint32_t*)0x20000354 = 9;
    *(uint32_t*)0x20000358 = 4;
    *(uint32_t*)0x2000035c = 0x7ff;
    *(uint32_t*)0x20000360 = 7;
    *(uint32_t*)0x20000364 = 1;
    *(uint32_t*)0x20000368 = 1;
    *(uint32_t*)0x2000036c = 9;
    *(uint32_t*)0x20000370 = 5;
    *(uint32_t*)0x20000374 = 0x1f80;
    *(uint32_t*)0x20000378 = 1;
    *(uint32_t*)0x2000037c = 3;
    *(uint32_t*)0x20000380 = 0xc000;
    *(uint32_t*)0x20000384 = 3;
    *(uint32_t*)0x20000388 = 0x10000;
    *(uint32_t*)0x2000038c = 0xd68;
    *(uint32_t*)0x20000390 = 5;
    *(uint32_t*)0x20000394 = 0x401;
    *(uint32_t*)0x20000398 = 4;
    *(uint32_t*)0x2000039c = 0x8c;
    *(uint32_t*)0x200003a0 = 0x1000;
    *(uint32_t*)0x200003a4 = 0x3f;
    *(uint32_t*)0x200003a8 = 5;
    *(uint32_t*)0x200003ac = 7;
    *(uint32_t*)0x200003b0 = 9;
    *(uint32_t*)0x200003b4 = 5;
    *(uint32_t*)0x200003b8 = 0x800;
    *(uint32_t*)0x200003bc = 0x7f;
    syscall(SYS_ioctl, r[1], 0xc1c06d00ul, 0x20000200ul);
    break;
  case 3:
    *(uint32_t*)0x20000480 = 0;
    *(uint32_t*)0x20000484 = 5;
    *(uint32_t*)0x20000488 = 0;
    *(uint64_t*)0x20000490 = 0;
    *(uint64_t*)0x20000498 = 5;
    *(uint32_t*)0x200004a0 = 4;
    *(uint32_t*)0x200004a4 = 0;
    *(uint64_t*)0x200004a8 = 0x3642;
    *(uint32_t*)0x200004b0 = 0x7fb05745;
    *(uint32_t*)0x200004b4 = 0xc945;
    *(uint64_t*)0x200004b8 = 0x20000040;
    memcpy((void*)0x20000040, "/dev/mdctl\000", 11);
    *(uint32_t*)0x200004c0 = 0x1ff;
    *(uint32_t*)0x200004c4 = 0xfffffffc;
    *(uint32_t*)0x200004c8 = 0xff;
    *(uint32_t*)0x200004cc = 0x6914;
    *(uint32_t*)0x200004d0 = 9;
    *(uint32_t*)0x200004d4 = 6;
    *(uint32_t*)0x200004d8 = 0;
    *(uint32_t*)0x200004dc = 0xfffffff7;
    *(uint32_t*)0x200004e0 = 0x1fc0;
    *(uint32_t*)0x200004e4 = 9;
    *(uint32_t*)0x200004e8 = 0xb5d;
    *(uint32_t*)0x200004ec = 7;
    *(uint32_t*)0x200004f0 = 0x20;
    *(uint32_t*)0x200004f4 = 0x80;
    *(uint32_t*)0x200004f8 = 0x20;
    *(uint32_t*)0x200004fc = 0x1000;
    *(uint32_t*)0x20000500 = 0x80;
    *(uint32_t*)0x20000504 = 0xfffffffc;
    *(uint32_t*)0x20000508 = 2;
    *(uint32_t*)0x2000050c = 0x7ff;
    *(uint32_t*)0x20000510 = 3;
    *(uint32_t*)0x20000514 = 6;
    *(uint32_t*)0x20000518 = 0x5d;
    *(uint32_t*)0x2000051c = 9;
    *(uint32_t*)0x20000520 = 0x8001;
    *(uint32_t*)0x20000524 = 6;
    *(uint32_t*)0x20000528 = 9;
    *(uint32_t*)0x2000052c = 0x10001;
    *(uint32_t*)0x20000530 = 9;
    *(uint32_t*)0x20000534 = 0xd411;
    *(uint32_t*)0x20000538 = 0x100;
    *(uint32_t*)0x2000053c = 0xa9;
    *(uint32_t*)0x20000540 = 9;
    *(uint32_t*)0x20000544 = 3;
    *(uint32_t*)0x20000548 = 3;
    *(uint32_t*)0x2000054c = 0xf8;
    *(uint32_t*)0x20000550 = 6;
    *(uint32_t*)0x20000554 = 4;
    *(uint32_t*)0x20000558 = 0;
    *(uint32_t*)0x2000055c = 7;
    *(uint32_t*)0x20000560 = 0x46;
    *(uint32_t*)0x20000564 = 9;
    *(uint32_t*)0x20000568 = 0x8000;
    *(uint32_t*)0x2000056c = 2;
    *(uint32_t*)0x20000570 = 0x10000;
    *(uint32_t*)0x20000574 = 0x80000000;
    *(uint32_t*)0x20000578 = 0xfffff000;
    *(uint32_t*)0x2000057c = 8;
    *(uint32_t*)0x20000580 = 8;
    *(uint32_t*)0x20000584 = 0;
    *(uint32_t*)0x20000588 = 0x7fff;
    *(uint32_t*)0x2000058c = 0;
    *(uint32_t*)0x20000590 = 0xffffff4b;
    *(uint32_t*)0x20000594 = 8;
    *(uint32_t*)0x20000598 = 0x3ff;
    *(uint32_t*)0x2000059c = 2;
    *(uint32_t*)0x200005a0 = 0xfffffff9;
    *(uint32_t*)0x200005a4 = 0xfc;
    *(uint32_t*)0x200005a8 = 0x101;
    *(uint32_t*)0x200005ac = 4;
    *(uint32_t*)0x200005b0 = 0xa8ee;
    *(uint32_t*)0x200005b4 = 0x100;
    *(uint32_t*)0x200005b8 = 5;
    *(uint32_t*)0x200005bc = 3;
    *(uint32_t*)0x200005c0 = 7;
    *(uint32_t*)0x200005c4 = 0xcf4;
    *(uint32_t*)0x200005c8 = 1;
    *(uint32_t*)0x200005cc = 0xfffffffb;
    *(uint32_t*)0x200005d0 = 0x80000001;
    *(uint32_t*)0x200005d4 = 0;
    *(uint32_t*)0x200005d8 = 0x1000;
    *(uint32_t*)0x200005dc = 1;
    *(uint32_t*)0x200005e0 = 0x8eda;
    *(uint32_t*)0x200005e4 = 3;
    *(uint32_t*)0x200005e8 = 0x1f;
    *(uint32_t*)0x200005ec = 0x800;
    *(uint32_t*)0x200005f0 = 8;
    *(uint32_t*)0x200005f4 = 0x3ff;
    *(uint32_t*)0x200005f8 = 9;
    *(uint32_t*)0x200005fc = 0x6c8;
    *(uint32_t*)0x20000600 = 0x80000001;
    *(uint32_t*)0x20000604 = 0x10000;
    *(uint32_t*)0x20000608 = 5;
    *(uint32_t*)0x2000060c = 3;
    *(uint32_t*)0x20000610 = 7;
    *(uint32_t*)0x20000614 = 2;
    *(uint32_t*)0x20000618 = 1;
    *(uint32_t*)0x2000061c = 2;
    *(uint32_t*)0x20000620 = 9;
    *(uint32_t*)0x20000624 = 4;
    *(uint32_t*)0x20000628 = 0x40;
    *(uint32_t*)0x2000062c = 3;
    *(uint32_t*)0x20000630 = 9;
    *(uint32_t*)0x20000634 = 7;
    *(uint32_t*)0x20000638 = 6;
    *(uint32_t*)0x2000063c = 0x80000000;
    syscall(SYS_ioctl, r[0], 0xc1c06d00ul, 0x20000480ul);
    break;
  }
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


