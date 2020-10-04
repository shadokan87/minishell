/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 01:17:40 by motoure           #+#    #+#             */
/*   Updated: 2019/11/08 13:52:57 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lprintf.h"

char	*ft_strdup(const char *s1)
{
	char *ret;

	ret = NULL;
	if (!s1)
		return (ft_strdup("(null)"));
	if (ft_strlen((char *)s1) == 0)
	{
		if (!(ret = malloc(sizeof(char) * 1)))
			return (0);
		ret[0] = '\0';
		return (ret);
	}
	while (*s1)
	{
		ft_putchar_str(&ret, *s1);
		s1++;
	}
	return (ret);
}
