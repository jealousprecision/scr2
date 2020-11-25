#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <ctype.h>

#define P_READ 0
#define P_WRITE 1
#define BUF_SIZE 128

int child_proc(int pipefd[]);
void send_buf(int in_fd, int out_fd);

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        const char usage_prompt[] = "usage: ./a.out imagefile\n";
        write(STDOUT_FILENO, usage_prompt, sizeof(usage_prompt));
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
    send_buf(file_fd, pipe_fd[P_WRITE]);

    const char continue_prompt[] = "Press enter to continue...";
    write(STDOUT_FILENO, continue_prompt, sizeof(continue_prompt));
    char c;
    read(STDIN_FILENO, &c, 1);

    close(pipe_fd[P_WRITE]);
    return 0;
}

int child_proc(int pipefd[])
{
    close(pipefd[P_WRITE]);
    close(STDIN_FILENO);
    dup2(pipefd[P_READ], STDIN_FILENO);
    execlp("display", "display", NULL);
    return -1;
}

void send_buf(int in_fd, int out_fd)
{
    char buf[BUF_SIZE];
    int bytes_read = 0;
    while ((bytes_read = read(in_fd, buf, sizeof(buf))) > 0)
    {
        write(out_fd, buf, bytes_read);
    }
}
