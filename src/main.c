/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 15:15:48 by tcase             #+#    #+#             */
/*   Updated: 2019/06/09 19:06:49 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		read_dir(t_ls *ls, t_ls **begin, int flags)
{
	DIR		*dir;
	t_dir	*entry;

	*begin = NULL;
	if (!(dir = opendir(ls->path)) && ft_dprintf(2, "ls: %s: Permission denied\n", ls->path))
		return ;
	if (!(flags & FL_DIR))
	{
		while ((entry = readdir(dir)))
		{
			if (entry->d_name[0] != '.' || flags & FL_ALL)
				add_ls(ls->path, entry->d_name, begin);
		}
	}
	closedir(dir);
}

void		recursion(t_ls *begin, int flags, int first)
{
	t_ls	*ls;

	ls = begin;
	while (ls)
	{
		if (S_ISDIR(ls->mode) && (first || (ft_strcmp(ls->name, ".")
						&& ft_strcmp(ls->name, ".."))))
		{
			flags & FL_SEPAR ? ft_printf("\n") : (flags |= FL_SEPAR);
			if ((flags & FL_HEADR || ls->next) && ft_printf("%s:\n", ls->path))
				flags |= FL_HEADR;
			read_dir(ls, &begin, flags);
			sort_ls(&begin, flags);
			print(begin, flags);
			(flags & FL_REC) ? recursion(begin, flags, 0) : 1;
			cleanup(&begin, 1, "");
		}
		ls = ls->next;
	}
}

int			main(int ac, char **av)
{
	int		flags;
	t_ls	*ls;

	flags = 0;
	ls = NULL;
	parse_params(&ac, &av, &flags);
	//ft_printf("%b\n", flags);
	init_ls(ac, av, &ls);
	sort_ls(&ls, flags);
	print_file(&ls, flags);
	recursion(ls, flags, 1);
	cleanup(&ls, 0, "Success");
}
