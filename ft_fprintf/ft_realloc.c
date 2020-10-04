/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 09:30:38 by motoure           #+#    #+#             */
/*   Updated: 2020/02/23 09:30:45 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lprintf.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*return_value;

	return_value = NULL;
	if (!ptr)
		return (malloc(size));
	else if (size <= (unsigned long)ft_strlen((char *)ptr))
		return (ptr);
	else
	{
		if (!(return_value = malloc(size)))
			return (0);
		ft_memsub((void **)&return_value, ptr, 0, -1);
		free(ptr);
	}
	return (return_value);
}
