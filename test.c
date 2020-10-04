
#include <stdlib.h>

void	printarr(char ***str)
{
	int i;
	int y;

	i = 0;
	y = 0;
	while (str[i])
	{
		printf("Command : %s / ", str[i][0]);
		while (str[i][++y])
			printf("Args : %s", str[i][y]);
		printf("\n");
		i++;
		y = 0;
	}
}

int	main(void)
{
	char ***str;
	int commandnum;
	int i;
	
	i = 0;
	commandnum = 4;
	str = malloc(sizeof(char**) * commandnum + 1);
	while (i < commandnum)
	{
		str[i] = malloc(sizeof(char *) * 3);
		str[i][0] = strdup("test");
		str[i][1] = strdup("arg");
		str[i][2] = NULL;
		i++;
	}
	str[commandnum] = NULL;
	printarr(str);
}
