
#include <stdlib.h>

int		ft_strlen(char *str)
{
	int i;
	
	i = -1;
	if (!str)
		return (0);
	while (str[++i]);
	return (i);	
}

char	*ft_strdup(char *str)
{
	char *ret;
	int i;

	ret = NULL;
	i = -1;
	if (!str)
		return (NULL);
	if (!(ret = malloc(sizeof(char) * ft_strlen(str) + 1)))
		return (0);
	ret[ft_strlen(str)] = '\0';
	while (str[++i])
		ret[i] = str[i];
	return (ret);
}

typedef struct s_queue
{
	char *command;
	struct s_queue * next;
	struct s_queue * prev;
}			t_queue;

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

void	print_list(t_queue *head)
{
	t_queue *print;

	print = head;
}

void	printlist(t_queue *head)
{
	t_queue *tmp;

	tmp = head;
	while (tmp)
	{
		printf("%s", tmp->command);
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
	t_queue *new;
	t_queue *head2;

	new = add(str);
	new->prev = *head;
	new->next = *head;
	*head = new;
}

int		enqueue(t_queue **queue, t_queue **head, char *str)
{
	t_queue *head2;
	t_queue *new;

	head2 = NULL;
	if (!*queue)
		create_queue(queue, head, str);
	else
		add_to_head(head, str);
}

int	main(void)
{
	int i;
	t_queue *c;
	t_queue *new;
	t_queue *head;
	t_queue *print;
	
	t_queue *queue;
	init_queue(&queue, &head);
	enqueue(&queue, &head, "test");
	enqueue(&queue, &head, "testaaa");
	print = head;
	printlist(print);
}
