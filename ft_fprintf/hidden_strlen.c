/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hidden_strlen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:20:34 by motoure           #+#    #+#             */
/*   Updated: 2020/02/24 09:20:36 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lprintf.h"

int	hidden_strlen(char *str, char *tmp)
{
	int i;

	i = 0;
	if (tmp && is_hidden(tmp))
		return (ft_strlen(hidden_of(tmp)));
	else
		return (ft_strlen(str));
}
