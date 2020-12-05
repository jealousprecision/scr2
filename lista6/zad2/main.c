#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define BUF_SIZE 256

void strip_whitespace(char* str);
void check_mmap_return_value(void* mapped);
void check_munmap_return_value(int mapped);
int child_proc();

const char out_filename[] = "output";

int main()
{
    if (fork() == 0)
    {
        return child_proc();
    }

    int out_fd = open(out_filename, O_RDWR);
    struct stat out_stats;
    fstat(out_fd, &out_stats);
    int out_mapped_size = out_stats.st_size;
    void* out_mapped = mmap(NULL, out_mapped_size, PROT_WRITE, MAP_SHARED, out_fd, 0);
    check_mmap_return_value(out_mapped);

    while (true)
    {
        const char prompt[] = "Filename: ";
        write(STDOUT_FILENO, prompt, sizeof(prompt));

        char filename[BUF_SIZE];
        int filename_size = read(STDIN_FILENO, filename, BUF_SIZE - 1);
        filename[filename_size] = '\0';
        strip_whitespace(filename);

        struct stat in_stats;
        stat(filename, &in_stats);

        check_munmap_return_value(munmap(out_mapped, out_mapped_size));
        ftruncate(out_fd, in_stats.st_size);

        out_mapped = mmap(NULL, in_stats.st_size, PROT_WRITE, MAP_SHARED, out_fd, 0);
        check_mmap_return_value(out_mapped);
        out_mapped_size = in_stats.st_size;

        int in_fd = open(filename, O_RDONLY);
        read(in_fd, out_mapped, in_stats.st_size);
        close(in_fd);

        msync(out_mapped, out_mapped_size, MS_SYNC);
    }
}

int child_proc()
{
    //execlp("display", "display", "-update", "1", out_filename, NULL);
    execlp("eom", "eom", out_filename, NULL);
    return -1;
}

void strip_whitespace(char* str)
{
    for (int n = strlen(str) - 1; n >= 0; --n)
    {
        if (isspace(str[n]))
            str[n] = '\0';
        else
            break;
    }
}

void check_mmap_return_value(void* mapped)
{
    if (mapped == MAP_FAILED)
    {
        const char error[] = "mmap failed\n";
        write(STDOUT_FILENO, error, sizeof(error));
        exit(-1);
    }
}

void check_munmap_return_value(int mapped)
{
    if (mapped != 0)
    {
        const char error[] = "munmap failed\n";
        write(STDOUT_FILENO, error, sizeof(error));
        exit(-1);
    }
}
