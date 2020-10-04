/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_putunsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:15:45 by motoure           #+#    #+#             */
/*   Updated: 2020/02/24 09:15:49 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lprintf.h"

void	arg_putunsigned(t_curr *flag, va_list args, int *ret)
{
	int to_ret;
	int n;

	n = va_arg(args, int);
	to_ret = ft_nbrlen_u(n);
	to_ret = flag->precision > 0 && flag->precision > to_ret ?
	flag->precision : to_ret;
	flag->width_type != DASH ? write_width(flag, to_ret, -1) : 0;
	write_precision(flag->fd, flag->precision, ft_nbrlen(n));
	print_value_u(flag, n, &to_ret);
	if (flag->precision == -1)
		*ret += n == 0 && flag->width > 0 ? to_ret : 0;
	else
		*ret += to_ret;
}
