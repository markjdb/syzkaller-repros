Syzkaller hit 'panic: wrong vnode type ADDR' bug.

login: panic: wrong vnode type 0xfffff8006584a1c0
cpuid = 0
time = 1703489899
KDB: stack backtrace:
db_trace_self_wrapper() at db_trace_self_wrapper+0x49/frame 0xfffffe0063df8f90
vpanic() at vpanic+0x1a4/frame 0xfffffe0063df90d0
panic() at panic+0x43/frame 0xfffffe0063df9130
cache_enter_time() at cache_enter_time+0x1fdd/frame 0xfffffe0063df9220
zfs_lookup() at zfs_lookup+0xd64/frame 0xfffffe0063df9300
zfs_freebsd_cachedlookup() at zfs_freebsd_cachedlookup+0x86/frame 0xfffffe0063df9450
vfs_cache_lookup() at vfs_cache_lookup+0x155/frame 0xfffffe0063df94b0
vfs_lookup() at vfs_lookup+0x874/frame 0xfffffe0063df9570
namei() at namei+0x560/frame 0xfffffe0063df95e0
vn_open_cred() at vn_open_cred+0x6f0/frame 0xfffffe0063df9750
zfs_getextattr_impl() at zfs_getextattr_impl+0x478/frame 0xfffffe0063df9a40
zfs_getextattr() at zfs_getextattr+0x179/frame 0xfffffe0063df9a80
extattr_get_vp() at extattr_get_vp+0x180/frame 0xfffffe0063df9b60
kern_extattr_get_path() at kern_extattr_get_path+0x17b/frame 0xfffffe0063df9c90
sys_extattr_get_link() at sys_extattr_get_link+0x95/frame 0xfffffe0063df9df0
amd64_syscall() at amd64_syscall+0x26b/frame 0xfffffe0063df9f30
fast_syscall_common() at fast_syscall_common+0xf8/frame 0xfffffe0063df9f30
--- syscall (0, FreeBSD ELF64, syscall), rip = 0x24756a, rsp = 0x821293ca8, rbp = 0x821293d00 ---
KDB: enter: panic
[ thread pid 801 tid 100193 ]
Stopped at      kdb_enter+0x6b: movq    $0,0x143968a(%rip)
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
rdx         0xffffffff81c8a65e
rbx         0xffffffff81cef79d  do_execve.fexecv_proc_title+0x6db6
rsp         0xfffffe0063df8f70
rbp         0xfffffe0063df8f90
rsi                        0x1
rdi                          0
r8                           0
r9          0x8080808080808080
r10         0xfffffe0063df8e40
r11         0xfffffffffffff59c
r12         0xffffffff82258830  ddb_dbbe
r13                      0x100
r14         0xffffffff81cef79d  do_execve.fexecv_proc_title+0x6db6
r15                          0
rip         0xffffffff812f8c7b  kdb_enter+0x6b
rflags                    0x86
kdb_enter+0x6b: movq    $0,0x143968a(%rip)
db> show proc
Process 801 (syz-executor2049533) at 0xfffffe00767b4580:
 state: NORMAL
 uid: 0  gids: 0, 0, 5
 parent: pid 799 at 0xfffffe00087c4ac0
 ABI: FreeBSD ELF64
 flag: 0x10000000  flag2: 0
 arguments: /root/syz-executor2049533591
 reaper: 0xfffffe00086bb040 reapsubtree: 1
 sigparent: 20
 vmspace: 0xfffff800100a59a0
   (map 0xfffff800100a59a0)
   (map.pmap 0xfffff800100a5a60)
   (pmap 0xfffff800100a5ad0)
 threads: 1
100193                   Run     CPU 0                       syz-executor2049533
db> ps
  pid  ppid  pgrp   uid  state   wmesg   wchan               cmd
  801   799   797     0  R       CPU 0                       syz-executor2049533
  800   798   797     0  R       CPU 1                       syz-executor2049533
  799   797   797     0  S       nanslp  0xffffffff827197e0  syz-executor2049533
  798   797   797     0  S       nanslp  0xffffffff827197e1  syz-executor2049533
  797   795   797     0  Ss      nanslp  0xffffffff827197e0  syz-executor2049533
  795   764   795     0  Ss      select  0xfffff800048a8b40  sshd
  782     1   782     0  Ss+     ttyin   0xfffff80004aeccb0  getty
  778     1   778     0  Ss      select  0xfffff800048a9e40  logger
  773   771    17     0  S+      nanslp  0xffffffff827197e0  sleep
  772     1    17     0  S+      piperd  0xfffffe007606f888  logger
  771     1    17     0  S+      wait    0xfffffe00767b4020  sh
  768     1   768     0  Ss      nanslp  0xffffffff827197e1  cron
  764     1   764     0  Ss      select  0xfffff800048a8240  sshd
  664     1   664     0  Ss      kqread  0xfffff80010eec100  syslogd
  465     1   465     0  Ss      select  0xfffff80004770ac0  devd
  361     1   361    65  Ss      select  0xfffff800048a81c0  dhclient
  277     1   277     0  Ss      select  0xfffff800048a8640  dhclient
  274     1   274     0  Ss      select  0xfffff80004770c40  dhclient
   16     0     0     0  DL      syncer  0xffffffff82800028  [syncer]
   15     0     0     0  DL      vlruwt  0xfffffe00087c65a0  [vnlru]
    9     0     0     0  DL      (threaded)                  [bufdaemon]
100091                   D       psleep  0xffffffff827ff030  [bufdaemon]
100094                   D       -       0xffffffff82203100  [bufspacedaemon-0]
100095                   D       -       0xffffffff82203380  [bufspacedaemon-1]
    8     0     0     0  DL      psleep  0xffffffff82832ad0  [vmdaemon]
    7     0     0     0  DL      (threaded)                  [pagedaemon]
100089                   D       psleep  0xffffffff8281af38  [dom0]
100092                   D       launds  0xffffffff8281af44  [laundry: dom0]
100093                   D       umarcl  0xffffffff817ee7b0  [uma]
    6     0     0     0  DL      -       0xffffffff8251afc0  [rand_harvestq]
    5     0     0     0  DL      (threaded)                  [zfskern]
100059                   D       t->zthr 0xfffff80004740248  [arc_evict]
100060                   D       t->zthr 0xfffff80004740148  [arc_reap]
100061                   D       -       0xfffff80004740000  [dbu_evict]
100062                   D       dbuf_ev 0xffffffff82477d68  [dbuf_evict_thread]
100063                   D       -       0xfffff80004741c00  [z_vdev_file_0]
100064                   D       -       0xfffff80004741c00  [z_vdev_file_1]
100065                   D       -       0xfffff80004741c00  [z_vdev_file_2]
100066                   D       -       0xfffff80004741c00  [z_vdev_file_3]
100067                   D       -       0xfffff80004741c00  [z_vdev_file_4]
100068                   D       -       0xfffff80004741c00  [z_vdev_file_5]
100069                   D       -       0xfffff80004741c00  [z_vdev_file_6]
100070                   D       -       0xfffff80004741c00  [z_vdev_file_7]
100071                   D       -       0xfffff80004741c00  [z_vdev_file_8]
100072                   D       -       0xfffff80004741c00  [z_vdev_file_9]
100073                   D       -       0xfffff80004741c00  [z_vdev_file_10]
100074                   D       -       0xfffff80004741c00  [z_vdev_file_11]
100075                   D       -       0xfffff80004741c00  [z_vdev_file_12]
100076                   D       -       0xfffff80004741c00  [z_vdev_file_13]
100077                   D       -       0xfffff80004741c00  [z_vdev_file_14]
100078                   D       -       0xfffff80004741c00  [z_vdev_file_15]
100079                   D       l2arc_f 0xffffffff824771a8  [l2arc_feed_thread]
100080                   D       -       0xfffff80004741a00  [zfsvfs]
100081                   S       zevent_ 0xffffffff824784c8  [sysevent]
100132                   D       -       0xfffff80006515600  [z_zvol]
100133                   D       -       0xfffff80006515500  [z_metaslab]
100134                   D       -       0xfffff80006515400  [z_prefetch_0]
100135                   D       -       0xfffff80006515400  [z_prefetch_1]
100136                   D       -       0xfffff80006515300  [z_upgrade_0]
100137                   D       -       0xfffff80006515300  [z_upgrade_1]
100140                   D       -       0xfffff800064c0700  [dp_sync_taskq_0]
100141                   D       -       0xfffff800064c0700  [dp_sync_taskq_1]
100142                   D       -       0xfffff80005278300  [dp_zil_clean_taskq_]
100143                   D       -       0xfffff80005278300  [dp_zil_clean_taskq_]
100144                   D       -       0xfffff80006517a00  [z_zrele_0]
100145                   D       -       0xfffff80006517a00  [z_zrele_1]
100146                   D       -       0xfffff80006517900  [z_unlinked_drain_0]
100147                   D       -       0xfffff80006517900  [z_unlinked_drain_1]
100163                   D       tx->tx_ 0xfffff800064be550  [txg_thread_enter]
100164                   D       tx->tx_ 0xfffff800064be530  [txg_thread_enter]
100165                   D       mmp->mm 0xffffffff832fa4d0  [mmp_thread_enter]
100166                   D       t->zthr 0xfffff8000f3b5048  [raidz_expand]
100167                   D       t->zthr 0xfffff8000f936c48  [z_indirect_condense]
100168                   D       t->zthr 0xfffff8000f935a48  [z_livelist_destroy]
100169                   D       t->zthr 0xfffff8000f3b4d48  [z_livelist_condense]
100170                   D       t->zthr 0xfffff8000f937148  [z_checkpoint_discar]
    4     0     0     0  DL      (threaded)                  [cam]
100042                   D       -       0xffffffff82441240  [doneq0]
100043                   D       -       0xffffffff824411c0  [async]
100088                   D       -       0xffffffff82441090  [scanner]
    3     0     0     0  DL      (threaded)                  [crypto]
100039                   D       crypto_ 0xffffffff828183f0  [crypto]
100040                   D       crypto_ 0xfffff800048c8030  [crypto returns 0]
100041                   D       crypto_ 0xfffff800048c8080  [crypto returns 1]
   14     0     0     0  DL      seqstat 0xfffff80004853488  [sequencer 00]
   13     0     0     0  DL      (threaded)                  [geom]
100033                   D       -       0xffffffff826d51b0  [g_event]
100034                   D       -       0xffffffff826d51b8  [g_up]
100035                   D       -       0xffffffff826d51c0  [g_down]
    2     0     0     0  WL      (threaded)                  [clock]
100029                   I                                   [clock (0)]
100030                   I                                   [clock (1)]
   12     0     0     0  WL      (threaded)                  [intr]
100012                   I                                   [swi6: task queue]
100013                   I                                   [swi6: Giant taskq]
100015                   I                                   [swi5: fast taskq]
100031                   I                                   [swi1: netisr 0]
100044                   I                                   [irq40: virtio_pci0]
100045                   I                                   [irq41: virtio_pci0]
100046                   I                                   [irq42: virtio_pci0]
100049                   I                                   [irq43: virtio_pci1]
100050                   I                                   [irq44: virtio_pci1]
100051                   I                                   [irq1: atkbd0]
100052                   I                                   [irq12: psm0]
100053                   I                                   [swi0: uart uart++]
   11     0     0     0  RL      (threaded)                  [idle]
100003                   CanRun                              [idle: cpu0]
100004                   CanRun                              [idle: cpu1]
    1     0     1     0  SLs     wait    0xfffffe00086bb040  [init]
   10     0     0     0  DL      audit_w 0xffffffff828188e0  [audit]
    0     0     0     0  DLs     (threaded)                  [kernel]
100000                   D       swapin  0xffffffff826d5720  [swapper]
100005                   D       -       0xfffff800046ea100  [softirq_0]
100006                   D       -       0xfffff800046ea000  [softirq_1]
100007                   D       -       0xfffff800046ebe00  [if_io_tqg_0]
100008                   D       -       0xfffff800046ebd00  [if_io_tqg_1]
100009                   D       -       0xfffff800046ebc00  [if_config_tqg_0]
100010                   D       -       0xfffff800041f0e00  [pci_hp taskq]
100011                   D       -       0xfffff800041f0d00  [kqueue_ctx taskq]
100014                   D       -       0xfffff800041f0800  [thread taskq]
100016                   D       -       0xfffff800041f0500  [aiod_kick taskq]
100017                   D       -       0xfffff800041f0400  [deferred_unmount ta]
100018                   D       -       0xfffff800041f0300  [inm_free taskq]
100019                   D       -       0xfffff800041f0200  [in6m_free taskq]
100020                   D       -       0xfffff800041f0100  [linuxkpi_irq_wq]
100021                   D       -       0xfffff800041f0000  [linuxkpi_short_wq_0]
100022                   D       -       0xfffff800041f0000  [linuxkpi_short_wq_1]
100023                   D       -       0xfffff800041f0000  [linuxkpi_short_wq_2]
100024                   D       -       0xfffff800041f0000  [linuxkpi_short_wq_3]
100025                   D       -       0xfffff800041efe00  [linuxkpi_long_wq_0]
100026                   D       -       0xfffff800041efe00  [linuxkpi_long_wq_1]
100027                   D       -       0xfffff800041efe00  [linuxkpi_long_wq_2]
100028                   D       -       0xfffff800041efe00  [linuxkpi_long_wq_3]
100032                   D       -       0xfffff800041efb00  [firmware taskq]
100037                   D       -       0xfffff800041ef900  [crypto_0]
100038                   D       -       0xfffff800041ef900  [crypto_1]
100047                   D       -       0xfffff8000473fa00  [vtnet0 rxq 0]
100048                   D       -       0xfffff8000473f900  [vtnet0 txq 0]
100054                   D       -       0xfffff8000473f200  [system_taskq_0]
100055                   D       -       0xfffff8000473f200  [system_taskq_1]
100056                   D       -       0xfffff8000473f100  [system_delay_taskq_]
100057                   D       -       0xfffff8000473f100  [system_delay_taskq_]
100058                   D       -       0xfffff80004740300  [arc_prune]
100082                   D       -       0xffffffff81f503a1  [deadlkres]
100083                   D       -       0xfffff80004741900  [acpi_task_0]
100084                   D       -       0xfffff80004741900  [acpi_task_1]
100085                   D       -       0xfffff80004741900  [acpi_task_2]
100087                   D       -       0xfffff800041ef800  [CAM taskq]
100098                   D       -       0xfffff800041ef100  [z_null_iss]
100099                   D       -       0xfffff800041ef000  [z_null_int]
100100                   D       -       0xfffff80006514500  [z_rd_iss_0]
100101                   D       -       0xfffff80006514500  [z_rd_iss_1]
100102                   D       -       0xfffff80006514500  [z_rd_iss_2]
100103                   D       -       0xfffff80006514500  [z_rd_iss_3]
100104                   D       -       0xfffff80006514500  [z_rd_iss_4]
100105                   D       -       0xfffff80006514500  [z_rd_iss_5]
100106                   D       -       0xfffff80006514500  [z_rd_iss_6]
100107                   D       -       0xfffff80006514500  [z_rd_iss_7]
100108                   D       -       0xfffff80006514400  [z_rd_int]
100109                   D       -       0xfffff80006514300  [z_wr_iss]
100110                   D       -       0xfffff80006514200  [z_wr_iss_h_0]
100111                   D       -       0xfffff80006514200  [z_wr_iss_h_1]
100112                   D       -       0xfffff80006514200  [z_wr_iss_h_2]
100113                   D       -       0xfffff80006514200  [z_wr_iss_h_3]
100114                   D       -       0xfffff80006514200  [z_wr_iss_h_4]
100115                   D       -       0xfffff80006514100  [z_wr_int]
100116                   D       -       0xfffff80006514000  [z_wr_int_h_0]
100117                   D       -       0xfffff80006514000  [z_wr_int_h_1]
100118                   D       -       0xfffff80006514000  [z_wr_int_h_2]
100119                   D       -       0xfffff80006514000  [z_wr_int_h_3]
100120                   D       -       0xfffff80006514000  [z_wr_int_h_4]
100121                   D       -       0xfffff80006515e00  [z_fr_iss]
100122                   D       -       0xfffff80006515d00  [z_fr_int]
100123                   D       -       0xfffff80006515c00  [z_cl_iss]
100124                   D       -       0xfffff80006515b00  [z_cl_int]
100125                   D       -       0xfffff80006515a00  [z_ioctl_iss]
100126                   D       -       0xfffff80006515900  [z_ioctl_int]
100127                   D       -       0xfffff80006515800  [z_trim_iss_0]
100128                   D       -       0xfffff80006515800  [z_trim_iss_1]
100129                   D       -       0xfffff80006515800  [z_trim_iss_2]
100130                   D       -       0xfffff80006515800  [z_trim_iss_3]
100131                   D       -       0xfffff80006515700  [z_trim_int]
db> show all locks
Process 801 (syz-executor2049533) thread 0xfffff8001044b000 (100193)
exclusive sleep mutex ncbuc (ncbuc) r = 0 (0xfffff80004a683c0) locked @ /root/freebsd/sys/kern/vfs_cache.c:2324
exclusive sleep mutex ncvn (ncvn) r = 0 (0xfffff80004ae61e0) locked @ /root/freebsd/sys/kern/vfs_cache.c:2254
exclusive sleep mutex ncvn (ncvn) r = 0 (0xfffff80004ae6120) locked @ /root/freebsd/sys/kern/vfs_cache.c:2251
shared lockmgr zfs (zfs) r = 0 (0xfffff8006584a770) locked @ /root/freebsd/sys/kern/vfs_vnops.c:2379
shared lockmgr zfs (zfs) r = 1 (0xfffff8006584a230) locked @ /root/freebsd/sys/contrib/openzfs/module/os/freebsd/zfs/zfs_vnops_os.c:694
Process 800 (syz-executor2049533) thread 0xfffff800103a6000 (100179)
shared lockmgr zfs (zfs) r = 0 (0xfffff800659a4e70) locked @ /root/freebsd/sys/kern/vfs_lookup.c:1083
db> show malloc
              Type        InUse        MemUse     Requests
           solaris        17995        10375K        90242
         sysctloid        38743         2268K        38838
          vfscache            3         2049K            3
              kobj          323         1292K          488
            devbuf         1333         1144K         3702
               pcb           17         1037K           46
         ufs_quota            1         1024K            1
          vfs_hash            1         1024K            1
           callout            2          512K            2
              intr            4          472K            4
         vnet_data            2          224K            2
          acpitask            1          224K            1
           subproc           91          161K          858
           tidhash            3          158K            3
            bus-sc           31          148K         1070
        tfo_ccache            1          128K            1
          IP reass            1          128K            1
               sem            4          106K            4
        gtaskqueue           18           98K           18
            DEVFS1           90           90K          102
            linker          231           87K          277
               bus          963           78K         3525
          mtx_pool            2           72K            2
          syncache            1           68K            1
     NFSD srvcache            3           68K            3
       ddb_capture            1           64K            1
            module          499           63K          499
           kdtrace          221           49K         1035
              umtx          384           48K          384
            acpica          420           39K        64280
              temp           17           37K         1511
               LRO            2           33K            2
              proc            3           33K            3
         hostcache            1           32K            1
               shm            1           32K            1
               msg            4           30K            4
            kbdmux            5           28K            5
            DEVFS3          106           27K          119
        kstat_data           26           26K           26
        DEVFS_RULE           61           22K           61
               BPF           10           18K           10
           ithread           92           17K           92
       pfs_vncache            1           16K            1
         taskqueue          146           16K          257
            KTRACE          100           13K          100
              vmem            2           12K            2
      eventhandler          144           12K          144
              rman          100           12K          525
              kenv           94           12K           94
            ifaddr           29           11K           29
          routetbl           43           10K          131
               rpc            4            9K            4
           devstat            4            9K            4
              UART           12            9K           12
             shmfd            1            8K            1
              GEOM           41            8K          547
     audit_evclass          238            8K          300
               UMA          300            6K          300
            sglist            3            6K            3
         pfs_nodes           20            5K           20
             hhook           15            5K           17
            kqueue           38            5K          805
           uidinfo            3            5K            8
             ifnet            3            5K            3
           io_apic            1            4K            1
               tty            4            4K            4
          filedesc            1            4K            1
             evdev            4            4K            4
              cred           15            4K          276
           lltable           10            3K           10
           acpisem           21            3K           21
         toponodes           10            3K           10
            plimit            9            3K          192
           pwddesc           35            3K          802
        local_apic            1            2K            1
         ipsec-saq            2            2K            2
             clone            8            2K            8
           CAM DEV            1            2K            2
             lockf           18            2K           21
               osd           80            2K          144
         proc-args           50            2K         1730
               msi           13            2K           13
           session           13            2K           29
          pci_link           16            2K           16
       vnodemarker            3            2K            5
            Unitno           25            2K           45
             selfd           23            2K         5564
           acpidev           22            2K           22
         CAM queue            2            2K            5
       ipsecpolicy            1            1K            1
            sahead            1            1K            1
          secasvar            1            1K            1
       ether_multi           13            1K           13
            select            8            1K           59
      NFSD session            1            1K            1
         in6_multi            9            1K            9
            CC Mem            3            1K            7
             nhops            6            1K            6
              pfil            6            1K            6
            biobuf            2            1K            2
         sfs_nodes            2            1K            2
             mount           16            1K           79
            crypto            4            1K            4
            isadev            5            1K            5
           CAM XPT           11            1K           12
           netlink            2            1K           44
          in_multi            2            1K            2
              cdev            2            1K            2
       lkpikmalloc            8            1K            9
 encap_export_host            8            1K            8
            ip6ndp            3            1K            3
    chacha20random            1            1K            1
        CAM periph            2            1K           14
               MCA            2            1K            2
               mld            2            1K            2
              igmp            2            1K            2
            vnodes            1            1K            1
          procdesc            2            1K           20
      NFSD lckfile            1            1K            1
     NFSD V4client            1            1K            1
             DEVFS            9            1K           10
            prison            8            1K            8
            feeder            7            1K            7
       inpcbpolicy            6            1K           59
        loginclass            3            1K            7
             taskq            2            1K            2
            apmdev            1            1K            1
          atkbddev            2            1K            2
          pmchooks            1            1K            1
            DEVFSP            2            1K            2
           CAM SIM            1            1K            1
            soname            4            1K         1000
          filecaps            4            1K           98
          nexusdev            6            1K            6
               tun            3            1K            3
           tcpfunc            1            1K            1
              vnet            1            1K            1
               pmc            1            1K            1
          acpiintr            1            1K            1
     CAM dev queue            1            1K            1
              cpus            2            1K            2
    vnet_data_free            1            1K            1
           Per-cpu            1            1K            1
           entropy            1            1K           65
          CAM path            1            1K           12
          p1003.1b            1            1K            1
           filemon            0            0K            0
         cryptodev            0            0K            0
        madt_table            0            0K            2
          smartpqi            0            0K            0
               ixl            0            0K            0
        ice-resmgr            0            0K            0
         ice-osdep            0            0K            0
               ice            0            0K            0
              iavf            0            0K            0
             axgbe            0            0K            0
           memdesc            0            0K            0
       fpukern_ctx            0            0K            0
          xen_intr            0            0K            0
           xen_hvm            0            0K            0
         legacydrv            0            0K            0
            bounce            0            0K            0
            busdma            0            0K            0
            qpidrv            0            0K            0
      dmar_idpgtbl            0            0K            0
          dmar_dom            0            0K            0
          dmar_ctx            0            0K            0
              isci            0            0K            0
      iommu_dmamap            0            0K            0
     hyperv_socket            0            0K            0
           bxe_ilt            0            0K            0
        aesni_data            0            0K            0
            xenbus            0            0K            0
     vm_fictitious            0            0K            0
           UMAHash            0            0K            0
         vm_pgdata            0            0K            0
         ufs_mount            0            0K            0
       ufs_dirhash            0            0K            0
           softdep            0            0K            0
           jblocks            0            0K            0
          savedino            0            0K            0
          sentinel            0            0K            0
            jfsync            0            0K            0
            jtrunc            0            0K            0
             sbdep            0            0K            0
           jsegdep            0            0K            0
              jseg            0            0K            0
         jfreefrag            0            0K            0
          jfreeblk            0            0K            0
           jnewblk            0            0K            0
            jmvref            0            0K            0
           jremref            0            0K            0
           jaddref            0            0K            0
           freedep            0            0K            0
          freework            0            0K            0
         newdirblk            0            0K            0
            dirrem            0            0K            0
             mkdir            0            0K            0
            diradd            0            0K            0
          freefile            0            0K            0
          freeblks            0            0K            0
          freefrag            0            0K            0
        allocindir            0            0K            0
          indirdep            0            0K            0
       allocdirect            0            0K            0
            newblk            0            0K            0
         bmsafemap            0            0K            0
          inodedep            0            0K            0
           pagedep            0            0K            0
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
          ktls_ocf            0            0K            0
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
           lkpimhi            0            0K            0
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
            statfs            0            0K            0
     namei_tracker            0            0K            0
       export_host            0            0K            0
        cl_savebuf            0            0K            0
               aio            0            0K            0
               lio            0            0K            0
               acl            0            0K            0
          mbuf_tag            0            0K            0
              ktls            0            0K            0
              accf            0            0K            0
               pts            0            0K            0
           timerfd            0            0K            0
               iov            0            0K         6383
          ioctlops            0            0K           69
           eventfd            0            0K            0
           Witness            0            0K            0
          terminal            0            0K            0
             stack            0            0K            0
              sbuf            0            0K          317
          firmware            0            0K            0
        compressor            0            0K            0
              SWAP            0            0K            0
         sysctltmp            0            0K          547
            sysctl            0            0K           39
              ekcd            0            0K            0
            dumper            0            0K            0
          sendfile            0            0K            0
              rctl            0            0K            0
             cache            0            0K            0
          kcovinfo            0            0K            0
      prison_racct            0            0K            0
       Fail Points            0            0K            0
             sigio            0            0K            1
filedesc_to_leader            0            0K            0
               pwd            0            0K            0
       tty console            0            0K            0
         boottrace            0            0K            0
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
         raid_data            0            0K           78
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
       NFSD V4lock            0            0K            0
      NFSD V4state            0            0K            0
       msdosfs_fat            0            0K            0
     msdosfs_mount            0            0K            0
      msdosfs_node            0            0K            0
            DEVFS4            0            0K            0
            DEVFS2            0            0K            0
            gntdev            0            0K            0
       privcmd_dev            0            0K            0
        evtchn_dev            0            0K            0
          xenstore            0            0K            0
               xnb            0            0K            0
          xen_acpi            0            0K            0
              xbbd            0            0K            0
               xbd            0            0K            0
           Balloon            0            0K            0
          sysmouse            0            0K            0
            vtfont            0            0K            0
                vt            0            0K            0
             vtbuf            0            0K            0
            pvscsi            0            0K            0
            USBdev            0            0K            0
               USB            0            0K            0
            twsbuf            0            0K            0
       tcp_log_dev            0            0K            0
      midi buffers            0            0K            0
             mixer            0            0K            0
              ac97            0            0K            0
             hdacc            0            0K            0
              hdac            0            0K            0
              hdaa            0            0K            0
       SIIS driver            0            0K            0
               PUC            0            0K            0
          ppbusdev            0            0K            0
            sr_iov            0            0K            0
               OCS            0            0K            0
               OCS            0            0K            0
              nvme            0            0K            0
               nvd            0            0K            0
            netmap            0            0K            0
            mwldev            0            0K            0
        MVS driver            0            0K            0
          mrsasbuf            0            0K            0
          mpt_user            0            0K            0
          mps_user            0            0K            0
            MPSSAS            0            0K            0
               mps            0            0K            0
          mpr_user            0            0K            0
            MPRSAS            0            0K            0
               mpr            0            0K            0
            mfibuf            0            0K            0
        md_sectors            0            0K            0
           md_disk            0            0K            0
           malodev            0            0K            0
               LED            0            0K            0
          ix_sriov            0            0K            0
                ix            0            0K            0
            ipsbuf            0            0K            0
         ciss_data            0            0K            0
         BACKLIGHT            0            0K            0
           ath_hal            0            0K            0
            athdev            0            0K            0
           ata_pci            0            0K            0
           ata_dma            0            0K            0
       ata_generic            0            0K            0
       AHCI driver            0            0K            0
               agp            0            0K            0
           acpipwr            0            0K            0
         acpi_perf            0            0K            0
         acpicmbat            0            0K            0
        aacraidcam            0            0K            0
       aacraid_buf            0            0K            0
            aaccam            0            0K            0
            aacbuf            0            0K            0
              zstd            0            0K            0
            XZ_DEC            0            0K            0
            nvlist            0            0K            0
        zones_data            0            0K            0
          SCSI ENC            0            0K            0
           SCSI sa            0            0K            0
         scsi_pass            0            0K            0
           scsi_da            0            0K            0
            ata_da            0            0K            0
           scsi_ch            0            0K            0
           scsi_cd            0            0K            0
           nvme_da            0            0K            0
           CAM CCB            0            0K            0
     CAM ccb queue            0            0K            0
 CAM I/O Scheduler            0            0K            0
db> show uma
              Zone   Size    Used    Free    Requests  Sleeps  Bucket  Total Mem    XFree
         abd_chunk   4096   52746       4      122833       0       2  216064000        0
zio_buf_comb_131072 131072      91     140        2996       0       1   30277632        0
   mbuf_jumbo_page   4096    1088     690       19448       0     254    7282688        0
     zio_buf_16384  16384      77     324        1431       0       2    6569984        0
       UMA Slabs 0    112   58127       7       58127       0     126    6511008        0
          BUF TRIE    144       0   26516           0       0      62    3818304        0
        malloc-256    256   13248     282       24554       0      62    3463680        0
       malloc-4096   4096      87     317         837       0       2    1654784        0
        malloc-128    128   12722     143       12755       0     126    1646720        0
      mbuf_cluster   2048     508     254         508       0     254    1560576        0
       malloc-4096   4096     323       3         489       0       2    1335296        0
zio_buf_comb_65536  65536       1      19          44       0       1    1310720        0
zio_buf_comb_1048576 1048576       0       1          17       0       1    1048576        0
arc_buf_hdr_t_full    376    2616      24        2669       0      30     992640        0
 zio_data_buf_4096   4096     215      11        1307       0       3     925696        0
        malloc-512    512    1643      69        4178       0      30     876544        0
      zio_buf_4096   4096     142       8         797       0       3     614400        0
              mbuf    256    1347     950       30154       0     254     588032        0
           dnode_t   1016     562      14         583       0      16     585216        0
        malloc-512    512    1027      53        1195       0      30     552960        0
              pbuf   2624       0     210           0       0       2     551040        0
            lkpimm    168       1    3095           1       0      62     520128        0
          lkpicurr    168       2    3094           2       0      62     520128        0
zio_buf_comb_32768  32768       0      15          43       0       1     491520        0
            socket    960      16     492        1106       0     254     487680        0
     FPU_save_area   2432     187       8         242       0       4     474240        0
       malloc-1024   1024     423      25       12989       0      16     458752        0
    dmu_buf_impl_t    408     739     251        2290       0      30     403920        0
         ddt_cache  24824      15       1          15       0       1     397184        0
        RADIX NODE    144    2166     463       29039       0      62     378576        0
zio_data_buf_16384  16384       2      20         627       0       1     360448        0
            THREAD   1824     185       7         232       0       8     350208        0
      malloc-65536  65536       4       1          48       0       1     327680        0
        256 Bucket   2048     139      21         568       0       8     327680        0
       malloc-2048   2048     133      11         167       0       8     294912        0
         zio_cache   1216       6     224       20666       0       9     279680        0
         malloc-64     64    4046     301        9611       0     254     278208        0
         malloc-16     16   16006     494       16101       0     254     264000        0
      malloc-65536  65536       1       3          20       0       1     262144        0
             VNODE    448     502      74         718       0      30     258048        0
        malloc-384    384     612      48        6124       0      30     253440        0
   zfs_znode_cache    464     485      59         493       0      30     252416        0
zfs_btree_leaf_cache   4096      33      25         686       0       2     237568        0
         VM OBJECT    264     825      45       11743       0      30     229680        0
         malloc-32     32    6378     300        6446       0     254     213696        0
         UMA Zones    768     272       2         272       0      16     210432        0
            DEVCTL   1024       0     196          95       0       0     200704        0
 zio_data_buf_8192   8192       0      21          61       0       1     172032        0
  zio_data_buf_512    512      71     233         642       0      30     155648        0
       malloc-4096   4096      36       2         803       0       2     155648        0
          sa_cache    272     485      33         493       0      30     140896        0
      malloc-65536  65536       2       0           2       0       1     131072        0
      malloc-65536  65536       0       2          11       0       1     131072        0
      malloc-32768  32768       3       1          51       0       1     131072        0
      malloc-32768  32768       4       0           4       0       1     131072        0
       malloc-2048   2048      46      18        1734       0       8     131072        0
        malloc-128    128     634     389       13711       0     126     130944        0
             unpcb    256       9     501        1017       0     254     130560        0
       mbuf_packet    256       0     508          69       0     254     130048        0
       S VFS Cache    104     945     225         994       0     126     121680        0
          ksiginfo    112      38    1006          66       0     126     116928        0
      malloc-16384  16384       4       3          14       0       1     114688        0
       malloc-1024   1024      98      14         276       0      16     114688        0
        128 Bucket   1024      54      45         886       0      16     101376        0
          UMA Kegs    384     259       4         259       0      30     100992        0
         malloc-64     64     916     659        4856       0     254     100800        0
         vmem btag     56    1490     298        1490       0     254     100128        0
zio_buf_comb_49152  49152       1       1           2       0       1      98304        0
zio_buf_comb_24576  24576       0       4          18       0       1      98304        0
         MAP ENTRY     96     732     276       39885       0     126      96768        0
        malloc-256    256     183     192        1791       0      62      96000        0
          2 Bucket     32     525    2121       64411       0     254      84672        0
        malloc-128    128     518     133        1470       0     126      83328        0
      malloc-16384  16384       0       5          82       0       1      81920        0
              PROC   1376      34      21         801       0       8      75680        0
         malloc-64     64     630     441        1267       0     254      68544        0
        malloc-128    128     332     195         644       0     126      67456        0
        malloc-128    128     393     134         905       0     126      67456        0
      zio_buf_8192   8192       0       8          51       0       1      65536        0
      malloc-65536  65536       1       0           1       0       1      65536        0
      malloc-65536  65536       1       0           1       0       1      65536        0
      malloc-32768  32768       1       1           2       0       1      65536        0
         64 Bucket    512      63      65         852       0      30      65536        0
        malloc-256    256     194      61         425       0      62      65280        0
         32 Bucket    256      88     167        1113       0      62      65280        0
     zio_buf_12288  12288       0       5          33       0       1      61440        0
         filedesc0   1072      35      14         802       0       8      52528        0
         malloc-32     32     742     896       15249       0     254      52416        0
            ttyinq    160     180     145         540       0      62      52000        0
        malloc-128    128     256     147       29362       0     126      51584        0
           ttyoutq    256      93     102         279       0      62      49920        0
      malloc-16384  16384       3       0           3       0       1      49152        0
       malloc-1024   1024      19      29          32       0      16      49152        0
           pcpu-64     64     454     314         454       0     254      49152        0
          syncache    168       0     264           5       0     254      44352        0
       malloc-8192   8192       4       1          85       0       1      40960        0
       malloc-8192   8192       4       1           5       0       1      40960        0
    zio_link_cache     48       0     840       14203       0     254      40320        0
   reference_cache     48      12     828        2142       0     254      40320        0
         udp_inpcb    424       2      88          51       0      30      38160        0
         malloc-64     64       6     561        6031       0     254      36288        0
         malloc-64     64     139     428         173       0     254      36288        0
         malloc-64     64     255     312        3343       0     254      36288        0
         malloc-64     64       4     563          55       0     254      36288        0
        malloc-128    128     153     126         728       0     126      35712        0
     routing nhops    256       8     127          13       0      62      34560        0
             g_bio    384       0      90       26672       0      30      34560        0
        malloc-384    384      69      21          70       0      30      34560        0
        malloc-384    384      64      26         249       0      30      34560        0
        malloc-256    256       8     127         290       0      62      34560        0
        malloc-256    256      37      98          44       0      62      34560        0
        malloc-256    256      35     100        1025       0      62      34560        0
        malloc-256    256       4     131          35       0      62      34560        0
         TURNSTILE    136     193      59         193       0      62      34272        0
           netlink   2048       0      16          32       0       8      32768        0
 zio_data_buf_2048   2048       1      15           2       0       8      32768        0
 zio_data_buf_1024   1024       2      30           5       0      16      32768        0
       zio_buf_512    512      13      51          40       0      30      32768        0
             NAMEI   1024       2      30       10763       0      16      32768        0
      malloc-32768  32768       1       0           1       0       1      32768        0
      malloc-32768  32768       1       0           1       0       1      32768        0
       malloc-4096   4096       7       1          15       0       2      32768        0
       malloc-2048   2048       3      13          45       0       8      32768        0
       malloc-2048   2048       4      12         215       0       8      32768        0
       malloc-2048   2048       1      15           6       0       8      32768        0
       malloc-1024   1024      12      20          16       0      16      32768        0
       malloc-1024   1024       3      29           3       0      16      32768        0
       malloc-1024   1024       0      32         865       0      16      32768        0
        malloc-512    512       4      60          14       0      30      32768        0
            pcpu-8      8    3634     462        3636       0     254      32768        0
          8 Bucket     80      43     357        1098       0     126      32000        0
              PGRP    120      13     251          29       0     126      31680        0
           VMSPACE    616      19      29         787       0      16      29568        0
         arc_buf_t     32     214     668        3630       0     254      28224        0
          4 Bucket     48      13     575         396       0     254      28224        0
            cpuset    200       7     121           7       0      62      25600        0
 zio_data_buf_6144   6144       0       4           5       0       1      24576        0
       malloc-4096   4096       5       1         139       0       2      24576        0
          rl_entry     40      29     577          35       0     254      24240        0
               PWD     40       9     597          78       0     254      24240        0
           rtentry    168      11     133          13       0      62      24192        0
              pipe    728       5      28         291       0      16      24024        0
             Files     80      66     234        6483       0     126      24000        0
         tcp_inpcb   1312       3      15           7       0       8      23616        0
     zil_lwb_cache    392       1      59           7       0      30      23520        0
        malloc-384    384       9      51           9       0      30      23040        0
        malloc-384    384       3      57           4       0      30      23040        0
        malloc-384    384       1      59           7       0      30      23040        0
        SLEEPQUEUE     88     193      63         193       0     126      22528        0
         hostcache     64       1     314           1       0     254      20160        0
   udp_inpcb ports     32       1     629           6       0     254      20160        0
              ertt     72       3     277           7       0     126      20160        0
         malloc-64     64       3     312           3       0     254      20160        0
         malloc-32     32       8     622          26       0     254      20160        0
         malloc-32     32      83     547         125       0     254      20160        0
         malloc-32     32     143     487        1623       0     254      20160        0
         malloc-32     32      24     606        5120       0     254      20160        0
         malloc-32     32      13     617          58       0     254      20160        0
         16 Bucket    144      54      86         350       0      62      20160        0
             KNOTE    160      11     114          30       0      62      20000        0
         malloc-16     16     474     776        3722       0     254      20000        0
        malloc-256    256       2      73           2       0      62      19200        0
 epoch_record pcpu    256       4      60           4       0      62      16384        0
      malloc-16384  16384       1       0           1       0       1      16384        0
      malloc-16384  16384       1       0           1       0       1      16384        0
      malloc-16384  16384       1       0           1       0       1      16384        0
       malloc-8192   8192       1       1           2       0       1      16384        0
       malloc-8192   8192       2       0           2       0       1      16384        0
       malloc-4096   4096       2       2           3       0       2      16384        0
       malloc-4096   4096       3       1           3       0       2      16384        0
       malloc-2048   2048       1       7           5       0       8      16384        0
       malloc-2048   2048       1       7           1       0       8      16384        0
       malloc-1024   1024       1      15           1       0      16      16384        0
        malloc-512    512       0      32           1       0      30      16384        0
        malloc-512    512       2      30           7       0      30      16384        0
           SMR CPU     32       7     504           7       0     254      16352        0
              kenv    258       2      58         706       0      30      15480        0
 zio_data_buf_1536   1536       0      10           2       0       8      15360        0
              vmem   1856       1       7           1       0       8      14848        0
             ripcb    392       1      35           1       0      30      14112        0
 zio_data_buf_3072   3072       1       3           3       0       4      12288        0
        SMR SHARED     24       7     504           7       0     254      12264        0
    ertt_txseginfo     40       1     302         317       0     254      12120        0
   tcp_inpcb ports     32       1     377           1       0     254      12096        0
         malloc-32     32       7     371           7       0     254      12096        0
     zil_zcw_cache     80       0     150           6       0     126      12000        0
         malloc-16     16       1     749         199       0     254      12000        0
         malloc-16     16      26     724         133       0     254      12000        0
         malloc-16     16     105     645       28138       0     254      12000        0
         malloc-16     16       2     748           3       0     254      12000        0
         malloc-16     16     190     560        7474       0     254      12000        0
         malloc-16     16       9     741          39       0     254      12000        0
       L VFS Cache    320       0      36           1       0      30      11520        0
        malloc-384    384       1      29           1       0      30      11520        0
       Mountpoints   2816       2       2           2       0       4      11264        0
        taskq_zone    160       0      63         557       0      62      10080        0
       malloc-8192   8192       1       0           1       0       1       8192        0
       malloc-8192   8192       1       0           1       0       1       8192        0
       malloc-8192   8192       1       0           1       0       1       8192        0
      vtnet_tx_hdr     24       1     333        9453       0     254       8016        0
           pcpu-16     16       4     252           4       0     254       4096        0
       UMA Slabs 1    176       7      15           7       0      62       3872        0
        KMAP ENTRY     96       9      30          10       0       0       3744        0
            da_ccb    544       0       0           0       0      16          0        0
           ada_ccb    272       0       0           0       0      30          0        0
             swblk    136       0       0           0       0      62          0        0
          swpctrie    144       0       0           0       0      62          0        0
tfo_ccache_entries     80       0       0           0       0     126          0        0
               tfo      4       0       0           0       0     254          0        0
          sackhole     32       0       0           0       0     254          0        0
               ipq     56       0       0           0       0     254          0        0
   tcp_log_id_node    120       0       0           0       0     126          0        0
 tcp_log_id_bucket    176       0       0           0       0      62          0        0
           tcp_log    416       0       0           0       0     254          0        0
          tcpreass     48       0       0           0       0     254          0        0
udplite_inpcb ports     32       0       0           0       0     254          0        0
     udplite_inpcb    424       0       0           0       0      30          0        0
       ripcb ports     32       0       0           0       0     254          0        0
    IPsec SA lft_c     16       0       0           0       0     254          0        0
            itimer    352       0       0           0       0      30          0        0
       sio_cache_2    168       0       0           0       0      62          0        0
       sio_cache_1    152       0       0           0       0      62          0        0
       sio_cache_0    136       0       0           0       0      62          0        0
arc_buf_hdr_t_l2only     96       0       0           0       0     126          0        0
zio_buf_comb_16777216 16777216       0       0           0       0       1          0        0
zio_buf_comb_12582912 12582912       0       0           0       0       1          0        0
zio_buf_comb_8388608 8388608       0       0           0       0       1          0        0
zio_buf_comb_6291456 6291456       0       0           0       0       1          0        0
zio_buf_comb_4194304 4194304       0       0           0       0       1          0        0
zio_buf_comb_3145728 3145728       0       0           0       0       1          0        0
zio_buf_comb_2097152 2097152       0       0           0       0       1          0        0
zio_buf_comb_1572864 1572864       0       0           0       0       1          0        0
zio_buf_comb_786432 786432       0       0           0       0       1          0        0
zio_buf_comb_524288 524288       0       0           0       0       1          0        0
zio_buf_comb_393216 393216       0       0           0       0       1          0        0
zio_buf_comb_262144 262144       0       0           0       0       1          0        0
zio_buf_comb_196608 196608       0       0           0       0       1          0        0
zio_buf_comb_98304  98304       0       0           0       0       1          0        0
zio_data_buf_12288  12288       0       0           0       0       1          0        0
      zio_buf_6144   6144       0       0           0       0       1          0        0
      zio_buf_3072   3072       0       0           0       0       4          0        0
      zio_buf_2048   2048       0       0           0       0       8          0        0
      zio_buf_1536   1536       0       0           0       0       8          0        0
      zio_buf_1024   1024       0       0           0       0      16          0        0
   ddt_entry_cache    392       0       0           0       0      30          0        0
brt_pending_entry_cache    160       0       0           0       0      62          0        0
   brt_entry_cache     40       0       0           0       0     254          0        0
metaslab_alloc_trace_cache     72       0       0           0       0     126          0        0
            AIOLIO    272       0       0           0       0      30          0        0
             AIOCB    552       0       0           0       0      16          0        0
               AIO    208       0       0           0       0      62          0        0
           DIRHASH   1024       0       0           0       0      16          0        0
        TMPFS node    232       0       0           0       0      62          0        0
           NCLNODE    608       0       0           0       0      16          0        0
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
            clpbuf   2624       0       0           0       0       4          0        0
            vnpbuf   2624       0       0           0       0      16          0        0
           nfspbuf   2624       0       0           0       0       4          0        0
            swwbuf   2624       0       0           0       0       2          0        0
            swrbuf   2624       0       0           0       0       4          0        0
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


Syzkaller reproducer:
# {Threaded:false Repeat:true RepeatTimes:0 Procs:2 Slowdown:1 Sandbox: SandboxArg:0 Leak:false NetInjection:false NetDevices:false NetReset:false Cgroups:false BinfmtMisc:false CloseFDs:false KCSAN:false DevlinkPCI:false NicVF:false USB:false VhciInjection:false Wifi:false IEEE802154:false Sysctl:false Swap:false UseTmpDir:false HandleSegv:false Repro:false Trace:false LegacyOptions:{Collide:false Fault:false FaultCall:0 FaultNth:0}}
open(&(0x7f0000000440)='./file0\x00', 0x89901e1cbd019ae4, 0x0)
extattr_set_file(&(0x7f0000000100)='./file0\x00', 0x1, &(0x7f0000000080)='JC\xfd\x9b\x04\xfa-!b\x1e\x03\x00\x00\x8e\x84\xc4%\xac\r\xab\xd7\xb6\xdb\x18g\"\xf0\t0\v8#\xcc\x16Z\xf6\xd7\x1e\x9c\xa0p}\xe6\xf6\x03hz', 0x0, 0x0)
extattr_get_link(&(0x7f0000000000)='./file0\x00', 0x1, &(0x7f0000000140)='..\x00', 0x0, 0x0)


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

void execute_one(void)
{
  memcpy((void*)0x20000440, "./file0\000", 8);
  syscall(SYS_open, /*file=*/0x20000440ul, /*flags=*/0x89901e1cbd019ae4ul,
          /*mode=*/0ul);
  memcpy((void*)0x20000100, "./file0\000", 8);
  memcpy((void*)0x20000080,
         "JC\375\233\004\372-!b\036\003\000\000\216\204\304%"
         "\254\r\253\327\266\333\030g\"\360\t0\v8#"
         "\314\026Z\366\327\036\234\240p}\346\366\003hz",
         47);
  syscall(SYS_extattr_set_file, /*file=*/0x20000100ul, /*attrnamespace=*/1ul,
          /*attrname=*/0x20000080ul, /*data=*/0ul, /*nbytes=*/0ul);
  memcpy((void*)0x20000000, "./file0\000", 8);
  memcpy((void*)0x20000140, "..\000", 3);
  syscall(SYS_extattr_get_link, /*file=*/0x20000000ul, /*attrnamespace=*/1ul,
          /*attrname=*/0x20000140ul, /*data=*/0ul, /*nbytes=*/0ul);
}
int main(void)
{
  syscall(SYS_mmap, /*addr=*/0x20000000ul, /*len=*/0x1000000ul, /*prot=*/7ul,
          /*flags=*/0x1012ul, /*fd=*/-1, /*offset=*/0ul);
  for (procid = 0; procid < 2; procid++) {
    if (fork() == 0) {
      loop();
    }
  }
  sleep(1000000);
  return 0;
}


