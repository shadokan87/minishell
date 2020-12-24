#include "shelllib.h"

int	main(int argc, char **argv)
{
	char *str;
	char *str2;
	int i;
	int space;

	i = 0;
	str = argv[1];
	str2 = NULL;
	space = 0;
	while (str[i])
	{
		if (str[i + 1] == '>' && str[i] != ' ')
			space = 1;
		ft_putchar_str(&str2, str[i]);
		space ? ft_putchar_str(&str2, ' ') : 0;
		space = 0;
		i++;
	}
	ft_fprintf(1, "%s", str2);
}
