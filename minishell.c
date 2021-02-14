
#include "shelllib.h"
#define DEBUG ft_fprintf(STDOUT_FILENO, 

typedef struct s_queue
{
	char *command;
	int read_mode;
	int write_mode;
	struct s_queue * n;
	struct s_queue * p;
}	t_queue;

typedef struct s_navigate
{
	int cursor;
} t_navigate;

typedef struct s_input
{
	char buff[BUFF_SIZE];
	char *tmp;
	char *on_screen_input;
	int prompt_status;
	int input_mode;
}	t_input;

typedef struct s_submit
{
	char *command;
	char *to_solve;
	int lop;
	int i;
	t_queue *cmd_q;
	t_queue *head;
	t_queue *tail;
}	t_submit;

typedef struct s_global
{
	t_input user_input;
	t_navigate nav;
	t_submit sub;
	t_queue *history;
	t_queue *head;
	t_queue *tail;
	t_queue *h_pos;
	int saved_stdout;
	int saved_stdin;
	int run_status;
	int	history_fd;
	int h_status;
	char *term_name;
	char *message;
	char **exec_path;
} t_global;

/////////////////

/*static char *ft_strndup(char *str, int len)
{
    char    *ret;
    int     i;

    i = 0;
    if (!str)
        return (0);
    if (!(ret = malloc(sizeof(char) * len + 1)))
        return (NULL);
    while (str[i] && i < len)
    {
        ret[i] = str[i];
        i++;
    }
    ret[i] = '\0';
    return (ret);
}
*/
////////////////

int	init_shell(t_global *global)
{
	const char *termName;
	char *bp;
	char *terminal;
	
	if (!(bp = malloc(sizeof(*bp))))
		return (0);
	if (!(terminal = getenv(global->term_name)))
		return (0);
	tgetent(bp, terminal);
	free(bp);
	ft_fprintf(1,
	global->term_name);
}

void	reset_attr()
{
	tcgetattr(STDIN_FILENO, &orig);
}

void	noncanon(t_global *global)
{
	tcgetattr(STDIN_FILENO, &orig);
	atexit(reset_attr);
	canon = orig;
 	canon.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &canon);
}

t_queue *fill(char *elem)
{
	t_queue *ret;

	if (!(ret = malloc(sizeof(t_queue))))
		return (0);
	ret->command = ft_strdup(elem);
	ret->n = NULL;
	ret->p = NULL;
	return (ret);
}

int		add(t_global *global, char *elem)
{
	t_queue *ret;

	ret = fill(elem);
	if (!global->head)
	{
		global->head = ret;
		global->tail = global->head;
		return (1);
	}
	ret->n = global->head;
	global->head->p = ret;
	global->head = ret;
	return (1);
}

void	init_queue(t_global *global)
{
	char *line;

	if (!(global->history_fd = open(HPATH, O_RDWR | O_CREAT, 0666 )))
		exit (0);
	global->history = NULL;
	global->head = NULL;
	global->tail = NULL;
	global->h_pos = NULL;
	while ((get_next_line(global->history_fd, &line)))
		add(global, line);
}

void	init_struct(t_global *global, char *term_name)
{
	global->term_name = ft_strdup(term_name);
	global->run_status = 1;
	global->nav.cursor = 0;
	global->user_input.on_screen_input = NULL;
	global->user_input.tmp = NULL;
	global->user_input.prompt_status = 0;
	global->sub.command = NULL;
	global->message = NULL;
	global->exec_path = ft_split(EXEC_PATH, '\n');
	init_queue(global);
}

int		update_cursor_pos(t_global *global, int ret)
{
	global->nav.cursor = ret;
	return (1);
}

int		keyleft(t_global *global)
{
	if (global->nav.cursor == 0)
		return (0);
	ft_fprintf(STDOUT_FILENO, "%s", KEYLEFT);
	update_cursor_pos(global, global->nav.cursor - 1);
	return (1);
}

int		keyright(t_global *global)
{
	if (global->nav.cursor == ft_strlen(global->user_input.on_screen_input))
		return (0);
	ft_fprintf(STDOUT_FILENO, "%s", KEYRIGHT);
	update_cursor_pos(global, global->nav.cursor + 1);
	return (1);
}

int		del_char(t_global *global, int len)
{
	int i;

	i = -1;
	if (global->nav.cursor == 0 || !len)
		return (0);
	while (++i < len)
	{
		ft_fprintf(STDOUT_FILENO, "\b \b");
		update_cursor_pos(global, global->nav.cursor - 1);
	}
	return (1);
}

int		trim_end(t_global *global)
{
	char *tmp;

	if (global->nav.cursor == 0)
		return (0);
	tmp = global->user_input.on_screen_input;
	del_char(global, 1);
	global->user_input.on_screen_input = ft_strndup(global->user_input.on_screen_input,
	ft_strlen(global->user_input.on_screen_input) - 1);
	free(tmp);
	return (1);
}

void	overwrite_user_input(t_global *global, char *new, int pos)
{
	while (keyright(global));
	while (trim_end(global));
	global->user_input.on_screen_input = ft_strdup(new);
	global->nav.cursor = ft_strlen(new);
	ft_fprintf(STDOUT_FILENO, "%s", global->user_input.on_screen_input);
	while (keyleft(global));
	while (pos)
	{
		keyright(global);
		pos--;
	}
}

int		keyup(t_global *global)
{
	if (!global->head)
		return (0);
	if (!global->h_pos)
	{
		global->h_pos = global->head;
		overwrite_user_input(global, global->h_pos->command, ft_strlen(global->h_pos->command));
		return (1);
	}
	else if (global->h_pos && global->h_pos != global->tail)
	{	
		global->h_pos = global->h_pos->n;
		if (!global->h_pos)
		{
			global->h_pos = global->tail;
			return (0);
		}
		overwrite_user_input(global, global->h_pos->command, ft_strlen(global->h_pos->command));
		return (1);
	}
	return (0);
}

int		keydown(t_global *global)
{
	if (!global->head)
		return (0);
	if (global->h_pos)
		global->h_pos = global->h_pos->p;
	if (global->h_pos)
		overwrite_user_input(global, global->h_pos->command, ft_strlen(global->h_pos->command));
	else
		global->h_pos = global->head;
	return (1);
}

int		listen_arrows(t_global *global)
{
	if (global->user_input.buff[0] != '\033')
		return (0);
	else if (ft_strcmp(KEYUP, global->user_input.buff))
		keyup(global);
	else if (ft_strcmp(KEYDOWN, global->user_input.buff))
		keydown(global);
	else if (ft_strcmp(KEYLEFT, global->user_input.buff))
		keyleft(global);
	else if (ft_strcmp(KEYRIGHT, global->user_input.buff))
		keyright(global);
	else
		return (0);
	return (1);

}

int		add_inside(t_global *global)
{
	char *new;

	new = NULL;
	if (global->user_input.buff[0] == '\033' || global->user_input.buff[0] == 127
	|| !ft_strlen(global->user_input.on_screen_input))
		return (0);
	if (global->user_input.buff[0] == '\n')
	{	
		ft_fprintf(STDOUT_FILENO, "\n Historique: %s", global->user_input.tmp);
		//exit (0);
	}
	new = ft_strjoin(ft_strjoin(ft_strndup(global->user_input.on_screen_input, global->nav.cursor),
	global->user_input.buff), &global->user_input.on_screen_input[global->nav.cursor]);
	overwrite_user_input(global, new, global->nav.cursor + 1);
	return (1);
}

void	trim_inside(t_global *global)
{
	char *new;

	new = ft_strjoin(ft_strndup(global->user_input.on_screen_input, global->nav.cursor - 1), 
	ft_strdup(&global->user_input.on_screen_input[global->nav.cursor]));
	overwrite_user_input(global, new, global->nav.cursor - 1);
}

int		listen_del(t_global *global)
{
	if (global->user_input.buff[0] != 127)
		return (0);
	if (global->nav.cursor > 0 &&
	global->nav.cursor == ft_strlen(global->user_input.on_screen_input))
		trim_end(global);
	else if (global->nav.cursor < ft_strlen(global->user_input.on_screen_input) &&
		global->nav.cursor)
		trim_inside(global);
}

void	 clear_buff(t_global *global)
{
	int i;

	i = -1;
	while (++i < BUFF_SIZE + 1)
		global->user_input.buff[i] = '\0';
}
void	navigate(t_global *global)
{
		listen_arrows(global);
}

int     check_single_symbol(char *str, int i)
{
    int y;
    char **symbols;

    y = SINGLE_SYMBOL_START;
    symbols = ft_split(SYMBOL_LIST, ' ');
    while (y <= DOUBLE_SYMBOL_END)
    {
        if (symbols[y][0] == str[i] && str[i + 1] != str[i])
            return (1);
        y++;
    }
    return (0);
}

int     check_double_symbol(char *str, int i)
{
    int y;
    char **symbols;

    y = DOUBLE_SYMBOL_START;
    symbols = ft_split(SYMBOL_LIST, ' ');
    while (y <= DOUBLE_SYMBOL_END)
    {
        if (symbols[y][0] == str[i] && symbols[y][1] == str[i + 1])
            return (1);
        y++;
    }
    return (0);
}

void	format_cmd(t_global *global)
{
	char *str;
	char *str2;
	int space;
	int i;

	str = global->user_input.on_screen_input;
	str2 = NULL;
	space = 0;
	i = 0;
	while (str[i])
	{
        if (check_double_symbol(str, i))
        {
            if (str[i - 1] != ' ')
                ft_putchar_str(&str2, ' ');
            ft_putchar_str(&str2, str[i]);
            ft_putchar_str(&str2, str[i + 1]);
            ft_putchar_str(&str2, ' ');
            i+=2;
        }
        else if (check_single_symbol(str, i))
        {
                str[i - 1] != ' ' ? ft_putchar_str(&str2, ' ') : 0;
                str[i + 1] != ' ' ? space = 1 : 0;
        }
        ft_putchar_str(&str2, str[i]);
        space ? ft_putchar_str(&str2, ' ') : 0;
        space = 0;
        i++;
    }
	global->sub.command = str2;
}

int		is_symbol(char *str)
{
	int i;
	char **symbols;

	i = 0;
	symbols = ft_split(ft_strdup(SYMBOL_LIST), ' ');
	while (symbols[i])
	{
		if (ft_strcmp(str, symbols[i]))
			return (i);
		i++;
	}
	return (0);
}

t_queue *fill_cmd(char *str, int read, int write)
{
	t_queue *ret;

	if (!(ret = malloc(sizeof(t_queue))))
		return (0);
	ret->command = ft_strdup(str);
	ret->read_mode = read;
	ret->write_mode = write;
	ret->n = NULL;
	ret->p = NULL;
	return (ret);
}

char	*splittostr(char **split, int i)
{
	char *ret;
	int y;

	y = 0;
	ret = NULL;
	while (y <= i)
	{
		if (!ret)
			ret = ft_strdup(split[i]);
	}
	return (ret);
}

void	debug_enqueue_cmd(t_global *global)
{	DEBUG "\n---- CMD QUEUE ----");
	DEBUG "\n%s", global->sub.head->command);
}

void	enqueue_cmd(t_global *global, char **split, int i, int read, int write)
{
	t_queue *ret;
	char *ret2;

	ret2 = splittostr(split, i);
	//exit (0);
	if (!global->sub.head)
	{
		global->sub.head = ret;
		global->sub.tail = global->sub.head;
		return ;
	}
	ret->n = global->sub.head;
	global->sub.head->p = ret;
	global->sub.head = ret;
}

void	cmd_queue(t_global *global)
{
	char **split;
	int i;
	int ret;

	i = 0;
	ret = -1;
	split = ft_split(global->sub.command, ' ');
	while (split[i])
	{
		if ((ret = is_symbol(split[i])))
		{
			ret == 1 ? enqueue_cmd(global, split, i - 1, 0, 1) : 0;
			ret == 1 ? enqueue_cmd(global, split, i + 1, 1, 0) : 0;
		}
		i++;
	}
}

int		process_cmd(t_global *global)
{
	if (!global->user_input.on_screen_input)
		return (0);
	global->sub.command = ft_strdup(global->user_input.on_screen_input);
	format_cmd(global);
	cmd_queue(global);
	return (1);
}

int check_par(t_global *global)
{
    int count;
    int open;
    int close;
    int i;
    int err;

    i = -1;
    open = 0;
    close = 0;
    err = 1;
	count = 0;
    while (global->sub.command[++i] && err)
    {
        if (global->sub.command[i] == '(' || global->sub.command[i] == ')')
            count++;
        close += global->sub.command[i] == ')' ? 1 : 0;
        err = close > open ? 0 : err;
        open += global->sub.command[i] == '(' ? 1 : 0;
    }
    err = open != close ? 0 : err;
    err = count % 2 == 0 ? err : 0;
    return (err);
}

int		do_solve(t_global *global)
{
	int i;
	char *str;

	str = global->sub.command;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '|' && str[i + 1] == '|')
		{
			ft_putchar_str(&global->sub.to_solve, '?');
			i += 2;
		}
		if (str[i] == '&' && str[i + 1] == '&')
		{
			ft_putchar_str(&global->sub.to_solve, ',');
			i += 2;
		}
		if (str[i] == ')' || str[i] == ';')
		{
			ft_putchar_str(&global->sub.to_solve, 27);
			ft_putchar_str(&global->sub.to_solve, '\n');
			ft_putchar_str(&global->sub.to_solve, 27);
		}
		else if (str[i] != '(')
			ft_putchar_str(&global->sub.to_solve, str[i]);
	}
	return (1);
}

int		exec_loop(t_global *global, char *str, char *path)
{
	int i;
	char **exec;
	pid_t pid;

	i = 0;
	exec = ft_split(str, ' ');
	if ((pid = fork()) == -1)
	{
		global->message = ft_strdup(PID_ERR);
		return (0);
	}
	else if (pid == 0)
		global->sub.lop = execve(ft_strjoin(path, exec[0]), &exec[0], NULL);
	if (waitpid(pid, 0, 0) == -1)
		return (-1);
	else
		return (1);
	return (0);

}

int		is_symbol2(t_global *global, int i)
{
	char **symbols;
	char c;
	int y;
	int z;
	char *str;

	y = 0;
	z = 0;
	symbols = ft_split(SYMBOL_LIST, ' ');
	str = global->sub.command;
	c = str[i];
	while (symbols[y])
	{
		if (symbols[y][0] == c && str[i + 1] != c)
		{
			if (str[i + 1] == '\0' || str[i + 1] == '\n')
				return (symbols[y][0]);
			return (1);
		}
		if (symbols[y][0] == c && str[i + 1] == c)
		{
			if (str[i + 2] == '\0' || str[i + 2] == '\n')
				return (symbols[y][0]);
			return (2);
		}
		y++;
	}
	return (0);
}

void	exec_all_path(t_global *global, char *str)
{
	int i;
	int ret;
	char **path;

	i = 0;
	ret = 0;
	path = ft_split(EXEC_PATH, '\n');
	while ((exec_loop(global, str, path[i]) && path[i]))
	{
		if (i > 0 && global->sub.lop == 0)
			break ;
		i++;
	}
}

void	exec_solve(t_global *global)
{
	char **split;

	global->sub.i = 0;
	split = ft_split(global->sub.to_solve, 27);
	while (global->sub.i < 1)
	{
		exec_all_path(global, split[global->sub.i]);
		global->sub.i++;
	}
}	


void	check_format(t_global *global)
{
	char *str;
	int i;
	int ret;

	i = 0;
	str = NULL;
	while (global->sub.command[i])
	{
		ret = is_symbol2(global, i);
		ret ? ft_putchar_str(&str, 27) : 0;
		ft_putchar_str(&str, global->sub.command[i]);
		ret == 2 ? ft_putchar_str(&str, global->sub.command[i+ 1]) : 0;
		ret ? ft_putchar_str(&str, 27) : 0;
		i+= ret == 2 ? 2 : 1;
	}
	free(global->sub.command);
	global->sub.command = str;
	do_solve(global);
	exec_solve(global);
}

int		submit(t_global *global)
{
	if (global->user_input.on_screen_input)
	{	
		add(global, global->user_input.on_screen_input);
		ft_fprintf(global->history_fd, "%s", global->user_input.on_screen_input);
		global->sub.command = ft_strdup(global->user_input.on_screen_input);
		check_format(global);
		exec_solve(global);
	}
	global->user_input.prompt_status = 0;
	return (global->message ? 0 : 1);
}

int		get_user_input(t_global *global)
{
	int ret;

	ret = 0;
	ret = read(STDIN_FILENO, &global->user_input.buff, 4);
	if (global->user_input.buff[0] == '\n')
		return (submit(global));
	global->user_input.input_mode = global->nav.cursor < ft_strlen(global->user_input.on_screen_input) ? 1 : 0;
	if (global->user_input.input_mode)
		return (add_inside(global));
	if (is_printable(global->user_input.buff[0]) && global->user_input.buff[0] != 127 &&
		global->nav.cursor == ft_strlen(global->user_input.on_screen_input))
		global->user_input.on_screen_input = global->user_input.on_screen_input ?
	ft_strjoin(global->user_input.on_screen_input, global->user_input.buff) : ft_strdup(global->user_input.buff);
	else if (global->nav.cursor < ft_strlen(global->user_input.on_screen_input))
		global->user_input.tmp = global->user_input.buff;
	return (is_printable(global->user_input.buff[0]) && global->user_input.buff[0] != 127 ? ret : 0);
}

int		echo_user_input(t_global *global)
{
	int ret;

	ret = 0;
	if ((ret = global->user_input.buff[0] && global->user_input.buff[0] != '\033' &&
		 global->user_input.buff[0] != 127) && !global->user_input.input_mode)
		ft_fprintf(STDOUT_FILENO, "%s", global->user_input.buff);
	return (ret);
}

int		set_prompt_margin(t_global *global)
{
	int i;

	i = -1;
	if (MARGIN <= 0)
		return (0);
	while (++i < MARGIN)
		ft_fprintf(STDOUT_FILENO, "%s", KEYRIGHT);
	return (i);
}

void	debug2(t_global *global)
{
	DEBUG "%s %d", global->user_input.on_screen_input, global->nav.cursor);
	exit(0);
}

void	debug_submit(t_global *global)
{
	if (!global->sub.command)
		return ;
	DEBUG "\nCommand: %s", global->sub.command);
	exit (0);
}

void	reset_message(t_global *global)
{
	if (global->message)
	{
		ft_fprintf(STDOUT_FILENO, "%s", global->message);
		free(global->message);
		global->message = NULL;
	}
	if (global->sub.command)
	{
		free(global->sub.command);
		global->sub.command = NULL;
	}
	if (global->sub.to_solve)
	{
		free(global->sub.to_solve);
		global->sub.to_solve = NULL;
	}
	global->sub.lop = 0;
}

int		new_prompt(t_global *global)
{
	if (global->user_input.prompt_status)
	{
		update_cursor_pos(global, global->nav.cursor + get_user_input(global));
		echo_user_input(global);
		//debug2(global);
		return (global->user_input.prompt_status);
	}
	if (global->user_input.on_screen_input)
	{
		free(global->user_input.on_screen_input);
		global->user_input.on_screen_input = NULL;
	}
	reset_message(global);
	global->nav.cursor = 0;
	global->h_pos = NULL;
	ft_fprintf(STDOUT_FILENO, "%s", PROMPT_HEADER);
	set_prompt_margin(global);
	global->user_input.prompt_status = 1;
	//debug_submit(global);
	return (global->user_input.prompt_status);
}

int		edit_user_input(t_global *global)
{
	listen_del(global);
}

int	main(void)
{
	t_global global;
	init_struct(&global, "minishell_v2");
	noncanon(&global);
	while (global.run_status)
	{
		new_prompt(&global);
		navigate(&global);
		edit_user_input(&global);
		clear_buff(&global);
	}
}
