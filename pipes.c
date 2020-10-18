
#include "shelllib.h"

int		redir_fd(int from, int to)
{
	if (from == -1 || to == -1)
		return (-1);
	else if (!(dup2(dup(from), to)))
		return (-1);
	return (to);
}

int		fd_from_to(int source, int target)
{
	if (!(dup2(dup(source), target)))
		return (0);
	return (1);
}

int     open_pipe(int pipedest)
{
	fd_from_to(pipedest, STDOUT_FILENO);
	fd_from_to(pipedest, STDIN_FILENO);
}

int	main(int argc, char **argv)
{
	int new_stdout;
	int saved_stdout;
	int saved_stdin;
	int pid;

	new_stdout = -1;
	if ((new_stdout = open("./testredir", O_CREAT | O_RDWR | O_APPEND)) == -1)
		return (0);
	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	open_pipe(new_stdout);
	printf("test");
	if ((pid = fork()) == 0)
	{
		if (!execve(ft_strjoin("/usr/bin/", argv[1]), &argv[1], NULL))
		return (0);
	}
	wait(NULL);
}
