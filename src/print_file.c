/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prinf_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 19:03:06 by tcase             #+#    #+#             */
/*   Updated: 2019/06/10 12:41:04 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_file_first(t_ls **ls, int flags)
{
	t_ls *tmp;

	tmp = *ls;
	if (!ls || !*ls)
		return ;
	if (S_ISREG(tmp->mode))
	{
		(*ls) = (*ls)->next;
		tmp->next = NULL;
		flags ^= FL_REGFL;
		print(tmp, flags);	
		ft_memdel((void**)&tmp);
		flags ^= FL_REGFL;
		flags |= FL_REGNL;
		print_file_first(ls, flags);
	}
}

void		print_file(t_ls **ls, int flags)
{
	t_ls *tmp;
	t_ls *cur;

	if (!ls || !*ls)
		return ;
	tmp = *ls;
	print_file_first(ls, flags);
	while (tmp->next)
	{
		if (tmp->next && (S_ISREG(tmp->next->mode)))
		{
			cur = tmp->next->next;
			tmp->next->next = NULL;
			flags ^= FL_REGFL;
			print(tmp->next, flags);
			flags ^= FL_REGFL;
			ft_memdel((void**)&(tmp->next));
			tmp->next = cur;
			flags |= FL_REGNL;
		}
		else
			tmp = tmp->next;
	}
	flags & FL_REGNL ? ft_printf("\n") : 1;
}
