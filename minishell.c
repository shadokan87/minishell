
#include "shelllib.h"
#define DEBUG ft_fprintf(STDOUT_FILENO, 

typedef struct s_queue
{
	char *command;
	int read;
	int output;
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
	
} t_global;

/////////////////

static char *ft_strndup(char *str, int len)
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
		exit (0);
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

int		submit(t_global *global)
{
	add(global, global->user_input.on_screen_input);
	ft_fprintf(global->history_fd, "%s\n", global->user_input.on_screen_input);
	global->user_input.prompt_status = 0;
	return (1);
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
		global->user_input.on_screen_input = 0;
	}
	global->nav.cursor = 0;
	global->h_pos = NULL;
	ft_fprintf(STDOUT_FILENO, "%s", PROMPT_HEADER);
	set_prompt_margin(global);
	global->user_input.prompt_status = 1;
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
