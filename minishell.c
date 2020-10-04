#include "shelllib.h"

typedef struct	s_var
{
	char	buff[BUFFER_SIZE];
	char	*command;
	char	*command_queue;
	int		shell;
	int		fd;
	int		cursor;
	int		cursor_pos;
}				t_var;

char	*ft_strndup(char *str, int len)
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

void	closeTerminal(void)
{
	exit (0);
}

void	commandPwd(void)
{
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	ft_fprintf(1, "%s", pwd);
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

void	init_struct(t_var *var)
{
	var->command = NULL;
	var->shell = 0;
	var->cursor = 0;
	var->command_queue = NULL;
}

void	exec_cmd(t_var *var)
{
	var->cursor = 0;
	ft_fprintf(STDOUT_FILENO, "\nCommnad: %s", var->command);
	ft_fprintf(var->fd, "%s\n", var->command);
	free(var->command);
	var->command = NULL;
	initShell();
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
	{
		keyleft(var);
	}
	//ft_fprintf(STDOUT_FILENO, "%d", var->cursor - var->cursor_pos - 1);
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
	left_cut = ft_strndup(var->command, var->cursor - 1);
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

void	keyup(t_var *var)
{
	char *cursor;

	cursor = tgetstr("cm", NULL);
	write(1, "\033[6n", 4);
	//ft_fprintf(STDOUT_FILENO, "%s", tgoto(cursor, 12, 1));
	//ft_fprintf(STDOUT_FILENO, "KEYUP ");
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
		ft_fprintf(STDOUT_FILENO, "KEYDOWN ");
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
	left_cut = ft_strjoin(ft_strndup(var->command, var->cursor - 1), var->buff);
	right_cut = ft_strdup(var->command + var->cursor - 1);
	free(var->command);
	var->command = ft_strjoin(left_cut, right_cut);
	clear_prompt(var, ft_strlen(var->buff));
	ft_fprintf(STDOUT_FILENO, "%s", var->command);
	set_cursor_pos(var, var->cursor_pos);
}

void	get_cmd(t_var *var)
{
		if (!(var->buff[0] == EOF || var->buff[0] == '\n'))
		{
			if (ft_strlen(var->command) && !(var->cursor == ft_strlen(var->command) + 1))
			{
				pop_in(var);
				//ft_fprintf(STDOUT_FILENO, "\nDebug\n%s\n%s\n%s", ft_strndup(var->command, var->cursor - 1), ft_strjoin(ft_strndup(var->command, var->cursor - 1), var->buff), ft_strdup(var->command + var->cursor - 1));
				return ;
			}
			ft_fprintf(STDOUT_FILENO, "%s", var->buff);
			var->command = var->command ? ft_strjoin(var->command, var->buff) :
			ft_strdup(var->buff);
		}
		else
			exec_cmd(var);
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

int	main(int argc, char **argv)
{
	t_var var;

	noncanon();
	commandClear();
	initShell();
	init_struct(&var);
	var.fd = open(HPATH, O_RDWR | O_CREAT | O_APPEND | O_TRUNC);
	if (!var.fd)
		ft_fprintf(STDOUT_FILENO, "fd err");;
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
		else
			get_cmd(&var);
	}
	close(var.fd);
	return (0);
}
