/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_width.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:20:19 by motoure           #+#    #+#             */
/*   Updated: 2020/02/24 09:20:21 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lprintf.h"

char	*get_width(t_curr *flag)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	while (flag->arg[i] && flag->arg[i] != '.')
	{
		ft_putchar_str(&tmp, flag->arg[i]);
		i++;
	}
	return (tmp);
}
