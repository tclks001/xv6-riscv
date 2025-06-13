#include "user/user.h"
#define MAXARG 10

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(2, "Usage: trace <trace_mask> <command> [args...]\n");
        exit(1);
    }
    int trace_mask = atoi(argv[1]);
    trace(trace_mask);
    exec(argv[2], &argv[2]);
    fprintf(2, "exec %s failed\n", argv[2]);
    exit(1);
}