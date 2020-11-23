#include <unistd.h>
#include <stdio.h>
#include <string.h>

int child_proc();

#define P_READ 0
#define P_WRITE 1

int main()
{
    int pipefd[2];
    pipe(pipefd);

    if (fork() == 0)
    {
        return child_proc(pipefd);
    }

    close(pipefd[P_READ]);

    const char* hello = "Hello, ";
    const char* world = "world!\n";
    write(pipefd[P_WRITE], hello, strlen(hello));
    write(pipefd[P_WRITE], world, strlen(world));

    close(pipefd[P_WRITE]);
    return 0;
}

int child_proc(int pipefd[])
{
    close(pipefd[P_WRITE]);

    char buffer[128];
    while (read(pipefd[P_READ], buffer, 128))
    {
        printf("%s", buffer);
    }

    close(pipefd[P_READ]);

    return 0;
}
