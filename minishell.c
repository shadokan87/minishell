#include "shelllib.h"
#define DEBUG ft_fprintf(STDOUT_FILENO,

typedef struct s_queue
{
	char *command;
	struct s_queue * next;
	struct s_queue * prev;
}			t_queue;

typedef struct	s_var
{
	char	buff[BUFFER_SIZE];
	char	*command;
	char	*command_queue;
	char	*to_free;
	int		shell;
	int		fd;
	int		cursor;
	int		cursor_pos;
	int		debug;
	int		launch_status;
	t_queue	*history;
	t_queue *h_head;
	t_queue *h_tail;
	t_queue *display_pos;
}				t_var;

static char	*strndup(char *str, int len)
{
	char	*ret;
	int		i;

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

int	ft_strcmp(char *str, char *str2)
{
	int i;

	i = 0;
	if (ft_strlen(str) != ft_strlen(str2))
		return (0);
	while (str[i])
	{
		if (str[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
}

//linked list start//

t_queue *add(char *str)
{
	t_queue *ret;

	if (!(ret = malloc(sizeof(t_queue))))
		return (NULL);
	ret->command = ft_strdup(str);
	ret->next = NULL;
	ret->prev = NULL;
	return (ret);
}

void	printlist(t_queue *head)
{
	t_queue *tmp;

	tmp = head;
	while (tmp)
	{
		ft_fprintf(STDOUT_FILENO, "\n Queue : %s - ", tmp->command);
		tmp = tmp->next;
	}
}

void	init_queue(t_queue **queue, t_queue **head)
{
	*queue = NULL;
	*head = NULL;
}

void	create_queue(t_queue **queue, t_queue **head, char *str)
{
	*queue = add(str);
	*head = *queue;
}

void	*add_to_head(t_queue **head, char *str)
{
	t_queue *head2;
	t_queue *new;
	t_queue *tmp;
	
	tmp = *head;
	head2 = NULL;
	head2 = *head;
	new = add(str);
	head2->prev = new;
	new->next = head2;
	head2 = new;
	*head = head2;
}

int		enqueue(t_queue **queue, t_queue **head, char *str)
{
	t_queue *head2;

	head2 = NULL;
	if (!*queue)
		create_queue(queue, head, str);
	else
		add_to_head(head, str);
}
// linked list end //
void	closeTerminal(void)
{
	exit (0);
}

void	commandPwd(void)
{
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	ft_fprintf(STDOUT_FILENO, "\n%s", pwd);
}

int	initShell(void)
{
	const char *termName;
	char  *bp;
	char  *terminal;
	int   height;
	int   width;

	bp = malloc(sizeof(*bp));
	termName = "TERM";
	if (!(terminal = getenv(termName)))
		closeTerminal();
	tgetent(bp, terminal);
	free(bp);
	ft_fprintf(1, "\n");
	ft_fprintf(1, "minishell");
	ft_fprintf(1, "_> ");
	return (1);
}

void	commandClear(void)
{
	char *str;

	str = NULL;
	str = tgetstr("cl", NULL);
	ft_fprintf(STDOUT_FILENO, "%s", str);
}

void	cmd_mv_cursor()
{
	char *cm_cap;

	cm_cap = tgetstr("cm", NULL);
	tputs(tgoto(cm_cap, 5, 5), 1, putchar);
}

void	test(void)
{
	tcgetattr(STDIN_FILENO, &orig);
}

void	noncanon(void)
{	
	tcgetattr(STDIN_FILENO, &orig);
	atexit(test);
	canon = orig;
	canon.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &canon);
}

void	init_struct(t_var *var, t_queue **queue, t_queue **head)
{
	var->command = NULL;
	var->shell = 0;
	var->cursor = 0;
	var->command_queue = NULL;
	*queue = NULL;
	*head = NULL;
}

t_queue *get_tail(t_queue **head)
{
	t_queue *ret;
	t_queue *tmp;

	tmp = NULL;
	ret = NULL;
	ret = *head;
	tmp = *head;
	while (tmp)
	{
		tmp = tmp->next;
		ret = tmp ? tmp : ret;
	}
	return (ret);
}

int		init_history(t_var *var)
{
	char *command;
	int ret;

	ret = -1;
	var->history = NULL;
	var->h_head = NULL;
	var->h_tail = NULL;
	var->to_free = NULL;
	var->fd = open(HPATH, O_RDWR | O_APPEND);
	while ((get_next_line(var->fd, &command)))
		enqueue(&var->history, &var->h_head, command);
	var->display_pos = var->h_head;
	//var->h_tail = get_tail(&var->h_head);
}

int		update_history(t_var *var)
{
	if (!var->h_head)
	{
		ft_fprintf(var->fd, "%s\n", var->command);
		init_history(var);
		return (0);
	}
	else if (!ft_strcmp(var->h_head->command, var->command) && ft_strlen(var->command))
	{
		ft_fprintf(var->fd, "%s\n", var->command);
		enqueue(&var->history, &var->h_head, var->command);
	}
	return (1);
}

void	reset(t_var *var, t_queue **queue, t_queue **head)
{
	initShell();
	if (var->command && ft_strlen(var->command))
		update_history(var);
	var->command ? free(var->command) : 0;
	init_struct(var, queue, head);
	var->display_pos = var->h_head;
}

int		trim_cmd(t_var *var, t_queue **queue, t_queue **head)
{
	char *str;
	char **split;
	int i;
	
	i = -1;
	str = NULL;
	split = NULL;
	while (var->command[++i])
	{
		if (var->command[i] == '&' && var->command[i + 1] != '&')
			var->command[i - 1] == '&' ? 0 : ft_putchar_str(&str, '\033');
		else if (!(var->command[i] == '&' && var->command[i + 1]))
			ft_putchar_str(&str, var->command[i]);
		else
			ft_putchar_str(&str, var->command[i]);
	}
	split = ft_split(str, '&');
	i = 0;
	while (split[i])
	{
		enqueue(queue, head, split[i]);
		free(split[i]);
		i++;
	}
	free(split);
	return (i);
}
 
char	*nonstrict(char *command)
{
	int i;
	char *ret;

	i = 0;
	ret = NULL;
	while (command[i] && command[i] == ' ')
		i++;
	while (command[i] && command [i] != ' ')
	{
		ft_putchar_str(&ret, command[i]);
		i++;
	}
	return (ret);
}

int		execute_command(char *command)
{
	if (ft_strcmp("pwd", nonstrict(command)))
		commandPwd();
	return (1);
}

int		process_cmd(t_var *var, t_queue **queue, t_queue **head)
{
	int command_num;
	t_queue *tail;

	tail = NULL;
	command_num = trim_cmd(var, queue, head);
	tail = get_tail(head);
	if (var->to_free)
	{
		free(var->to_free);
		var->to_free = NULL;
	}
	while (tail != *head)
	{
		execute_command(tail->command);
		tail = tail->prev;
	}
	execute_command(tail->command);
	return (2);
}

void	del_char(t_var *var, int len)
{
	int i;
	
	i = 0;
	while (i < len)
	{
		ft_fprintf(STDOUT_FILENO, "\b \b");
		if (var->cursor > 0)
			var->cursor--;
		i++;
	}
	var->command[var->cursor] = '\0';
	if (var->command[0] == '\0')
	{
		free(var->command);
		var->command = NULL;
	}
}

int		keyleft(t_var *var)
{
	if (var->cursor > 0)
	{
		var->cursor--;
		ft_fprintf(STDOUT_FILENO, "%s", KEYLEFT);
		//ft_fprintf(STDOUT_FILENO, "%d" ,var->cursor);
		return (1);
	}
	return (0);
}

int		keyright(t_var *var)
{
	if (var->cursor < ft_strlen(var->command))
	{
		var->cursor++;
		ft_fprintf(STDOUT_FILENO, "%s", KEYRIGHT);
		return (1);
	}
	return (0);
}

int		clear_prompt(t_var *var, int mode)
{
	int i;
	
	i = -1;
	while (keyright(var));
	while (++i < ft_strlen(var->command) - mode)
		ft_fprintf(STDOUT_FILENO, "\b \b");
	return (1);
}

void	set_cursor_pos(t_var *var, int pos)
{
	int i;

	i = 0;
	while (var->cursor != pos)
		keyleft(var);
}

void	substitute(t_var *var)
{
	char *left_cut;
	char *right_cut;

	right_cut = NULL;
	left_cut = NULL;
	//ft_fprintf(STDOUT_FILENO, "\b \b");
	//clear_prompt(var);
	//ft_fprintf(STDOUT_FILENO, "%s", var->command);
	left_cut = strndup(var->command, var->cursor - 1);
	right_cut = ft_strdup(var->command + var->cursor);
	var->cursor_pos = var->cursor - 1;
	clear_prompt(var, 0);
	free(var->command);
	var->command = NULL;
	var->command = ft_strjoin(left_cut, right_cut);
	ft_fprintf(STDOUT_FILENO, "%s", var->command);
	var->cursor = ft_strlen(var->command);
	set_cursor_pos(var, var->cursor_pos);
}

void	clearbuff(t_var *var)
{
	int i;
	
	i = 0;
	while (i < BUFFER_SIZE)
	{
		var->buff[i] = (char)0;
		i++;
	}
}

int		overrite_command(t_var *var, char *command)
{
	char *to_free;
	
	to_free = NULL;
	if (var->command)
	{
		to_free = var->command;
		clear_prompt(var, 0);
	}
	var->command = ft_strdup(command);
	ft_fprintf(STDOUT_FILENO, "%s", var->command);
	var->cursor = ft_strlen(var->command);
	return (1);
}

int		keyup(t_var *var)
{
	if (!var->to_free)
		var->to_free = ft_strdup(var->command);
	if (!var->h_head)
		return (0);
	overrite_command(var, var->display_pos->command);
	if (var->display_pos->next)
		var->display_pos = var->display_pos->next;
}

int		keydown(t_var *var)
{
	if (!var->h_head || !var->display_pos->prev->prev)
		return (0);
	overrite_command(var, var->display_pos->prev->prev->command);
	var->display_pos = var->display_pos->prev;
}

int		stream(t_var *var)
{
	if (var->buff[0] == 127 && var->command
		&& ft_strlen(var->command) == var->cursor)
		del_char(var, 1);
	else if (var->buff[0] == 127 && var->command
	&& var->cursor < ft_strlen(var->command) && var->cursor != 0)
		substitute(var);
	else if (ft_strcmp(KEYUP, var->buff))
		keyup(var);
	else if (ft_strcmp(KEYDOWN, var->buff))
		keydown(var);
	else if (ft_strcmp(KEYLEFT, var->buff))
		keyleft(var);
	else if (ft_strcmp(KEYRIGHT, var->buff))
		keyright(var);
	return (1);
}

void	pop_in(t_var *var)
{
	char *left_cut;
	char *right_cut;

	var->cursor_pos = var->cursor;
	left_cut = ft_strjoin(strndup(var->command, var->cursor - 1), var->buff);
	right_cut = ft_strdup(var->command + var->cursor - 1);
	free(var->command);
	var->command = ft_strjoin(left_cut, right_cut);
	clear_prompt(var, ft_strlen(var->buff));
	ft_fprintf(STDOUT_FILENO, "%s", var->command);
	set_cursor_pos(var, var->cursor_pos);
}

int		get_cmd(t_var *var, t_queue **queue, t_queue **head)
{
		if (!(var->buff[0] == EOF || var->buff[0] == '\n'))
		{
			if (ft_strlen(var->command) && !(var->cursor == ft_strlen(var->command) + 1))
			{
				pop_in(var);
				return (1);
			}
			ft_fprintf(STDOUT_FILENO, "%s", var->buff);
			var->command = var->command ? ft_strjoin(var->command, var->buff) :
			ft_strdup(var->buff);
		}
		else if (ft_strlen(var->command))
			return (process_cmd(var, queue, head));
		else
			reset(var, queue, head);
		return (0);
}

int	main(int argc, char **argv)
{
	t_var var;
	t_queue *queue;
	t_queue *head;
	t_queue *print;

	noncanon();
	initShell();
	init_struct(&var, &queue, &head);
	init_history(&var);
	while (1)
	{
		clearbuff(&var);
		var.cursor += read(STDIN_FILENO, &var.buff, 3);
		var.buff[3] = '\0';
		if (var.buff[0] == '\033' || (int)var.buff[0] == 127)
		{
			var.cursor -= ft_strlen(var.buff);
			stream(&var);
		}
		else if (get_cmd(&var, &queue, &head) == 2)
			reset(&var, &queue, &head);
	}
	close(var.fd);
	return (0);
}
