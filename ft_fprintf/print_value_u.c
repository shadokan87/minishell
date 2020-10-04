/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_value_u.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:21:24 by motoure           #+#    #+#             */
/*   Updated: 2020/02/24 09:21:26 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lprintf.h"

void	print_value_u(t_curr *flag, int n, int *to_ret)
{
	if (flag->precision == -1)
		n == 0 && flag->width > 0 ? ft_putchar(flag->fd, ' ') : 0;
	else
		ft_putstr(flag->fd, ft_putnbr_base_u(n, DEC));
	flag->width_type == DASH ? write_width(flag, *to_ret, -1) : 0;
	*to_ret = *to_ret < flag->width ? flag->width : *to_ret;
}
