#include "types.h"
#include "riscv.h"
#include "defs.h"

// Directly copy from src to dst,
// using user memory space virtual address
// which also mapped in kernel page table
// when myproc()->kpagetable set in satp
int copyin_new(char *dst, const char *src, uint64 len)
{
    if (src >= MAXVA || src + len >= MAXVA)
    {
        return -1;
    }
    memmove(dst, src, len);
    return 0;
}

// Directly use virtual address when myproc()->kpagetable set in satp.
// Copy will stop when encounter '\0' or max bytes copied.
// If get '\0', return 0, else return -1.
int copyinstr_new(char *dst, const char *src, uint64 max)
{
    if (src >= MAXVA)
    {
        return -1;
    }
    int got_null = 0;
    char *p = src;
    while (got_null == 0 && max > 0)
    {
        if (p < 0 || p >= MAXVA)
        {
            return -1;
        }
        if (*p == '\0')
        {
            *dst = '\0';
            got_null = 1;
            break;
        }
        else
        {
            *dst = *p;
        }
        --max;
        ++dst;
        ++p;
    }
    return got_null ? 0 : -1;
}