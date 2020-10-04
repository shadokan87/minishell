/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_puthexa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:15:08 by motoure           #+#    #+#             */
/*   Updated: 2020/08/15 18:46:53 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lprintf.h"

void	arg_puthexa(t_curr *flag, va_list args, int *ret)
{
	int				to_ret;
	unsigned int	n;

	n = va_arg(args, unsigned int);
	to_ret = ft_strlen(ft_putnbr_base_u(n, HEXD));
	if (flag->width_type != DASH)
		write_width(flag, (to_ret < flag->precision ?
					flag->precision : to_ret), -1);
	write_precision(flag->fd, flag->precision, to_ret);
	to_ret = to_ret < flag->precision ? flag->precision : to_ret;
	if (n != 0)
		ft_putstr(flag->fd, ft_putnbr_base_u(n, flag->type == 'x' ?
HEXD : MAJHEXD));
	else if (n == 0 && flag->precision != -1)
		ft_putchar(flag->fd, '0');
	else if (flag->precision == -1 && flag->width > 0)
		ft_putchar(flag->fd, ' ');
	flag->width_type == DASH ? write_width(flag, to_ret, -1) : 0;
	to_ret = to_ret < flag->width ? flag->width : to_ret;
	*ret += to_ret - (flag->precision == -1 &&
			flag->width == 0 && n == 0 ? to_ret : 0);
}
