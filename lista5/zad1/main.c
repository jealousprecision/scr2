#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/sendfile.h>
#include <sys/stat.h>

#define P_READ 0
#define P_WRITE 1

int child_proc(int pipefd[]);

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        const char* usage_prompt = "usage: ./a.out textfile\n";
        write(STDOUT_FILENO, usage_prompt, strlen(usage_prompt));
        return -1;
    }

    int pipe_fd[2];
    pipe(pipe_fd);

    if (fork() == 0)
    {
        return child_proc(pipe_fd);
    }

    close(pipe_fd[P_READ]);

    int file_fd = open(argv[1], O_RDONLY);
    struct stat file_stats;
    fstat(file_fd, &file_stats);

    //sendfile(pipefd[P_WRITE], file_fd, NULL, file_stats.st_size);
    splice(file_fd, NULL, pipe_fd[P_WRITE], NULL, file_stats.st_size, 0);

    close(pipe_fd[P_WRITE]);
    return 0;
}

int child_proc(int pipefd[])
{
    close(pipefd[P_WRITE]);

    char buf[128];
    int bytes_read = 0;
    while ( (bytes_read = read(pipefd[P_READ], buf, sizeof(buf))) > 0 )
    {
        write(STDOUT_FILENO, buf, bytes_read);
    }

    close(pipefd[P_READ]);
    return 0;
}
