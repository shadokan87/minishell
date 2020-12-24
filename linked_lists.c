
#include "shelllib.h"

typedef struct s_queue
{
	char *elem;
	struct s_queue * p;
}	t_queue;

typedef struct s_global
{
	t_queue *front;
	t_queue *queue;
} t_global;

void	init_queue(t_global *global)
{
	global->queue = NULL;
	global->front = NULL;
}

int		enqueue(t_global *global, char *elem)
{
	t_queue *ret;

	if (!(ret = malloc(sizeof(t_queue))))
		return (0);
	if (!global->queue)
	{
		ret->elem = ft_strdup(elem);
		
	}
	
}

int		dequeue(t_global *global)
{
	
}

int	main(void)
{
	t_global global;

	init_queue(&global);
	ft_fprintf(1, "%s", global.tail->p->elem);
	return (0);
}
