
#include <unistd.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int pid;
	int status;
	
	status = 0;
	if ((pid = fork()) == 0)
		execve(argv[1], &argv[1], NULL);
	wait();
	write(1, "test", 4);
	write(1, "test", 4);
	write(1, "test", 4);
}
