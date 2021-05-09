Syzkaller hit 'panic: ASan: Invalid access 8-byte read at ADDR, MallocRedZone' bug.

panic: ASan: Invalid access 8-byte read at 0xfffffe0003c4b878, MallocRedZone
cpuid = 1
time = 1608318967
KDB: stack backtrace:
db_trace_self_wrapper() at db_trace_self_wrapper+0x47/frame 0xfffffe008246d4a0
vpanic() at vpanic+0x263/frame 0xfffffe008246d500
panic() at panic+0x4f/frame 0xfffffe008246d560
__asan_load8_noabort() at __asan_load8_noabort+0x31e/frame 0xfffffe008246d620
sendfile_iodone() at sendfile_iodone+0x2a8/frame 0xfffffe008246d690
vn_sendfile() at vn_sendfile+0x2994/frame 0xfffffe008246d9d0
sendfile() at sendfile+0x245/frame 0xfffffe008246da90
amd64_syscall() at amd64_syscall+0x377/frame 0xfffffe008246dbf0
fast_syscall_common() at fast_syscall_common+0xf8/frame 0xfffffe008246dbf0
--- syscall (0, FreeBSD ELF64, nosys), rip = 0x41a2ba, rsp = 0x7fffffffe9f8, rbp = 0x7fffffffea20 ---
KDB: enter: panic
[ thread pid 727 tid 100100 ]
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
rsp         0xfffffe008246d480
rbp         0xfffffe008246d4a0
rsi                        0x1
rdi                          0
r8                           0
r9                  0xffffffff
r10         0xfffffe008246d347
r11         0xfffffe008275dc10
r12         0xfffffe008275d700
r13                          0
r14         0xffffffff828cd5c0  .str.18
r15         0xffffffff828cd5c0  .str.18
rip         0xffffffff81665abb  kdb_enter+0x6b
rflags                    0x82
kdb_enter+0x6b: movq    $0,0x25c787a(%rip)
db> show proc
Process 727 (syz-executor4472448) at 0xfffffe00827a7000:
 state: NORMAL
 uid: 0  gids: 0, 0, 5
 parent: pid 720 at 0xfffffe0082041a50
 ABI: FreeBSD ELF64
 arguments: /root/syz-executor447244820
 reaper: 0xfffffe0004302528 reapsubtree: 1
 sigparent: 20
 vmspace: 0xfffffe0082762000
   (map 0xfffffe0082762000)
   (map.pmap 0xfffffe00827620c0)
   (pmap 0xfffffe0082762120)
 threads: 1
100100                   Run     CPU 1                       syz-executor4472448
db> ps
  pid  ppid  pgrp   uid  state   wmesg   wchan               cmd
  727   720   718     0  R       CPU 1                       syz-executor4472448
  720   718   718     0  S       nanslp  0xffffffff83bfa240  syz-executor4472448
  718   716   718     0  Ss      pause   0xfffffe00675a75d8  csh
  716   640   716     0  Ss      select  0xfffffe004afb36c0  sshd
  693     1   693     0  Ss+     ttyin   0xfffffe004b1704b0  getty
  644     1   644     0  Ss      nanslp  0xffffffff83bfa241  cron
  640     1   640     0  Ss      select  0xfffffe0082328d40  sshd
  450     1   450     0  Ss      select  0xfffffe004afb3a40  syslogd
  379     1   379     0  Ss      select  0xfffffe004afd52c0  devd
  378     1   378    65  Ss      select  0xfffffe004afd5240  dhclient
  308     1   308     0  Ss      select  0xfffffe004afb3cc0  dhclient
  305     1   305     0  Ss      select  0xfffffe004afd5140  dhclient
   90     1    90     0  Ss      pause   0xfffffe0081f805d8  adjkerntz
   22     0     0     0  DL      syncer  0xffffffff83d1d4c0  [syncer]
   21     0     0     0  DL      vlruwt  0xfffffe006752ca50  [vnlru]
   18     0     0     0  DL      (threaded)                  [bufdaemon]
100056                   D       qsleep  0xffffffff83d1b420  [bufdaemon]
100057                   D       -       0xffffffff83011cc0  [bufspacedaemon-0]
100067                   D       sdflush 0xfffffe004b1554e8  [/ worker]
   17     0     0     0  DL      psleep  0xffffffff83d4eec0  [vmdaemon]
   16     0     0     0  DL      (threaded)                  [pagedaemon]
100054                   D       psleep  0xffffffff83d42a38  [dom0]
100058                   D       launds  0xffffffff83d42a44  [laundry: dom0]
100059                   D       umarcl  0xffffffff81bd8270  [uma]
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
100003                   Run     CPU 0                       [idle: cpu0]
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
100044                   D       -       0xffffffff828d43a0  [deadlkres]
100048                   D       -       0xfffffe004b028b00  [acpi_task_0]
100049                   D       -       0xfffffe004b028b00  [acpi_task_1]
100050                   D       -       0xfffffe004b028b00  [acpi_task_2]
100052                   D       -       0xfffffe004ae49d00  [CAM taskq]
100068                   D       -       0xfffffe004ae49b00  [linuxkpi_short_wq_0]
100069                   D       -       0xfffffe004ae49b00  [linuxkpi_short_wq_1]
100070                   D       -       0xfffffe004ae49b00  [linuxkpi_short_wq_2]
100071                   D       -       0xfffffe004ae49b00  [linuxkpi_short_wq_3]
100072                   D       -       0xfffffe004b028900  [linuxkpi_long_wq_0]
100073                   D       -       0xfffffe004b028900  [linuxkpi_long_wq_1]
100074                   D       -       0xfffffe004b028900  [linuxkpi_long_wq_2]
100075                   D       -       0xfffffe004b028900  [linuxkpi_long_wq_3]
db> show all locks
Process 727 (syz-executor4472448) thread 0xfffffe008275d700 (100100)
exclusive sx so_snd_sx (so_snd_sx) r = 0 (0xfffffe008278a630) locked @ /usr/home/markj/src/freebsd-dev/sys/kern/uipc_sockbuf.c:464
db> show page
vm_cnt.v_free_count: 143873
vm_cnt.v_inactive_count: 407
vm_cnt.v_active_count: 1926
vm_cnt.v_laundry_count: 0
vm_cnt.v_wire_count: 85138
vm_cnt.v_free_reserved: 369
vm_cnt.v_free_min: 1533
vm_cnt.v_free_target: 5025
vm_cnt.v_inactive_target: 7537
db> show malloc
              Type        InUse        MemUse     Requests
            linker          352         2523K          402
         sysctloid        26358         1545K        26393
              kobj          334         1336K          549
            devbuf         1362         1150K         1396
            newblk          135          546K          588
          vfscache            3          513K            3
           callout            2          512K            2
              intr            4          472K            4
          inodedep            5          258K          101
         ufs_quota            1          256K            1
          vfs_hash            1          256K            1
               pcb           15          201K           35
         vnet_data            1          168K            1
           subproc           86          156K          780
           tidhash            3          141K            3
              SWAP            1          132K            1
        tfo_ccache            1          128K            1
               sem            4          106K            4
            DEVFS1           79           79K           93
               bus          968           77K         2489
            bus-sc           29           75K         1005
              vmem            3           74K            6
          mtx_pool            2           72K            2
          syncache            1           68K            1
           pagedep            4           65K           90
          acpitask            1           64K            1
       ddb_capture            1           64K            1
            module          506           64K          506
         pfs_nodes          149           56K          149
            acpica          401           37K        57552
         hostcache            1           32K            1
               shm            1           32K            1
               msg            4           30K            4
           kdtrace          135           28K          829
              umtx          216           27K          216
        gtaskqueue           18           26K           18
            DEVFS3          101           26K          119
         ufs_mount            5           25K            6
            kbdmux            5           22K            5
        DEVFS_RULE           56           20K           56
               BPF           10           18K           10
           ithread           97           18K           97
              temp           17           17K         1472
              proc            3           17K            3
           devstat            8           17K            8
            KTRACE          100           13K          100
              GEOM           79           13K          702
            ifaddr           32           12K           32
              rman           96           12K          523
              kenv           61           11K           61
      eventhandler          114           10K          114
       pfs_vncache            6            9K            6
               rpc            2            8K            2
         bmsafemap            1            8K           65
             shmfd            1            8K            1
     audit_evclass          233            8K          291
       ufs_dirhash           36            8K           36
            sglist            3            6K            3
         taskqueue           45            5K           45
             ifnet            3            5K            3
              UART            6            5K            6
           io_apic            1            4K            1
              cred           16            4K          279
          filedesc            1            4K            1
             evdev            4            4K            4
               UMA          234            4K          234
             mount           76            4K          153
          routetbl           16            4K           16
             hhook           13            4K           13
           lltable           11            4K           11
           uidinfo            3            3K            9
            plimit            9            3K          210
            kqueue           34            3K          728
           pwddesc           34            3K          728
             linux           33            3K           33
       ether_multi           26            3K           36
        local_apic            1            2K            1
           CAM DEV            1            2K            2
         ipsec-saq            2            2K            2
               tty            2            2K            2
           acpisem           15            2K           15
         in6_multi           15            2K           15
             selfd           27            2K        10936
             lockf           16            2K           26
               msi           13            2K           13
            Unitno           27            2K           51
          pci_link           16            2K           16
           session           12            2K           22
              pgrp           12            2K           22
           acpidev           20            2K           20
         toponodes           10            2K           10
         proc-args           29            2K          434
           softdep            1            1K            1
       ipsecpolicy            1            1K            1
            sahead            1            1K            1
          secasvar            1            1K            1
             clone            8            1K            8
       vnodemarker            2            1K           22
      NFSD session            1            1K            1
            select            7            1K           23
             nhops            6            1K            6
            ip6ndp            4            1K            5
            isadev            5            1K            5
            crypto            3            1K            3
           CAM XPT           11            1K           12
         CAM queue            2            1K            5
          in_multi            2            1K            4
              pfil            4            1K            4
              cdev            2            1K            2
 encap_export_host            8            1K            8
        CAM periph            2            1K           14
            diradd            3            1K           51
    chacha20random            1            1K            1
            prison           12            1K           12
               osd            3            1K           10
               MCA            2            1K            2
          indirdep            1            1K            3
               mld            2            1K            2
              igmp            2            1K            2
            vnodes            1            1K            1
           CAM SIM            1            1K            1
      NFSD lckfile            1            1K            1
     NFSD V4client            1            1K            1
             DEVFS            9            1K           10
            feeder            7            1K            7
       inpcbpolicy            6            1K           78
        loginclass            3            1K            7
             linux            5            1K            6
            apmdev            1            1K            1
          atkbddev            2            1K            2
         vm_pgdata            1            1K            1
          freefile            1            1K           38
          procdesc            1            1K            2
          sendfile            2            1K           14
          pmchooks            1            1K            1
            DEVFSP            2            1K            2
            soname            4            1K         2670
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
           entropy            1            1K           34
    vnet_data_free            1            1K            1
           Per-cpu            1            1K            1
             cache            1            1K            1
       fdesc_mount            1            1K            1
          freework            1            1K           35
          p1003.1b            1            1K            1
          filecaps            1            1K           51
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
          savedino            0            0K            1
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
         newdirblk            0            0K           16
            dirrem            0            0K           40
             mkdir            0            0K           32
          freeblks            0            0K           34
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
            statfs            0            0K          209
     namei_tracker            0            0K           15
       export_host            0            0K            0
        cl_savebuf            0            0K            4
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
          mbuf_tag            0            0K           27
              accf            0            0K            0
               pts            0            0K            0
               iov            0            0K        11914
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
         sysctltmp            0            0K          521
            sysctl            0            0K            1
            MPRSAS            0            0K            0
              ekcd            0            0K            0
            dumper            0            0K            0
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
      mbuf_cluster   2048    2614       2        2614       0     254    5357568        0
              pbuf   2632       0     778           0       0       2    2047696        0
       malloc-4096   4096     336       2         586       0       2    1384448        0
        malloc-128    128    8649      31        8674       0     126    1111040        0
          BUF TRIE    144     188    6504         698       0      62     963648        0
       mbuf_packet    256    1024    1526       15300       0     254     652800        0
         FFS inode   1128     514      18         552       0       8     600096        0
        malloc-512    512    1042       6        1062       0      30     536576        0
      malloc-65536  65536       6       0           6       0       1     393216        0
        RADIX NODE    144    2162     297       17843       0      62     354096        0
      malloc-65536  65536       4       1          71       0       1     327680        0
         vmem btag     56    5392     127        5392       0     254     309064        0
       malloc-2048   2048     141       1         141       0       8     290816        0
             VNODE    488     546      46         586       0      30     288896        0
       UMA Slabs 0    112    2222       7        2222       0     126     249648        0
         VM OBJECT    264     825     120       11688       0      30     249480        0
       malloc-4096   4096      54       5         988       0       2     241664        0
        256 Bucket   2048     100      18        1990       0       8     241664        0
            DEVCTL   1024       0     196          96       0       0     200704        0
      malloc-65536  65536       1       2          38       0       1     196608        0
      malloc-65536  65536       3       0           3       0       1     196608        0
      malloc-32768  32768       6       0           6       0       1     196608        0
            THREAD   1792     100       8         100       0       8     193536        0
         malloc-16     16   11139     111       11176       0     254     180000        0
         malloc-64     64    2687      85        2691       0     254     177408        0
         UMA Zones    768     206       3         206       0      16     160512        0
        malloc-256    256     305     280         855       0      62     149760        0
       FFS2 dinode    256     514      26         552       0      62     138240        0
      malloc-16384  16384       8       0           8       0       1     131072        0
         malloc-32     32    3940      92        3962       0     254     129024        0
          ksiginfo    112      36    1008          54       0     126     116928        0
       S VFS Cache    104     996      96        1064       0     126     113568        0
              mbuf    256     323     112        7573       0     254     111360        0
       malloc-1024   1024      88      12         216       0      16     102400        0
         MAP ENTRY     96     621     345       36227       0     126      92736        0
        malloc-128    128     611      71        1151       0     126      87296        0
            clpbuf   2632       0      32          46       0      16      84224        0
        malloc-384    384     201       9         201       0      30      80640        0
        malloc-128    128     532      57        3121       0     126      75392        0
          UMA Kegs    384     192       1         192       0      30      74112        0
       malloc-8192   8192       9       0           9       0       1      73728        0
           VMSPACE   2544      14      13         709       0       4      68688        0
              PROC   1320      33      18         727       0       8      67320        0
      malloc-65536  65536       1       0           1       0       1      65536        0
      malloc-65536  65536       1       0           1       0       1      65536        0
      malloc-65536  65536       1       0           1       0       1      65536        0
         malloc-64     64     871      74        1813       0     254      60480        0
         filedesc0   1072      34      22         728       0       8      60032        0
           DIRHASH   1024      54       2          54       0      16      57344        0
        malloc-128    128     361      42       26743       0     126      51584        0
      malloc-16384  16384       1       2          71       0       1      49152        0
             g_bio    408       0     120        6595       0      30      48960        0
        128 Bucket   1024      35      12         457       0      16      48128        0
        malloc-384    384      83      27         179       0      30      42240        0
        malloc-256    256     128      22         574       0      62      38400        0
      malloc-32768  32768       1       0           1       0       1      32768        0
      malloc-32768  32768       0       1           1       0       1      32768        0
      malloc-32768  32768       0       1          56       0       1      32768        0
      malloc-32768  32768       1       0           1       0       1      32768        0
       malloc-8192   8192       4       0           4       0       1      32768        0
           pcpu-64     64     434      78         434       0     254      32768        0
            pcpu-8      8    3094     490        3098       0     254      28672        0
         64 Bucket    512      48       8         678       0      30      28672        0
        malloc-256    256      41      64         410       0      62      26880        0
            socket    944      16      12        1027       0     254      26432        0
   mbuf_jumbo_page   4096       0       6          10       0     254      24576        0
       malloc-8192   8192       3       0          44       0       1      24576        0
       malloc-8192   8192       3       0           3       0       1      24576        0
       malloc-4096   4096       6       0           6       0       2      24576        0
       malloc-1024   1024      21       3          28       0      16      24576        0
             tcpcb   1048       3      19           7       0     254      23056        0
        malloc-256    256      67      23         185       0      62      23040        0
         32 Bucket    256      50      40        4111       0      62      23040        0
              pipe    744       6      24         273       0      16      22320        0
        malloc-128    128      89      66         570       0     126      19840        0
       Mountpoints   2752       6       1           6       0       4      19264        0
         TURNSTILE    136     109      17         109       0      62      17136        0
             NAMEI   1024       0      16       11141       0      16      16384        0
      malloc-16384  16384       0       1           4       0       1      16384        0
      malloc-16384  16384       1       0           1       0       1      16384        0
      malloc-16384  16384       1       0           1       0       1      16384        0
       malloc-8192   8192       0       2          48       0       1      16384        0
       malloc-8192   8192       2       0           3       0       1      16384        0
       malloc-8192   8192       2       0           2       0       1      16384        0
       malloc-4096   4096       2       2          18       0       2      16384        0
       malloc-2048   2048       3       5         232       0       8      16384        0
       malloc-1024   1024       6      10         808       0      16      16384        0
         malloc-64     64     162      90       11789       0     254      16128        0
         malloc-64     64     196      56        1566       0     254      16128        0
             Files     80      62     138        6162       0     126      16000        0
        malloc-256    256      35      25         896       0      62      15360        0
         malloc-32     32     258     120         336       0     254      12096        0
         malloc-16     16     463     287        1212       0     254      12000        0
        malloc-128    128      41      52         127       0     126      11904        0
        SLEEPQUEUE     88     109      19         109       0     126      11264        0
       malloc-4096   4096       0       2         212       0       2       8192        0
       malloc-2048   2048       0       4          18       0       8       8192        0
       malloc-2048   2048       3       1           3       0       8       8192        0
       malloc-2048   2048       2       2           3       0       8       8192        0
       malloc-1024   1024       3       5          70       0      16       8192        0
       malloc-1024   1024       2       6          13       0      16       8192        0
        malloc-512    512       0      16         195       0      30       8192        0
        malloc-512    512      14       2          45       0      30       8192        0
        malloc-512    512       2      14           3       0      30       8192        0
        malloc-512    512       3      13           3       0      30       8192        0
           rtentry    176      13      33          17       0      62       8096        0
          rl_entry     40      31     171          31       0     254       8080        0
          syncache    168       0      48           5       0     254       8064        0
             udpcb     32       2     250          70       0     254       8064        0
               ipq     56       0     144          94       0     227       8064        0
               PWD     32      13     239         109       0     254       8064        0
         malloc-64     64      51      75       12465       0     254       8064        0
         malloc-64     64      68      58          98       0     254       8064        0
         malloc-64     64       7     119         227       0     254       8064        0
         malloc-32     32      13     239          49       0     254       8064        0
         malloc-32     32     100     152         656       0     254       8064        0
         malloc-32     32      89     163        4688       0     254       8064        0
         malloc-32     32      30     222         152       0     254       8064        0
         malloc-32     32       6     246          17       0     254       8064        0
         16 Bucket    144      29      27         192       0      62       8064        0
          4 Bucket     48       7     161          34       0     254       8064        0
          2 Bucket     32      47     205         501       0     254       8064        0
      vtnet_tx_hdr     24       1     333        6694       0     254       8016        0
            ttyinq    160      15      35          45       0      62       8000        0
         malloc-16     16      16     484          63       0     254       8000        0
         malloc-16     16      12     488          14       0     254       8000        0
         malloc-16     16      11     489          84       0     254       8000        0
         malloc-16     16      56     444       25481       0     254       8000        0
         malloc-16     16       1     499           6       0     254       8000        0
          8 Bucket     80      28      72         385       0     126       8000        0
        malloc-128    128       3      59          40       0     126       7936        0
        malloc-128    128      19      43          29       0     126       7936        0
         tcp_inpcb    488       3      13           7       0     254       7808        0
         udp_inpcb    488       2      14          70       0     254       7808        0
              kenv    258       2      28         646       0      30       7740        0
     routing nhops    256      10      20          17       0      62       7680        0
             unpcb    256       9      21         933       0     254       7680        0
           ttyoutq    256       8      22          24       0      62       7680        0
        malloc-384    384      12       8          28       0      30       7680        0
        malloc-384    384       0      20         168       0      30       7680        0
        malloc-256    256       6      24           7       0      62       7680        0
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
         malloc-32     32      16     110          68       0     254       4032        0
             ripcb    488       1       7           1       0     254       3904        0
       UMA Slabs 1    176       6      16           6       0      62       3872        0
        malloc-384    384       0      10           1       0      30       3840        0
        malloc-384    384       1       9           1       0      30       3840        0
        malloc-256    256       1      14          41       0      62       3840        0
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
# {Threaded:false Collide:false Repeat:true RepeatTimes:0 Procs:1 Sandbox: Fault:false FaultCall:-1 FaultNth:0 Leak:false NetInjection:false NetDevices:false NetReset:false Cgroups:false BinfmtMisc:false CloseFDs:false KCSAN:false DevlinkPCI:false USB:false VhciInjection:false Wifi:false Sysctl:false UseTmpDir:true HandleSegv:false Repro:false Trace:false}
r0 = openat(0xffffffffffffff9c, &(0x7f0000000000)='./file0\x00', 0x700e02, 0x0)
socketpair$unix(0x1, 0x1, 0x0, &(0x7f00000004c0)={<r1=>0xffffffffffffffff})
r2 = open(&(0x7f0000000000)='./file0\x00', 0x781, 0x0)
writev(r2, &(0x7f0000000640)=[{&(0x7f0000000200)="f4", 0x1}], 0x1)
r3 = dup(r1)
sendfile(r0, r3, 0x0, 0x0, 0x0, 0x0, 0x1c)


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
#include <sys/stat.h>
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
      if (current_time_ms() - start < 5 * 1000)
        continue;
      kill_and_wait(pid, &status);
      break;
    }
    remove_dir(cwdbuf);
  }
}

uint64_t r[4] = {0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff,
                 0xffffffffffffffff};

void execute_one(void)
{
  intptr_t res = 0;
  memcpy((void*)0x20000000, "./file0\000", 8);
  res = syscall(SYS_openat, 0xffffff9c, 0x20000000ul, 0x700e02ul, 0ul);
  if (res != -1)
    r[0] = res;
  res = syscall(SYS_socketpair, 1ul, 1ul, 0, 0x200004c0ul);
  if (res != -1)
    r[1] = *(uint32_t*)0x200004c0;
  memcpy((void*)0x20000000, "./file0\000", 8);
  res = syscall(SYS_open, 0x20000000ul, 0x781ul, 0ul);
  if (res != -1)
    r[2] = res;
  *(uint64_t*)0x20000640 = 0x20000200;
  memcpy((void*)0x20000200, "\xf4", 1);
  *(uint64_t*)0x20000648 = 1;
  syscall(SYS_writev, r[2], 0x20000640ul, 1ul);
  res = syscall(SYS_dup, r[1]);
  if (res != -1)
    r[3] = res;
  syscall(SYS_sendfile, r[0], r[3], 0ul, 0ul, 0ul, 0ul, 0x1cul);
}
int main(void)
{
  syscall(SYS_mmap, 0x20000000ul, 0x1000000ul, 7ul, 0x1012ul, -1, 0ul);
  use_temporary_dir();
  loop();
  return 0;
}


