/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 20:34:41 by tcase             #+#    #+#             */
/*   Updated: 2019/06/09 15:56:54 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	swap_ls(t_ls *ls1, t_ls *ls2, t_ls **start)
{
	t_ls	*tmp;
	
	tmp = *start;
	if (tmp != ls1)
		while (tmp->next != ls1)
			tmp = tmp->next;
	ls1->next = ls2->next;
	ls2->next = ls1;
	if (tmp != ls1)
		tmp->next = ls2;
	else 
	{
		tmp = ls2;
		*start = tmp;
	}
}

void	sort_ls_lex(t_ls **ls)
{
	t_ls *tmp;

	tmp = *ls;
	while (tmp->next)
	{
		if (ft_strcmp(tmp->name, tmp->next->name) > 0)
		{
			swap_ls(tmp, tmp->next, ls);
			return (sort_ls_lex(ls));
		}
		tmp = tmp->next;
	}
}

void	sort_ls_rev(t_ls **ls)
{
	t_ls *tmp;

	tmp = *ls;
	while (tmp->next)
	{
		if (ft_strcmp(tmp->name, tmp->next->name) < 0)
		{
			swap_ls(tmp, tmp->next, ls);
			return (sort_ls_rev(ls));
		}
		tmp = tmp->next;
	}
}

void	sort_ls_mtime(t_ls **ls)
{
	t_ls *tmp;

	tmp = *ls;
	while (tmp->next)
	{
		if (tmp->mtime < tmp->next->mtime)
		{
			swap_ls(tmp, tmp->next, ls);
			return (sort_ls_mtime(ls));
		}
		tmp = tmp->next;
	}
}
void	sort_ls(t_ls **ls, int flags)
{
	int		size;

	size = 0;
	if (!ls || !*ls || !(*ls)->next || flags & FL_SRT)
		return ;
	sort_ls_lex(ls);
	if (flags & FL_STM)
		sort_ls_mtime(ls);
	if (flags & FL_REV)
		sort_ls_rev(ls);

}
