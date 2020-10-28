#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    const char* KOM = "Komunikat dla rodzica.\n";
    int potok_fd[2], licz, status;
    char bufor[BUFSIZ];

    pipe(potok_fd);
    if (fork() == 0)
    {
        // child
        write(potok_fd[1], KOM, strlen(KOM));
        exit(0);

        // after child exits, their
        // pipe handles are removed
    }

    // parent
    // close our pipe save handle
    close(potok_fd[1]);

    while ( (licz=read(potok_fd[0], bufor, BUFSIZ)) > 0)
    {
        //write(1, bufor, licz);
        fwrite(bufor, sizeof(char), licz, stdout);
    }

    wait(&status);
    return status;
}
