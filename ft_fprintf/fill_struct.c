/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:16:14 by motoure           #+#    #+#             */
/*   Updated: 2020/02/24 09:16:16 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lprintf.h"

int	fill_struct(t_curr *flag)
{
	flag->type = flag->arg[ft_strlen(flag->arg) - 1];
	fill_width(flag);
	fill_precision(flag);
	fill_width_type(flag);
	return (ft_strlen(flag->raw_arg) + 1);
}
