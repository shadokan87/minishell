/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 01:19:23 by motoure           #+#    #+#             */
/*   Updated: 2020/01/18 06:31:13 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		c_len(char *str, char c)
{
	int i;

	i = 0;
	if (!str)
		return (-1);
	if (c == '\0')
	{
		while (str[i])
			i++;
		return (i);
	}
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strndup(char *str, int len)
{
	char	*ret;
	int		i;

	i = 0;
	if (!str)
		return (0);
	if (!(ret = malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (str[i] && i < len)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

void	str_join(char **dst, char *src)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	if (!(tmp = malloc(S(char) * c_len(*dst, '\0') + c_len(src, '\0') + 1)))
		return ;
	tmp2 = *dst;
	while (*tmp2)
	{
		tmp[i] = *tmp2;
		tmp2++ && i++;
	}
	free(*dst);
	while (*src)
	{
		tmp[i] = *src ? *src : '\0';
		src++ && i++;
	}
	tmp[i] = '\0';
	*dst = tmp;
}

int		return_value(char **stack, char **line)
{
	char *tmp;

	if (c_len(*stack, ENDL) > -1)
	{
		*line = ft_strndup(*stack, c_len(*stack, ENDL));
		tmp = ft_strndup(&(*stack)[c_len(*stack, ENDL) + 1],
				c_len(*stack, '\0'));
		free(*stack);
		*stack = tmp;
		return (1);
	}
	if (*stack && *stack[0] != '\0')
	{
		*line = ft_strndup(*stack, c_len(*stack, '\0'));
		free(*stack);
		*stack = NULL;
		return (1);
	}
	*stack ? free(*stack) : 0;
	*stack = NULL;
	return (0);
}
