#include <time.h>

#define NANO_TO_MILLI 1000000

int main()
{
	struct timespec tspec;
	tspec.tv_sec = 0;
	tspec.tv_nsec = 100 * NANO_TO_MILLI;

	volatile int i = 0;
	while (1)
	{
		++i;
		//nanosleep(&tspec, NULL);
	}
}

// top -d ss.t
// ss - seconds, t - tenths
