#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

int volatile count;

void handler(int sig)
{
	printf("singal%douch that hurt\n" ,sig);
	count++;
}
int main(void)
{
	struct sigaction sa;

	int pid = getpid();
	printf("ok,let's go, kill me(%d) if you can !\n", pid);
	sa.sa_handler = handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL) != 0)
		return (1);
	while (count != 4)
	{}
	printf("ive had enough\n");
	return (0);
}