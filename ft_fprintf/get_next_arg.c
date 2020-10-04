/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:20:12 by motoure           #+#    #+#             */
/*   Updated: 2020/05/13 16:08:08 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lprintf.h"

int		locate_c(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	write_star_suite(char **ret, int n, char *ptr, int precision)
{
	int		y;
	char	*tmp;

	tmp = NULL;
	y = 0;
	if ((!precision && n < 0 && ptr && ptr[ft_strlen(ptr) - 1] != '-')
	|| (!precision && n < 0 && !ptr))
		ft_putchar_str(ret, '-');
	n = n < 0 ? n * -1 : n;
	tmp = ft_putnbr_base(n, DEC);
	while (tmp[y])
	{
		ft_putchar_str(ret, tmp[y]);
		y++;
	}
}

void	write_star(char **ret, int n)
{
	char	*tmp;
	char	*ptr;
	int		y;
	int		precision;

	y = 0;
	ptr = NULL;
	ptr = *ret;
	precision = 0;
	if (ptr && locate_c(*ret, '.') >= 0)
	{
		if (n < 0)
		{
			tmp = ft_strdup(*ret);
			tmp[locate_c(tmp, '.')] = '\0';
			*ret ? free(*ret) : 0;
			*ret = ft_strdup(tmp);
			tmp ? free(tmp) : 0;
			return ;
		}
		precision = 1;
	}
	write_star_suite(ret, n, ptr, precision);
}

char	*get_next_arg(const char *str, int i, va_list args)
{
	char *ret;

	ret = NULL;
	i++;
	while (str && str[i])
	{
		str[i] == STAR ? write_star(&ret, va_arg(args, int)) : 0;
		str[i] != STAR ? ft_putchar_str(&ret, str[i]) : 0;
		if (is_arg(ret[ft_strlen(ret) - 1]))
			break ;
		i++;
	}
	if (ret && !is_arg(ret[ft_strlen(ret) - 1]))
	{
		free(ret);
		ret = NULL;
	}
	return (ret);
}
