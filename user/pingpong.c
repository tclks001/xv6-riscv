// user/pingpong.c
#include "kernel/types.h"
#include "user/user.h"

int main()
{

    // create two pipes
    // p1: parent to child
    // p2: child to parent
    int p1[2], p2[2];
    int get_num = 0, send_num = 0;

    // 0 means read end, 1 means write end
    pipe(p1);
    pipe(p2);

    if (fork() == 0)
    {
        // child process
        // read from p1[0] and write to p2[1]
        close(p1[1]);
        close(p2[0]);

        read(p1[0], &get_num, sizeof(int));
        printf("%d: recieved ping\n", getpid());
        write(p2[1], &send_num, sizeof(int));

        close(p1[0]);
        close(p2[1]);
        exit(0);
    }
    else
    {
        // parent process
        // read from p2[0] and write to p1[1]
        close(p1[0]);
        close(p2[1]);

        write(p1[1], &send_num, sizeof(int));
        read(p2[0], &get_num, sizeof(int));
        printf("%d: recieved pong\n", getpid());

        close(p1[1]);
        close(p2[0]);
        wait(0);
        exit(0);
    }
}