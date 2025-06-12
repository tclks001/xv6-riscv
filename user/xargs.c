#include "user/user.h"
#include "kernel/param.h"

char *strdup(const char *s)
{
    char *p = malloc(sizeof(char) * (strlen(s) + 1));
    strcpy(p, s); // 拷贝
    return p;
}

int main(int argc, char *argv[])
{
    char *xargv[MAXARG];
    for (int i = 1; i < argc; ++i)
    {
        xargv[i - 1] = argv[i];
    }
    int ori_argc = --argc;
    char get_char;
    char buf[512];
    int i = 0;
    /*
    for (int i = 0; i < argc; ++i)
    {
        printf("xargv[%d]: %s\n", i, xargv[i]);
    }
    */
    while (read(0, &get_char, sizeof(char)) == sizeof(char))
    {
        if (get_char == '\n')
        {
            buf[i] = 0;
            xargv[argc++] = strdup(buf);
            // printf("xargv[%d]=%s\n", argc - 1, xargv[argc - 1]);
            xargv[argc] = 0;
            if (fork() == 0)
            {
                exec(xargv[0], xargv);
                fprintf(2, "exec failed\n");
                exit(1);
            }
            else
            {
                wait((int *)0);
                i = 0;
                argc = ori_argc;
            }
        }
        else if (get_char == ' ')
        {
            buf[i] = 0;
            xargv[argc++] = strdup(buf);
            // printf("xargv[%d]=%s\n", argc - 1, xargv[argc - 1]);
            i = 0;
        }
        else
        {
            buf[i++] = get_char;
        }
    }
    exit(0);
}