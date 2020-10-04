/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motoure <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 01:23:40 by motoure           #+#    #+#             */
/*   Updated: 2020/01/18 06:31:50 by motoure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define ENDL '\n'
# define S sizeof
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../shelllib.h"

int		get_next_line(int fd, char **line);
int		c_len(char *str, char c);
char	*ft_strndup(char *str, int len);
void	str_join(char **dst, char *src);
int		return_value(char **stack, char **line);

#endif
