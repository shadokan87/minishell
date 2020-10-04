/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_width_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:16:28 by motoure           #+#    #+#             */
/*   Updated: 2020/02/24 09:16:32 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lprintf.h"

void	fill_width_type(t_curr *flag)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	while (flag->arg && flag->arg[i] && flag->arg[i - 1] != '.')
	{
		ft_putchar_str(&tmp, flag->arg[i]);
		i++;
	}
	i = 0;
	if (tmp && c_str(tmp, DASH))
		flag->width_type = flag->width > 0 ? DASH : 0;
	else
	{
		while (tmp && tmp[i] && !is_num(tmp[i]))
			i++;
		if (tmp && tmp[i] == '0' && flag->width_type != DASH &&
		!c_str(flag->arg, '.'))
			flag->width_type = flag->width > 0 ? ZERO : 0;
	}
	free(tmp);
}
