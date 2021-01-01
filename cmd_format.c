#include "shelllib.h"

typedef struct s_node
{
	int nb;
	struct s_node *div;
	struct s_node * n;
}	t_node;

t_node *fill(int nb)
{
	t_node *ret;

	ret = NULL;
	if (!(ret = malloc(sizeof(t_node))))
		return (0);
	ret->nb = nb;
	return (ret);
}

int	main(void)
{
	t_node *node;
	t_node *last;
	t_node *head;

	last = NULL;
	//
	node = fill(1);
	node->n = NULL;
	node->div = NULL;
	last = node;
	head = node;
	ft_fprintf(1, "%d", last->nb);
	//
	node->n = fill(2);
	last = node->n;
	ft_fprintf(1, "%d", last->nb);
	last->div = fill(3);
	last->div->n = fill(4);
	ft_fprintf(1, "%d%d", last->div->nb, last->div->n->nb);
	last->n = fill(5);
	last = last->n;
	ft_fprintf(1, "%d", last->nb);
	return (0);
}
