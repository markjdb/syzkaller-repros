Syzkaller hit 'Fatal trap 18: integer divide fault in tcp_mss' bug.

Fatal trap 18: integer divide fault while in kernel mode
cpuid = 1; apic id = 01
instruction pointer	= 0x20:0xffffffff81396340
stack pointer	        = 0x28:0xfffffe00517ae690
frame pointer	        = 0x28:0xfffffe00517ae700
code segment		= base 0x0, limit 0xfffff, type 0x1b
			= DPL 0, pres 1, long 1, def32 0, gran 1
processor eflags	= interrupt enabled, resume, IOPL = 0
current process		= 724 (syz-executor0129033)
trap number		= 18
panic: integer divide fault
cpuid = 1
time = 1621455096
KDB: stack backtrace:
db_trace_self_wrapper() at db_trace_self_wrapper+0x47/frame 0xfffffe00517ae360
vpanic() at vpanic+0x1c7/frame 0xfffffe00517ae3c0
panic() at panic+0x43/frame 0xfffffe00517ae420
trap_fatal() at trap_fatal+0x4cd/frame 0xfffffe00517ae4a0
trap() at trap+0xf7/frame 0xfffffe00517ae5c0
calltrap() at calltrap+0x8/frame 0xfffffe00517ae5c0
--- trap 0x12, rip = 0xffffffff81396340, rsp = 0xfffffe00517ae690, rbp = 0xfffffe00517ae700 ---
tcp_mss() at tcp_mss+0x230/frame 0xfffffe00517ae700
tcp_usr_send() at tcp_usr_send+0x931/frame 0xfffffe00517ae7d0
sosend_generic() at sosend_generic+0x9ae/frame 0xfffffe00517ae8d0
sosend() at sosend+0xc6/frame 0xfffffe00517ae940
kern_sendit() at kern_sendit+0x35b/frame 0xfffffe00517ae9f0
sendit() at sendit+0x229/frame 0xfffffe00517aea50
sys_sendto() at sys_sendto+0x5c/frame 0xfffffe00517aeab0
amd64_syscall() at amd64_syscall+0x247/frame 0xfffffe00517aebf0
fast_syscall_common() at fast_syscall_common+0xf8/frame 0xfffffe00517aebf0
--- syscall (0, FreeBSD ELF64, nosys), rip = 0x400a4a, rsp = 0x7fffffffea98, rbp = 0x7fffffffeab0 ---
KDB: enter: panic
[ thread pid 724 tid 100102 ]
Stopped at      kdb_enter+0x67: movq    $0,0x14393fe(%rip)
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
rdx         0xffffffff81a049f3
rbx                          0
rsp         0xfffffe00517ae340
rbp         0xfffffe00517ae360
rsi                        0x1
rdi                          0
r8                           0
r9          0x8080808080808080
r10         0xfffffe00517ae230
r11              0x1ffaefff59c
r12         0xffffffff82067b80  ddb_dbbe
r13                          0
r14         0xffffffff81a603d1
r15         0xffffffff81a603d1
rip         0xffffffff8112ea07  kdb_enter+0x67
rflags                    0x86
kdb_enter+0x67: movq    $0,0x14393fe(%rip)
db> show proc
Process 724 (syz-executor0129033) at 0xfffff8001650f000:
 state: NORMAL
 uid: 0  gids: 0, 0, 5
 parent: pid 722 at 0xfffff8001698ba70
 ABI: FreeBSD ELF64
 flag: 0x10004000  flag2: 0
 arguments: /root/syz-executor012903385
 reaper: 0xfffff8000354c538 reapsubtree: 1
 sigparent: 20
 vmspace: 0xfffffe0051db43e0
   (map 0xfffffe0051db43e0)
   (map.pmap 0xfffffe0051db44a0)
   (pmap 0xfffffe0051db4500)
 threads: 1
100102                   Run     CPU 1                       syz-executor0129033
db> ps
  pid  ppid  pgrp   uid  state   wmesg   wchan               cmd
  724   722   722     0  R       CPU 1                       syz-executor0129033
  722   720   722     0  Ss      pause   0xfffff8001698bb20  csh
  720   642   720     0  Ss      select  0xfffff800164b7cc0  sshd
  694     1   694     0  Ss+     ttyin   0xfffff8000359f8b0  getty
  692     1    22     0  S+      piperd  0xfffff80003d082e8  logger
  691   690    22     0  S+      nanslp  0xffffffff8253b560  sleep
  690     1    22     0  S+      wait    0xfffff800163cc000  sh
  646     1   646     0  Ss      nanslp  0xffffffff8253b561  cron
  642     1   642     0  Ss      select  0xfffff800037592c0  sshd
  450     1   450     0  Ss      select  0xfffff80003e651c0  syslogd
  379     1   379     0  Ss      select  0xfffff80003e653c0  devd
  378     1   378    65  Ss      select  0xfffff80003e65340  dhclient
  308     1   308     0  Ss      select  0xfffff80003e65240  dhclient
  305     1   305     0  Ss      select  0xfffff8000376c6c0  dhclient
   90     1    90     0  Ss      pause   0xfffff80003e68b20  adjkerntz
   21     0     0     0  DL      syncer  0xffffffff8262a9d0  [syncer]
   20     0     0     0  DL      vlruwt  0xfffff80003b1c538  [vnlru]
   19     0     0     0  DL      (threaded)                  [bufdaemon]
100069                   D       qsleep  0xffffffff82629a80  [bufdaemon]
100072                   D       -       0xffffffff8200ae80  [bufspacedaemon-0]
100084                   D       sdflush 0xfffff80003e4ece8  [/ worker]
   18     0     0     0  DL      psleep  0xffffffff8264f7c8  [vmdaemon]
   17     0     0     0  DL      (threaded)                  [pagedaemon]
100067                   D       psleep  0xffffffff82643c38  [dom0]
100070                   D       launds  0xffffffff82643c44  [laundry: dom0]
100071                   D       umarcl  0xffffffff815ba850  [uma]
   16     0     0     0  DL      -       0xffffffff8236f908  [rand_harvestq]
   15     0     0     0  DL      -       0xffffffff826270dc  [soaiod4]
    9     0     0     0  DL      -       0xffffffff826270dc  [soaiod3]
    8     0     0     0  DL      -       0xffffffff826270dc  [soaiod2]
    7     0     0     0  DL      -       0xffffffff826270dc  [soaiod1]
    6     0     0     0  DL      (threaded)                  [cam]
100044                   D       -       0xffffffff82246dc0  [doneq0]
100045                   D       -       0xffffffff82246d40  [async]
100066                   D       -       0xffffffff82246c10  [scanner]
   14     0     0     0  DL      seqstat 0xfffff80003652888  [sequencer 00]
    5     0     0     0  DL      crypto_ 0xfffff80003647d80  [crypto returns 1]
    4     0     0     0  DL      crypto_ 0xfffff80003647d30  [crypto returns 0]
    3     0     0     0  DL      crypto_ 0xffffffff82641160  [crypto]
   13     0     0     0  DL      (threaded)                  [geom]
100035                   D       -       0xffffffff8251ada0  [g_event]
100036                   D       -       0xffffffff8251ada8  [g_up]
100037                   D       -       0xffffffff8251adb0  [g_down]
    2     0     0     0  DL      (threaded)                  [KTLS]
100028                   D       -       0xfffff80003524d00  [thr_0]
100029                   D       -       0xfffff80003524d80  [thr_1]
   12     0     0     0  WL      (threaded)                  [intr]
100013                   I                                   [swi6: task queue]
100016                   I                                   [swi6: Giant taskq]
100019                   I                                   [swi5: fast taskq]
100030                   I                                   [swi1: netisr 0]
100031                   I                                   [swi3: vm]
100032                   I                                   [swi4: clock (0)]
100033                   I                                   [swi4: clock (1)]
100046                   I                                   [irq40: virtio_pci0]
100047                   I                                   [irq41: virtio_pci0]
100048                   I                                   [irq42: virtio_pci0]
100051                   I                                   [irq43: virtio_pci1]
100052                   I                                   [irq44: virtio_pci1]
100053                   I                                   [irq1: atkbd0]
100054                   I                                   [irq12: psm0]
100055                   I                                   [swi0: uart uart++]
   11     0     0     0  RL      (threaded)                  [idle]
100003                   Run     CPU 0                       [idle: cpu0]
100004                   CanRun                              [idle: cpu1]
    1     0     1     0  SLs     wait    0xfffff8000354c538  [init]
   10     0     0     0  DL      audit_w 0xffffffff82641670  [audit]
    0     0     0     0  DLs     (threaded)                  [kernel]
100000                   D       swapin  0xffffffff8251b330  [swapper]
100005                   D       -       0xfffff80003143d00  [if_io_tqg_0]
100006                   D       -       0xfffff80003143c00  [if_io_tqg_1]
100007                   D       -       0xfffff80003143b00  [if_config_tqg_0]
100008                   D       -       0xfffff80003143a00  [softirq_0]
100009                   D       -       0xfffff80003143900  [softirq_1]
100010                   D       -       0xfffff8000352cd00  [kqueue_ctx taskq]
100011                   D       -       0xfffff8000352cc00  [pci_hp taskq]
100012                   D       -       0xfffff8000352cb00  [linuxkpi_irq_wq]
100014                   D       -       0xfffff8000352c800  [in6m_free taskq]
100015                   D       -       0xfffff8000352c700  [inm_free taskq]
100017                   D       -       0xfffff8000352c400  [thread taskq]
100018                   D       -       0xfffff8000352c300  [aiod_kick taskq]
100020                   D       -       0xfffff8000352c000  [linuxkpi_short_wq_0]
100021                   D       -       0xfffff8000352c000  [linuxkpi_short_wq_1]
100022                   D       -       0xfffff8000352c000  [linuxkpi_short_wq_2]
100023                   D       -       0xfffff8000352c000  [linuxkpi_short_wq_3]
100024                   D       -       0xfffff80003524e00  [linuxkpi_long_wq_0]
100025                   D       -       0xfffff80003524e00  [linuxkpi_long_wq_1]
100026                   D       -       0xfffff80003524e00  [linuxkpi_long_wq_2]
100027                   D       -       0xfffff80003524e00  [linuxkpi_long_wq_3]
100034                   D       -       0xfffff80003524700  [firmware taskq]
100038                   D       -       0xfffff80003524500  [crypto_0]
100039                   D       -       0xfffff80003524500  [crypto_1]
100049                   D       -       0xfffff800035b8600  [vtnet0 rxq 0]
100050                   D       -       0xfffff800035b8500  [vtnet0 txq 0]
100060                   D       -       0xffffffff81e0cb71  [deadlkres]
100062                   D       -       0xfffff8000387a400  [acpi_task_0]
100063                   D       -       0xfffff8000387a400  [acpi_task_1]
100064                   D       -       0xfffff8000387a400  [acpi_task_2]
100065                   D       -       0xfffff80003524400  [CAM taskq]
db> show all locks
Process 724 (syz-executor0129033) thread 0xfffffe00877da3a0 (100102)
exclusive sleep mutex so_rcv (so_rcv) r = 0 (0xfffff800164dd8a8) locked @ /usr/home/markj/src/freebsd/sys/netinet/tcp_input.c:3897
exclusive rw tcpinp (tcpinp) r = 0 (0xfffff800164489a8) locked @ /usr/home/markj/src/freebsd/sys/netinet/tcp_usrreq.c:989
exclusive sx so_snd_sx (so_snd_sx) r = 0 (0xfffff800164dd9e0) locked @ /usr/home/markj/src/freebsd/sys/kern/uipc_sockbuf.c:469
db> show malloc
              Type        InUse        MemUse     Requests
         sysctloid        29282         1727K        29321
              kobj          325         1300K          522
            linker          304         1157K          342
            newblk          525         1155K          566
            devbuf         1362         1150K         1386
          vfscache            3         1025K            3
          inodedep           45          529K           67
         ufs_quota            1          512K            1
          vfs_hash            1          512K            1
           callout            2          512K            2
              intr            4          472K            4
               pcb           16          393K           36
         vnet_data            1          168K            1
           subproc           89          168K          777
           tidhash            3          141K            3
              SWAP            1          132K            1
           pagedep           13          131K           19
        tfo_ccache            1          128K            1
               sem            4          106K            4
            DEVFS1           92           92K          106
               bus          970           78K         2574
            bus-sc           31           76K         1054
          mtx_pool            2           72K            2
          syncache            1           68K            1
          acpitask            1           64K            1
       ddb_capture            1           64K            1
            module          499           63K          499
         pfs_nodes          155           59K          155
            acpica          420           39K        61005
               LRO            2           33K            2
              temp           18           33K         1496
         hostcache            1           32K            1
               shm            1           32K            1
               msg            4           30K            4
            DEVFS3          114           29K          132
           kdtrace          141           29K          829
              umtx          220           28K          220
        gtaskqueue           18           26K           18
         ufs_mount            5           25K            6
            kbdmux            5           22K            5
        DEVFS_RULE           56           20K           56
           ithread          101           18K          101
               BPF           10           18K           10
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
         bmsafemap            2            9K           41
       pfs_vncache            6            9K            6
              UART           12            9K           12
               rpc            2            8K            2
             shmfd            1            8K            1
     audit_evclass          236            8K          294
       ufs_dirhash           36            8K           36
         taskqueue           51            6K           51
            sglist            3            6K            3
              cred           17            5K          277
             ifnet            3            5K            3
           io_apic            1            4K            1
            dirrem           16            4K           28
               tty            4            4K            4
             evdev            4            4K            4
          filedesc            1            4K            1
               UMA          240            4K          240
             mount           76            4K          153
             hhook           13            4K           13
           lltable           11            4K           11
       fpukern_ctx            3            3K            3
            diradd           24            3K           37
           acpisem           21            3K           21
            kqueue           37            3K          725
           pwddesc           37            3K          725
           uidinfo            3            3K            9
            plimit            9            3K          208
             linux           33            3K           33
       ether_multi           26            3K           36
        local_apic            1            2K            1
         ipsec-saq            2            2K            2
           CAM DEV            1            2K            2
         in6_multi           15            2K           15
             selfd           27            2K        10693
               msi           13            2K           13
            Unitno           27            2K           51
           session           13            2K           22
             lockf           15            2K           22
          pci_link           16            2K           16
           acpidev           22            2K           22
         toponodes           10            2K           10
         proc-args           32            2K          435
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
            crypto            4            1K            4
            ip6ndp            4            1K            5
            isadev            5            1K            5
           CAM XPT           11            1K           12
         CAM queue            2            1K            5
         newdirblk            4            1K            8
             mkdir            4            1K           16
          in_multi            2            1K            4
              pfil            4            1K            4
              cdev            2            1K            2
 encap_export_host            8            1K            8
    chacha20random            1            1K            1
        CAM periph            2            1K           14
            prison           12            1K           12
               osd            3            1K           10
     NFSD V4client            1            1K            1
             DEVFS            9            1K           10
               MCA            2            1K            2
               mld            2            1K            2
              igmp            2            1K            2
            vnodes            1            1K            1
           CAM SIM            1            1K            1
              ktls            1            1K            1
      NFSD lckfile            1            1K            1
       inpcbpolicy            7            1K           79
            feeder            7            1K            7
        loginclass            3            1K            7
             linux            5            1K            6
        aesni_data            2            1K            2
            soname            5            1K         2702
            DEVFSP            2            1K            2
            apmdev            1            1K            1
          atkbddev            2            1K            2
         vm_pgdata            1            1K            1
          procdesc            1            1K            2
          pmchooks            1            1K            1
          filecaps            4            1K           55
          nexusdev            6            1K            6
               tun            3            1K            3
        debugfsint            2            1K            2
     CAM dev queue            1            1K            1
           tcpfunc            1            1K            1
              vnet            1            1K            1
          acpiintr            1            1K            1
               pmc            1            1K            1
              cpus            2            1K            2
          freework            1            1K           20
    vnet_data_free            1            1K            1
          CAM path            1            1K           12
           entropy            1            1K           34
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
          savedino            0            0K            9
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
          freefrag            0            0K            4
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
            statfs            0            0K          206
     namei_tracker            0            0K            1
       export_host            0            0K            0
        cl_savebuf            0            0K            7
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
               iov            0            0K        11915
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
         sysctltmp            0            0K          526
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
   mbuf_jumbo_page   4096    1088    1034       13374       0     254    8691712        0
              pbuf   2624       0     778           0       0       2    2041472        0
          BUF TRIE    144     184   13312         464       0      62    1943424        0
       malloc-4096   4096     325       1         522       0       2    1335296        0
        malloc-128    128    9626      46        9632       0     126    1238016        0
         FFS inode   1160     524      15         534       0       8     625240        0
              mbuf    256    1347    1053       20574       0     254     614400        0
        malloc-512    512    1029      11        1037       0      30     532480        0
      malloc-65536  65536       7       0           7       0       1     458752        0
            lkpimm    160       1    2324           1       0      62     372000        0
          lkpicurr    160       2    2323           2       0      62     372000        0
       UMA Slabs 0    112    3049       8        3049       0     126     342384        0
        RADIX NODE    144    1960     193       17922       0      62     310032        0
       malloc-2048   2048     129       1         129       0       8     266240        0
      malloc-65536  65536       2       2         109       0       1     262144        0
      malloc-65536  65536       4       0           4       0       1     262144        0
             VNODE    448     555      21         567       0      30     258048        0
         VM OBJECT    264     852      48       11694       0      30     237600        0
         malloc-64     64    3475     179        4180       0     254     233856        0
        256 Bucket   2048      96      18        2707       0       8     233472        0
       malloc-4096   4096      50       3         738       0       2     217088        0
            DEVCTL   1024       0     200          97       0       0     204800        0
         malloc-16     16   12173     327       12222       0     254     200000        0
            THREAD   1808     103       7         103       0       8     198880        0
         UMA Zones    768     212       2         212       0      16     164352        0
        malloc-256    256     606       9        1035       0      62     157440        0
         malloc-32     32    4319      91        4346       0     254     141120        0
       FFS2 dinode    256     524      16         534       0      62     138240        0
      malloc-65536  65536       2       0           2       0       1     131072        0
      malloc-32768  32768       4       0           4       0       1     131072        0
        malloc-128    128     880      50        1896       0     126     119040        0
          ksiginfo    112      34    1010          47       0     126     116928        0
       S VFS Cache    104    1003      89        1058       0     126     113568        0
       malloc-1024   1024      93      11         114       0      16     106496        0
      mbuf_cluster   2048      45       1          45       0     254      94208        0
         MAP ENTRY     96     668     298       35277       0     126      92736        0
         vmem btag     56    1596      48        1596       0     254      92064        0
            clpbuf   2624       0      32          33       0      16      83968        0
          UMA Kegs    384     197       6         197       0      30      77952        0
       malloc-8192   8192       8       1          98       0       1      73728        0
        128 Bucket   1024      35      32         510       0      16      68608        0
              PROC   1336      36      15         724       0       8      68136        0
      malloc-65536  65536       1       0           1       0       1      65536        0
      malloc-65536  65536       1       0           1       0       1      65536        0
      malloc-16384  16384       4       0          76       0       1      65536        0
      malloc-16384  16384       4       0           4       0       1      65536        0
        malloc-384    384     155       5         155       0      30      61440        0
           DIRHASH   1024      54       2          54       0      16      57344        0
           VMSPACE   2544      16       5         705       0       4      53424        0
             g_bio    408       0     130        5146       0      30      53040        0
         filedesc0   1072      37      12         725       0       8      52528        0
        malloc-128    128     359      44       30501       0     126      51584        0
        malloc-256    256     157      38         585       0      62      49920        0
         malloc-64     64     605      88         853       0     254      44352        0
        malloc-128    128     284      57         530       0     126      43648        0
         32 Bucket    256      43     122        4799       0      62      42240        0
       Mountpoints   2752       6       8           6       0       4      38528        0
        malloc-256    256     121      29         145       0      62      38400        0
             NAMEI   1024       0      36       10796       0      16      36864        0
         64 Bucket    512      53      19        1051       0      30      36864        0
      malloc-32768  32768       0       1          52       0       1      32768        0
      malloc-32768  32768       1       0           1       0       1      32768        0
      malloc-32768  32768       1       0           1       0       1      32768        0
       malloc-8192   8192       4       0           4       0       1      32768        0
       malloc-8192   8192       4       0           4       0       1      32768        0
       malloc-4096   4096       6       2         272       0       2      32768        0
           pcpu-64     64     453      59         453       0     254      32768        0
        malloc-384    384      53      27          87       0      30      30720        0
        malloc-384    384      66      14          66       0      30      30720        0
       malloc-4096   4096       5       2         212       0       2      28672        0
            pcpu-8      8    3154     430        3166       0     254      28672        0
        malloc-256    256      87      18         135       0      62      26880        0
        malloc-384    384      52       8          52       0      30      23040        0
            socket    944      15       9        1024       0     254      22656        0
       malloc-2048   2048       6       4          62       0       8      20480        0
       malloc-2048   2048       9       1           9       0       8      20480        0
        malloc-128    128     115      40         163       0     126      19840        0
              pipe    744       7      18         274       0      16      18600        0
         TURNSTILE    136     111      15         111       0      62      17136        0
      malloc-16384  16384       0       1           2       0       1      16384        0
      malloc-16384  16384       1       0           1       0       1      16384        0
       malloc-4096   4096       3       1          49       0       2      16384        0
       malloc-1024   1024       8       8         966       0      16      16384        0
       malloc-1024   1024      13       3          13       0      16      16384        0
       malloc-1024   1024      11       5          11       0      16      16384        0
         malloc-64     64     132     120        1556       0     254      16128        0
         malloc-64     64     185      67       13379       0     254      16128        0
         malloc-32     32     323     181         432       0     254      16128        0
             tcpcb   1064       4      10           8       0     254      14896        0
        SLEEPQUEUE     88     111      49         111       0     126      14080        0
       malloc-4096   4096       1       2           5       0       2      12288        0
       malloc-2048   2048       3       3          12       0       8      12288        0
       malloc-2048   2048       1       5         212       0       8      12288        0
       malloc-1024   1024       7       5          11       0      16      12288        0
       malloc-1024   1024       4       8          15       0      16      12288        0
        malloc-512    512      12      12          12       0      30      12288        0
         malloc-64     64      84     105       10774       0     254      12096        0
         udp_inpcb    488       2      22          70       0     254      11712        0
       mbuf_packet    256       0      45          97       0     254      11520        0
        malloc-256    256      18      27         528       0      62      11520        0
        malloc-256    256      10      35         319       0      62      11520        0
       malloc-8192   8192       1       0           1       0       1       8192        0
       malloc-8192   8192       1       0           1       0       1       8192        0
       malloc-1024   1024       0       8           4       0      16       8192        0
       malloc-1024   1024       6       2           6       0      16       8192        0
        malloc-512    512       3      13         230       0      30       8192        0
        malloc-512    512       6      10           7       0      30       8192        0
           rtentry    176      13      33          17       0      62       8096        0
              PGRP     88      13      79          22       0     126       8096        0
          rl_entry     40      28     174          28       0     254       8080        0
             udpcb     32       2     250          70       0     254       8064        0
               PWD     32      11     241         101       0     254       8064        0
         malloc-64     64     112      14         140       0     254       8064        0
         malloc-64     64      18     108         248       0     254       8064        0
         malloc-32     32       5     247           6       0     254       8064        0
         malloc-32     32      89     163         243       0     254       8064        0
         malloc-32     32      39     213         629       0     254       8064        0
         malloc-32     32      46     206        4978       0     254       8064        0
         malloc-32     32      32     220         167       0     254       8064        0
         16 Bucket    144      36      20         207       0      62       8064        0
          4 Bucket     48       6     162          51       0     254       8064        0
          2 Bucket     32      40     212         478       0     254       8064        0
      vtnet_tx_hdr     24       1     333        6372       0     254       8016        0
            ttyinq    160      15      35          45       0      62       8000        0
             Files     80      63      37        5800       0     126       8000        0
         malloc-16     16      54     446          93       0     254       8000        0
         malloc-16     16     276     224         532       0     254       8000        0
         malloc-16     16      20     480          21       0     254       8000        0
         malloc-16     16     180     320         957       0     254       8000        0
         malloc-16     16      32     468       26661       0     254       8000        0
         malloc-16     16      15     485          21       0     254       8000        0
          8 Bucket     80      32      68         307       0     126       8000        0
        malloc-128    128       5      57          12       0     126       7936        0
        malloc-128    128      32      30          46       0     126       7936        0
        malloc-128    128      10      52          70       0     126       7936        0
         tcp_inpcb    488       4      12           8       0     254       7808        0
              kenv    258       2      28         697       0      30       7740        0
     routing nhops    256      10      20          17       0      62       7680        0
             unpcb    256       7      23         929       0     254       7680        0
           ttyoutq    256       8      22          24       0      62       7680        0
        malloc-384    384       0      20          16       0      30       7680        0
        malloc-384    384       5      15         183       0      30       7680        0
        malloc-384    384       7      13           7       0      30       7680        0
        malloc-384    384       0      20           3       0      30       7680        0
        malloc-256    256      14      16          89       0      62       7680        0
        malloc-256    256      16      14          26       0      62       7680        0
     FPU_save_area    832       1       8           1       0      16       7488        0
            cpuset    104       7      55           7       0     126       6448        0
 epoch_record pcpu    256       4      12           4       0      62       4096        0
       malloc-2048   2048       1       1           1       0       8       4096        0
       malloc-2048   2048       1       1           2       0       8       4096        0
       malloc-2048   2048       1       1           1       0       8       4096        0
        malloc-512    512       0       8           1       0      30       4096        0
           pcpu-16     16      14     242          14       0     254       4096        0
         hostcache     64       1      62           1       0     254       4032        0
          syncache    168       0      24           5       0     254       4032        0
         malloc-64     64       6      57           7       0     254       4032        0
         malloc-32     32       2     124           4       0     254       4032        0
         malloc-16     16       0     250           4       0     254       4000        0
             ripcb    488       1       7           1       0     254       3904        0
       UMA Slabs 1    176       6      16           6       0      62       3872        0
        KMAP ENTRY     96      21      18          25       0       0       3744        0
              vmem   1856       1       1           1       0       8       3712        0
           SMR CPU     32       3      60           3       0     254       2016        0
        SMR SHARED     24       3      60           3       0     254       1512        0
             swblk    136       0       0           0       0      62          0        0
          swpctrie    144       0       0           0       0      62          0        0
           ada_ccb    272       0       0           0       0      30          0        0
            da_ccb    544       0       0           0       0      16          0        0
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
               ipq     56       0       0           0       0     254          0        0
             KNOTE    160       0       0           0       0      62          0        0
            itimer    352       0       0           0       0      30          0        0
            AIOLIO    272       0       0           0       0      30          0        0
             AIOCB    552       0       0           0       0      16          0        0
              AIOP     32       0       0           0       0     254          0        0
               AIO    208       0       0           0       0      62          0        0
           NCLNODE    584       0       0           0       0      16          0        0
        TMPFS node    224       0       0           0       0      62          0        0
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
       malloc-8192   8192       0       0           0       0       1          0        0
       malloc-4096   4096       0       0           0       0       2          0        0
       malloc-4096   4096       0       0           0       0       2          0        0
        malloc-512    512       0       0           0       0      30          0        0
        malloc-512    512       0       0           0       0      30          0        0
        malloc-512    512       0       0           0       0      30          0        0
           pcpu-32     32       0       0           0       0     254          0        0
            pcpu-4      4       0       0           0       0     254          0        0
            fakepg    104       0       0           0       0     126          0        0
          UMA Hash    256       0       0           0       0      62          0        0


Syzkaller reproducer:
# {Threaded:false Collide:false Repeat:false RepeatTimes:0 Procs:1 Slowdown:1 Sandbox: Fault:false FaultCall:-1 FaultNth:0 Leak:false NetInjection:false NetDevices:false NetReset:false Cgroups:false BinfmtMisc:false CloseFDs:false KCSAN:false DevlinkPCI:false USB:false VhciInjection:false Wifi:false IEEE802154:false Sysctl:false UseTmpDir:false HandleSegv:false Repro:false Trace:false}
r0 = socket$inet6_tcp(0x1c, 0x1, 0x0)
sendto$inet6(r0, 0x0, 0x0, 0x101, &(0x7f0000000200)={0x1c, 0x1c, 0x1, 0x0, @local={0xfe, 0x80, '\x00', 0x0}}, 0x1c)
sendto$inet6(r0, 0x0, 0x0, 0x80, &(0x7f0000000000)={0x1c, 0x1c, 0x1, 0x0, @loopback}, 0x1c)


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
  res = syscall(SYS_socket, 0x1cul, 1ul, 0);
  if (res != -1)
    r[0] = res;
  *(uint8_t*)0x20000200 = 0x1c;
  *(uint8_t*)0x20000201 = 0x1c;
  *(uint16_t*)0x20000202 = htobe16(0x4e21);
  *(uint32_t*)0x20000204 = 0;
  *(uint8_t*)0x20000208 = 0xfe;
  *(uint8_t*)0x20000209 = 0x80;
  memset((void*)0x2000020a, 0, 12);
  *(uint8_t*)0x20000216 = 0;
  *(uint8_t*)0x20000217 = 0xaa;
  *(uint32_t*)0x20000218 = 0;
  syscall(SYS_sendto, r[0], 0ul, 0ul, 0x101ul, 0x20000200ul, 0x1cul);
  *(uint8_t*)0x20000000 = 0x1c;
  *(uint8_t*)0x20000001 = 0x1c;
  *(uint16_t*)0x20000002 = htobe16(0x4e21);
  *(uint32_t*)0x20000004 = 0;
  *(uint64_t*)0x20000008 = htobe64(0);
  *(uint64_t*)0x20000010 = htobe64(1);
  *(uint32_t*)0x20000018 = 0;
  syscall(SYS_sendto, r[0], 0ul, 0ul, 0x80ul, 0x20000000ul, 0x1cul);
  return 0;
}


