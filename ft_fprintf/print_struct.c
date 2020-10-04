/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:21:07 by motoure           #+#    #+#             */
/*   Updated: 2020/02/24 09:21:10 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lprintf.h"

int	print_struct(t_curr *flag, va_list args)
{
	int ret;

	ret = 0;
	flag->type == 'd' ? arg_putnbr(flag, args, &ret) : 0;
	flag->type == 'i' ? arg_putnbr(flag, args, &ret) : 0;
	flag->type == 'u' ? arg_putunsigned(flag, args, &ret) : 0;
	flag->type == 'p' ? arg_putptr(flag, args, &ret) : 0;
	flag->type == 's' ? arg_putstr(flag, args, &ret) : 0;
	flag->type == 'x' ? arg_puthexa(flag, args, &ret) : 0;
	flag->type == 'X' ? arg_puthexa(flag, args, &ret) : 0;
	flag->type == 'c' ? arg_putchar(flag, args, &ret) : 0;
	flag->type == '%' ? arg_putchar(flag, args, &ret) : 0;
	return (ret);
}
