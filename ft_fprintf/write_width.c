/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_width.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:22:01 by motoure           #+#    #+#             */
/*   Updated: 2020/02/24 09:22:07 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lprintf.h"

void	write_width(t_curr *flag, int len, int exception)
{
	int tmp;

	tmp = flag->width;
	if (exception > -1)
	{
		while (exception)
		{
			ft_putchar(flag->fd, ' ');
			exception--;
		}
		return ;
	}
	if (tmp == 0 || tmp <= len)
		return ;
	while (tmp != len)
	{
		ft_putchar(flag->fd, flag->width_type == ZERO ? '0' : ' ');
		tmp--;
	}
}
