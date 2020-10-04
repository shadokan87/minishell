/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 13:11:46 by motoure           #+#    #+#             */
/*   Updated: 2020/01/07 22:26:22 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lprintf.h"

static char	*cpy_from_till(const char *s, char *str, int from, int till)
{
	int i;

	i = 0;
	while (i < till)
	{
		str[i] = s[from];
		i++;
		from++;
	}
	str[i] = '\0';
	return (str);
}

static int	words_count(char const *s, char c)
{
	int count;
	int i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	**ft_free(char **arr, int i)
{
	while (--i)
	{
		free(arr[i]);
		arr[i] = 0;
	}
	free(arr);
	arr = 0;
	return (NULL);
}

static int	*ewl(char const *s, char c)
{
	int y;
	int count;
	int *ret;

	count = 0;
	y = 0;
	if (!(ret = malloc(sizeof(int) * words_count(s, c))))
		return (0);
	while (*s != '\0')
	{
		*s == c ? s++ : 0;
		if (*s != c && *s != '\0')
		{
			while (*s != c && *s != '\0')
			{
				s++;
				count++;
			}
			ret[y] = count;
			count = 0;
			y++;
		}
	}
	return (ret);
}

char		**ft_split(char const *s, char c)
{
	int		i;
	int		*words_len;
	char	**arr;
	int		y;

	if (!s || (!(words_len = ewl(s, c))))
		return (0);
	i = 0;
	y = 0;
	if ((!(arr = malloc(sizeof(char *) * words_count(s, c) + 1))))
		return (0);
	while (i < words_count(s, c))
	{
		if (!(arr[i] = malloc(sizeof(char) * words_len[i] + 1)))
			return (ft_free(arr, i));
		while (s[y] == c && s[y])
			y++;
		cpy_from_till(s, arr[i], y, words_len[i]);
		while (s[y] && s[y] != c)
			y++;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
