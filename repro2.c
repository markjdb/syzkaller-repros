Syzkaller hit 'panic: ASan: Invalid access 4-byte read at ADDR, MallocRedZone' bug.

login: panic: ASan: Invalid access 4-byte read at 0xfffffe00043f6308, MallocRedZone
cpuid = 1
time = 1608312202
KDB: stack backtrace:
db_trace_self_wrapper() at db_trace_self_wrapper+0x47/frame 0xfffffe004adcf760
vpanic() at vpanic+0x263/frame 0xfffffe004adcf7c0
panic() at panic+0x4f/frame 0xfffffe004adcf820
__asan_load4_noabort() at __asan_load4_noabort+0x1db/frame 0xfffffe004adcf8e0
udp6_connect() at udp6_connect+0xde/frame 0xfffffe004adcf980
soconnectat() at soconnectat+0x213/frame 0xfffffe004adcf9e0
kern_connectat() at kern_connectat+0x28e/frame 0xfffffe004adcfa50
sys_connect() at sys_connect+0xfb/frame 0xfffffe004adcfa90
amd64_syscall() at amd64_syscall+0x377/frame 0xfffffe004adcfbf0
fast_syscall_common() at fast_syscall_common+0xf8/frame 0xfffffe004adcfbf0
--- syscall (0, FreeBSD ELF64, nosys), rip = 0x4009aa, rsp = 0x7fffffffea98, rbp = 0x7fffffffeab0 ---
KDB: enter: panic
[ thread pid 696 tid 100088 ]
Stopped at      kdb_enter+0x6b: movq    $0,0x25c787a(%rip)
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
rcx         0xfffff78000000000
rdx                        0x7
rbx                          0
rsp         0xfffffe004adcf740
rbp         0xfffffe004adcf760
rsi                        0x1
rdi                          0
r8                           0
r9                  0xffffffff
r10         0xfffffe004adcf607
r11         0xfffffe008e9c2810
r12         0xfffffe008e9c2300
r13                          0
r14         0xffffffff828cd5c0  .str.18
r15         0xffffffff828cd5c0  .str.18
rip         0xffffffff81665abb  kdb_enter+0x6b
rflags                    0x86
kdb_enter+0x6b: movq    $0,0x25c787a(%rip)
db> show proc
Process 696 (syz-executor8524540) at 0xfffffe008e9bf000:
 state: NORMAL
 uid: 0  gids: 0, 0, 5
 parent: pid 694 at 0xfffffe008eebea50
 ABI: FreeBSD ELF64
 arguments: /root/syz-executor852454035
 reaper: 0xfffffe0004302528 reapsubtree: 1
 sigparent: 20
 vmspace: 0xfffffe008e9b53e0
   (map 0xfffffe008e9b53e0)
   (map.pmap 0xfffffe008e9b54a0)
   (pmap 0xfffffe008e9b5500)
 threads: 1
100088                   Run     CPU 1                       syz-executor8524540
db> ps
  pid  ppid  pgrp   uid  state   wmesg   wchan               cmd
  696   694   694     0  R       CPU 1                       syz-executor8524540
  694   692   694     0  Ss      pause   0xfffffe008eebeb00  csh
  692   619   692     0  Rs      CPU 0                       sshd
  671     1   671     0  Ss+     ttyin   0xfffffe004b1704b0  getty
  669     1    21     0  S+      piperd  0xfffffe00695be2e8  logger
  668   667    21     0  S+      nanslp  0xffffffff83bfa241  sleep
  667     1    21     0  S+      wait    0xfffffe00695b5528  sh
  623     1   623     0  Ss      nanslp  0xffffffff83bfa241  cron
  619     1   619     0  Ss      select  0xfffffe004afd5140  sshd
  429     1   429     0  Ss      select  0xfffffe004afb36c0  syslogd
  358     1   358     0  Ss      select  0xfffffe004afd51c0  devd
  357     1   357    65  Ss      select  0xfffffe004afd5240  dhclient
  308     1   308     0  Ss      select  0xfffffe004afb37c0  dhclient
  305     1   305     0  Ss      select  0xfffffe004afd52c0  dhclient
   90     1    90     0  Ss      pause   0xfffffe00695b5b00  adjkerntz
   20     0     0     0  DL      syncer  0xffffffff83d1d4c0  [syncer]
   19     0     0     0  DL      vlruwt  0xfffffe004b49f528  [vnlru]
   18     0     0     0  DL      (threaded)                  [bufdaemon]
100056                   D       qsleep  0xffffffff83d1b420  [bufdaemon]
100061                   D       -       0xffffffff83011cc0  [bufspacedaemon-0]
100068                   D       sdflush 0xfffffe004b1498e8  [/ worker]
   17     0     0     0  DL      psleep  0xffffffff83d4eec0  [vmdaemon]
   16     0     0     0  DL      (threaded)                  [pagedaemon]
100054                   D       psleep  0xffffffff83d42a38  [dom0]
100059                   D       launds  0xffffffff83d42a44  [laundry: dom0]
100060                   D       umarcl  0xffffffff81bd8270  [uma]
   15     0     0     0  DL      -       0xffffffff839b1340  [rand_harvestq]
    9     0     0     0  DL      -       0xffffffff83d19540  [soaiod4]
    8     0     0     0  DL      -       0xffffffff83d19540  [soaiod3]
    7     0     0     0  DL      -       0xffffffff83d19540  [soaiod2]
    6     0     0     0  DL      -       0xffffffff83d19540  [soaiod1]
    5     0     0     0  DL      (threaded)                  [cam]
100032                   D       -       0xffffffff83837340  [doneq0]
100053                   D       -       0xffffffff838371c0  [scanner]
    4     0     0     0  DL      crypto_ 0xfffffe00043ac390  [crypto returns 1]
    3     0     0     0  DL      crypto_ 0xfffffe00043ac330  [crypto returns 0]
    2     0     0     0  DL      crypto_ 0xffffffff83d3cce0  [crypto]
   14     0     0     0  DL      seqstat 0xfffffe0003c57888  [sequencer 00]
   13     0     0     0  DL      (threaded)                  [geom]
100023                   D       -       0xffffffff83bcd800  [g_event]
100024                   D       -       0xffffffff83bcd840  [g_up]
100025                   D       -       0xffffffff83bcd880  [g_down]
   12     0     0     0  WL      (threaded)                  [intr]
100010                   I                                   [swi6: task queue]
100013                   I                                   [swi6: Giant taskq]
100015                   I                                   [swi5: fast taskq]
100018                   I                                   [swi4: clock (0)]
100019                   I                                   [swi4: clock (1)]
100020                   I                                   [swi3: vm]
100021                   I                                   [swi1: netisr 0]
100033                   I                                   [irq40: virtio_pci0]
100034                   I                                   [irq41: virtio_pci0]
100035                   I                                   [irq42: virtio_pci0]
100038                   I                                   [irq43: virtio_pci1]
100039                   I                                   [irq44: virtio_pci1]
100040                   I                                   [irq1: atkbd0]
100041                   I                                   [irq12: psm0]
100042                   I                                   [swi0: uart uart]
   11     0     0     0  RL      (threaded)                  [idle]
100003                   CanRun                              [idle: cpu0]
100004                   CanRun                              [idle: cpu1]
    1     0     1     0  SLs     wait    0xfffffe0004302528  [init]
   10     0     0     0  DL      audit_w 0xffffffff83d3dac0  [audit]
    0     0     0     0  DLs     (threaded)                  [kernel]
100000                   D       swapin  0xffffffff83bce700  [swapper]
100005                   D       -       0xfffffe00041e2d00  [if_config_tqg_0]
100006                   D       -       0xfffffe00041e2c00  [softirq_0]
100007                   D       -       0xfffffe00041e2b00  [softirq_1]
100008                   D       -       0xfffffe00041e2a00  [if_io_tqg_0]
100009                   D       -       0xfffffe00041e2900  [if_io_tqg_1]
100011                   D       -       0xfffffe00041e2700  [in6m_free taskq]
100012                   D       -       0xfffffe00041e2600  [aiod_kick taskq]
100014                   D       -       0xfffffe00041e2400  [thread taskq]
100016                   D       -       0xfffffe00041e2200  [inm_free taskq]
100017                   D       -       0xfffffe00041e2100  [kqueue_ctx taskq]
100022                   D       -       0xfffffe00041e2000  [firmware taskq]
100027                   D       -       0xfffffe004ae49e00  [crypto_0]
100028                   D       -       0xfffffe004ae49e00  [crypto_1]
100036                   D       -       0xfffffe004b028e00  [vtnet0 rxq 0]
100037                   D       -       0xfffffe004b028d00  [vtnet0 txq 0]
100047                   D       -       0xffffffff828d43a0  [deadlkres]
100048                   D       -       0xfffffe004b028b00  [acpi_task_0]
100049                   D       -       0xfffffe004b028b00  [acpi_task_1]
100050                   D       -       0xfffffe004b028b00  [acpi_task_2]
100052                   D       -       0xfffffe004ae49d00  [CAM taskq]
100070                   D       -       0xfffffe004ae49900  [linuxkpi_short_wq_0]
100071                   D       -       0xfffffe004ae49900  [linuxkpi_short_wq_1]
100072                   D       -       0xfffffe004ae49900  [linuxkpi_short_wq_2]
100073                   D       -       0xfffffe004ae49900  [linuxkpi_short_wq_3]
100074                   D       -       0xfffffe004b028a00  [linuxkpi_long_wq_0]
100075                   D       -       0xfffffe004b028a00  [linuxkpi_long_wq_1]
100076                   D       -       0xfffffe004b028a00  [linuxkpi_long_wq_2]
100077                   D       -       0xfffffe004b028a00  [linuxkpi_long_wq_3]
db> show all locks
Process 696 (syz-executor8524540) thread 0xfffffe008e9c2300 (100088)
exclusive rw udpinp (udpinp) r = 0 (0xfffffe008e686020) locked @ /usr/home/markj/src/freebsd-dev/sys/netinet6/udp6_usrreq.c:1190
db> show page
vm_cnt.v_free_count: 137621
vm_cnt.v_inactive_count: 343
vm_cnt.v_active_count: 2290
vm_cnt.v_laundry_count: 0
vm_cnt.v_wire_count: 91128
vm_cnt.v_free_reserved: 369
vm_cnt.v_free_min: 1533
vm_cnt.v_free_target: 5025
vm_cnt.v_inactive_target: 7537
db> show malloc
              Type        InUse        MemUse     Requests
            linker          352         2523K          402
         sysctloid        26358         1545K        26393
              kobj          334         1336K          549
            devbuf         1362         1150K         1393
            newblk          503          638K          551
          vfscache            3          513K            3
           callout            2          512K            2
              intr            4          472K            4
          inodedep            8          259K           77
         ufs_quota            1          256K            1
          vfs_hash            1          256K            1
               pcb           15          201K           30
         vnet_data            1          168K            1
           subproc           79          161K          740
           tidhash            3          141K            3
              SWAP            1          132K            1
        tfo_ccache            1          128K            1
               sem            4          106K            4
            DEVFS1           79           79K           93
               bus          968           77K         2489
            bus-sc           29           75K         1005
          mtx_pool            2           72K            2
          syncache            1           68K            1
           pagedep            7           66K           57
          acpitask            1           64K            1
       ddb_capture            1           64K            1
            module          506           64K          506
         pfs_nodes          149           56K          149
              vmem            3           50K            4
            acpica          401           37K        57552
         hostcache            1           32K            1
               shm            1           32K            1
               msg            4           30K            4
        gtaskqueue           18           26K           18
            DEVFS3          101           26K          119
           kdtrace          127           25K          788
              umtx          198           25K          198
         ufs_mount            5           25K            6
            kbdmux            5           22K            5
        DEVFS_RULE           56           20K           56
               BPF           10           18K           10
           ithread           97           18K           97
              temp           17           17K         1390
              proc            3           17K            3
           devstat            8           17K            8
            KTRACE          100           13K          100
              GEOM           79           13K          702
            ifaddr           31           12K           31
              rman           96           12K          523
              kenv           61           11K           61
      eventhandler          114           10K          114
         bmsafemap            2            9K           42
       pfs_vncache            6            9K            6
               rpc            2            8K            2
             shmfd            1            8K            1
     audit_evclass          233            8K          291
       ufs_dirhash           36            8K           36
            sglist            3            6K            3
         taskqueue           45            5K           45
              cred           17            5K          269
             ifnet            3            5K            3
              UART            6            5K            6
           io_apic            1            4K            1
          filedesc            1            4K            1
             evdev            4            4K            4
               UMA          234            4K          234
             mount           76            4K          153
          routetbl           16            4K           16
             hhook           13            4K           13
           lltable           11            4K           11
           uidinfo            3            3K            8
            plimit            9            3K          194
            kqueue           36            3K          697
           pwddesc           36            3K          697
             linux           33            3K           33
       ether_multi           26            3K           31
        local_apic            1            2K            1
           CAM DEV            1            2K            2
         ipsec-saq            2            2K            2
               tty            2            2K            2
           acpisem           15            2K           15
         in6_multi           15            2K           15
               msi           13            2K           13
            Unitno           27            2K           51
           session           13            2K           21
              pgrp           13            2K           21
             lockf           15            2K           22
          pci_link           16            2K           16
             selfd           20            2K         9524
           acpidev           20            2K           20
         toponodes           10            2K           10
         proc-args           32            2K          407
           softdep            1            1K            1
       ipsecpolicy            1            1K            1
            sahead            1            1K            1
          secasvar            1            1K            1
             clone            8            1K            8
       vnodemarker            2            1K           10
      NFSD session            1            1K            1
            select            7            1K           23
          indirdep            3            1K            3
             nhops            6            1K            6
            ip6ndp            4            1K            5
            isadev            5            1K            5
            crypto            3            1K            3
           CAM XPT           11            1K           12
         CAM queue            2            1K            5
            diradd            4            1K           34
          in_multi            2            1K            3
              pfil            4            1K            4
              cdev            2            1K            2
 encap_export_host            8            1K            8
        CAM periph            2            1K           14
    chacha20random            1            1K            1
            prison           12            1K           12
               osd            3            1K           10
               MCA            2            1K            2
            dirrem            1            1K           26
               mld            2            1K            2
              igmp            2            1K            2
            vnodes            1            1K            1
           CAM SIM            1            1K            1
      NFSD lckfile            1            1K            1
     NFSD V4client            1            1K            1
             DEVFS            9            1K           10
            feeder            7            1K            7
       inpcbpolicy            7            1K           70
        loginclass            3            1K            7
             linux            5            1K            6
            apmdev            1            1K            1
          atkbddev            2            1K            2
         vm_pgdata            1            1K            1
            soname            5            1K         2681
          procdesc            1            1K            2
          pmchooks            1            1K            1
            DEVFSP            2            1K            2
          filecaps            4            1K           51
               tun            3            1K            3
        debugfsint            2            1K            2
     CAM dev queue            1            1K            1
          nexusdev            4            1K            4
           tcpfunc            1            1K            1
              vnet            1            1K            1
               pmc            1            1K            1
          acpiintr            1            1K            1
              cpus            2            1K            2
          CAM path            1            1K           12
           entropy            1            1K           33
    vnet_data_free            1            1K            1
           Per-cpu            1            1K            1
             cache            1            1K            1
       fdesc_mount            1            1K            1
          freework            1            1K           21
          p1003.1b            1            1K            1
          seq_file            0            0K            0
             radix            0            0K            0
               idr            0            0K            0
      linuxcurrent            0            0K            0
         BACKLIGHT            0            0K            0
          futex wp            0            0K            0
             futex            0            0K            0
            lepoll            0            0K            0
          SCSI ENC            0            0K            0
           SCSI sa            0            0K            0
         scsi_pass            0            0K            0
        madt_table            0            0K            2
          smartpqi            0            0K            0
         ciss_data            0            0K            0
            pvscsi            0            0K            0
           ath_hal            0            0K            0
            athdev            0            0K            0
           ata_pci            0            0K            0
           ata_dma            0            0K            0
       ata_generic            0            0K            0
               amr            0            0K            0
              iavf            0            0K            0
               ixl            0            0K            0
           scsi_da            0            0K            0
            ata_da            0            0K            0
           scsi_ch            0            0K            0
           scsi_cd            0            0K            0
            USBdev            0            0K            0
               USB            0            0K            0
        ice-resmgr            0            0K            0
         ice-osdep            0            0K            0
               ice            0            0K            0
             axgbe            0            0K            0
           memdesc            0            0K            0
       fpukern_ctx            0            0K            0
       AHCI driver            0            0K            0
          xen_intr            0            0K            0
               agp            0            0K            0
           xen_hvm            0            0K            0
         legacydrv            0            0K            0
            qpidrv            0            0K            0
           nvme_da            0            0K            0
      dmar_idpgtbl            0            0K            0
          dmar_dom            0            0K            0
          dmar_ctx            0            0K            0
 CAM I/O Scheduler            0            0K            0
           acpipwr            0            0K            0
            twsbuf            0            0K            0
              isci            0            0K            0
      iommu_dmamap            0            0K            0
      twe_commands            0            0K            0
     hyperv_socket            0            0K            0
           bxe_ilt            0            0K            0
            xenbus            0            0K            0
      twa_commands            0            0K            0
       tcp_log_dev            0            0K            0
      midi buffers            0            0K            0
     vm_fictitious            0            0K            0
             mixer            0            0K            0
              ac97            0            0K            0
             hdacc            0            0K            0
              hdac            0            0K            0
              hdaa            0            0K            0
         acpi_perf            0            0K            0
         acpicmbat            0            0K            0
       SIIS driver            0            0K            0
           UMAHash            0            0K            0
           CAM CCB            0            0K            0
           jblocks            0            0K            0
          savedino            0            0K            2
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
         newdirblk            0            0K            7
             mkdir            0            0K           14
          freefile            0            0K           23
          freeblks            0            0K           20
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
               LRO            0            0K            0
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
            statfs            0            0K          203
     namei_tracker            0            0K            1
       export_host            0            0K            0
        cl_savebuf            0            0K            3
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
            biobuf            0            0K            0
              aios            0            0K            0
               lio            0            0K            0
               acl            0            0K            0
        MVS driver            0            0K            0
          mbuf_tag            0            0K           16
              accf            0            0K            0
               pts            0            0K            0
               iov            0            0K        11742
          ioctlops            0            0K           76
           Witness            0            0K            0
          terminal            0            0K            0
             stack            0            0K            0
     CAM ccb queue            0            0K            0
          mrsasbuf            0            0K            0
          mpt_user            0            0K            0
              sbuf            0            0K          486
          mps_user            0            0K            0
          firmware            0            0K            0
        compressor            0            0K            0
            MPSSAS            0            0K            0
               mps            0            0K            0
          mpr_user            0            0K            0
         sysctltmp            0            0K          522
            sysctl            0            0K            1
            MPRSAS            0            0K            0
              ekcd            0            0K            0
            dumper            0            0K            0
          sendfile            0            0K            0
              rctl            0            0K            0
               mpr            0            0K            0
            mfibuf            0            0K            0
        md_sectors            0            0K            0
           md_disk            0            0K            0
           malodev            0            0K            0
               LED            0            0K            0
          kcovinfo            0            0K            0
      prison_racct            0            0K            0
       Fail Points            0            0K            0
             sigio            0            0K            1
filedesc_to_leader            0            0K            0
               pwd            0            0K            0
       tty console            0            0K            0
          ix_sriov            0            0K            0
        aacraidcam            0            0K            0
                ix            0            0K            0
            ipsbuf            0            0K            0
            iirbuf            0            0K            0
       aacraid_buf            0            0K            0
            aaccam            0            0K            0
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
         raid_data            0            0K          108
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
NFSCL diroffdiroff            0            0K            0
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
       NFSD V4lock            0            0K            0
      NFSD V4state            0            0K            0
     NFSD srvcache            0            0K            0
       msdosfs_fat            0            0K            0
     msdosfs_mount            0            0K            0
      msdosfs_node            0            0K            0
            DEVFS4            0            0K            0
            DEVFS2            0            0K            0
            gntdev            0            0K            0
       privcmd_dev            0            0K            0
        evtchn_dev            0            0K            0
          xenstore            0            0K            0
            aacbuf            0            0K            0
               xnb            0            0K            0
              xbbd            0            0K            0
               xbd            0            0K            0
           Balloon            0            0K            0
          sysmouse            0            0K            0
            vtfont            0            0K            0
                vt            0            0K            0
             vtbuf            0            0K            0
              zstd            0            0K            0
            nvlist            0            0K            0
db> show uma
              Zone   Size    Used    Free    Requests  Sleeps  Bucket  Total Mem    XFree
      mbuf_cluster   2048    2119       1        2119       0     254    4341760        0
              pbuf   2632       0     973           0       0       2    2560936        0
       malloc-4096   4096     336       2         586       0       2    1384448        0
        malloc-128    128    8649      31        8673       0     126    1111040        0
          BUF TRIE    144     196    6496         553       0      62     963648        0
         FFS inode   1128     507      11         530       0       8     584304        0
        malloc-512    512    1042       6        1050       0      30     536576        0
       mbuf_packet    256    1024    1031       13776       0     254     526080        0
      malloc-65536  65536       6       0           6       0       1     393216        0
        RADIX NODE    144    2168     235       17148       0      62     346032        0
      malloc-65536  65536       4       1          71       0       1     327680        0
         vmem btag     56    5312      63        5312       0     254     301000        0
       malloc-2048   2048     141       1         141       0       8     290816        0
             VNODE    488     539      29         564       0      30     277184        0
       malloc-4096   4096      56       3         957       0       2     241664        0
         VM OBJECT    264     851      64       11315       0      30     241560        0
        256 Bucket   2048      95      17        1690       0       8     229376        0
       UMA Slabs 0    112    1967      10        1967       0     126     221424        0
            DEVCTL   1024       0     196          96       0       0     200704        0
      malloc-65536  65536       1       2          35       0       1     196608        0
      malloc-65536  65536       3       0           3       0       1     196608        0
      malloc-32768  32768       6       0           6       0       1     196608        0
         malloc-16     16   11139     111       11176       0     254     180000        0
            THREAD   1792      90       9          90       0       8     177408        0
         malloc-64     64    2687      22        2691       0     254     173376        0
        malloc-256    256     663      12         809       0      62     172800        0
         UMA Zones    768     206       3         206       0      16     160512        0
       FFS2 dinode    256     507      18         530       0      62     134400        0
      malloc-16384  16384       8       0           8       0       1     131072        0
         malloc-32     32    3940      92        3962       0     254     129024        0
          ksiginfo    112      26    1018          39       0     126     116928        0
              mbuf    256     322     128        7220       0     254     115200        0
       S VFS Cache    104     983      70        1037       0     126     109512        0
       malloc-1024   1024      88       8         216       0      16      98304        0
         MAP ENTRY     96     686     322       34762       0     126      96768        0
            clpbuf   2632       0      32          42       0      16      84224        0
        malloc-128    128     612      39        1088       0     126      83328        0
        malloc-384    384     201       9         201       0      30      80640        0
          UMA Kegs    384     192       1         192       0      30      74112        0
       malloc-8192   8192       9       0           9       0       1      73728        0
        malloc-128    128     515      43        3104       0     126      71424        0
      malloc-65536  65536       1       0           1       0       1      65536        0
      malloc-65536  65536       1       0           1       0       1      65536        0
           VMSPACE   2544      16       8         678       0       4      61056        0
         malloc-64     64     873      72        1782       0     254      60480        0
           DIRHASH   1024      54       2          54       0      16      57344        0
              PROC   1320      35       7         696       0       8      55440        0
         filedesc0   1072      36      13         697       0       8      52528        0
        128 Bucket   1024      35      12         472       0      16      48128        0
        malloc-128    128     360      12       26740       0     126      47616        0
        malloc-384    384      77      43         146       0      30      46080        0
        malloc-256    256     129      36         564       0      62      42240        0
         32 Bucket    256      47     118       10545       0      62      42240        0
             NAMEI   1024       0      32       10724       0      16      32768        0
      malloc-32768  32768       1       0           1       0       1      32768        0
      malloc-32768  32768       1       0           1       0       1      32768        0
      malloc-32768  32768       0       1          56       0       1      32768        0
      malloc-32768  32768       1       0           1       0       1      32768        0
      malloc-16384  16384       2       0           2       0       1      32768        0
      malloc-16384  16384       1       1          71       0       1      32768        0
       malloc-8192   8192       4       0           4       0       1      32768        0
           pcpu-64     64     434      78         434       0     254      32768        0
             g_bio    408       0      80        5939       0      30      32640        0
        malloc-256    256      69      51         147       0      62      30720        0
       malloc-1024   1024      21       7          28       0      16      28672        0
            pcpu-8      8    3090     494        3093       0     254      28672        0
       malloc-8192   8192       3       0          44       0       1      24576        0
       malloc-8192   8192       3       0           3       0       1      24576        0
       malloc-4096   4096       6       0           6       0       2      24576        0
         64 Bucket    512      42       6         537       0      30      24576        0
             tcpcb   1048       3      19           7       0     254      23056        0
        malloc-256    256      41      49         387       0      62      23040        0
        malloc-256    256      38      52         848       0      62      23040        0
            socket    944      15       9        1000       0     254      22656        0
         malloc-64     64     196     119        1565       0     254      20160        0
        malloc-128    128      89      66         569       0     126      19840        0
       Mountpoints   2752       6       1           6       0       4      19264        0
         TURNSTILE    136     100      26         100       0      62      17136        0
   mbuf_jumbo_page   4096       0       4          10       0     254      16384        0
      malloc-16384  16384       0       1           4       0       1      16384        0
      malloc-16384  16384       1       0           1       0       1      16384        0
       malloc-8192   8192       0       2          48       0       1      16384        0
       malloc-8192   8192       1       1           2       0       1      16384        0
       malloc-8192   8192       2       0           2       0       1      16384        0
       malloc-2048   2048       3       5         232       0       8      16384        0
       malloc-1024   1024       6      10         751       0      16      16384        0
         malloc-64     64     157      95       10344       0     254      16128        0
              pipe    744       7      13         264       0      16      14880        0
       malloc-4096   4096       2       1          18       0       2      12288        0
        malloc-512    512      14      10          45       0      30      12288        0
         malloc-64     64      53     136       12269       0     254      12096        0
         malloc-32     32     258     120         336       0     254      12096        0
         malloc-16     16     464     286        1212       0     254      12000        0
        malloc-128    128      41      52         128       0     126      11904        0
        SLEEPQUEUE     88     100      28         100       0     126      11264        0
       malloc-4096   4096       0       2         206       0       2       8192        0
       malloc-2048   2048       0       4          18       0       8       8192        0
       malloc-2048   2048       3       1           3       0       8       8192        0
       malloc-2048   2048       2       2           3       0       8       8192        0
       malloc-1024   1024       3       5          70       0      16       8192        0
       malloc-1024   1024       2       6          13       0      16       8192        0
        malloc-512    512       0      16         195       0      30       8192        0
        malloc-512    512       2      14           3       0      30       8192        0
        malloc-512    512       3      13           3       0      30       8192        0
           rtentry    176      13      33          16       0      62       8096        0
          rl_entry     40      21     181          21       0     254       8080        0
             udpcb     32       3     249          62       0     254       8064        0
               ipq     56       0     144          10       0     227       8064        0
               PWD     32      11     241          94       0     254       8064        0
         malloc-64     64      66      60          83       0     254       8064        0
         malloc-64     64       8     118         210       0     254       8064        0
         malloc-32     32      13     239          49       0     254       8064        0
         malloc-32     32     100     152         639       0     254       8064        0
         malloc-32     32      93     159        4675       0     254       8064        0
         malloc-32     32      32     220         146       0     254       8064        0
         malloc-32     32       6     246          17       0     254       8064        0
         16 Bucket    144      29      27         190       0      62       8064        0
          4 Bucket     48       7     161          47       0     254       8064        0
          2 Bucket     32      45     207         490       0     254       8064        0
      vtnet_tx_hdr     24       1     333        6356       0     254       8016        0
             Files     80      63      37        5904       0     126       8000        0
         malloc-16     16      16     484          63       0     254       8000        0
         malloc-16     16      12     488          14       0     254       8000        0
         malloc-16     16      11     489          83       0     254       8000        0
         malloc-16     16      56     444       25481       0     254       8000        0
         malloc-16     16       1     499           4       0     254       8000        0
          8 Bucket     80      27      73         393       0     126       8000        0
        malloc-128    128       2      60          25       0     126       7936        0
        malloc-128    128      20      42          28       0     126       7936        0
         tcp_inpcb    488       3      13           7       0     254       7808        0
         udp_inpcb    488       3      13          62       0     254       7808        0
              kenv    258       2      28         646       0      30       7740        0
     routing nhops    256      10      20          16       0      62       7680        0
             unpcb    256       7      23         919       0     254       7680        0
        malloc-384    384      11       9          27       0      30       7680        0
        malloc-384    384       0      20         168       0      30       7680        0
        malloc-256    256       6      24           6       0      62       7680        0
     FPU_save_area    832       1       8           1       0      16       7488        0
            cpuset    104       7      55           7       0     126       6448        0
 epoch_record pcpu    256       4      12           4       0      62       4096        0
       malloc-4096   4096       1       0           1       0       2       4096        0
       malloc-2048   2048       1       1           2       0       8       4096        0
       malloc-1024   1024       0       4           1       0      16       4096        0
       malloc-1024   1024       3       1           3       0      16       4096        0
        malloc-512    512       1       7           1       0      30       4096        0
           pcpu-16     16       7     249           7       0     254       4096        0
            fakepg    104       1      38           1       0     126       4056        0
         hostcache     96       1      41           1       0     254       4032        0
          syncache    168       0      24           5       0     254       4032        0
         malloc-32     32      16     110          57       0     254       4032        0
            ttyinq    160      15      10          45       0      62       4000        0
             ripcb    488       1       7           1       0     254       3904        0
       UMA Slabs 1    176       6      16           6       0      62       3872        0
           ttyoutq    256       8       7          24       0      62       3840        0
        malloc-384    384       0      10           1       0      30       3840        0
        malloc-384    384       1       9           1       0      30       3840        0
        malloc-256    256       3      12          26       0      62       3840        0
        malloc-256    256       2      13           2       0      62       3840        0
        KMAP ENTRY     96      33       6          49       0       0       3744        0
              vmem   1856       1       1           1       0       8       3712        0
           SMR CPU     32       2      61           2       0     254       2016        0
        SMR SHARED     24       2      61           2       0     254       1512        0
  linux_dma_object     24       0       0           0       0     254          0        0
  linux_dma_pctrie    144       0       0           0       0      62          0        0
             swblk    136       0       0           0       0      62          0        0
          swpctrie    144       0       0           0       0      62          0        0
       FFS1 dinode    128       0       0           0       0     126          0        0
    IPsec SA lft_c     16       0       0           0       0     254          0        0
     udplite_inpcb    488       0       0           0       0     254          0        0
      tcp_log_node    120       0       0           0       0     126          0        0
    tcp_log_bucket    176       0       0           0       0      62          0        0
           tcp_log    416       0       0           0       0     254          0        0
          tcpreass     48       0       0           0       0     254          0        0
tfo_ccache_entries     80       0       0           0       0     126          0        0
               tfo      4       0       0           0       0     254          0        0
          sackhole     32       0       0           0       0     254          0        0
             tcptw     88       0       0           0       0     254          0        0
             KNOTE    160       0       0           0       0      62          0        0
            itimer    352       0       0           0       0      30          0        0
            AIOLIO    272       0       0           0       0      30          0        0
             AIOCB    488       0       0           0       0      30          0        0
              AIOP     32       0       0           0       0     254          0        0
               AIO    208       0       0           0       0      62          0        0
        TMPFS node    224       0       0           0       0      62          0        0
           NCLNODE    592       0       0           0       0      16          0        0
     LTS VFS Cache    360       0       0           0       0      30          0        0
       L VFS Cache    320       0       0           0       0      30          0        0
     STS VFS Cache    144       0       0           0       0      62          0        0
    crypto_session     72       0       0           0       0     126          0        0
           cryptop    280       0       0           0       0      30          0        0
   IOMMU_MAP_ENTRY    120       0       0           0       0     126          0        0
    mbuf_jumbo_16k  16384       0       0           0       0     254          0        0
     mbuf_jumbo_9k   9216       0       0           0       0     254          0        0
      audit_record   1280       0       0           0       0       8          0        0
         domainset     40       0       0           0       0     254          0        0
        MAC labels     40       0       0           0       0     254          0        0
            vnpbuf   2632       0       0           0       0      64          0        0
            mdpbuf   2632       0       0           0       0       3          0        0
           nfspbuf   2632       0       0           0       0      16          0        0
            swwbuf   2632       0       0           0       0       8          0        0
            swrbuf   2632       0       0           0       0      16          0        0
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
       malloc-4096   4096       0       0           0       0       2          0        0
       malloc-4096   4096       0       0           0       0       2          0        0
       malloc-2048   2048       0       0           0       0       8          0        0
       malloc-2048   2048       0       0           0       0       8          0        0
       malloc-1024   1024       0       0           0       0      16          0        0
        malloc-512    512       0       0           0       0      30          0        0
        malloc-512    512       0       0           0       0      30          0        0
        malloc-384    384       0       0           0       0      30          0        0
        malloc-384    384       0       0           0       0      30          0        0
         malloc-64     64       0       0           0       0     254          0        0
         malloc-16     16       0       0           0       0     254          0        0
           pcpu-32     32       0       0           0       0     254          0        0
            pcpu-4      4       0       0           0       0     254          0        0
          UMA Hash    256       0       0           0       0      62          0        0


Syzkaller reproducer:
# {Threaded:false Collide:false Repeat:false RepeatTimes:0 Procs:1 Sandbox: Fault:false FaultCall:-1 FaultNth:0 Leak:false NetInjection:false NetDevices:false NetReset:false Cgroups:false BinfmtMisc:false CloseFDs:false KCSAN:false DevlinkPCI:false USB:false VhciInjection:false Wifi:false Sysctl:false UseTmpDir:false HandleSegv:false Repro:false Trace:false}
r0 = socket$inet6_udp(0x1c, 0x2, 0x0)
connect$inet6(r0, &(0x7f0000001240)={0x1c, 0x1c, 0x0, 0x2, @mcast1, 0x2}, 0x3)


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
  res = syscall(SYS_socket, 0x1cul, 2ul, 0);
  if (res != -1)
    r[0] = res;
  *(uint8_t*)0x20001240 = 0x1c;
  *(uint8_t*)0x20001241 = 0x1c;
  *(uint16_t*)0x20001242 = htobe16(0x4e20);
  *(uint32_t*)0x20001244 = 2;
  *(uint8_t*)0x20001248 = -1;
  *(uint8_t*)0x20001249 = 1;
  *(uint8_t*)0x2000124a = 0;
  *(uint8_t*)0x2000124b = 0;
  *(uint8_t*)0x2000124c = 0;
  *(uint8_t*)0x2000124d = 0;
  *(uint8_t*)0x2000124e = 0;
  *(uint8_t*)0x2000124f = 0;
  *(uint8_t*)0x20001250 = 0;
  *(uint8_t*)0x20001251 = 0;
  *(uint8_t*)0x20001252 = 0;
  *(uint8_t*)0x20001253 = 0;
  *(uint8_t*)0x20001254 = 0;
  *(uint8_t*)0x20001255 = 0;
  *(uint8_t*)0x20001256 = 0;
  *(uint8_t*)0x20001257 = 1;
  *(uint32_t*)0x20001258 = 2;
  syscall(SYS_connect, r[0], 0x20001240ul, 3ul);
  return 0;
}


