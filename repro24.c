Syzkaller hit 'Fatal trap 9: general protection fault in set_user_ldt_rv' bug.

Fatal trap 9: general protection fault while in kernel mode
cpuid = 1; apic id = 01
instruction pointer	= 0x20:0xffffffff81801263
stack pointer	        = 0x0:0xfffffe00517fa780
frame pointer	        = 0x0:0xfffffe00517fa790
code segment		= base 0x0, limit 0xfffff, type 0x1b
			= DPL 0, pres 1, long 1, def32 0, gran 1
processor eflags	= resume, IOPL = 0
current process		= 719 (syz-executor4025265)
trap number		= 9
panic: general protection fault
cpuid = 1
time = 1622850540
KDB: stack backtrace:
db_trace_self_wrapper() at db_trace_self_wrapper+0x47/frame 0xfffffe00517fa450
vpanic() at vpanic+0x1c7/frame 0xfffffe00517fa4b0
panic() at panic+0x43/frame 0xfffffe00517fa510
trap_fatal() at trap_fatal+0x4cd/frame 0xfffffe00517fa590
trap() at trap+0xf7/frame 0xfffffe00517fa6b0
calltrap() at calltrap+0x8/frame 0xfffffe00517fa6b0
--- trap 0x9, rip = 0xffffffff81801263, rsp = 0xfffffe00517fa780, rbp = 0xfffffe00517fa790 ---
set_user_ldt_rv() at set_user_ldt_rv+0x53/frame 0xfffffe00517fa790
smp_rendezvous_action() at smp_rendezvous_action+0x12d/frame 0xfffffe00517fa7e0
Xrendezvous() at Xrendezvous+0xae/frame 0xfffffe00517fa7e0
--- interrupt, rip = 0xffffffff81125db0, rsp = 0xfffffe00517fa8b8, rbp = 0xfffffe00517fa8f0 ---
__sanitizer_cov_trace_const_cmp4() at __sanitizer_cov_trace_const_cmp4/frame 0xfffffe00517fa8f0
vm_fault() at vm_fault+0xcaa/frame 0xfffffe00517faa10
vm_fault_trap() at vm_fault_trap+0xa5/frame 0xfffffe00517faa60
trap_pfault() at trap_pfault+0x3fc/frame 0xfffffe00517faad0
trap() at trap+0x916/frame 0xfffffe00517fabf0
calltrap() at calltrap+0x8/frame 0xfffffe00517fabf0
--- trap 0xc, rip = 0x4105dc, rsp = 0x7fffffffe8e0, rbp = 0x7fffffffe900 ---
KDB: enter: panic
[ thread pid 719 tid 100089 ]
Stopped at      kdb_enter+0x67: movq    $0,0x163649e(%rip)
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
rax                       0x12
rcx                       0x80
rdx         0xffffffff81a0d2bc
rbx                          0
rsp         0xfffffe00517fa430
rbp         0xfffffe00517fa450
rsi                        0x1
rdi                          0
r8                           0
r9          0x8080808080808080
r10         0xfffffe00517fa320
r11              0x1ffaefff59c
r12         0xffffffff82267b90  ddb_dbbe
r13                          0
r14         0xffffffff81a6912b
r15         0xffffffff81a6912b
rip         0xffffffff81131c67  kdb_enter+0x67
rflags                    0x86
kdb_enter+0x67: movq    $0,0x163649e(%rip)
db> show proc
Process 719 (syz-executor4025265) at 0xfffff80003e62000:
 state: NORMAL
 uid: 0  gids: 0, 0, 5
 parent: pid 717 at 0xfffff80003c7e000
 ABI: FreeBSD ELF64
 flag: 0x10004080  flag2: 0
 arguments: /root/syz-executor402526512
 reaper: 0xfffff80003553530 reapsubtree: 1
 sigparent: 20
 vmspace: 0xfffffe0051dd2000
   (map 0xfffffe0051dd2000)
   (map.pmap 0xfffffe0051dd20c0)
   (pmap 0xfffffe0051dd2120)
 threads: 2
100089                   Run     CPU 1                       syz-executor4025265
100101                   D       ppwait  0xfffff80003e2ea10  syz-executor4025265
db> ps
  pid  ppid  pgrp   uid  state   wmesg   wchan               cmd
  724   719   717     0  RV      CPU 0                       syz-executor4025265
  723     0     0     0  DL      aiordy  0xfffff80003db7530  [aiod4]
  722     0     0     0  DL      aiordy  0xfffff8000b466530  [aiod3]
  721     0     0     0  DL      aiordy  0xfffff80003d61000  [aiod2]
  720     0     0     0  DL      aiordy  0xfffff80003c7e530  [aiod1]
  719   717   717     0  R       (threaded)                  syz-executor4025265
100089                   Run     CPU 1                       syz-executor4025265
100101                   D       ppwait  0xfffff80003e2ea10  syz-executor4025265
  717   715   717     0  Ss      pause   0xfffff80003c7e0b0  csh
  715   642   715     0  Ss      select  0xfffff8000b43b740  sshd
  694     1   694     0  Ss+     ttyin   0xfffff80003853cb0  getty
  692   690    22     0  S+      nanslp  0xffffffff8273b860  sleep
  691     1    22     0  S+      piperd  0xfffff8000b384000  logger
  690     1    22     0  S+      wait    0xfffff8000b2dea60  sh
  646     1   646     0  Ss      nanslp  0xffffffff8273b860  cron
  642     1   642     0  Ss      select  0xfffff8000b3bfe40  sshd
  450     1   450     0  Ss      select  0xfffff80003d6e740  syslogd
  379     1   379     0  Ss      select  0xfffff80003d6e7c0  devd
  378     1   378    65  Ss      select  0xfffff80003d6e6c0  dhclient
  308     1   308     0  Ss      select  0xfffff80003d6e640  dhclient
  305     1   305     0  Ss      select  0xfffff8000b3bfec0  dhclient
   90     1    90     0  Ss      pause   0xfffff80003d61b10  adjkerntz
   21     0     0     0  DL      vlruwt  0xfffff80003ce5530  [vnlru]
   20     0     0     0  DL      syncer  0xffffffff8282ac50  [syncer]
   19     0     0     0  DL      (threaded)                  [bufdaemon]
100069                   D       qsleep  0xffffffff82829d20  [bufdaemon]
100070                   D       -       0xffffffff8220ae80  [bufspacedaemon-0]
100084                   D       sdflush 0xfffff800035e38e8  [/ worker]
   18     0     0     0  DL      psleep  0xffffffff8284fa48  [vmdaemon]
   17     0     0     0  DL      (threaded)                  [pagedaemon]
100067                   D       psleep  0xffffffff82843eb8  [dom0]
100071                   D       launds  0xffffffff82843ec4  [laundry: dom0]
100072                   D       umarcl  0xffffffff815bf9b0  [uma]
   16     0     0     0  DL      -       0xffffffff8256fc08  [rand_harvestq]
   15     0     0     0  DL      -       0xffffffff828273dc  [soaiod4]
    9     0     0     0  DL      -       0xffffffff828273dc  [soaiod3]
    8     0     0     0  DL      -       0xffffffff828273dc  [soaiod2]
    7     0     0     0  DL      -       0xffffffff828273dc  [soaiod1]
    6     0     0     0  DL      (threaded)                  [cam]
100044                   D       -       0xffffffff824470c0  [doneq0]
100045                   D       -       0xffffffff82447040  [async]
100066                   D       -       0xffffffff82446f10  [scanner]
   14     0     0     0  DL      seqstat 0xfffff80003707488  [sequencer 00]
    5     0     0     0  DL      crypto_ 0xfffff8000359f180  [crypto returns 1]
    4     0     0     0  DL      crypto_ 0xfffff8000359f130  [crypto returns 0]
    3     0     0     0  DL      crypto_ 0xffffffff828413e0  [crypto]
   13     0     0     0  DL      (threaded)                  [geom]
100035                   D       -       0xffffffff8271b0a0  [g_event]
100036                   D       -       0xffffffff8271b0a8  [g_up]
100037                   D       -       0xffffffff8271b0b0  [g_down]
    2     0     0     0  DL      (threaded)                  [KTLS]
100028                   D       -       0xfffff80003521e00  [thr_0]
100029                   D       -       0xfffff80003521e80  [thr_1]
   12     0     0     0  WL      (threaded)                  [intr]
100012                   I                                   [swi6: task queue]
100015                   I                                   [swi6: Giant taskq]
100018                   I                                   [swi5: fast taskq]
100030                   I                                   [swi3: vm]
100031                   I                                   [swi4: clock (0)]
100032                   I                                   [swi4: clock (1)]
100033                   I                                   [swi1: netisr 0]
100046                   I                                   [irq40: virtio_pci0]
100047                   I                                   [irq41: virtio_pci0]
100048                   I                                   [irq42: virtio_pci0]
100051                   I                                   [irq43: virtio_pci1]
100052                   I                                   [irq44: virtio_pci1]
100053                   I                                   [irq1: atkbd0]
100054                   I                                   [irq12: psm0]
100055                   I                                   [swi0: uart uart++]
   11     0     0     0  RL      (threaded)                  [idle]
100003                   CanRun                              [idle: cpu0]
100004                   CanRun                              [idle: cpu1]
    1     0     1     0  SLs     wait    0xfffff80003553530  [init]
   10     0     0     0  DL      audit_w 0xffffffff828418f0  [audit]
    0     0     0     0  DLs     (threaded)                  [kernel]
100000                   D       swapin  0xffffffff8271b630  [swapper]
100005                   D       -       0xfffff80003530b00  [if_config_tqg_0]
100006                   D       -       0xfffff80003530a00  [softirq_0]
100007                   D       -       0xfffff80003530900  [softirq_1]
100008                   D       -       0xfffff80003530800  [if_io_tqg_0]
100009                   D       -       0xfffff80003530700  [if_io_tqg_1]
100010                   D       -       0xfffff80003530600  [pci_hp taskq]
100011                   D       -       0xfffff80003530500  [linuxkpi_irq_wq]
100013                   D       -       0xfffff80003530200  [in6m_free taskq]
100014                   D       -       0xfffff80003530100  [inm_free taskq]
100016                   D       -       0xfffff80003529d00  [thread taskq]
100017                   D       -       0xfffff80003529c00  [aiod_kick taskq]
100019                   D       -       0xfffff80003529900  [kqueue_ctx taskq]
100020                   D       -       0xfffff80003529800  [linuxkpi_short_wq_0]
100021                   D       -       0xfffff80003529800  [linuxkpi_short_wq_1]
100022                   D       -       0xfffff80003529800  [linuxkpi_short_wq_2]
100023                   D       -       0xfffff80003529800  [linuxkpi_short_wq_3]
100024                   D       -       0xfffff80003529700  [linuxkpi_long_wq_0]
100025                   D       -       0xfffff80003529700  [linuxkpi_long_wq_1]
100026                   D       -       0xfffff80003529700  [linuxkpi_long_wq_2]
100027                   D       -       0xfffff80003529700  [linuxkpi_long_wq_3]
100034                   D       -       0xfffff80003529100  [firmware taskq]
100038                   D       -       0xfffff8000364fe00  [crypto_0]
100039                   D       -       0xfffff8000364fe00  [crypto_1]
100049                   D       -       0xfffff800035ba600  [vtnet0 rxq 0]
100050                   D       -       0xfffff800035ba500  [vtnet0 txq 0]
100060                   D       -       0xffffffff81e15c90  [deadlkres]
100062                   D       -       0xfffff8000385a900  [acpi_task_0]
100063                   D       -       0xfffff8000385a900  [acpi_task_1]
100064                   D       -       0xfffff8000385a900  [acpi_task_2]
100065                   D       -       0xfffff8000364fc00  [CAM taskq]
db> show all locks
Process 724 (syz-executor4025265) thread 0xfffffe0051c61740 (100085)
exclusive sleep mutex descriptor tables (descriptor tables) r = 0 (0xffffffff8287bd20) locked @ /usr/home/markj/src/freebsd/sys/amd64/amd64/sys_machdep.c:534
Process 719 (syz-executor4025265) thread 0xfffffe0051da1ac0 (100089)
shared sx vm map (user) (vm map (user)) r = 0 (0xfffffe0051dd2060) locked @ /usr/home/markj/src/freebsd/sys/vm/vm_map.c:4935
db> show malloc
              Type        InUse        MemUse     Requests
         sysctloid        29282         1727K        29321
              kobj          325         1300K          522
            linker          297         1164K          335
            devbuf         1362         1150K         1386
            newblk          374         1118K          582
          vfscache            3         1025K            3
          inodedep           25          521K           66
         ufs_quota            1          512K            1
          vfs_hash            1          512K            1
           callout            2          512K            2
              intr            4          472K            4
               pcb           15          393K           35
           subproc           92          187K          775
         vnet_data            1          168K            1
           tidhash            3          141K            3
              SWAP            1          132K            1
           pagedep            8          130K           18
        tfo_ccache            1          128K            1
               sem            4          106K            4
            DEVFS1           92           92K          106
               bus          970           78K         2576
            bus-sc           31           76K         1056
          mtx_pool            2           72K            2
          syncache            1           68K            1
          acpitask            1           64K            1
       ddb_capture            1           64K            1
            module          498           63K          498
         pfs_nodes          155           59K          155
            acpica          420           39K        61071
               LRO            2           33K            2
         hostcache            1           32K            1
               shm            1           32K            1
               msg            4           30K            4
            DEVFS3          114           29K          132
           kdtrace          144           29K          827
              umtx          220           28K          220
        gtaskqueue           18           26K           18
         ufs_mount            5           25K            6
            kbdmux            5           22K            5
        DEVFS_RULE           56           20K           56
           ithread          101           18K          101
               BPF           10           18K           10
              temp           18           17K         1479
              proc            3           17K            3
           devstat            8           17K            8
              vmem            3           14K            4
            KTRACE          100           13K          100
              GEOM           79           13K          662
              rman          102           12K          526
            ifaddr           30           12K           32
          routetbl           52           11K          178
              kenv           63           11K           63
      eventhandler          115           10K          115
         bmsafemap            2            9K           42
       pfs_vncache            6            9K            6
              UART           12            9K           12
               rpc            2            8K            2
             shmfd            1            8K            1
     audit_evclass          236            8K          294
       ufs_dirhash           36            8K           36
         taskqueue           51            6K           51
            sglist            3            6K            3
              cred           17            5K          268
             ifnet            3            5K            3
           io_apic            1            4K            1
               tty            4            4K            4
             evdev            4            4K            4
          filedesc            1            4K            1
               UMA          240            4K          240
             mount           76            4K          153
             hhook           13            4K           13
           lltable           11            4K           11
       fpukern_ctx            3            3K            3
           acpisem           21            3K           21
            kqueue           42            3K          725
           pwddesc           42            3K          725
           uidinfo            3            3K            8
            plimit            9            3K          193
             linux           33            3K           33
       ether_multi           26            3K           36
        local_apic            1            2K            1
         ipsec-saq            2            2K            2
           CAM DEV            1            2K            2
         in6_multi           15            2K           15
             selfd           27            2K        10163
               msi           13            2K           13
            Unitno           27            2K           51
           session           13            2K           21
             lockf           15            2K           22
          pci_link           16            2K           16
          freefile           12            2K           22
           acpidev           22            2K           22
         toponodes           10            2K           10
         proc-args           32            2K          429
           softdep            1            1K            1
            dirrem            4            1K           28
       ipsecpolicy            1            1K            1
            sahead            1            1K            1
          secasvar            1            1K            1
             clone            8            1K            8
       vnodemarker            2            1K           10
      NFSD session            1            1K            1
            diradd            7            1K           36
            select            7            1K           23
             nhops            6            1K            6
            crypto            4            1K            4
            ip6ndp            4            1K            5
            isadev            5            1K            5
           CAM XPT           11            1K           12
         CAM queue            2            1K            5
         newdirblk            4            1K            8
             mkdir            4            1K           16
          indirdep            2            1K            3
          in_multi            2            1K            4
              pfil            4            1K            4
              cdev            2            1K            2
 encap_export_host            8            1K            8
    chacha20random            1            1K            1
        CAM periph            2            1K           14
            prison           12            1K           12
       inpcbpolicy           10            1K           78
               osd            3            1K           10
      NFSD lckfile            1            1K            1
     NFSD V4client            1            1K            1
             DEVFS            9            1K           10
               MCA            2            1K            2
               mld            2            1K            2
              igmp            2            1K            2
            vnodes            1            1K            1
              ktls            1            1K            1
            feeder            7            1K            7
        loginclass            3            1K            7
             linux            5            1K            6
        aesni_data            2            1K            2
            DEVFSP            2            1K            2
            apmdev            1            1K            1
          atkbddev            2            1K            2
         vm_pgdata            1            1K            1
           CAM SIM            1            1K            1
          procdesc            1            1K            2
          pmchooks            1            1K            1
            soname            4            1K         2698
          filecaps            4            1K           51
          nexusdev            6            1K            6
               tun            3            1K            3
        debugfsint            2            1K            2
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
            vtfont            0            0K            0
     hyperv_socket            0            0K            0
           bxe_ilt            0            0K            0
            xenbus            0            0K            0
                vt            0            0K            0
             vtbuf            0            0K            0
           ath_hal            0            0K            0
     vm_fictitious            0            0K            0
            athdev            0            0K            0
           ata_pci            0            0K            0
           ata_dma            0            0K            0
       ata_generic            0            0K            0
               amr            0            0K            0
            pvscsi            0            0K            0
           scsi_da            0            0K            0
            ata_da            0            0K            0
           scsi_ch            0            0K            0
           scsi_cd            0            0K            0
           UMAHash            0            0K            0
       AHCI driver            0            0K            0
            USBdev            0            0K            0
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
               USB            0            0K            0
               agp            0            0K            0
           nvme_da            0            0K            0
 CAM I/O Scheduler            0            0K            0
           acpipwr            0            0K            0
         acpi_perf            0            0K            0
            twsbuf            0            0K            0
          ktls_ocf            0            0K            0
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
            statfs            0            0K          205
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
               iov            0            0K        11859
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
              sbuf            0            0K          478
        md_sectors            0            0K            0
          firmware            0            0K            0
        compressor            0            0K            0
           md_disk            0            0K            0
           malodev            0            0K            0
               LED            0            0K            0
         sysctltmp            0            0K          525
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
db> show uma
              Zone   Size    Used    Free    Requests  Sleeps  Bucket  Total Mem    XFree
   mbuf_jumbo_page   4096    1088    1030       13782       0     254    8675328        0
              pbuf   2624       0     778           0       0       2    2041472        0
          BUF TRIE    144     182   13314         479       0      62    1943424        0
       malloc-4096   4096     367       1        1247       0       2    1507328        0
        malloc-128    128   10338      47       10371       0     126    1329280        0
      malloc-65536  65536      11       0          11       0       1     720896        0
         FFS inode   1160     510      22         532       0       8     617120        0
              mbuf    256    1347    1053       21196       0     254     614400        0
        malloc-512    512    1030      10        1030       0      30     532480        0
            lkpimm    160       1    2324           1       0      62     372000        0
          lkpicurr    160       2    2323           2       0      62     372000        0
       UMA Slabs 0    112    3041      16        3041       0     126     342384        0
        RADIX NODE    144    1975     178       17577       0      62     310032        0
       malloc-2048   2048     138       0         138       0       8     282624        0
      malloc-65536  65536       2       2          71       0       1     262144        0
             VNODE    448     541      35         565       0      30     258048        0
         VM OBJECT    264     850      50       11616       0      30     237600        0
        256 Bucket   2048     102      14        2697       0       8     237568        0
         malloc-64     64    3267      72        3276       0     254     213696        0
            DEVCTL   1024       0     200          97       0       0     204800        0
            THREAD   1808     101       9         101       0       8     198880        0
         malloc-16     16   12168      82       12217       0     254     196000        0
         UMA Zones    768     212       2         212       0      16     164352        0
         malloc-32     32    4536     126        4653       0     254     149184        0
       FFS2 dinode    256     510      30         532       0      62     138240        0
      malloc-65536  65536       0       2          38       0       1     131072        0
      malloc-65536  65536       2       0           2       0       1     131072        0
      malloc-65536  65536       2       0           2       0       1     131072        0
      malloc-32768  32768       4       0           4       0       1     131072        0
        malloc-256    256     417      63         739       0      62     122880        0
          ksiginfo    112      31    1013          44       0     126     116928        0
       malloc-1024   1024     102      10         123       0      16     114688        0
       S VFS Cache    104     993      99        1047       0     126     113568        0
         MAP ENTRY     96     672     378       35044       0     126     100800        0
         vmem btag     56    1594      50        1594       0     254      92064        0
            clpbuf   2624       0      32          32       0      16      83968        0
        malloc-384    384     179      31         220       0      30      80640        0
          UMA Kegs    384     197       6         197       0      30      77952        0
      mbuf_cluster   2048      30       2          30       0     254      65536        0
              PROC   1328      41       7         724       0       8      63744        0
           VMSPACE   2544      16       8         700       0       4      61056        0
         filedesc0   1072      42      14         725       0       8      60032        0
           DIRHASH   1024      54       2          54       0      16      57344        0
       malloc-8192   8192       7       0           7       0       1      57344        0
       malloc-4096   4096      14       0          14       0       2      57344        0
             g_bio    408       0     140        5201       0      30      57120        0
        128 Bucket   1024      37      14         513       0      16      52224        0
      malloc-16384  16384       3       0           3       0       1      49152        0
        malloc-128    128     315      26         371       0     126      43648        0
        malloc-256    256     136      29         386       0      62      42240        0
         32 Bucket    256      44     121        2718       0      62      42240        0
       malloc-8192   8192       4       1          53       0       1      40960        0
       malloc-8192   8192       5       0           5       0       1      40960        0
         64 Bucket    512      58      22        1062       0      30      40960        0
        malloc-256    256     106      44         509       0      62      38400        0
             NAMEI   1024       0      36       10691       0      16      36864        0
        malloc-256    256     118      17         306       0      62      34560        0
      malloc-32768  32768       1       0           1       0       1      32768        0
      malloc-32768  32768       1       0           1       0       1      32768        0
      malloc-32768  32768       0       1          52       0       1      32768        0
      malloc-32768  32768       1       0           1       0       1      32768        0
      malloc-16384  16384       2       0           6       0       1      32768        0
           pcpu-64     64     453      59         453       0     254      32768        0
         malloc-64     64     414      90       22222       0     254      32256        0
         malloc-64     64     457      47         670       0     254      32256        0
        malloc-128    128     221      27       27766       0     126      31744        0
            pcpu-8      8    3154     430        3166       0     254      28672        0
       malloc-4096   4096       6       0           7       0       2      24576        0
       malloc-2048   2048       6       6          39       0       8      24576        0
        malloc-128    128     122      64         159       0     126      23808        0
        malloc-128    128     151      35         649       0     126      23808        0
        malloc-384    384      53       7          53       0      30      23040        0
        malloc-384    384      52       8          52       0      30      23040        0
            socket    944      18       6        1022       0     254      22656        0
       malloc-1024   1024      11       9         792       0      16      20480        0
         malloc-64     64     212     103        1663       0     254      20160        0
         TURNSTILE    136     111      36         111       0      62      19992        0
        malloc-128    128     105      50         836       0     126      19840        0
       Mountpoints   2752       6       1           6       0       4      19264        0
        malloc-256    256      52      23         195       0      62      19200        0
      malloc-16384  16384       0       1           2       0       1      16384        0
      malloc-16384  16384       1       0           1       0       1      16384        0
      malloc-16384  16384       0       1          68       0       1      16384        0
      malloc-16384  16384       1       0           1       0       1      16384        0
       malloc-4096   4096       3       1          16       0       2      16384        0
       malloc-4096   4096       2       2         299       0       2      16384        0
       malloc-1024   1024      14       2          14       0      16      16384        0
         malloc-64     64      88     164         989       0     254      16128        0
         malloc-64     64     168      84        1648       0     254      16128        0
             tcpcb   1064       7       7           7       0     254      14896        0
              pipe    744       7      13         271       0      16      14880        0
       malloc-4096   4096       1       2           4       0       2      12288        0
       malloc-4096   4096       1       2         206       0       2      12288        0
        malloc-512    512      12      12          12       0      30      12288        0
        malloc-384    384      20      10          21       0      30      11520        0
        malloc-256    256      12      33          36       0      62      11520        0
        SLEEPQUEUE     88     111      17         111       0     126      11264        0
       malloc-8192   8192       1       0          42       0       1       8192        0
       malloc-8192   8192       1       0           1       0       1       8192        0
       malloc-2048   2048       1       3          17       0       8       8192        0
       malloc-2048   2048       3       1           4       0       8       8192        0
       malloc-2048   2048       2       2           2       0       8       8192        0
       malloc-2048   2048       0       4         211       0       8       8192        0
       malloc-1024   1024       3       5          64       0      16       8192        0
       malloc-1024   1024       3       5          14       0      16       8192        0
       malloc-1024   1024       3       5         117       0      16       8192        0
       malloc-1024   1024       5       3           5       0      16       8192        0
        malloc-512    512       2      14         183       0      30       8192        0
        malloc-512    512       3      13          22       0      30       8192        0
        malloc-512    512       3      13          40       0      30       8192        0
           rtentry    176      13      33          17       0      62       8096        0
              PGRP     88      13      79          21       0     126       8096        0
          rl_entry     40      25     177          25       0     254       8080        0
             udpcb     32       2     250          70       0     254       8064        0
               PWD     32      11     241          99       0     254       8064        0
         malloc-64     64      15     111          60       0     254       8064        0
         malloc-64     64       9     117          18       0     254       8064        0
         malloc-32     32      92     160         141       0     254       8064        0
         malloc-32     32      84     168         175       0     254       8064        0
         malloc-32     32      39     213         673       0     254       8064        0
         malloc-32     32      17     235         100       0     254       8064        0
         malloc-32     32      56     196         197       0     254       8064        0
         malloc-32     32      24     228        4819       0     254       8064        0
         16 Bucket    144      34      22         200       0      62       8064        0
          4 Bucket     48       5     163          49       0     254       8064        0
          2 Bucket     32      45     207         478       0     254       8064        0
      vtnet_tx_hdr     24       1     333        6601       0     254       8016        0
            ttyinq    160      15      35          45       0      62       8000        0
             Files     80      62      38        5751       0     126       8000        0
         malloc-16     16      77     423         233       0     254       8000        0
         malloc-16     16      33     467         283       0     254       8000        0
         malloc-16     16     182     318         930       0     254       8000        0
         malloc-16     16       9     491          11       0     254       8000        0
         malloc-16     16     236     264         241       0     254       8000        0
         malloc-16     16      31     469       26573       0     254       8000        0
          8 Bucket     80      33      67         319       0     126       8000        0
        malloc-128    128      27      35          99       0     126       7936        0
        malloc-128    128      26      36        2627       0     126       7936        0
         tcp_inpcb    488       7       9           7       0     254       7808        0
         udp_inpcb    488       2      14          70       0     254       7808        0
              kenv    258       2      28         699       0      30       7740        0
     routing nhops    256      10      20          17       0      62       7680        0
             unpcb    256       7      23         928       0     254       7680        0
           ttyoutq    256       8      22          24       0      62       7680        0
       mbuf_packet    256       0      30          96       0     254       7680        0
        malloc-384    384       2      18          12       0      30       7680        0
        malloc-384    384       0      20         196       0      30       7680        0
        malloc-384    384       7      13           9       0      30       7680        0
        malloc-384    384       1      19           3       0      30       7680        0
        malloc-256    256      11      19         592       0      62       7680        0
        malloc-256    256       4      26          93       0      62       7680        0
     FPU_save_area    832       1       8           1       0      16       7488        0
            cpuset    104       7      55           7       0     126       6448        0
 epoch_record pcpu    256       4      12           4       0      62       4096        0
       malloc-4096   4096       1       0           1       0       2       4096        0
       malloc-2048   2048       0       2          16       0       8       4096        0
       malloc-2048   2048       1       1           1       0       8       4096        0
       malloc-1024   1024       1       3           1       0      16       4096        0
           pcpu-16     16       7     249           7       0     254       4096        0
          syncache    168       0      24           5       0     254       4032        0
              AIOP     32       4     122           4       0     254       4032        0
         malloc-32     32       7     119          44       0     254       4032        0
         malloc-16     16      15     235          52       0     254       4000        0
               AIO    208       1      18           1       0      62       3952        0
             ripcb    488       1       7           1       0     254       3904        0
       UMA Slabs 1    176       6      16           6       0      62       3872        0
             AIOCB    552       0       7           1       0      16       3864        0
        KMAP ENTRY     96      21      18          26       0       0       3744        0
              vmem   1856       1       1           1       0       8       3712        0
           SMR CPU     32       3      60           3       0     254       2016        0
        SMR SHARED     24       3      60           3       0     254       1512        0
             swblk    136       0       0           0       0      62          0        0
          swpctrie    144       0       0           0       0      62          0        0
       FFS1 dinode    128       0       0           0       0     126          0        0
           ada_ccb    272       0       0           0       0      30          0        0
            da_ccb    544       0       0           0       0      16          0        0
     udplite_inpcb    488       0       0           0       0     254          0        0
      tcp_log_node    120       0       0           0       0     126          0        0
    tcp_log_bucket    176       0       0           0       0      62          0        0
           tcp_log    416       0       0           0       0     254          0        0
          tcpreass     48       0       0           0       0     254          0        0
tfo_ccache_entries     80       0       0           0       0     126          0        0
               tfo      4       0       0           0       0     254          0        0
          sackhole     32       0       0           0       0     254          0        0
         hostcache     64       0       0           0       0     254          0        0
             tcptw     88       0       0           0       0     254          0        0
               ipq     56       0       0           0       0     254          0        0
    IPsec SA lft_c     16       0       0           0       0     254          0        0
             KNOTE    160       0       0           0       0      62          0        0
            itimer    352       0       0           0       0      30          0        0
            AIOLIO    272       0       0           0       0      30          0        0
        TMPFS node    224       0       0           0       0      62          0        0
           NCLNODE    584       0       0           0       0      16          0        0
     LTS VFS Cache    360       0       0           0       0      30          0        0
       L VFS Cache    320       0       0           0       0      30          0        0
     STS VFS Cache    144       0       0           0       0      62          0        0
           cryptop    280       0       0           0       0      30          0        0
  linux_dma_object     24       0       0           0       0     254          0        0
  linux_dma_pctrie    144       0       0           0       0      62          0        0
   IOMMU_MAP_ENTRY    120       0       0           0       0     126          0        0
      ktls_session    128       0       0           0       0     126          0        0
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
      malloc-16384  16384       0       0           0       0       1          0        0
      malloc-16384  16384       0       0           0       0       1          0        0
       malloc-8192   8192       0       0           0       0       1          0        0
       malloc-8192   8192       0       0           0       0       1          0        0
       malloc-8192   8192       0       0           0       0       1          0        0
        malloc-512    512       0       0           0       0      30          0        0
        malloc-512    512       0       0           0       0      30          0        0
        malloc-512    512       0       0           0       0      30          0        0
           pcpu-32     32       0       0           0       0     254          0        0
            pcpu-4      4       0       0           0       0     254          0        0
            fakepg    104       0       0           0       0     126          0        0
          UMA Hash    256       0       0           0       0      62          0        0


Syzkaller reproducer:
# {Threaded:true Collide:true Repeat:false RepeatTimes:0 Procs:1 Slowdown:1 Sandbox: Fault:false FaultCall:-1 FaultNth:0 Leak:false NetInjection:false NetDevices:false NetReset:false Cgroups:false BinfmtMisc:false CloseFDs:false KCSAN:false DevlinkPCI:false USB:false VhciInjection:false Wifi:false IEEE802154:false Sysctl:false UseTmpDir:false HandleSegv:false Repro:false Trace:false}
sysarch$I386_SET_LDT(0x1, &(0x7f0000000080)={0x0, 0x0})
aio_write(&(0x7f0000000340)={0xffffffffffffffff, 0x8, &(0x7f0000000080)="2428ef5b0478bab023477f11a3fbad3b993611e32c1566980bc55ed1add891d37ec450128aee31dc210b329eeb418467ed9e60749dce06565f8958e5b4c818cae14b30b0b41b3bb3faf04846acdc0849749b624e53f3622de34c52a9b078cc7f759a950bffb9a637e4600c0ffaac4b86030150a8c29b919532e47bf92143f05ac0c05695c049213ec9e21ca3dedf521b8cce3311a088e6b14ea169aded126825aa86a1b5009909fb93a505a1758035a0c367d7135c8f7270d33850c0088abab7d0c1aaa4d476c9757f34f8fd43f315b6a8fac0", 0xd3, [0x3, 0x58e], 0x9, 0x6, 0x2, {0x6, 0x1, 0x0}, {0x3, 0x1, @sival_int=0x2, @thr={0x0, 0x0}}})
vfork()


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

void execute_call(int call)
{
  switch (call) {
  case 0:
    *(uint32_t*)0x20000080 = 0;
    *(uint64_t*)0x20000088 = 0;
    *(uint32_t*)0x20000090 = 0;
    syscall(SYS_sysarch, 1ul, 0x20000080ul);
    break;
  case 1:
    *(uint32_t*)0x20000340 = -1;
    *(uint64_t*)0x20000348 = 8;
    *(uint64_t*)0x20000350 = 0x20000080;
    memcpy(
        (void*)0x20000080,
        "\x24\x28\xef\x5b\x04\x78\xba\xb0\x23\x47\x7f\x11\xa3\xfb\xad\x3b\x99"
        "\x36\x11\xe3\x2c\x15\x66\x98\x0b\xc5\x5e\xd1\xad\xd8\x91\xd3\x7e\xc4"
        "\x50\x12\x8a\xee\x31\xdc\x21\x0b\x32\x9e\xeb\x41\x84\x67\xed\x9e\x60"
        "\x74\x9d\xce\x06\x56\x5f\x89\x58\xe5\xb4\xc8\x18\xca\xe1\x4b\x30\xb0"
        "\xb4\x1b\x3b\xb3\xfa\xf0\x48\x46\xac\xdc\x08\x49\x74\x9b\x62\x4e\x53"
        "\xf3\x62\x2d\xe3\x4c\x52\xa9\xb0\x78\xcc\x7f\x75\x9a\x95\x0b\xff\xb9"
        "\xa6\x37\xe4\x60\x0c\x0f\xfa\xac\x4b\x86\x03\x01\x50\xa8\xc2\x9b\x91"
        "\x95\x32\xe4\x7b\xf9\x21\x43\xf0\x5a\xc0\xc0\x56\x95\xc0\x49\x21\x3e"
        "\xc9\xe2\x1c\xa3\xde\xdf\x52\x1b\x8c\xce\x33\x11\xa0\x88\xe6\xb1\x4e"
        "\xa1\x69\xad\xed\x12\x68\x25\xaa\x86\xa1\xb5\x00\x99\x09\xfb\x93\xa5"
        "\x05\xa1\x75\x80\x35\xa0\xc3\x67\xd7\x13\x5c\x8f\x72\x70\xd3\x38\x50"
        "\xc0\x08\x8a\xba\xb7\xd0\xc1\xaa\xa4\xd4\x76\xc9\x75\x7f\x34\xf8\xfd"
        "\x43\xf3\x15\xb6\xa8\xfa\xc0",
        211);
    *(uint64_t*)0x20000358 = 0xd3;
    *(uint32_t*)0x20000360 = 3;
    *(uint32_t*)0x20000364 = 0x58e;
    *(uint64_t*)0x20000368 = 9;
    *(uint32_t*)0x20000370 = 6;
    *(uint32_t*)0x20000374 = 2;
    *(uint64_t*)0x20000378 = 6;
    *(uint64_t*)0x20000380 = 1;
    *(uint64_t*)0x20000388 = 0;
    *(uint32_t*)0x20000390 = 3;
    *(uint32_t*)0x20000394 = 1;
    *(uint32_t*)0x20000398 = 2;
    *(uint64_t*)0x200003a0 = 0;
    *(uint64_t*)0x200003a8 = 0;
    syscall(SYS_aio_write, 0x20000340ul);
    break;
  case 2:
    syscall(SYS_vfork);
    break;
  }
}
int main(void)
{
  syscall(SYS_mmap, 0x20000000ul, 0x1000000ul, 7ul, 0x1012ul, -1, 0ul);
  loop();
  return 0;
}


