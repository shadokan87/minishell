/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_putstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:15:37 by motoure           #+#    #+#             */
/*   Updated: 2020/02/24 09:15:40 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lprintf.h"

void	arg_putstr(t_curr *flag, va_list args, int *ret)
{
	int		to_ret;
	char	*str;
	char	*tmp;
	int		i;

	i = 0;
	tmp = va_arg(args, char *);
	str = ft_strdup(tmp);
	if (flag->precision > 0 && flag->precision < ft_strlen(str))
		str[flag->precision] = '\0';
	to_ret = hidden_strlen(str, tmp);
	if (flag->width_type != DASH)
		write_width(flag, to_ret,
		flag->precision == -1 ? flag->width : -1);
	flag->precision > -1 ? ft_putstr(flag->fd, str) : 0;
	if (flag->width_type == DASH)
		write_width(flag, to_ret,
	flag->precision == -1 ? flag->width : -1);
	to_ret = to_ret < flag->width ? flag->width : to_ret;
	to_ret = flag->width && flag->precision == -1 ? flag->width : to_ret;
	*ret += !flag->width && flag->precision == -1 ? 0 : to_ret;
}
