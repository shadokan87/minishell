/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 09:19:45 by motoure           #+#    #+#             */
/*   Updated: 2020/02/23 09:19:53 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lprintf.h"

int			count(int n, int b_len)
{
	int count;

	count = 0;
	while (n)
	{
		n /= b_len;
		count++;
	}
	return (count);
}

static int	chck(char *base)
{
	int i;

	i = 0;
	while (base[i])
	{
		if (base[i] == ' ' || base[i] == '-'
		|| base[i] == '+')
			return (0);
		i++;
	}
	return (1);
}

static int	check_base(char *base)
{
	int i;
	int y;

	i = 0;
	y = 0;
	if (ft_strlen(base) <= 1 || !base || (!chck(base)))
		return (0);
	while (i <= ft_strlen(base) - 2)
	{
		y = i + 1;
		while (y <= ft_strlen(base) - 1)
		{
			if (base[i] == base[y])
				return (0);
			y++;
		}
		i++;
	}
	return (1);
}

char		*ft_putnbr_base(int n, char *base)
{
	int		i;
	char	*ret;
	int		negative;
	int		b_len;

	b_len = ft_strlen(base);
	negative = n > 0 ? 0 : 1;
	n = (negative) ? n *= -1 : n;
	i = 0;
	if (n == 0)
		return ("0");
	if (n == -2147483648 && base == DEC)
		return (ft_strdup("-2147483648"));
	if ((!(ret = malloc(sizeof(char) * count(n, b_len) + (negative) ? 2 : 1)))
	|| !check_base(base))
		return (0);
	while (n)
	{
		ret[i] = base[n % b_len];
		n /= b_len;
		i++;
	}
	ret[i] = (negative) ? '-' : '\0';
	ret[i + 1] = ret[i + 1] == '\0' ? 0 : '\0';
	return (ft_strrev(ret));
}
