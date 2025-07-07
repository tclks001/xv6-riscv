> xv6 is a re-implementation of Dennis Ritchie's and Ken Thompson's Unix
> Version 6 (v6). xv6 loosely follows the structure and style of v6,
> but is implemented for a modern RISC-V multiprocessor using ANSI C.
>
> ACKNOWLEDGMENTS
>
> xv6 is inspired by John Lions's Commentary on UNIX 6th Edition (Peer
> to Peer Communications; ISBN: 1-57398-013-7; 1st edition (June 14,
> 2000)). See also https://pdos.csail.mit.edu/6.1810/, which provides
> pointers to on-line resources for v6.
>
> The following people have made contributions: Russ Cox (context switching,
> locking), Cliff Frey (MP), Xiao Yu (MP), Nickolai Zeldovich, and Austin
> Clements.
>
> We are also grateful for the bug reports and patches contributed by
> Takahiro Aoyagi, Marcelo Arroyo, Silas Boyd-Wickizer, Anton Burtsev,
> carlclone, Ian Chen, Dan Cross, Cody Cutler, Mike CAT, Tej Chajed,
> Asami Doi,Wenyang Duan, eyalz800, Nelson Elhage, Saar Ettinger, Alice
> Ferrazzi, Nathaniel Filardo, flespark, Peter Froehlich, Yakir Goaron,
> Shivam Handa, Matt Harvey, Bryan Henry, jaichenhengjie, Jim Huang,
> Matúš Jókay, John Jolly, Alexander Kapshuk, Anders Kaseorg, kehao95,
> Wolfgang Keller, Jungwoo Kim, Jonathan Kimmitt, Eddie Kohler, Vadim
> Kolontsov, Austin Liew, l0stman, Pavan Maddamsetti, Imbar Marinescu,
> Yandong Mao, Matan Shabtay, Hitoshi Mitake, Carmi Merimovich, Mark
> Morrissey, mtasm, Joel Nider, Hayato Ohhashi, OptimisticSide,
> phosphagos, Harry Porter, Greg Price, RayAndrew, Jude Rich, segfault,
> Ayan Shafqat, Eldar Sehayek, Yongming Shen, Fumiya Shigemitsu, snoire,
> Taojie, Cam Tenny, tyfkda, Warren Toomey, Stephen Tu, Alissa Tung,
> Rafael Ubal, Amane Uehara, Pablo Ventura, Xi Wang, WaheedHafez,
> Keiichi Watanabe, Lucas Wolf, Nicolas Wolovick, wxdao, Grant Wu, x653,
> Jindong Zhang, Icenowy Zheng, ZhUyU1997, and Zou Chang Wei.
>
> ERROR REPORTS
>
> Please send errors and suggestions to Frans Kaashoek and Robert Morris
> (kaashoek,rtm@mit.edu). The main purpose of xv6 is as a teaching
> operating system for MIT's 6.1810, so we are more interested in
> simplifications and clarifications than new features.
>
> BUILDING AND RUNNING XV6
>
> You will need a RISC-V "newlib" tool chain from
> https://github.com/riscv/riscv-gnu-toolchain, and qemu compiled for
> riscv64-softmmu. Once they are installed, and in your shell
> search path, you can run "make qemu".

# 新增功能

## lab1

1. `sleep` 命令：休眠一段时间，由第二个参数指定，表示休眠的 ticks 数。
2. `pingpong`：创建管道和子进程，父进程给子进程发送数据，子进程接收数据并发送给父进程，父进程收到数据。
3. `primes`：创建管道和子进程。父进程首先给子进程发送 2~35，子进程将第一个数判断为质数，并筛掉后边是本数倍数的数，再创建子进程，递归判断，直到筛完。
4. `find` 命令：在指定目录及其子目录递归查找文件，支持正则表达式。
5. `xargs` 命令：从标准输入读取若干行，每行都作为该命令的额外参数执行。
6. `uptime` 命令：显示开机以来运行的 ticks 数。
7. `pwd` 命令：显示当前工作目录。
8. 修改 `shell`，始终显示当前工作目录。

## lab2

1. 实现 `trace` 系统调用，记录系统调用和返回值。
2. 实现 `sysinfo` 系统调用，显示系统信息：空闲内存、进程数、平均负载。

## lab3

1. 实现`vmprint`函数，打印当前页表树。

    > ```
    > ..0             : pte 0x0000000021fd2801 pa 0x0000000087f4a000 ----v
    > .. ..0          : pte 0x0000000021fd2401 pa 0x0000000087f49000 ----v
    > .. .. ..0       : pte 0x0000000021fd2c1b pa 0x0000000087f4b000 ux-rv
    > .. .. ..1       : pte 0x0000000021fd2017 pa 0x0000000087f48000 u-wrv
    > .. .. ..2       : pte 0x0000000021fd1c07 pa 0x0000000087f47000 --wrv
    > .. .. ..3       : pte 0x0000000021fd1817 pa 0x0000000087f46000 u-wrv
    > ..255           : pte 0x0000000021fd3401 pa 0x0000000087f4d000 ----v
    > .. ..511        : pte 0x0000000021fd3001 pa 0x0000000087f4c000 ----v
    > .. .. ..510     : pte 0x0000000021fd5807 pa 0x0000000087f56000 --wrv
    > .. .. ..511     : pte 0x000000002000180b pa 0x0000000080006000 -x-rv
    > ```

2. 实现每个进程的内核页表，进程在内核态执行时切换成内核页表。
3. 修改`copyin`和`copyinstr`函数，在内核页表下直接引用虚拟地址。

## lab4

1. 实现`backtrace`，在内核 panic 时打印调用栈。
