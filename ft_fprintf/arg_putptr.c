/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_putptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:15:30 by motoure           #+#    #+#             */
/*   Updated: 2020/02/24 09:15:32 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lprintf.h"

void	arg_putptr(t_curr *flag, va_list args, int *ret)
{
	int					to_ret;
	unsigned long int	n;

	n = va_arg(args, unsigned long int);
	to_ret = ft_ptrlen(n) - (n == 0 && flag->precision == -1 ? 1 : 0);
	write_precision(flag->fd, flag->precision, to_ret);
	to_ret = to_ret < flag->precision ? flag->precision : to_ret;
	if (flag->width_type != DASH)
		write_width(flag, to_ret, flag->precision ==
		-1 && n == 0 && flag->width ? flag->width - 2 : -1);
	ft_putptr(n, flag);
	if (flag->width_type == DASH)
		write_width(flag, to_ret, flag->precision ==
		-1 && n == 0 && flag->width ? flag->width - 2 : -1);
	to_ret = to_ret < flag->width ? flag->width : to_ret;
	*ret += to_ret;
}
