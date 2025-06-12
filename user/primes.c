// user/primes.c
#include "kernel/types.h"
#include "user/user.h"

void sieve(int);

int main()
{
    int p[2];
    pipe(p);
    if (fork() == 0)
    {
        close(p[1]);
        sieve(p[0]);
    }
    else
    {
        close(p[0]);
        for (int i = 2; i <= 35; ++i)
        {
            write(p[1], &i, sizeof(int));
        }
        close(p[1]);
        wait((int *)0);
    }
    exit(0);
}

void sieve(int read_fd)
{
    int first_num;
    if (read(read_fd, &first_num, sizeof(int)) == 0)
    {
        exit(0);
    }
    printf("pid: %d, prime: %d\n", getpid(), first_num);
    int p[2];
    pipe(p);
    if (fork() == 0)
    {
        close(p[1]);
        sieve(p[0]);
    }
    else
    {
        close(p[0]);
        int get_num;
        while (read(read_fd, &get_num, sizeof(int)))
        {
            if (get_num % first_num != 0)
            {
                write(p[1], &get_num, sizeof(int));
            }
        }
        close(p[1]);
        wait((int *)0);
    }
    exit(0);
}