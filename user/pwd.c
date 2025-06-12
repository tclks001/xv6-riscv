#include "user/user.h"
#include "kernel/fcntl.h"
#include "kernel/stat.h"
#include "kernel/fs.h"

#define MAX_DEPTH 10

void getpwd(char *path)
{
    struct stat st, parent_st;
    char name[DIRSIZ + 1];
    char *paths[MAX_DEPTH];
    int depth = 0;

    int fd = open(".", O_RDONLY);
    fstat(fd, &st);
    while (1)
    {
        // printf("depth = %d\n", depth);
        // printf("cwd ino: %d\n", st.ino);
        int parent_fd = open("..", O_RDONLY);
        fstat(parent_fd, &parent_st);
        if (parent_st.ino == st.ino) // 根目录
        {
            close(parent_fd);
            break;
        }
        // printf("pnt ino: %d\n", parent_st.ino);
        chdir("..");
        struct dirent de;
        while (read(parent_fd, &de, sizeof(de)) == sizeof(de))
        {
            if (de.inum == 0 || strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
            {
                continue;
            }
            strcpy(name, de.name);
            name[DIRSIZ] = '\0';
            int fd_check = open(name, O_RDONLY);
            struct stat st_check;
            fstat(fd_check, &st_check);

            // printf("bro ino: %d\n", st_check.ino);

            if (st_check.ino == st.ino)
            {
                char *copy = malloc(strlen(name) + 2);
                strcpy(copy, name);
                paths[depth++] = copy;
                // printf("paths[%d] = %s\n", depth - 1, paths[depth - 1]);
                close(fd_check);
                break;
            }
            close(fd_check);
        }

        close(fd);
        fd = parent_fd;
        st = parent_st;
    }
    char *p = path;
    *p = '~';
    --depth;
    while (depth >= 0)
    {
        p = path + strlen(path);
        *p++ = '/';
        strcpy(p, paths[depth]);
        chdir(paths[depth]);
        free(paths[depth]);
        --depth;
    }
    return;
}

int main()
{
    char path[512] = "";
    getpwd(path);
    printf("%s\n", path);
    exit(0);
}