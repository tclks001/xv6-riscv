#include "kernel/sysinfo.h"
#include "user/user.h"

int main()
{
    struct sysinfo info;
    sysinfo(&info);
    printf("Free memory: %d\n", info.freemem);
    printf("Number of processes: %d\n", info.nproc);

    int intpart = info.load / 100;
    int fracpart = info.load % 100;
    // format the load average string
    if (fracpart < 10)
        printf("Load average: %d.0%d\n", intpart, fracpart);
    else
        printf("Load average: %d.%d\n", intpart, fracpart);
    exit(0);
}