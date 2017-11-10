//
// Created by Alexandre ROULIN on 10/30/17.
//

#include <sh.h>

static t_node			*init_node(t_parsing *list)
{
	t_node		*node;
	
	node = (t_node *)ft_memalloc(sizeof(t_node));
	node->content= list;
	return (node);
}

t_node					*create_binary_tree(t_parsing *list, t_parsing *compare, int priority)
{
	t_node			*node;
	t_parsing		*keep;
	t_parsing		*temp;

	keep = NULL;
	temp = list;
	if (priority == 6 || list == NULL)
		return (NULL);
	while (temp != compare)
	{
		if (temp->priority == priority)
			keep = temp;
		temp = temp->next;
	}
	if (keep)
	{
		node = init_node(keep);
		node->left = create_binary_tree(list, keep, priority);
		node->right = create_binary_tree(keep->next, compare, priority + 1);
		return (node);
	}
	else
		return (create_binary_tree(list, compare, priority + 1));
}