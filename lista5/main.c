#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <fcntl.h>
#include <ctype.h>

#define P_READ 0
#define P_WRITE 1

int child_proc(int pipefd[]);
void trim_whitespace(char* string);

int main()
{
    int pipefd[2];
    pipe(pipefd);

    if (fork() == 0)
    {
        return child_proc(pipefd);
    }

    close(pipefd[P_READ]);


    const char* prompt = "Enter image name: ";
    write(STDOUT_FILENO, prompt, strlen(prompt));


    char img_name[80];
    int img_name_size = read(STDIN_FILENO, img_name, sizeof(img_name) - 1);
    img_name[img_name_size] = '\0';
    trim_whitespace(img_name);


    int img_fd = open(img_name, O_RDONLY);
    char img_buf[512];
    int img_buf_size = 0;
    while ( (img_buf_size = read(img_fd, img_buf, sizeof(img_buf))) > 0)
    {
        write(pipefd[P_WRITE], img_buf, img_buf_size);
    }


    const char* continue_prompt = "Press enter to continue...";
    write(STDOUT_FILENO, continue_prompt, strlen(continue_prompt));
    char c;
    read(STDIN_FILENO, &c, 1);


    close(pipefd[P_WRITE]);
    return 0;
}

int child_proc(int pipefd[])
{
    close(pipefd[P_WRITE]);

    dup2(pipefd[P_READ], STDIN_FILENO);
    execlp("display", "display", NULL);

    // just in case
    close(pipefd[P_READ]);
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
