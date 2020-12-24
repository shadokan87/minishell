#ifndef SHELLLIB_H
# define SHELLLIB_H
# define PROMPT_HEADER "Minishell_v2"
# define COMMANDS "ls pwd echo export unset cd env exit"
# define SYMBOL_LIST ">> < > |"
# define HPATH "srcs/history.msh"
# define MARGIN 2
# define KEYUP "\033[A"
# define KEYDOWN "\033[B"
# define KEYLEFT "\033[D"
# define KEYRIGHT "\033[C"
# define BUFFER_SIZE 4
# define PIPEDEST "./srcs/pipe.msh"
# define FD_NO_CREAT_NL "\nCouldn't create/access: "
# define ISDIR_NL "\nIs directory: "
# define LS "ls"
# define BUFF_SIZE 4
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
