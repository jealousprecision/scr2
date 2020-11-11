#include <time.h>
#include <signal.h>
#include <stdio.h>
#include <stdbool.h>

#define NANO_TO_MILLI 1000000

void signal_handle(int sig);

bool running = true;

int main()
{
	signal(SIGALRM, signal_handle);
	signal(SIGTERM, signal_handle);
	signal(SIGUSR1, signal_handle);
	signal(SIGUSR2, signal_handle);

	struct timespec tspec;
	tspec.tv_sec = 0;
	tspec.tv_nsec = 100 * NANO_TO_MILLI;

	volatile int i = 0;
	while (running)
	{
		++i;
		nanosleep(&tspec, NULL);
	}
}

void signal_handle(int sig)
{
	switch (sig)
	{
	case SIGALRM:
		printf("Catched SIGALRM\n");
		break;
	case SIGTERM:
		printf("Catched SIGTERM\n");
		running = false;
		break;
	case SIGUSR1:
		printf("Catched SIGUSR1\n");
		break;
	}
}
