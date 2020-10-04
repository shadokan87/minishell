/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contain_num.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:15:59 by motoure           #+#    #+#             */
/*   Updated: 2020/02/24 09:16:03 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lprintf.h"

int		contain_num(char *str)
{
	int i;
	int ret;

	ret = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (is_num(str[i]))
			ret = 1;
		i++;
	}
	return (ret);
}
