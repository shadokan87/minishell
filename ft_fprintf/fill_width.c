/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_width.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:16:20 by motoure           #+#    #+#             */
/*   Updated: 2020/02/24 09:16:25 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lprintf.h"

void	fill_width(t_curr *flag)
{
	int		i;
	char	*tmp;
	char	*n;

	i = 0;
	tmp = get_width(flag);
	n = NULL;
	if (tmp && tmp[i] == '0')
		i++;
	while (tmp && tmp[i] && contain_num(tmp) &&
			!is_num(tmp[i]) && !c_str(tmp, STAR))
		i++;
	while (tmp && is_num(tmp[i]) && !c_str(tmp, STAR))
	{
		ft_putchar_str(&n, tmp[i]);
		i++;
	}
	if (n)
		flag->width = ft_atoi(n);
	!n ? flag->width = 0 : 0;
	n ? free(n) : 0;
	tmp ? free(tmp) : 0;
}
