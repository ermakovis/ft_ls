/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prinf_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 19:03:06 by tcase             #+#    #+#             */
/*   Updated: 2019/06/23 12:49:28 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	print_file_check(t_ls *tmp, int *flags)
{
	t_stat		stat;
	char		link[NAME_MAX + 1];

	if (S_ISREG(tmp->mode))
		return (1);
	if (S_ISDIR(tmp->mode) && *flags & FL_DIR)
		return (1);
	if (!S_ISLNK(tmp->mode))
		return (0);
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
	t_ls	*cur;

	while ((*ls) && print_file_check((*ls), flags))
	{
		cur = *ls;
		(*ls) = (*ls)->next;
		print_file_output(cur, flags);
	}
}

static void	print_file_rest(t_ls **ls, int *flags)
{
	t_ls	*cur;
	t_ls	*prev;

	prev = NULL;
	cur = *ls;
	while (cur)
	{
		if (print_file_check(cur, flags))
		{
			prev->next = cur->next;
			print_file_output(cur, flags);
			cur = prev->next;
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}

void		print_file(t_ls **ls, int *flags)
{
	print_file_first(ls, flags);
	print_file_rest(ls, flags);
}

