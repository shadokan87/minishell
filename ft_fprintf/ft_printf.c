/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 08:16:21 by motoure           #+#    #+#             */
/*   Updated: 2020/05/13 15:57:04 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lprintf.h"

char	*get_raw_arg(const char *str, int i)
{
	char *ret;

	ret = NULL;
	i++;
	while (str && str[i])
	{
		ft_putchar_str(&ret, str[i]);
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

int		ft_fprintf(int fd, const char *str, ...)
{
	int		i;
	int		ret;
	t_curr	flag;
	va_list args;

	i = 0;
	ret = ft_strlen((char *)str);
	reset_struct(&flag);
	va_start(args, str);
	flag.fd = fd;
	while (str[i])
	{
		if (str[i] == '%' && (flag.arg = get_next_arg(str, i, args)) != NULL)
		{
			flag.raw_arg = get_raw_arg(str, i);
			ret -= ret > 0 ? (fill_struct(&flag)) : 0;
			ret += print_struct(&flag, args);
			i += ft_strlen(flag.raw_arg) + 1;
			reset_struct(&flag);
		}
		else
			write_const(flag.fd, str, &i);
	}
	va_end(args);
	return (ret);
}
