/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prinf_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 19:03:06 by tcase             #+#    #+#             */
/*   Updated: 2019/06/22 22:49:40 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	print_file_lnkcheck(t_ls *tmp, int *flags)
{
	t_stat		stat;
	char		link[NAME_MAX + 1];

	ft_bzero(link, sizeof(link));
	link[0] = '.';
	link[1] = '/';
	readlink(tmp->path, link + 2, NAME_MAX);
	if (lstat(link, &stat) != 1 && S_ISDIR(stat.st_mode))
		return (0);
	return (1);
}

static void print_file_output(t_ls *tmp, int *flags)
{
	tmp->next = NULL;
	*flags ^= FL_REGFL;
	*flags & FL_LNG ? print_detail(tmp, *flags) : print_brief(tmp, *flags);
	ft_memdel((void**)&tmp);
	*flags ^= FL_REGFL;
	*flags |= FL_REGNL;
}

static void	print_file_first(t_ls **ls, int *flags)
{
	t_ls *tmp;

	tmp = *ls;
	if (!ls || !*ls)
		return ;
	if (S_ISREG(tmp->mode) || print_file_lnkcheck(tmp, flags))
	{
		(*ls) = (*ls)->next;
		print_file_output(tmp, flags);	
		print_file_first(ls, flags);
	}
}

void		print_file_rest(t_ls **ls, int *flags)
{
	t_ls *tmp;
	t_ls *cur;

	if (!ls || !*ls)
		return ;
	tmp = *ls;
	while (tmp->next)
	{
		if (tmp->next && (S_ISREG(tmp->next->mode) ||\
					print_file_lnkcheck(tmp->next, flags)))
		{
			cur = tmp->next->next;
			print_file_output(tmp->next, flags);
			tmp->next = cur;
		}
		else
			tmp = tmp->next;
	}
}

void		print_file(t_ls **ls, int *flags)
{
	print_file_first(ls, flags);
	print_file_rest(ls, flags);
	*flags & FL_REGNL && *ls ? ft_printf("\n") : 1;
}

