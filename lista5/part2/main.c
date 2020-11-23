#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <ctype.h>

void trim_whitespace(char* string);

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        const char* error_prompt = "usage: ./a.out FIFO\n";
        write(STDOUT_FILENO, error_prompt, strlen(error_prompt));
        return -1;
    }

    int fifo_fd = open(argv[1], O_WRONLY);

    while (1)
    {
        const char* prompt = "Enter file name: ";
        write(STDOUT_FILENO, prompt, strlen(prompt));

        char img_name[80];
        int img_name_size = read(STDIN_FILENO, img_name, sizeof(img_name) - 1);
        img_name[img_name_size] = '\0';
        trim_whitespace(img_name);

        int file_fd = open(img_name, O_RDONLY);
        char file_buf[512];
        int file_buf_size = 0;
        while ( (file_buf_size = read(file_fd, file_buf, sizeof(file_buf))) > 0)
        {
            write(fifo_fd, file_buf, file_buf_size);
        }

        if (file_buf_size < 0)
        {
            const char* error_prompt = "Error when reading a file\n";
            write(STDOUT_FILENO, error_prompt, strlen(error_prompt));
            break;
        }
    }


    close(fifo_fd);

    return 0;
}

void trim_whitespace(char* string)
{
    for (int i = strlen(string) - 1; i > 0; --i)
    {
        if (isspace(string[i]))
            string[i] = '\0';
        else
            break;
    }
}
