
#include <stdlib.h>

int		ft_strlen(char *str)
{
	int i;
	
	i = -1;
	if (!str)
		return (0);
	while (str[++i]);
	return (i);	
}

char	*ft_strdup(char *str)
{
	char *ret;
	int i;

	ret = NULL;
	i = -1;
	if (!(ret = malloc(sizeof(char) * ft_strlen(str) + 1)))
		return (0);
	ret[ft_strlen(str)] = '\0';
	while (str[++i])
		ret[i] = str[i];
	return (ret);
}

typedef struct s_queue
{
	char *command;
	struct s_queue * next;
	struct s_queue * prev;
}			t_queue;

int		init_queue(t_queue * fi)
{
	return (1);
}

int	main(void)
{
	t_queue fi;

	fi.command = ft_strdup("test");
	printf("%s", fi.command);
}
