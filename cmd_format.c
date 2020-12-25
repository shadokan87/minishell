#include "shelllib.h"

int		check_single_symbol(char *str, int i)
{
	int y;
	char **symbols;

	y = SINGLE_SYMBOL_START;
	symbols = ft_split(SYMBOL_LIST, ' ');
	while (y <= DOUBLE_SYMBOL_END)
	{
		if (symbols[y][0] == str[i] && str[i + 1] != str[i])
			return (1);
		y++;
	}
	return (0);
}

int		check_double_symbol(char *str, int i)
{
	int y;
	char **symbols;

	y = DOUBLE_SYMBOL_START;
	symbols = ft_split(SYMBOL_LIST, ' ');
	while (y <= DOUBLE_SYMBOL_END)
	{
		if (symbols[y][0] == str[i] && symbols[y][1] == str[i + 1])
			return (1);
		y++;
	}
	return (0);
}

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
		if (check_double_symbol(str, i))
		{
			if (str[i - 1] != ' ')
				ft_putchar_str(&str2, ' ');
			ft_putchar_str(&str2, str[i]);
			ft_putchar_str(&str2, str[i + 1]);
			ft_putchar_str(&str2, ' ');
			i+=2;
		}
		else if (check_single_symbol(str, i))
		{
				str[i - 1] != ' ' ? ft_putchar_str(&str2, ' ') : 0;
				str[i + 1] != ' ' ? space = 1 : 0;
		}
		ft_putchar_str(&str2, str[i]);
		space ? ft_putchar_str(&str2, ' ') : 0;
		space = 0;
		i++;
	}
	ft_fprintf(1, "%s", str2);
}
