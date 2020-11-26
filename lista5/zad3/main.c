#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 128

void send_buf(int in_fd, int out_fd);

int main(int argc, const char** argv)
{
    if (argc < 2)
    {
        const char prompt[] = "usage: ./a.out files...\n";
        write(STDOUT_FILENO, prompt, sizeof(prompt));
        return -1;
    }

    int fd_pipe = open("potok1", O_WRONLY);

    for (int file_idx = 1; file_idx < argc; ++file_idx)
    {
        int file_fd = open(argv[file_idx], O_RDONLY);
        send_buf(file_fd, fd_pipe);
        close(file_fd);

        printf("Sent file: %s\n", argv[file_idx]);
        sleep(2);
    }

    close(fd_pipe);
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
