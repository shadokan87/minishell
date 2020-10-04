/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hidden_of.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:20:26 by motoure           #+#    #+#             */
/*   Updated: 2020/02/24 09:20:29 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lprintf.h"

char	*hidden_of(char *str)
{
	int		i;
	char	*hidden;

	hidden = NULL;
	i = 0;
	while (*str)
	{
		ft_putchar_str(&hidden,
		ft_putnbr_base((unsigned int)*str, HEXD)[0]);
		str++;
	}
	return (hidden);
}
