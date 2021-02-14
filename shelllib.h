#ifndef SHELLLIB_H
# define TYPE 0
# define ID 1
# define STATE 2
# define MAIN 0
# define CMD 1
# define OR 2
# define NA 2
# define FAILURE 0
# define SUCCESS 1
# define SHELLLIB_H
# define PROMPT_HEADER "Minishell_v2"
# define COMMANDS "ls pwd echo export unset cd env exit"
# define SYMBOL_LIST "> | < >> || << &&"
# define SINGLE_SYMBOL_END 2
# define SINGLE_SYMBOL_START 0
# define DOUBLE_SYMBOL_START 3
# define DOUBLE_SYMBOL_END 6
# define HPATH "srcs/history.msh"
# define CPATH "srcs/cache.msh"
# define EXEC_PATH "/bin/\n/bin/bash/\n/usr/bin/"
# define MARGIN 2
# define KEYUP "\033[A"
# define KEYDOWN "\033[B"
# define KEYLEFT "\033[D"
# define KEYRIGHT "\033[C"
# define BUFFER_SIZE 4
# define PIPEDEST "./srcs/pipe.msh"
# define FD_NO_CREAT_NL "\nCouldn't create/access: "
# define ISDIR_NL "\nIs directory: "
# define PAR_ERR "Unbalanced parenthesis.\n"
# define PID_ERR "Couldn't create pid\n"
# define LS "ls"
# define BUFF_SIZE 4
# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include "libft/libft.h"
# include "ft_fprintf/lprintf.h"
# include "gnl_working/get_next_line.h"
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
