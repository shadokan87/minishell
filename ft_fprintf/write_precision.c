/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_precision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:21:52 by motoure           #+#    #+#             */
/*   Updated: 2020/02/24 09:21:54 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lprintf.h"

void	write_precision(int fd, int precision, int len)
{
	if (precision <= len)
		return ;
	while (precision != len)
	{
		ft_putchar(fd, '0');
		precision--;
	}
}
