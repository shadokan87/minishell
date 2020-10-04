/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 09:25:22 by motoure           #+#    #+#             */
/*   Updated: 2020/02/23 09:25:34 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lprintf.h"

void	ft_putstr(int fd, char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	write(fd, str, i);
}
