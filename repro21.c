Syzkaller hit 'panic: filesystem goof: vop_panic[vop_readdir]' bug.

panic: filesystem goof: vop_panic[vop_readdir]
cpuid = 0
time = 1621100158
KDB: stack backtrace:
db_trace_self_wrapper() at db_trace_self_wrapper+0x47/frame 0xfffffe0051f37430
vpanic() at vpanic+0x1c7/frame 0xfffffe0051f37490
panic() at panic+0x43/frame 0xfffffe0051f374f0
vop_panic() at vop_panic+0x18/frame 0xfffffe0051f37500
VOP_READDIR_APV() at VOP_READDIR_APV+0x78/frame 0xfffffe0051f37530
vfs_emptydir() at vfs_emptydir+0x114/frame 0xfffffe0051f37600
vfs_domount() at vfs_domount+0x613/frame 0xfffffe0051f37870
vfs_donmount() at vfs_donmount+0xc8a/frame 0xfffffe0051f37920
kernel_mount() at kernel_mount+0x92/frame 0xfffffe0051f37980
cd9660_cmount() at cd9660_cmount+0x160/frame 0xfffffe0051f37a50
sys_mount() at sys_mount+0x3d3/frame 0xfffffe0051f37ab0
amd64_syscall() at amd64_syscall+0x247/frame 0xfffffe0051f37bf0
fast_syscall_common() at fast_syscall_common+0xf8/frame 0xfffffe0051f37bf0
--- syscall (0, FreeBSD ELF64, nosys), rip = 0x4116ea, rsp = 0x7fffdfffdf88, rbp = 0x7fffdfffdfc0 ---
KDB: enter: panic
[ thread pid 718 tid 100085 ]
Stopped at      kdb_enter+0x67: movq    $0,0x163a09e(%rip)
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
rcx                       0x80
rdx         0xffffffff81a06d05
rbx                          0
rsp         0xfffffe0051f37410
rbp         0xfffffe0051f37430
rsi                        0x1
rdi                          0
r8                           0
r9          0x8080808080808080
r10         0xfffffe0051f37300
r11              0x1ffaefff59c
r12         0xffffffff82267ac0  ddb_dbbe
r13                          0
r14         0xffffffff81a62785
r15         0xffffffff81a62785
rip         0xffffffff8112e0e7  kdb_enter+0x67
rflags                    0x82
kdb_enter+0x67: movq    $0,0x163a09e(%rip)
db> show proc
Process 718 (syz-executor4054160) at 0xfffff80010337538:
 state: NORMAL
 uid: 0  gids: 0, 0, 5
 parent: pid 716 at 0xfffff800103e2538
 ABI: FreeBSD ELF64
 flag: 0x10004080  flag2: 0
 arguments: /root/syz-executor405416094
 reaper: 0xfffff8000357b538 reapsubtree: 1
 sigparent: 20
 vmspace: 0xfffffe0051d8b3e0
   (map 0xfffffe0051d8b3e0)
   (map.pmap 0xfffffe0051d8b4a0)
   (pmap 0xfffffe0051d8b500)
 threads: 2
100080                   RunQ                                syz-executor4054160
100085                   Run     CPU 0                       syz-executor4054160
db> ps
  pid  ppid  pgrp   uid  state   wmesg   wchan               cmd
  718   716   716     0  R       (threaded)                  syz-executor4054160
100080                   RunQ                                syz-executor4054160
100085                   Run     CPU 0                       syz-executor4054160
  716   714   716     0  Ss      pause   0xfffff800103e25e8  csh
  714   641   714     0  Ss      select  0xfffff80003e05ec0  sshd
  693     1   693     0  Ss+     ttyin   0xfffff8000373f8b0  getty
  692   689    21     0  S+      nanslp  0xffffffff8273b8e0  sleep
  690     1    21     0  S+      piperd  0xfffff80003cf22e8  logger
  689     1    21     0  S+      wait    0xfffff800103e2a70  sh
  645     1   645     0  Ss      nanslp  0xffffffff8273b8e0  cron
  641     1   641     0  Ss      select  0xfffff80003e05f40  sshd
  449     1   449     0  Ss      select  0xfffff80003d3e140  syslogd
  378     1   378     0  Ss      select  0xfffff80003d3ec40  devd
  377     1   377    65  Ss      select  0xfffff8000384d2c0  dhclient
  307     1   307     0  Ss      select  0xfffff80003d450c0  dhclient
  304     1   304     0  Ss      select  0xfffff80003d3ea40  dhclient
   89     1    89     0  Ss      pause   0xfffff80003cf40b0  adjkerntz
   20     0     0     0  DL      -       0xffffffff8282745c  [soaiod4]
   19     0     0     0  DL      -       0xffffffff8282745c  [soaiod3]
   18     0     0     0  DL      -       0xffffffff8282745c  [soaiod2]
   17     0     0     0  DL      -       0xffffffff8282745c  [soaiod1]
   16     0     0     0  DL      syncer  0xffffffff8282ad50  [syncer]
   15     0     0     0  DL      vlruwt  0xfffff80003aa3000  [vnlru]
    9     0     0     0  DL      (threaded)                  [bufdaemon]
100058                   D       qsleep  0xffffffff82829e00  [bufdaemon]
100063                   D       -       0xffffffff8220ae80  [bufspacedaemon-0]
100073                   D       sdflush 0xfffff80003abf8e8  [/ worker]
    8     0     0     0  DL      psleep  0xffffffff8284fb48  [vmdaemon]
    7     0     0     0  DL      (threaded)                  [pagedaemon]
100056                   D       psleep  0xffffffff82843fb8  [dom0]
100061                   D       launds  0xffffffff82843fc4  [laundry: dom0]
100062                   D       umarcl  0xffffffff815b9fd0  [uma]
    6     0     0     0  DL      -       0xffffffff8256fc78  [rand_harvestq]
    5     0     0     0  DL      (threaded)                  [cam]
100037                   D       -       0xffffffff82447140  [doneq0]
100038                   D       -       0xffffffff824470c0  [async]
100055                   D       -       0xffffffff82446f90  [scanner]
   14     0     0     0  DL      seqstat 0xfffff800035ca888  [sequencer 00]
    4     0     0     0  DL      crypto_ 0xfffff800035b6f30  [crypto returns 0]
    3     0     0     0  DL      crypto_ 0xffffffff828414e0  [crypto]
   13     0     0     0  DL      (threaded)                  [geom]
100030                   D       -       0xffffffff8271b120  [g_event]
100031                   D       -       0xffffffff8271b128  [g_up]
100032                   D       -       0xffffffff8271b130  [g_down]
    2     0     0     0  DL      -       0xfffff80003071280  [thr_0]
   12     0     0     0  WL      (threaded)                  [intr]
100009                   I                                   [swi6: task queue]
100012                   I                                   [swi6: Giant taskq]
100015                   I                                   [swi5: fast taskq]
100026                   I                                   [swi3: vm]
100027                   I                                   [swi4: clock (0)]
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
    1     0     1     0  SLs     wait    0xfffff8000357b538  [init]
   10     0     0     0  DL      audit_w 0xffffffff828419f0  [audit]
    0     0     0     0  DLs     (threaded)                  [kernel]
100000                   D       swapin  0xffffffff8271b6b0  [swapper]
100004                   D       -       0xfffff80003136d00  [if_config_tqg_0]
100005                   D       -       0xfffff80003136c00  [softirq_0]
100006                   D       -       0xfffff80003136b00  [if_io_tqg_0]
100007                   D       -       0xfffff8000355dd00  [pci_hp taskq]
100008                   D       -       0xfffff8000355dc00  [linuxkpi_irq_wq]
100010                   D       -       0xfffff8000355d900  [in6m_free taskq]
100011                   D       -       0xfffff8000355d800  [inm_free taskq]
100013                   D       -       0xfffff8000355d500  [thread taskq]
100014                   D       -       0xfffff8000355d400  [aiod_kick taskq]
100016                   D       -       0xfffff8000355d100  [kqueue_ctx taskq]
100017                   D       -       0xfffff8000355d000  [linuxkpi_short_wq_0]
100018                   D       -       0xfffff8000355d000  [linuxkpi_short_wq_1]
100019                   D       -       0xfffff8000355d000  [linuxkpi_short_wq_2]
100020                   D       -       0xfffff8000355d000  [linuxkpi_short_wq_3]
100021                   D       -       0xfffff80003556e00  [linuxkpi_long_wq_0]
100022                   D       -       0xfffff80003556e00  [linuxkpi_long_wq_1]
100023                   D       -       0xfffff80003556e00  [linuxkpi_long_wq_2]
100024                   D       -       0xfffff80003556e00  [linuxkpi_long_wq_3]
100029                   D       -       0xfffff80003556900  [firmware taskq]
100033                   D       -       0xfffff80003556700  [crypto]
100042                   D       -       0xfffff80003756c00  [vtnet0 rxq 0]
100043                   D       -       0xfffff80003756b00  [vtnet0 txq 0]
100049                   D       -       0xffffffff81e0eff0  [deadlkres]
100051                   D       -       0xfffff80003ab2a00  [acpi_task_0]
100052                   D       -       0xfffff80003ab2a00  [acpi_task_1]
100053                   D       -       0xfffff80003ab2a00  [acpi_task_2]
100054                   D       -       0xfffff80003556600  [CAM taskq]
db> show all locks
Process 718 (syz-executor4054160) thread 0xfffffe0051d85000 (100085)
exclusive lockmgr ufs (ufs) r = 0 (0xfffff80003d8d070) locked @ /usr/home/markj/src/freebsd/sys/kern/vfs_subr.c:3035
db> show malloc
              Type        InUse        MemUse     Requests
         sysctloid        29067         1714K        29106
              kobj          329         1316K          526
            newblk          566         1166K          578
            linker          306         1157K          344
            devbuf         1360         1149K         1380
          vfscache            3         1025K            3
          inodedep           45          529K           67
         ufs_quota            1          512K            1
          vfs_hash            1          512K            1
              intr            4          472K            4
               pcb           15          393K           35
           callout            1          256K            1
         vnet_data            1          168K            1
           subproc           73          158K          756
           tidhash            3          141K            3
              SWAP            1          132K            1
           pagedep           13          131K           18
        tfo_ccache            1          128K            1
               sem            4          106K            4
            DEVFS1           92           92K          106
               bus          975           78K         2579
            bus-sc           31           76K         1058
          mtx_pool            2           72K            2
          syncache            1           68K            1
          acpitask            1           64K            1
       ddb_capture            1           64K            1
            module          503           63K          503
         pfs_nodes          151           57K          151
            acpica          420           39K        61011
              temp           20           35K         1502
               LRO            2           33K            2
         hostcache            1           32K            1
               shm            1           32K            1
               msg            4           30K            4
            DEVFS3          114           29K          132
              vmem            3           26K            5
        gtaskqueue           12           25K           12
         ufs_mount            5           25K            6
           kdtrace          122           24K          805
              umtx          176           22K          176
            kbdmux            5           22K            5
        DEVFS_RULE           56           20K           56
               BPF           10           18K           10
           ithread           98           18K           98
              proc            3           17K            3
           devstat            8           17K            8
            KTRACE          100           13K          100
              GEOM           79           13K          662
              rman          102           12K          526
            ifaddr           30           12K           32
          routetbl           52           11K          178
              kenv           63           11K           63
      eventhandler          115           10K          115
         bmsafemap            4            9K           43
       pfs_vncache            6            9K            6
              UART           12            9K           12
               rpc            2            8K            2
             shmfd            1            8K            1
             mount          112            8K          237
     audit_evclass          236            8K          294
       ufs_dirhash           36            8K           36
         taskqueue           51            6K           51
            sglist            3            6K            3
              cred           17            5K          268
             ifnet            3            5K            3
           io_apic            1            4K            1
            dirrem           16            4K           28
               tty            4            4K            4
             evdev            4            4K            4
          filedesc            1            4K            1
               UMA          238            4K          238
             hhook           13            4K           13
            diradd           25            4K           37
           lltable           11            4K           11
           acpisem           21            3K           21
           uidinfo            3            3K            8
            plimit            9            3K          193
            kqueue           36            3K          719
           pwddesc           36            3K          719
             linux           33            3K           33
       ether_multi           26            3K           36
       fpukern_ctx            2            2K            2
         ipsec-saq            2            2K            2
           CAM DEV            1            2K            2
         in6_multi           15            2K           15
             selfd           27            2K        10680
               msi           13            2K           13
            Unitno           27            2K           51
           session           13            2K           21
             lockf           15            2K           22
          pci_link           16            2K           16
           acpidev           22            2K           22
        local_apic            1            1K            1
           softdep            1            1K            1
       ipsecpolicy            1            1K            1
            sahead            1            1K            1
          secasvar            1            1K            1
             clone            8            1K            8
       vnodemarker            2            1K           10
      NFSD session            1            1K            1
         proc-args           24            1K          421
            select            7            1K           23
          indirdep            3            1K            3
             nhops            6            1K            6
            ip6ndp            4            1K            5
            isadev            5            1K            5
           CAM XPT           11            1K           12
         CAM queue            2            1K            5
         newdirblk            4            1K            8
             mkdir            4            1K           16
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
          freework            1            1K           20
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
          savedino            0            0K           19
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
          freefile            0            0K           10
          freeblks            0            0K           19
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
        cl_savebuf            0            0K            4
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
               iov            0            0K        11855
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
              sbuf            0            0K          482
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
   mbuf_jumbo_page   4096    1088     665       13769       0     254    7180288        0
              pbuf   2624       0     973           0       0       4    2553152        0
          BUF TRIE    144     184   13312         461       0      62    1943424        0
       malloc-4096   4096     329       1         526       0       2    1351680        0
        malloc-128    128    9554      25        9559       0     126    1226112        0
         FFS inode   1160     523       9         534       0       8     617120        0
        malloc-512    512    1029       3        1037       0      30     528384        0
              mbuf    256    1347     678       21450       0     254     518400        0
      malloc-65536  65536       7       0           7       0       1     458752        0
            lkpimm    160       1    2324           1       0      62     372000        0
          lkpicurr    160       2    2323           2       0      62     372000        0
        RADIX NODE    144    1967     298       17656       0      62     326160        0
       UMA Slabs 0    112    2593      32        2593       0     126     294000        0
       malloc-2048   2048     129       1         129       0       8     266240        0
      malloc-65536  65536       4       0           4       0       1     262144        0
             VNODE    448     554      13         567       0      30     254016        0
         VM OBJECT    264     852      18       11485       0      30     229680        0
         malloc-64     64    3450      15        4147       0     254     221760        0
            DEVCTL   1024       0     216         114       0       0     221184        0
       malloc-4096   4096      49       1         732       0       2     204800        0
      malloc-65536  65536       2       1         108       0       1     196608        0
         malloc-16     16   12080     170       12129       0     254     196000        0
        malloc-256    256     649      11        1040       0      62     168960        0
            THREAD   1808      85       3          85       0       8     159104        0
         malloc-32     32    4291     119        4318       0     254     141120        0
         UMA Zones    640     210       4         210       0      16     136960        0
       FFS2 dinode    256     523       2         534       0      62     134400        0
      malloc-65536  65536       2       0           2       0       1     131072        0
      malloc-32768  32768       4       0           4       0       1     131072        0
          ksiginfo    112      26    1018          39       0     126     116928        0
        malloc-128    128     839      29        1850       0     126     111104        0
        256 Bucket   2048      53       1        2184       0       8     110592        0
       S VFS Cache    104     994      59        1049       0     126     109512        0
       malloc-1024   1024      93      11         114       0      16     106496        0
         vmem btag     56    1805      55        1805       0     254     104160        0
            clpbuf   2624       0      32          31       0      32      83968        0
      malloc-16384  16384       5       0          77       0       1      81920        0
          UMA Kegs    384     195       8         195       0      30      77952        0
         MAP ENTRY     96     672     126       35044       0     126      76608        0
      malloc-65536  65536       1       0           1       0       1      65536        0
      malloc-65536  65536       1       0           1       0       1      65536        0
      malloc-16384  16384       4       0           4       0       1      65536        0
       malloc-8192   8192       8       0          98       0       1      65536        0
        malloc-384    384     151       9         151       0      30      61440        0
           DIRHASH   1024      54       2          54       0      16      57344        0
              PROC   1336      35       1         718       0       8      48096        0
        malloc-128    128     360      12       30911       0     126      47616        0
           VMSPACE   2544      16       2         700       0       4      45792        0
         filedesc0   1072      36       6         719       0       8      45024        0
         malloc-64     64     609      21         853       0     254      40320        0
        malloc-128    128     285      25         529       0     126      39680        0
        malloc-256    256     140      10         553       0      62      38400        0
        malloc-256    256     122      13         149       0      62      34560        0
      mbuf_cluster   2048      15       1          15       0     254      32768        0
      malloc-32768  32768       0       1          52       0       1      32768        0
      malloc-32768  32768       1       0           1       0       1      32768        0
      malloc-32768  32768       1       0           1       0       1      32768        0
       malloc-8192   8192       4       0           4       0       1      32768        0
       malloc-8192   8192       4       0           4       0       1      32768        0
           pcpu-64     64     453      59         453       0     254      32768        0
       malloc-4096   4096       6       1         272       0       2      28672        0
            pcpu-8      8    3146     438        3158       0     254      28672        0
        128 Bucket   1024      22       5         638       0      16      27648        0
        malloc-256    256      85      20         133       0      62      26880        0
       malloc-4096   4096       5       1         210       0       2      24576        0
             g_bio    408       0      60        5116       0      30      24480        0
        malloc-384    384      52       8          54       0      30      23040        0
        malloc-384    384      53       7          87       0      30      23040        0
        malloc-384    384      51       9          51       0      30      23040        0
       malloc-2048   2048       9       1           9       0       8      20480        0
       Mountpoints   2752       6       1           6       0       4      19264        0
      malloc-16384  16384       0       1           2       0       1      16384        0
      malloc-16384  16384       1       0           1       0       1      16384        0
       malloc-2048   2048       6       2          62       0       8      16384        0
       malloc-1024   1024      14       2          14       0      16      16384        0
         64 Bucket    512      29       3         476       0      30      16384        0
        malloc-128    128     105      19         153       0     126      15872        0
            socket    944      14       2        1158       0     254      15104        0
         TURNSTILE    136      89      16          89       0      62      14280        0
       malloc-4096   4096       2       1          49       0       2      12288        0
       malloc-1024   1024       9       3         958       0      16      12288        0
       malloc-1024   1024       7       5          11       0      16      12288        0
       malloc-1024   1024      10       2          10       0      16      12288        0
         malloc-64     64     130      59        1551       0     254      12096        0
         malloc-64     64     185       4       13323       0     254      12096        0
         malloc-32     32     322      56         431       0     254      12096        0
        SLEEPQUEUE     88      89       7          89       0     126       8448        0
       malloc-8192   8192       1       0           1       0       1       8192        0
       malloc-8192   8192       1       0           1       0       1       8192        0
       malloc-4096   4096       1       1           4       0       2       8192        0
       malloc-2048   2048       3       1          12       0       8       8192        0
       malloc-1024   1024       4       4          15       0      16       8192        0
       malloc-1024   1024       5       3           5       0      16       8192        0
        malloc-512    512      12       4          12       0      30       8192        0
         malloc-64     64      98      28       10790       0     254       8064        0
         malloc-64     64     112      14         140       0     254       8064        0
             Files     80      63      37        5887       0     126       8000        0
         malloc-16     16     274     226         545       0     254       8000        0
        malloc-128    128      31      31          46       0     126       7936        0
        malloc-256    256      14      16          89       0      62       7680        0
        malloc-256    256      16      14         594       0      62       7680        0
        malloc-256    256      10      20         325       0      62       7680        0
         32 Bucket    256      22       8         335       0      62       7680        0
     FPU_save_area    832       1       8           1       0      16       7488        0
             tcpcb   1064       3       4           7       0     254       7448        0
              pipe    744       7       3         271       0      16       7440        0
             NAMEI   1024       0       4       11098       0      16       4096        0
 epoch_record pcpu    256       4      12           4       0      62       4096        0
       malloc-2048   2048       1       1           1       0       8       4096        0
       malloc-2048   2048       2       0           4       0       8       4096        0
       malloc-2048   2048       0       2         211       0       8       4096        0
       malloc-2048   2048       1       1           1       0       8       4096        0
       malloc-1024   1024       0       4           4       0      16       4096        0
        malloc-512    512       1       7           2       0      30       4096        0
        malloc-512    512       3       5         230       0      30       4096        0
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
         malloc-32     32       4     122          10       0     254       4032        0
         malloc-32     32      89      37         244       0     254       4032        0
         malloc-32     32      39      87         629       0     254       4032        0
         malloc-32     32      44      82        4972       0     254       4032        0
         malloc-32     32      24     102         158       0     254       4032        0
         16 Bucket    144      14      14         182       0      62       4032        0
          4 Bucket     48       3      81          10       0     254       4032        0
          2 Bucket     32      26     100         464       0     254       4032        0
      vtnet_tx_hdr     24       1     166        6848       0     254       4008        0
            ttyinq    160      15      10          45       0      62       4000        0
         malloc-16     16       1     249           5       0     254       4000        0
         malloc-16     16      72     178         131       0     254       4000        0
         malloc-16     16      20     230          21       0     254       4000        0
         malloc-16     16     180      70         959       0     254       4000        0
         malloc-16     16      32     218       26662       0     254       4000        0
         malloc-16     16      15     235          21       0     254       4000        0
          8 Bucket     80      17      33         225       0     126       4000        0
        malloc-128    128       5      26          11       0     126       3968        0
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
        malloc-384    384       5       5         183       0      30       3840        0
        malloc-384    384       6       4           6       0      30       3840        0
        malloc-384    384       0      10           3       0      30       3840        0
        malloc-256    256      15       0          24       0      62       3840        0
        KMAP ENTRY     96      21      18          25       0       0       3744        0
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
      malloc-32768  32768       0       0           0       0       1          0        0
      malloc-16384  16384       0       0           0       0       1          0        0
      malloc-16384  16384       0       0           0       0       1          0        0
      malloc-16384  16384       0       0           0       0       1          0        0
      malloc-16384  16384       0       0           0       0       1          0        0
       malloc-8192   8192       0       0           0       0       1          0        0
       malloc-8192   8192       0       0           0       0       1          0        0
       malloc-8192   8192       0       0           0       0       1          0        0
       malloc-4096   4096       0       0           0       0       2          0        0
       malloc-4096   4096       0       0           0       0       2          0        0
        malloc-512    512       0       0           0       0      30          0        0
        malloc-512    512       0       0           0       0      30          0        0
           pcpu-32     32       0       0           0       0     254          0        0
            pcpu-4      4       0       0           0       0     254          0        0
            fakepg    104       0       0           0       0     126          0        0
          UMA Hash    256       0       0           0       0      62          0        0


Syzkaller reproducer:
# {Threaded:true Collide:true Repeat:false RepeatTimes:0 Procs:1 Slowdown:1 Sandbox: Fault:false FaultCall:-1 FaultNth:0 Leak:false NetInjection:false NetDevices:false NetReset:false Cgroups:false BinfmtMisc:false CloseFDs:false KCSAN:false DevlinkPCI:false USB:false VhciInjection:false Wifi:false IEEE802154:false Sysctl:false UseTmpDir:false HandleSegv:false Repro:false Trace:false}
mount(&(0x7f0000000040)='cd9660\x00', &(0x7f0000000000)='./file0\x00', 0xd8200309, &(0x7f0000000100))
r0 = openat(0xffffffffffffff9c, &(0x7f0000000900)='.\x00', 0x0, 0x0)
mknodat(r0, &(0x7f0000000000)='./file0\x00', 0x1000, 0x0)


C reproducer:
// autogenerated by syzkaller (https://github.com/google/syzkaller)

#define _GNU_SOURCE

#include <errno.h>
#include <pthread.h>
#include <pwd.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/endian.h>
#include <sys/syscall.h>
#include <time.h>
#include <unistd.h>

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

static void loop(void)
{
  int i, call, thread;
  int collide = 0;
again:
  for (call = 0; call < 3; call++) {
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

uint64_t r[1] = {0xffffffffffffffff};

void execute_call(int call)
{
  intptr_t res = 0;
  switch (call) {
  case 0:
    memcpy((void*)0x20000040, "cd9660\000", 7);
    memcpy((void*)0x20000000, "./file0\000", 8);
    syscall(SYS_mount, 0x20000040ul, 0x20000000ul, 0xd8200309ul, 0x20000100ul);
    break;
  case 1:
    memcpy((void*)0x20000900, ".\000", 2);
    res = syscall(SYS_openat, 0xffffff9c, 0x20000900ul, 0ul, 0ul);
    if (res != -1)
      r[0] = res;
    break;
  case 2:
    memcpy((void*)0x20000000, "./file0\000", 8);
    syscall(SYS_mknodat, r[0], 0x20000000ul, 0x1000ul, 0ul);
    break;
  }
}
int main(void)
{
  syscall(SYS_mmap, 0x20000000ul, 0x1000000ul, 7ul, 0x1012ul, -1, 0ul);
  loop();
  return 0;
}


