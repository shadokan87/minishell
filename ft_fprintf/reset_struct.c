/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_struct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:21:35 by motoure           #+#    #+#             */
/*   Updated: 2020/02/24 09:21:39 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lprintf.h"

void	reset_struct(t_curr *flag)
{
	flag->arg = NULL;
	flag->type = '0';
	flag->precision = 0;
	flag->width = 0;
	flag->width_type = 0;
}
