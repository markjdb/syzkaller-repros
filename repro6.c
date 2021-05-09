Syzkaller hit 'panic: kmsan_intr_enter: mtd->ctx = 6' bug.

login: panic: kmsan_intr_enter: mtd->ctx = 6
cpuid = 0
time = 1620540753
KDB: stack backtrace:
db_trace_self_wrapper() at db_trace_self_wrapper+0xde/frame 0xfffffe00847c9fd0
vpanic() at vpanic+0x656/frame 0xfffffe00847ca090
panic() at panic+0x1ad/frame 0xfffffe00847ca190
kmsan_intr_enter() at kmsan_intr_enter+0x6a/frame 0xfffffe00847ca1a0
calltrap() at calltrap+0x5/frame 0xfffffe00847ca1a0
--- trap 0xc, rip = 0xffffffff85cb4fc6, rsp = 0xfffffe00847ca270, rbp = 0xfffffe00847ca270 ---
copyout_nosmap_erms() at copyout_nosmap_erms+0x156/frame 0xfffffe00847ca270
sendsig() at sendsig+0xf6e/frame 0xfffffe00847ca8d0
trapsignal() at trapsignal+0xee4/frame 0xfffffe00847ca9e0
trap() at trap+0x252e/frame 0xfffffe00847cabf0
calltrap() at calltrap+0xd/frame 0xfffffe00847cabf0
--- trap 0xc, rip = 0x401060, rsp = 0x7fffffffea38, rbp = 0x7fffffffea40 ---
KDB: enter: panic
[ thread pid 722 tid 100079 ]
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
ss                           0
rax         0xffffffff86333744
rcx                          0
rdx         0xffffffff8702b000  msan_dummy_orig
rbx                          0
rsp         0xfffffe00847c9f70
rbp         0xfffffe00847c9fd0
rsi                        0x1
rdi         0xffffffff87022290  kdb_why
r8                         0x3
r9                           0
r10                          0
r11                          0
r12                          0
r13                        0x1
r14         0xffffffff87028e28  dummy_tls
r15         0xffffffff86333744
rip         0xffffffff83fc8007  kdb_enter+0x1c7
rflags                    0x46
kdb_enter+0x1c7:        movq    $0x87022290,%rdi
db> show proc
Process 722 (syz-executor7439197) at 0xfffffe00c9cac000:
 state: NORMAL
 uid: 0  gids: 0, 0, 5
 parent: pid 718 at 0xfffffe00c9cf0538
 ABI: FreeBSD ELF64
 flag: 0x10000000  flag2: 0
 arguments: /root/syz-executor743919733
 reaper: 0xfffffe0070a77538 reapsubtree: 1
 sigparent: 20
 vmspace: 0xfffffe00c9ccd9f0
   (map 0xfffffe00c9ccd9f0)
   (map.pmap 0xfffffe00c9ccdab0)
   (pmap 0xfffffe00c9ccdb10)
 threads: 1
100079                   Run     CPU 0                       syz-executor7439197
db> ps
  pid  ppid  pgrp   uid  state   wmesg   wchan               cmd
  722   718   716     0  R       CPU 0                       syz-executor7439197
  718   716   716     0  S       nanslp  0xffffffff86ff59e0  syz-executor7439197
  716   714   716     0  Ss      pause   0xfffffe00c9d1f5e8  csh
  714   641   714     0  Rs                                  sshd
  693     1   693     0  Ss+     ttyin   0xfffffe0070eaf8b0  getty
  692   689    21     0  S+      nanslp  0xffffffff86ff59e0  sleep
  690     1    21     0  S+      piperd  0xfffffe00aed0c2e8  logger
  689     1    21     0  S+      wait    0xfffffe00c9d1fa70  sh
  645     1   645     0  Ss      nanslp  0xffffffff86ff59e0  cron
  641     1   641     0  Ss      select  0xfffffe00c9daaec0  sshd
  449     1   449     0  Ss      select  0xfffffe00aec8fe40  syslogd
  378     1   378     0  Ss      select  0xfffffe00aec8f740  devd
  377     1   377    65  Ss      select  0xfffffe0078e3d240  dhclient
  307     1   307     0  Ss      select  0xfffffe00aec8fb40  dhclient
  304     1   304     0  Ss      select  0xfffffe00aecd2040  dhclient
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
   12     0     0     0  WL      (threaded)                  [intr]
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
100045                   I                                   [irq44: virtio_pci1]
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
db> show malloc
              Type        InUse        MemUse     Requests
             kmsan           85         2720K           85
            newblk          529         2180K          615
          vfscache            3         2049K            3
            linker          306         1981K          344
         sysctloid        29067         1714K        29106
               pcb           15         1545K           35
              kobj          329         1316K          526
            devbuf         1360         1149K         1380
          inodedep           52         1044K           67
         ufs_quota            1         1024K            1
          vfs_hash            1         1024K            1
              intr            4          472K            4
           callout            1          256K            1
         vnet_data            1          168K            1
           subproc           74          162K          760
           tidhash            3          158K            3
              SWAP            1          132K            1
           pagedep           13          131K           18
        tfo_ccache            1          128K            1
               sem            4          106K            4
            DEVFS1           92           92K          106
              vmem            3           81K            3
               bus          976           78K         2580
            bus-sc           31           76K         1058
          mtx_pool            2           72K            2
          syncache            1           68K            1
          acpitask            1           64K            1
       ddb_capture            1           64K            1
            module          503           63K          503
         pfs_nodes          151           57K          151
            acpica          420           39K        61011
               LRO            2           33K            2
              proc            3           33K            3
              temp           18           33K         1602
         hostcache            1           32K            1
               shm            1           32K            1
               msg            4           30K            4
            DEVFS3          114           29K          132
        gtaskqueue           12           25K           12
         ufs_mount            5           25K            6
           kdtrace          123           24K          809
              umtx          176           22K          176
            kbdmux            5           22K            5
        DEVFS_RULE           56           20K           56
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
         bmsafemap            4            9K           40
              UART           12            9K           12
               rpc            2            8K            2
             shmfd            1            8K            1
     audit_evclass          236            8K          294
       ufs_dirhash           36            8K           36
         taskqueue           51            6K           51
            sglist            3            6K            3
            dirrem           17            5K           28
           uidinfo            3            5K            8
              cred           17            5K          268
             ifnet            3            5K            3
           io_apic            1            4K            1
               tty            4            4K            4
             evdev            4            4K            4
          filedesc            1            4K            1
               UMA          238            4K          238
             mount           76            4K          153
             hhook           13            4K           13
            diradd           25            4K           37
           lltable           11            4K           11
           acpisem           21            3K           21
            plimit           10            3K          197
            kqueue           37            3K          723
           pwddesc           37            3K          723
          freework            9            3K           28
             linux           33            3K           33
       ether_multi           26            3K           36
       fpukern_ctx            2            2K            2
          freeblks            8            2K           21
         ipsec-saq            2            2K            2
           CAM DEV            1            2K            2
         in6_multi           15            2K           15
             lockf           16            2K           32
               msi           13            2K           13
            Unitno           27            2K           51
           session           13            2K           21
          pci_link           16            2K           16
           acpidev           22            2K           22
             selfd           20            2K         8800
        local_apic            1            1K            1
           softdep            1            1K            1
             mkdir            8            1K           16
          indirdep            4            1K            6
       ipsecpolicy            1            1K            1
            sahead            1            1K            1
          secasvar            1            1K            1
             clone            8            1K            8
       vnodemarker            2            1K            8
      NFSD session            1            1K            1
         proc-args           24            1K          421
            select            7            1K           23
             nhops            6            1K            6
            ip6ndp            4            1K            5
            isadev            5            1K            5
           CAM XPT           11            1K           12
         CAM queue            2            1K            5
         newdirblk            4            1K            8
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
          freefile            2            1K           10
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
          freefrag            1            1K            6
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
           entropy            1            1K           33
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
        cl_savebuf            0            0K            3
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
               iov            0            0K        11906
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
              sbuf            0            0K          502
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
   mbuf_jumbo_page   4096    1088     518       13219       0     254    6578176        0
      malloc-32768  32768      85       0          85       0       1    2785280        0
              pbuf   2624       0     973           0       0       4    2553152        0
          BUF TRIE    144     199   16909         539       0      62    2463552        0
       malloc-4096   4096     330       1         527       0       2    1355776        0
        malloc-128    128    9555      24        9566       0     126    1226112        0
         FFS inode   1160     523       2         533       0       8     609000        0
        malloc-512    512    1028       4        1034       0      30     528384        0
              mbuf    256    1346     529       20715       0     254     480000        0
      malloc-65536  65536       6       0           6       0       1     393216        0
        RADIX NODE    144    2534      64       37066       0      62     374112        0
            lkpimm    160       1    2324           1       0      62     372000        0
          lkpicurr    160       2    2323           2       0      62     372000        0
         vmem btag     56    6380      76        6380       0     254     361536        0
       UMA Slabs 0    112    2526      27        2526       0     126     285936        0
       malloc-2048   2048     129       1         129       0       8     266240        0
      malloc-65536  65536       3       1         109       0       1     262144        0
      malloc-65536  65536       4       0           4       0       1     262144        0
             VNODE    448     554      13         566       0      30     254016        0
         VM OBJECT    264     854      16       11486       0      30     229680        0
         malloc-64     64    3451      14        4154       0     254     221760        0
            DEVCTL   1024       0     216         114       0       0     221184        0
       malloc-4096   4096      49       0         735       0       2     200704        0
         malloc-16     16   12080     170       12129       0     254     196000        0
        malloc-256    256     613      32        1074       0      62     165120        0
      malloc-32768  32768       5       0           5       0       1     163840        0
            THREAD   1808      85       3          85       0       8     159104        0
         malloc-32     32    4291     119        4318       0     254     141120        0
         UMA Zones    640     210       4         210       0      16     136960        0
       FFS2 dinode    256     523       2         533       0      62     134400        0
      malloc-65536  65536       2       0           2       0       1     131072        0
          ksiginfo    112      26    1018          38       0     126     116928        0
        256 Bucket   2048      56       0        2409       0       8     114688        0
        malloc-128    128     840      28        1853       0     126     111104        0
       S VFS Cache    104     994      59        1048       0     126     109512        0
       malloc-1024   1024      93      11         114       0      16     106496        0
      malloc-16384  16384       6       0          78       0       1      98304        0
            clpbuf   2624       0      32          56       0      32      83968        0
          UMA Kegs    384     195       8         195       0      30      77952        0
         MAP ENTRY     96     676     122       35073       0     126      76608        0
      malloc-65536  65536       1       0           1       0       1      65536        0
      malloc-65536  65536       1       0           1       0       1      65536        0
      malloc-32768  32768       2       0           2       0       1      65536        0
        malloc-384    384     151       9         151       0      30      61440        0
           DIRHASH   1024      54       2          54       0      16      57344        0
       malloc-8192   8192       6       1          96       0       1      57344        0
      malloc-16384  16384       3       0           3       0       1      49152        0
      malloc-16384  16384       2       1           7       0       1      49152        0
              PROC   1336      36       0         722       0       8      48096        0
        malloc-128    128     366       6       30911       0     126      47616        0
           VMSPACE   2544      17       1         704       0       4      45792        0
         filedesc0   1072      37       5         723       0       8      45024        0
       malloc-8192   8192       5       0           5       0       1      40960        0
         malloc-64     64     610      20         854       0     254      40320        0
        malloc-128    128     286      24         554       0     126      39680        0
        malloc-256    256     141       9         560       0      62      38400        0
        malloc-256    256     121      14         145       0      62      34560        0
      mbuf_cluster   2048      15       1          15       0     254      32768        0
      malloc-32768  32768       0       1          52       0       1      32768        0
      malloc-32768  32768       1       0           1       0       1      32768        0
           pcpu-64     64     454      58         454       0     254      32768        0
       malloc-4096   4096       6       1         272       0       2      28672        0
            pcpu-8      8    3146     438        3158       0     254      28672        0
        malloc-384    384      60      10          87       0      30      26880        0
        malloc-256    256      94      11         138       0      62      26880        0
       malloc-4096   4096       5       1         210       0       2      24576        0
        malloc-384    384      52       8          52       0      30      23040        0
        malloc-384    384      51       9          51       0      30      23040        0
       malloc-2048   2048       9       1           9       0       8      20480        0
        128 Bucket   1024      17       2         431       0      16      19456        0
       Mountpoints   2752       6       1           6       0       4      19264        0
       malloc-8192   8192       2       0           2       0       1      16384        0
       malloc-2048   2048       5       3          73       0       8      16384        0
       malloc-1024   1024      14       2          14       0      16      16384        0
         64 Bucket    512      26       6         791       0      30      16384        0
        malloc-128    128     105      19         153       0     126      15872        0
            socket    944      14       2        1158       0     254      15104        0
         TURNSTILE    136      89      16          89       0      62      14280        0
       malloc-4096   4096       2       1          48       0       2      12288        0
       malloc-2048   2048       3       3          12       0       8      12288        0
       malloc-1024   1024       9       3         992       0      16      12288        0
       malloc-1024   1024       7       5          11       0      16      12288        0
       malloc-1024   1024       9       3           9       0      16      12288        0
         malloc-64     64     132      57        1604       0     254      12096        0
         malloc-64     64     185       4       13354       0     254      12096        0
         malloc-32     32     322      56         431       0     254      12096        0
        SLEEPQUEUE     88      89       7          89       0     126       8448        0
       malloc-8192   8192       1       0           1       0       1       8192        0
       malloc-8192   8192       1       0           1       0       1       8192        0
       malloc-4096   4096       1       1           4       0       2       8192        0
       malloc-1024   1024       4       4          15       0      16       8192        0
       malloc-1024   1024       6       2           6       0      16       8192        0
        malloc-512    512      12       4          12       0      30       8192        0
             g_bio    408       0      20        5492       0      30       8160        0
         malloc-64     64      78      48        8882       0     254       8064        0
         malloc-64     64     113      13         141       0     254       8064        0
             Files     80      62      38        5886       0     126       8000        0
         malloc-16     16     274     226         543       0     254       8000        0
        malloc-256    256      22       8          97       0      62       7680        0
        malloc-256    256      16      14         593       0      62       7680        0
         32 Bucket    256      20      10         330       0      62       7680        0
     FPU_save_area    832       1       8           1       0      16       7488        0
             tcpcb   1064       3       4           7       0     254       7448        0
              pipe    744       7       3         271       0      16       7440        0
             NAMEI   1024       0       4       11096       0      16       4096        0
 epoch_record pcpu    256       4      12           4       0      62       4096        0
       malloc-2048   2048       1       1           2       0       8       4096        0
       malloc-2048   2048       0       2         211       0       8       4096        0
       malloc-2048   2048       2       0           2       0       8       4096        0
       malloc-1024   1024       0       4           4       0      16       4096        0
        malloc-512    512       3       5         236       0      30       4096        0
        malloc-512    512       0       8           1       0      30       4096        0
        malloc-512    512       6       2           7       0      30       4096        0
           pcpu-16     16       7     249           7       0     254       4096        0
           rtentry    176      13      10          17       0      62       4048        0
              PGRP     88      13      33          21       0     126       4048        0
          rl_entry     40      17      84          17       0     254       4040        0
         hostcache     64       1      62           1       0     254       4032        0
          syncache    168       0      24           5       0     254       4032        0
             udpcb     32       2     124          70       0     254       4032        0
               PWD     32      11     115          99       0     254       4032        0
         malloc-64     64       6      57           7       0     254       4032        0
         malloc-64     64      17      46         243       0     254       4032        0
         malloc-32     32       4     122           5       0     254       4032        0
         malloc-32     32       2     124           4       0     254       4032        0
         malloc-32     32      89      37         244       0     254       4032        0
         malloc-32     32      39      87         629       0     254       4032        0
         malloc-32     32      44      82        4972       0     254       4032        0
         malloc-32     32      24     102         158       0     254       4032        0
         16 Bucket    144      15      13         167       0      62       4032        0
          4 Bucket     48       3      81          10       0     254       4032        0
          2 Bucket     32      26     100         550       0     254       4032        0
      vtnet_tx_hdr     24       1     166        6701       0     254       4008        0
            ttyinq    160      15      10          45       0      62       4000        0
         malloc-16     16       0     250           4       0     254       4000        0
         malloc-16     16      54     196          93       0     254       4000        0
         malloc-16     16      20     230          21       0     254       4000        0
         malloc-16     16     180      70         957       0     254       4000        0
         malloc-16     16      32     218       26662       0     254       4000        0
         malloc-16     16      15     235          21       0     254       4000        0
          8 Bucket     80      15      35        2325       0     126       4000        0
        malloc-128    128       6      25          12       0     126       3968        0
        malloc-128    128      31       0          44       0     126       3968        0
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
        malloc-256    256      10       5         326       0      62       3840        0
        malloc-256    256      15       0          24       0      62       3840        0
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
# {Threaded:false Collide:false Repeat:true RepeatTimes:0 Procs:1 Slowdown:1 Sandbox: Fault:false FaultCall:-1 FaultNth:0 Leak:false NetInjection:false NetDevices:false NetReset:false Cgroups:false BinfmtMisc:false CloseFDs:false KCSAN:false DevlinkPCI:false USB:false VhciInjection:false Wifi:false IEEE802154:false Sysctl:false UseTmpDir:false HandleSegv:true Repro:false Trace:false}
setrlimit(0x3, &(0x7f0000000040)={0xf74, 0x1})


C reproducer:
// autogenerated by syzkaller (https://github.com/google/syzkaller)

#define _GNU_SOURCE

#include <sys/types.h>

#include <pwd.h>
#include <setjmp.h>
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

static __thread int skip_segv;
static __thread jmp_buf segv_env;

static void segv_handler(int sig, siginfo_t* info, void* ctx)
{
  uintptr_t addr = (uintptr_t)info->si_addr;
  const uintptr_t prog_start = 1 << 20;
  const uintptr_t prog_end = 100 << 20;
  int skip = __atomic_load_n(&skip_segv, __ATOMIC_RELAXED) != 0;
  int valid = addr < prog_start || addr > prog_end;
  if (sig == SIGBUS) {
    valid = 1;
  }
  if (skip && valid) {
    _longjmp(segv_env, 1);
  }
  exit(sig);
}

static void install_segv_handler(void)
{
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sa.sa_sigaction = segv_handler;
  sa.sa_flags = SA_NODEFER | SA_SIGINFO;
  sigaction(SIGSEGV, &sa, NULL);
  sigaction(SIGBUS, &sa, NULL);
}

#define NONFAILING(...)                                                        \
  ({                                                                           \
    int ok = 1;                                                                \
    __atomic_fetch_add(&skip_segv, 1, __ATOMIC_SEQ_CST);                       \
    if (_setjmp(segv_env) == 0) {                                              \
      __VA_ARGS__;                                                             \
    } else                                                                     \
      ok = 0;                                                                  \
    __atomic_fetch_sub(&skip_segv, 1, __ATOMIC_SEQ_CST);                       \
    ok;                                                                        \
  })

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
      if (current_time_ms() - start < 5000) {
        continue;
      }
      kill_and_wait(pid, &status);
      break;
    }
  }
}

void execute_one(void)
{
  NONFAILING(*(uint64_t*)0x20000040 = 0xf74);
  NONFAILING(*(uint64_t*)0x20000048 = 1);
  syscall(SYS_setrlimit, 3ul, 0x20000040ul);
}
int main(void)
{
  syscall(SYS_mmap, 0x20000000ul, 0x1000000ul, 7ul, 0x1012ul, -1, 0ul);
  install_segv_handler();
  loop();
  return 0;
}


