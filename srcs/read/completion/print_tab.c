/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 06:58:08 by aroulin           #+#    #+#             */
/*   Updated: 2017/08/30 20:03:55 by aroulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

int			init_page(t_read **read_std, t_file **tmp)
{
	(*read_std)->tab_->page = ((*read_std)->tab_->index) /
		((*read_std)->tab_->elem_page);
	while ((*tmp)->next && (*tmp)->index != (*read_std)->tab_->page * (*read_std)->tab_->elem_page)
		(*tmp) = (*tmp)->next;
	return ((*read_std)->tab_->elem_page * ((*read_std)->tab_->page + 1));
}


int			print_element(t_file *file, int color)
{
	(!color) ? P_INV_FD(init_fd()) : NULL;
	color_completion(file->type, color);
	my_togo(file->ms.y, file->ms.x);
	STR_FD(file->name, init_fd());
	STR_FD(RST, init_fd());
	add_little_char(file->type);
	my_tobackto(file->ms.y, file->ms.x + 100);
	P_RST_FD(init_fd());
	return (1);
}



int			print_tab(t_read **read_std)
{
	t_file		*tmp;
	int			stop;

	tmp = (*read_std)->tab_->file;
	if ((*read_std)->tab_->element == 1)
		complete_command(read_std);
	else if ((stop = init_page(read_std, &tmp)))
	{
		while (tmp && tmp->index < stop)
		{
			tmp->ms.y = (((tmp->index % (*read_std)->tab_->elem_page)
						/ (*read_std)->tab_->nbr));
			tmp->ms.x = (((tmp->index % (*read_std)->tab_->elem_page)
				% (*read_std)->tab_->nbr) * (*read_std)->tab_->len
					% (*read_std)->tab_->co);
			(tmp->index == (*read_std)->tab_->index)
				? print_element(tmp, 0) : print_element(tmp, 1);
			tmp->ms.y += ((*read_std)->cur.line - (*read_std)->cur.save);
			tmp = tmp->next;
		}
	}
	return (1);
}