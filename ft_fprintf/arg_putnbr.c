/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_putnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:15:21 by motoure           #+#    #+#             */
/*   Updated: 2020/02/24 09:15:24 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lprintf.h"

void	arg_putnbr(t_curr *flag, va_list args, int *ret)
{
	int to_ret;
	int n;
	int swap;

	n = va_arg(args, int);
	swap = n;
	to_ret = ft_nbrlen(n);
	to_ret = flag->precision > 0 && flag->precision > to_ret ?
	flag->precision : to_ret;
	n < 0 ? flag->width-- : 0;
	if (n != INT_MIN)
		n < 0 && flag->precision == 0 &&
		flag->width_type == ZERO ? ft_putchar(flag->fd, '-') : 0;
	flag->width_type != DASH ? write_width(flag, to_ret, -1) : 0;
	if (n != INT_MIN)
		n < 0 && flag->precision != 0 ? ft_putchar(flag->fd, '-') : 0;
	write_precision(flag->fd, flag->precision, ft_nbrlen(n));
	n < 0 ? n *= -1 : 0;
	print_value_d(flag, n, swap, &to_ret);
	*ret += !flag->width && flag->precision == -1 ? 0 : to_ret;
}
