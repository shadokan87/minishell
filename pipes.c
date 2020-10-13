
#include <unistd.h>
#include <fcntl.h>

int	redir_fd(int from, int to)
{
	if (from == -1 || to == -1)
		return (-1);
	else if (!(dup2(dup(from), to)))
		return (-1);
	return (to);
}

int		open_pipe()
{
	int fd;
	int save;

	save = -1;
	if ((fd = open("./srcs/pipe.msh", O_CREAT | O_RDWR | O_TRUNC)) == -1)
		return (0);
	if ((save = redir_fd(fd, STDOUT_FILENO) == -1))
		return (0);
}

int		close_pipe()
{
	
}

int	main(void)
{

}
