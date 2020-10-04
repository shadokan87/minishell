/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 22:48:46 by motoure           #+#    #+#             */
/*   Updated: 2020/01/08 16:05:44 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lprintf.h"

int	ft_atoi(const char *str)
{
	int return_value;
	int i;
	int sign;
	int check;

	sign = 1;
	return_value = 0;
	i = 0;
	check = -1;
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		return_value = return_value * 10 + str[i] - '0';
		i++;
	}
	return (return_value * sign);
}
