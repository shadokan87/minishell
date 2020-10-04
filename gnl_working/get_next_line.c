/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 01:21:02 by motoure           #+#    #+#             */
/*   Updated: 2020/01/18 06:31:07 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	char		buff[BUFFER_SIZE + 1];
	static char *stack[4094];
	int			file;
	char		*tmp;

	tmp = NULL;
	if (fd < 0 || line == NULL)
		return (-1);
	while (c_len(stack[fd], ENDL) == -1)
	{
		file = read(fd, buff, BUFFER_SIZE);
		buff[file] = '\0';
		if (file > 0)
		{
			if (!stack[fd])
				stack[fd] = ft_strndup(buff, c_len(buff, '\0'));
			else
				str_join(&stack[fd], buff);
		}
		if (file == 0)
			break ;
	}
	return (return_value(&stack[fd], line));
}
