
#include "lprintf.h"

int	ft_strcmp(char *str1, char *str2)
{
	int i;

	i = 0;
	if (ft_strlen(str1) != ft_strlen(str2) || !str1 || !str2)
		return (0);
	while (str1[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
}
