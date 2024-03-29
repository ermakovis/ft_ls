/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 15:15:48 by tcase             #+#    #+#             */
/*   Updated: 2019/06/23 18:04:02 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		read_dir(t_ls *ls, t_ls **begin, int flags)
{
	DIR		*dir;
	t_dir	*entry;

	*begin = NULL;
	if (!(dir = opendir(ls->path)))
	{
		ft_dprintf(2, "ft_ls: %s: Permission denied\n", ls->path);
		return ;
	}
	if (!(flags & FL_DIR))
	{
		while ((entry = readdir(dir)))
		{
			if (entry->d_name[0] != '.' || flags & FL_ALL)
				add_ls(ls->path, entry->d_name, begin, flags);
			else if (entry->d_name[0] == '.' && ft_isprint(entry->d_name[1])\
					&& entry->d_name[1] != '.' && flags & FL_HID)
				add_ls(ls->path, entry->d_name, begin, flags);
		}
	}
	closedir(dir);
}

void		print_link(t_ls *ls, int *flags)
{
	t_ls		*tmp;
	t_ls		*begin;
	char		link[NAME_MAX];

	*flags & FL_SEPAR ? ft_printf("\n") : (*flags |= FL_SEPAR);
	*flags & FL_HEADR ? ft_printf("%s:\n", ls->path) : 1;
	ft_bzero(link, sizeof(link));
	link[0] = '.';
	link[1] = '/';
	readlink(ls->path, link + 2, NAME_MAX);
	ft_bzero(ls->path, sizeof(ls->path));
	ft_memcpy(ls->path, link, ft_strlen(link));
	read_dir(ls, &begin, *flags);
	sort_ls(&begin, *flags);
	print_brief(begin, *flags);
	cleanup(&begin, 1, "");
}

void		recursion(t_ls *begin, int flags, int first)
{
	t_ls	*ls;

	ls = begin;
	while (ls)
	{
		if (S_ISLNK(ls->mode) && first)
			print_link(ls, &flags);
		if (S_ISDIR(ls->mode) && (first || (ft_strcmp(ls->name, ".")
						&& ft_strcmp(ls->name, ".."))))
		{
			flags & FL_REGNL && (flags ^= FL_REGNL) ? ft_printf("\n") : 1;
			flags & FL_SEPAR ? ft_printf("\n") : (flags |= FL_SEPAR);
			flags & FL_HEADR || !first ? ft_printf("%s:\n", ls->path) : 1;
			read_dir(ls, &begin, flags);
			sort_ls(&begin, flags);
			flags & FL_LNG ? print_detail(begin, flags) :\
				print_brief(begin, flags);
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
	sort_av(ac, &av, flags);
	init_ls(ac, av, &ls, flags);
	sort_ls(&ls, flags);
	print_file(&ls, &flags);
	recursion(ls, flags, 1);
	cleanup(&ls, 0, "Success");
}
