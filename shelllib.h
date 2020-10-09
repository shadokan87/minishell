#ifndef SHELLLIB_H
# define SHELLLIB_H
# define HPATH "srcs/history"
# define KEYUP "\033[A"
# define KEYDOWN "\033[B"
# define KEYLEFT "\033[D"
# define KEYRIGHT "\033[C"
# define BUFFER_SIZE 4
# define LS "ls"
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include "libft/libft.h"
# include "ft_fprintf/lprintf.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
#include        <stdio.h>
#include        <curses.h>
#include        <term.h>
#include		<termios.h>
#include        <stdlib.h>
struct		termios canon;
struct		termios orig;
# endif
