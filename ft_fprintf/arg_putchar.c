/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_putchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:14:58 by motoure           #+#    #+#             */
/*   Updated: 2020/02/24 09:15:01 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lprintf.h"

void	arg_putchar(t_curr *flag, va_list args, int *ret)
{
	int		to_ret;
	char	c;

	c = flag->type == '%' ? '%' : (char)va_arg(args, int);
	to_ret = 1;
	flag->width_type != DASH ? write_width(flag, to_ret, -1) : 0;
	ft_putchar(flag->fd, c);
	flag->width_type == DASH ? write_width(flag, to_ret, -1) : 0;
	to_ret = to_ret < flag->width ? flag->width : to_ret;
	*ret += to_ret;
}
