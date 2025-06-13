struct sysinfo
{
    int freemem; // free memory in bytes
    int nproc;   // number of processes whose state is not UNUSED
    int load;    // load average * 100
};