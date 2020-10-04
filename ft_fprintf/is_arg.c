/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_arg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:20:43 by motoure           #+#    #+#             */
/*   Updated: 2020/02/24 09:20:45 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lprintf.h"

int	is_arg(char c)
{
	int		i;
	char	*arg_list;

	arg_list = ft_strdup("cspdiuxX%");
	i = 0;
	while (arg_list[i])
	{
		if (c == arg_list[i])
			return (1);
		i++;
	}
	return (0);
}
