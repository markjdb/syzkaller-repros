Syzkaller hit 'Fatal trap NUM: general protection fault while in kernel mode' bug.

Fatal trap 9: general protection fault while in kernel mode
Memory modified after free 0xfffff80003db8200 (256, malloc-256, 0xffffffff81f576a0) + 96 = 0
panic: Memory modified after free 0xfffff80003db8200 (256, malloc-256, in_multi) + 96 = 0

cpuid = 1
time = 1702761974
KDB: stack backtrace:
db_trace_self_wrapper() at db_trace_self_wrapper+0x49/frame 0xfffffe00619df7d0
vpanic() at vpanic+0x1a4/frame 0xfffffe00619df910
panic() at panic+0x43/frame 0xfffffe00619df970
mtrash_ctor() at mtrash_ctor+0x1eb/frame 0xfffffe00619df9d0
item_ctor() at item_ctor+0x23b/frame 0xfffffe00619dfa20
malloc() at malloc+0xaf/frame 0xfffffe00619dfa60
in_joingroup_locked() at in_joingroup_locked+0x435/frame 0xfffffe00619dfb20
inp_setmoptions() at inp_setmoptions+0x19c4/frame 0xfffffe00619dfcc0
sosetopt() at sosetopt+0x116/frame 0xfffffe00619dfd40
kern_setsockopt() at kern_setsockopt+0x14a/frame 0xfffffe00619dfdc0
sys_setsockopt() at sys_setsockopt+0x33/frame 0xfffffe00619dfdf0
amd64_syscall() at amd64_syscall+0x26b/frame 0xfffffe00619dff30
fast_syscall_common() at fast_syscall_common+0xf8/frame 0xfffffe00619dff30
--- syscall (0, FreeBSD ELF64, syscall), rip = 0x2474da, rsp = 0x820f920f8, rbp = 0x820f92150 ---
KDB: enter: panic
[ thread pid 20285 tid 100122 ]
Stopped at      kdb_enter+0x6b: movq    $0,0x124ff9a(%rip)
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
rdx         0xffffffff818face1
rbx         0xffffffff8194c4b2  do_execve.fexecv_proc_title+0x6df2
rsp         0xfffffe00619df7b0
rbp         0xfffffe00619df7d0
rsi                        0x1
rdi                          0
r8                           0
r9          0x8080808080808080
r10         0xfffffe00619df680
r11         0xfffffffffffff59c
r12         0xffffffff81e27c90  ddb_dbbe
r13                      0x100
r14         0xffffffff8194c4b2  do_execve.fexecv_proc_title+0x6df2
r15                          0
rip         0xffffffff81005ceb  kdb_enter+0x6b
rflags                    0x86
kdb_enter+0x6b: movq    $0,0x124ff9a(%rip)
db> show proc
Process 20285 (syz-executor4210095) at 0xfffffe0051d7c020:
 state: NORMAL
 uid: 0  gids: 0, 0, 5
 parent: pid 797 at 0xfffffe0051d7bac0
 ABI: FreeBSD ELF64
 flag: 0x10000000  flag2: 0
 arguments: /root/syz-executor4210095866
 reaper: 0xfffffe0004213040 reapsubtree: 1
 sigparent: 20
 vmspace: 0xfffff80003e344d0
   (map 0xfffff80003e344d0)
   (map.pmap 0xfffff80003e34590)
   (pmap 0xfffff80003e34600)
 threads: 1
100122                   Run     CPU 1                       syz-executor4210095
db> ps
  pid  ppid  pgrp   uid  state   wmesg   wchan               cmd
20285   797   795     0  R       CPU 1                       syz-executor4210095
20284   796   795     0  RE      CPU 0                       syz-executor4210095
  797   795   795     0  S       nanslp  0xffffffff8223d161  syz-executor4210095
  796   795   795     0  S       nanslp  0xffffffff8223d161  syz-executor4210095
  795   793   795     0  Ss      nanslp  0xffffffff8223d160  syz-executor4210095
  793   762   793     0  Ss      select  0xfffff8002a129840  sshd
  780     1   780     0  Ss+     ttyin   0xfffff800036c50b0  getty
  777     1   777     0  Ss      select  0xfffff8002a129bc0  logger
  771     1    16     0  S+      piperd  0xfffffe0051b7fe38  logger
  770   769    16     0  S+      nanslp  0xffffffff8223d160  sleep
  769     1    16     0  S+      wait    0xfffffe0051d58ac0  sh
  766     1   766     0  Ss      nanslp  0xffffffff8223d160  cron
  762     1   762     0  Ss      select  0xfffff8002a129c40  sshd
  662     1   662     0  Ss      kqread  0xfffff800034afa00  syslogd
  463     1   463     0  Ss      select  0xfffff80003cf7940  devd
  360     1   360    65  Ss      select  0xfffff80003cf7840  dhclient
  276     1   276     0  Ss      select  0xfffff8002a129e40  dhclient
  273     1   273     0  Ss      select  0xfffff80003dd8bc0  dhclient
   15     0     0     0  DL      syncer  0xffffffff823239a8  [syncer]
    9     0     0     0  DL      vlruwt  0xfffffe000431eb00  [vnlru]
    8     0     0     0  DL      (threaded)                  [bufdaemon]
100063                   D       psleep  0xffffffff823229b0  [bufdaemon]
100068                   D       -       0xffffffff81e03100  [bufspacedaemon-0]
100076                   D       sdflush 0xfffff800038aece8  [/ worker]
    7     0     0     0  DL      psleep  0xffffffff82377c10  [vmdaemon]
    6     0     0     0  DL      (threaded)                  [pagedaemon]
100061                   D       psleep  0xffffffff82360078  [dom0]
100064                   D       launds  0xffffffff82360084  [laundry: dom0]
100066                   D       umarcl  0xffffffff814fb3b0  [uma]
    5     0     0     0  DL      -       0xffffffff8203e960  [rand_harvestq]
    4     0     0     0  DL      (threaded)                  [cam]
100042                   D       -       0xffffffff82010240  [doneq0]
100043                   D       -       0xffffffff820101c0  [async]
100060                   D       -       0xffffffff82010090  [scanner]
    3     0     0     0  DL      (threaded)                  [crypto]
100039                   D       crypto_ 0xffffffff8235d530  [crypto]
100040                   D       crypto_ 0xfffff800034afe30  [crypto returns 0]
100041                   D       crypto_ 0xfffff800034afe80  [crypto returns 1]
   14     0     0     0  DL      seqstat 0xfffff80003780088  [sequencer 00]
   13     0     0     0  DL      (threaded)                  [geom]
100033                   D       -       0xffffffff821f8b40  [g_event]
100034                   D       -       0xffffffff821f8b48  [g_up]
100035                   D       -       0xffffffff821f8b50  [g_down]
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
    1     0     1     0  SLs     wait    0xfffffe0004213040  [init]
   10     0     0     0  DL      audit_w 0xffffffff8235da20  [audit]
    0     0     0     0  DLs     (threaded)                  [kernel]
100000                   D       swapin  0xffffffff821f90c0  [swapper]
100005                   D       -       0xfffff800034dcd00  [softirq_0]
100006                   D       -       0xfffff800034dcc00  [softirq_1]
100007                   D       -       0xfffff800034dcb00  [if_io_tqg_0]
100008                   D       -       0xfffff800034dca00  [if_io_tqg_1]
100009                   D       -       0xfffff800034dc900  [if_config_tqg_0]
100010                   D       -       0xfffff800034b1000  [pci_hp taskq]
100011                   D       -       0xfffff800034b0e00  [kqueue_ctx taskq]
100014                   D       -       0xfffff800034b0b00  [thread taskq]
100016                   D       -       0xfffff800034b0900  [aiod_kick taskq]
100017                   D       -       0xfffff800034b0800  [deferred_unmount ta]
100018                   D       -       0xfffff800034b0700  [inm_free taskq]
100019                   D       -       0xfffff800034b0600  [in6m_free taskq]
100020                   D       -       0xfffff800034b0500  [linuxkpi_irq_wq]
100021                   D       -       0xfffff800034b0400  [linuxkpi_short_wq_0]
100022                   D       -       0xfffff800034b0400  [linuxkpi_short_wq_1]
100023                   D       -       0xfffff800034b0400  [linuxkpi_short_wq_2]
100024                   D       -       0xfffff800034b0400  [linuxkpi_short_wq_3]
100025                   D       -       0xfffff800034b0300  [linuxkpi_long_wq_0]
100026                   D       -       0xfffff800034b0300  [linuxkpi_long_wq_1]
100027                   D       -       0xfffff800034b0300  [linuxkpi_long_wq_2]
100028                   D       -       0xfffff800034b0300  [linuxkpi_long_wq_3]
100032                   D       -       0xfffff800034b0200  [firmware taskq]
100037                   D       -       0xfffff800034b0000  [crypto_0]
100038                   D       -       0xfffff800034b0000  [crypto_1]
100047                   D       -       0xfffff80003921300  [vtnet0 rxq 0]
100048                   D       -       0xfffff80003921200  [vtnet0 txq 0]
100054                   D       -       0xffffffff81b19151  [deadlkres]
100055                   D       -       0xfffff80003921100  [acpi_task_0]
100056                   D       -       0xfffff80003921100  [acpi_task_1]
100057                   D       -       0xfffff80003921100  [acpi_task_2]
100059                   D       -       0xfffff800034afd00  [CAM taskq]
db> show all locks
Process 20285 (syz-executor4210095) thread 0xfffff80003f29000 (100122)
exclusive sleep mutex if_addr_lock (if_addr_lock) r = 0 (0xfffff8000392b1a0) locked @ /root/freebsd/sys/netinet/in_mcast.c:538
exclusive sleep mutex in_multi_list_mtx (in_multi_list_mtx) r = 0 (0xffffffff82326990) locked @ /root/freebsd/sys/netinet/in_mcast.c:537
exclusive sx in_multi_sx (in_multi_sx) r = 0 (0xffffffff823269b0) locked @ /root/freebsd/sys/netinet/in_mcast.c:2039
db> show malloc
              Type        InUse        MemUse     Requests
         sysctloid        29973         1763K        30015
              kobj          323         1292K          486
            newblk          847         1236K          859
            devbuf         1333         1144K         1350
          vfscache            3         1025K            3
          inodedep           56          533K           72
               pcb           17          525K           46
         ufs_quota            1          512K            1
          vfs_hash            1          512K            1
           callout            2          512K            2
              intr            4          472K            4
         vnet_data            2          224K            2
          acpitask            1          224K            1
           subproc           90          157K        20342
            bus-sc           31          148K         1070
           tidhash            3          141K            3
           pagedep           18          133K           25
        tfo_ccache            1          128K            1
          IP reass            1          128K            1
               sem            4          106K            4
        gtaskqueue           18           98K           18
            DEVFS1           91           91K          103
            linker          230           87K          271
               bus          962           78K         3524
          mtx_pool            2           72K            2
          syncache            1           68K            1
     NFSD srvcache            3           68K            3
       ddb_capture            1           64K            1
            module          495           62K          495
            acpica          420           39K        64280
              temp           17           37K         1504
               LRO            2           33K            2
         hostcache            1           32K            1
               shm            1           32K            1
               msg            4           30K            4
              umtx          224           28K          224
            DEVFS3          110           28K          126
            kbdmux            5           28K            5
           kdtrace          132           27K        20413
        DEVFS_RULE           61           22K           61
               BPF           10           18K           10
           ithread           92           17K           92
         ufs_mount            4           17K            5
              proc            3           17K            3
            KTRACE          100           13K          100
           devstat            6           13K            6
      eventhandler          140           12K          140
              rman           99           12K          524
              kenv           90           12K           90
            ifaddr           29           11K           29
              GEOM           61           11K          494
          routetbl           43           10K          131
         bmsafemap            3            9K           69
               rpc            4            9K            4
              UART           12            9K           12
             shmfd            1            8K            1
       pfs_vncache            1            8K            1
     audit_evclass          238            8K          300
              vmem            3            7K            3
         taskqueue           56            6K          143
            sglist            3            6K            3
            diradd           40            5K           76
         pfs_nodes           20            5K           20
             hhook           15            5K           17
            kqueue           37            5K        20289
       ufs_dirhash           24            5K           24
             ifnet            3            5K            3
           io_apic            1            4K            1
               tty            4            4K            4
          filedesc            1            4K            1
             evdev            4            4K            4
               UMA          240            4K          240
              cred           15            4K          276
           lltable           10            3K           10
           acpisem           21            3K           21
         toponodes           10            3K           10
           uidinfo            3            3K            8
            plimit            9            3K          192
           pwddesc           33            3K        20286
        local_apic            1            2K            1
         ipsec-saq            2            2K            2
             clone            8            2K            8
           CAM DEV            1            2K            2
         proc-args           50            2K        21211
               msi           13            2K           13
           session           13            2K           29
             lockf           15            2K           18
          pci_link           16            2K           16
            Unitno           25            2K           47
             selfd           23            2K       279140
           acpidev           22            2K           22
       ether_multi           17            2K        38941
             mkdir            9            2K           20
         CAM queue            2            2K            5
           softdep            1            1K            1
       ipsecpolicy            1            1K            1
            sahead            1            1K            1
          secasvar            1            1K            1
       vnodemarker            2            1K           10
            select            8            1K           59
      NFSD session            1            1K            1
         in6_multi            9            1K            9
         newdirblk            7            1K           10
          indirdep            3            1K            3
            CC Mem            3            1K            7
             nhops            6            1K            6
              pfil            6            1K            6
             mount           16            1K           89
            crypto            4            1K            4
            isadev            5            1K            5
           CAM XPT           11            1K           12
           netlink            2            1K           44
          in_multi            2            1K        19465
              cdev            2            1K            2
 encap_export_host            8            1K            8
               osd            8            1K           45
            ip6ndp            3            1K            3
    chacha20random            1            1K            1
            biobuf            1            1K            1
        CAM periph            2            1K           14
               MCA            2            1K            2
            dirrem            1            1K           21
               mld            2            1K            2
              igmp            2            1K            2
            vnodes            1            1K            1
          procdesc            2            1K           20
      NFSD lckfile            1            1K            1
     NFSD V4client            1            1K            1
             DEVFS            9            1K           10
       inpcbpolicy            7            1K        19547
            feeder            7            1K            7
        loginclass            3            1K            7
            prison            6            1K            6
       lkpikmalloc            5            1K            6
            apmdev            1            1K            1
          atkbddev            2            1K            2
       ip_moptions            2            1K        19488
        in_mfilter            2            1K        19488
          pmchooks            1            1K            1
            DEVFSP            2            1K            2
           CAM SIM            1            1K            1
            soname            4            1K          957
          filecaps            4            1K           98
          nexusdev            6            1K            6
               tun            3            1K            3
          freework            1            1K            9
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
           jblocks            0            0K            0
          savedino            0            0K           11
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
          freefile            0            0K            7
          freeblks            0            0K            8
          freefrag            0            0K            1
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
            statfs            0            0K           11
     namei_tracker            0            0K            0
       export_host            0            0K            0
        cl_savebuf            0            0K            3
               aio            0            0K            0
               lio            0            0K            0
               acl            0            0K            0
          mbuf_tag            0            0K            0
              ktls            0            0K            0
              accf            0            0K            0
               pts            0            0K            0
           timerfd            0            0K            0
               iov            0            0K         6384
          ioctlops            0            0K           69
           eventfd            0            0K            0
           Witness            0            0K            0
          terminal            0            0K            0
             stack            0            0K            0
              sbuf            0            0K          310
          firmware            0            0K            0
        compressor            0            0K            0
              SWAP            0            0K            0
         sysctltmp            0            0K          525
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
         raid_data            0            0K           72
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
   mbuf_jumbo_page   4096    1088     944       29209       0     254    8323072        0
          BUF TRIE    144     183   13341         534       0      62    1947456        0
       malloc-4096   4096     363       5       20912       0       2    1507328        0
        malloc-128    128    9980     126       10987       0     126    1293568        0
      mbuf_cluster   2048     508       0         508       0     254    1040384        0
              mbuf    256    1347     950      156686       0     254     588032        0
        malloc-512    512    1027      53        1030       0      30     552960        0
      malloc-65536  65536       6       2           8       0       1     524288        0
            lkpimm    168       1    3095           1       0      62     520128        0
          lkpicurr    168       2    3094           2       0      62     520128        0
              pbuf   2624       0     198           0       0       2     519552        0
            socket    960      18     490       20551       0     254     487680        0
       UMA Slabs 0    112    3316      26        3316       0     126     374304        0
        RADIX NODE    144    1776     405       87635       0      62     314064        0
       malloc-2048   2048     134      10         136       0       8     294912        0
        256 Bucket   2048     115      21         418       0       8     278528        0
     FPU_save_area   2432      99       6         136       0       4     255360        0
         VM OBJECT    264     863      67      167638       0      30     245520        0
             VNODE    448     503      37         512       0      30     241920        0
        malloc-256    256     848      82         871       0      62     238080        0
         malloc-64     64    3279     312       23818       0     254     229824        0
         malloc-16     16   12658     592       14013       0     254     212000        0
            THREAD   1824      97      15         126       0       8     204288        0
            DEVCTL   1024       0     192          90       0       0     196608        0
         malloc-32     32    4342     824       24033       0     254     165312        0
         UMA Zones    768     212       2         212       0      16     164352        0
       FFS2 dinode    256     483      87         490       0      62     145920        0
      malloc-65536  65536       0       2          11       0       1     131072        0
      malloc-65536  65536       1       1          45       0       1     131072        0
      malloc-32768  32768       3       1           7       0       1     131072        0
      malloc-32768  32768       3       1           4       0       1     131072        0
             unpcb    256       9     501         974       0     254     130560        0
       mbuf_packet    256       0     508          69       0     254     130048        0
       S VFS Cache    104     942     228         991       0     126     121680        0
          ksiginfo    112      34    1010          62       0     126     116928        0
       malloc-1024   1024     104       8         117       0      16     114688        0
         FFS inode    200     483      77         490       0      62     112000        0
         MAP ENTRY     96     732     402      273580       0     126     108864        0
        malloc-128    128     546     229        1200       0     126      99200        0
        128 Bucket   1024      46      37         770       0      16      84992        0
        malloc-256    256     143     172       19699       0      62      80640        0
          UMA Kegs    384     199       4         199       0      30      77952        0
              PROC   1376      33      22       20285       0       8      75680        0
         64 Bucket    512      79      65        4917       0      30      73728        0
        malloc-128    128     298     229         411       0     126      67456        0
        malloc-128    128     384     143       29920       0     126      67456        0
      malloc-65536  65536       1       0           1       0       1      65536        0
      malloc-32768  32768       2       0           2       0       1      65536        0
           ttyoutq    256      93     162         279       0      62      65280        0
         filedesc0   1072      34      22       20286       0       8      60032        0
        malloc-384    384     117      33         299       0      30      57600        0
         malloc-64     64      85     734      299499       0     254      52416        0
         malloc-64     64     458     361         692       0     254      52416        0
            ttyinq    160     180     145         540       0      62      52000        0
         vmem btag     56     701     223         701       0     254      51744        0
        malloc-128    128     278     125         337       0     126      51584        0
        malloc-128    128      16     387       19479       0     126      51584        0
        malloc-256    256      57     138         148       0      62      49920        0
        malloc-256    256      76     119         377       0      62      49920        0
        malloc-256    256     108      87         517       0      62      49920        0
         32 Bucket    256      50     145       11760       0      62      49920        0
           DIRHASH   1024      33      15          33       0      16      49152        0
             NAMEI   1024       0      48       10719       0      16      49152        0
      malloc-16384  16384       0       3          12       0       1      49152        0
             g_bio    384       0     120        4668       0      30      46080        0
          syncache    168       0     264           5       0     254      44352        0
       malloc-8192   8192       5       0          33       0       1      40960        0
       malloc-4096   4096       9       1          10       0       2      40960        0
           VMSPACE    616      19      47       20272       0      16      40656        0
              pipe    728       5      50         291       0      16      40040        0
         udp_inpcb    424       3      87       19539       0      30      38160        0
         malloc-64     64      17     550       19584       0     254      36288        0
         malloc-64     64      21     546          21       0     254      36288        0
         malloc-64     64     362     205       19861       0     254      36288        0
         malloc-64     64     301     266       28064       0     254      36288        0
         malloc-64     64       5     562          50       0     254      36288        0
        malloc-128    128      28     251          92       0     126      35712        0
        malloc-128    128      12     267          17       0     126      35712        0
     routing nhops    256       8     127          13       0      62      34560        0
        malloc-384    384      55      35          71       0      30      34560        0
        malloc-256    256      27     108         576       0      62      34560        0
        malloc-256    256      63      72         178       0      62      34560        0
        malloc-256    256      10     125         283       0      62      34560        0
           netlink   2048       0      16          32       0       8      32768        0
      malloc-32768  32768       1       0           1       0       1      32768        0
      malloc-32768  32768       0       1          48       0       1      32768        0
      malloc-16384  16384       2       0           2       0       1      32768        0
       malloc-8192   8192       3       1           4       0       1      32768        0
       malloc-2048   2048       3      13           3       0       8      32768        0
       malloc-2048   2048       2      14           7       0       8      32768        0
       malloc-2048   2048       3      13           3       0       8      32768        0
       malloc-2048   2048       2      14         255       0       8      32768        0
       malloc-1024   1024       2      30          50       0      16      32768        0
       malloc-1024   1024       4      28           4       0      16      32768        0
       malloc-1024   1024       4      28         867       0      16      32768        0
       malloc-1024   1024       4      28          14       0      16      32768        0
       malloc-1024   1024      11      21         135       0      16      32768        0
       malloc-1024   1024       2      30           2       0      16      32768        0
       malloc-1024   1024       9      23          14       0      16      32768        0
        malloc-512    512       4      60         139       0      30      32768        0
        malloc-512    512       9      55           9       0      30      32768        0
        malloc-512    512       5      59          46       0      30      32768        0
           pcpu-64     64     449      63         449       0     254      32768        0
    ertt_txseginfo     40       1     807       19787       0     254      32320        0
          8 Bucket     80      38     362        1112       0     126      32000        0
              PGRP    120      13     251          29       0     126      31680        0
            clpbuf   2624       0      12          32       0       4      31488        0
            pcpu-8      8    3169     415        3171       0     254      28672        0
         malloc-32     32     267     615         388       0     254      28224        0
         16 Bucket    144      41     155         500       0      62      28224        0
          4 Bucket     48      10     578          36       0     254      28224        0
         TURNSTILE    136     113      76         113       0      62      25704        0
            cpuset    200       7     121           7       0      62      25600        0
       malloc-4096   4096       3       3          10       0       2      24576        0
       malloc-4096   4096       4       2          15       0       2      24576        0
          rl_entry     40      25     581          31       0     254      24240        0
               PWD     40       9     597          78       0     254      24240        0
           rtentry    168      11     133          13       0      62      24192        0
             Files     80      67     233       25914       0     126      24000        0
         tcp_inpcb   1312       3      15           7       0       8      23616        0
        malloc-384    384      11      49          14       0      30      23040        0
        malloc-384    384       7      53          10       0      30      23040        0
        malloc-384    384      14      46          18       0      30      23040        0
        SLEEPQUEUE     88     113     143         113       0     126      22528        0
         hostcache     64       1     314           1       0     254      20160        0
              ertt     72       3     277           7       0     126      20160        0
         malloc-32     32      74     556          74       0     254      20160        0
         malloc-32     32      26     604          75       0     254      20160        0
         malloc-32     32      53     577         689       0     254      20160        0
         malloc-32     32      24     606        5015       0     254      20160        0
         malloc-32     32      31     599       19615       0     254      20160        0
          2 Bucket     32      49     581         314       0     254      20160        0
             KNOTE    160      11     114          31       0      62      20000        0
 epoch_record pcpu    256       4      60           4       0      62      16384        0
      malloc-16384  16384       1       0           1       0       1      16384        0
      malloc-16384  16384       1       0           1       0       1      16384        0
      malloc-16384  16384       0       1          64       0       1      16384        0
      malloc-16384  16384       1       0           1       0       1      16384        0
       malloc-8192   8192       1       1           2       0       1      16384        0
       malloc-8192   8192       2       0           2       0       1      16384        0
       malloc-4096   4096       0       4           3       0       2      16384        0
       malloc-4096   4096       1       3           2       0       2      16384        0
       malloc-2048   2048       0       8          12       0       8      16384        0
       malloc-2048   2048       1       7          25       0       8      16384        0
       malloc-2048   2048       2       6           2       0       8      16384        0
        malloc-512    512       0      32           5       0      30      16384        0
        malloc-512    512       1      31           1       0      30      16384        0
           SMR CPU     32       7     504           7       0     254      16352        0
         malloc-16     16      11     989       19483       0     254      16000        0
              kenv    258       2      58         706       0      30      15480        0
              vmem   1856       1       7           1       0       8      14848        0
             ripcb    392       1      35           1       0      30      14112        0
        SMR SHARED     24       7     504           7       0     254      12264        0
   udp_inpcb ports     32       1     377           6       0     254      12096        0
   tcp_inpcb ports     32       1     377           1       0     254      12096        0
         malloc-32     32      14     364          59       0     254      12096        0
         malloc-16     16      26     724         126       0     254      12000        0
         malloc-16     16     260     490         387       0     254      12000        0
         malloc-16     16      13     737          19       0     254      12000        0
         malloc-16     16     179     571        2034       0     254      12000        0
         malloc-16     16      28     722       28150       0     254      12000        0
       L VFS Cache    320       0      36           1       0      30      11520        0
        malloc-384    384       1      29           1       0      30      11520        0
       Mountpoints   2816       2       2           2       0       4      11264        0
       malloc-8192   8192       1       0           1       0       1       8192        0
       malloc-8192   8192       1       0          42       0       1       8192        0
       malloc-8192   8192       1       0           1       0       1       8192        0
       malloc-8192   8192       1       0           1       0       1       8192        0
       malloc-4096   4096       1       1           1       0       2       8192        0
       malloc-4096   4096       1       1           1       0       2       8192        0
      vtnet_tx_hdr     24       1     333       28914       0     254       8016        0
         malloc-16     16       8     492           8       0     254       8000        0
           pcpu-16     16       4     252           4       0     254       4096        0
       UMA Slabs 1    176       6      16           6       0      62       3872        0
        KMAP ENTRY     96       9      30          10       0       0       3744        0
             swblk    136       0       0           0       0      62          0        0
          swpctrie    144       0       0           0       0      62          0        0
       FFS1 dinode    128       0       0           0       0     126          0        0
            da_ccb    544       0       0           0       0      16          0        0
           ada_ccb    272       0       0           0       0      30          0        0
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
            AIOLIO    272       0       0           0       0      30          0        0
             AIOCB    552       0       0           0       0      16          0        0
               AIO    208       0       0           0       0      62          0        0
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
            vnpbuf   2624       0       0           0       0      16          0        0
           nfspbuf   2624       0       0           0       0       4          0        0
            swwbuf   2624       0       0           0       0       2          0        0
            swrbuf   2624       0       0           0       0       4          0        0
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
      malloc-16384  16384       0       0           0       0       1          0        0
      malloc-16384  16384       0       0           0       0       1          0        0
        malloc-512    512       0       0           0       0      30          0        0
        malloc-512    512       0       0           0       0      30          0        0
        malloc-384    384       0       0           0       0      30          0        0
        malloc-384    384       0       0           0       0      30          0        0
           pcpu-32     32       0       0           0       0     254          0        0
            pcpu-4      4       0       0           0       0     254          0        0
            fakepg    104       0       0           0       0     126          0        0
          UMA Hash    256       0       0           0       0      62          0        0


Syzkaller reproducer:
# {Threaded:false Repeat:true RepeatTimes:0 Procs:2 Slowdown:1 Sandbox: SandboxArg:0 Leak:false NetInjection:false NetDevices:false NetReset:false Cgroups:false BinfmtMisc:false CloseFDs:false KCSAN:false DevlinkPCI:false NicVF:false USB:false VhciInjection:false Wifi:false IEEE802154:false Sysctl:false Swap:false UseTmpDir:false HandleSegv:false Repro:false Trace:false LegacyOptions:{Collide:false Fault:false FaultCall:0 FaultNth:0}}
r0 = socket$inet_udp(0x2, 0x2, 0x0)
setsockopt$inet_mreq(r0, 0x0, 0xc, &(0x7f0000000000)={@multicast2, @loopback}, 0x8)


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
  res = syscall(SYS_socket, /*domain=*/2ul, /*type=*/2ul, /*proto=*/0);
  if (res != -1)
    r[0] = res;
  *(uint32_t*)0x20000000 = htobe32(0xe0000002);
  *(uint32_t*)0x20000004 = htobe32(0x7f000001);
  syscall(SYS_setsockopt, /*fd=*/r[0], /*level=*/0, /*optname=*/0xc,
          /*optval=*/0x20000000ul, /*optlen=*/8ul);
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


