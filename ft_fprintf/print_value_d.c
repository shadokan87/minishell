/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_value_d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:21:16 by motoure           #+#    #+#             */
/*   Updated: 2020/02/24 09:21:18 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lprintf.h"

void	print_value_d(t_curr *flag, int n, int swap, int *to_ret)
{
	if (swap != INT_MIN)
		swap < 0 && flag->precision == 0 && flag->width_type
		!= ZERO ? ft_putchar(flag->fd, '-') : 0;
	if (flag->precision == -1 && n == 0 && swap != INT_MIN)
		flag->width > 0 ? ft_putchar(flag->fd, ' ') : 0;
	else
		ft_putnbr(flag->fd, n);
	flag->width_type == DASH ? write_width(flag, *to_ret, -1) : 0;
	*to_ret += (swap < 0 ? 1 : 0);
	if (*to_ret < flag->width)
		*to_ret = flag->width + (swap < 0 ? 1 : 0);
}
