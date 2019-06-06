/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 15:15:48 by tcase             #+#    #+#             */
/*   Updated: 2019/06/02 18:21:42 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		read_dir(t_ls *ls, t_ls **begin, int flags)
{
	DIR		*dir;
	t_dir	*entry;

	if (!(dir = opendir(ls->path)) && ft_dprintf(2, "Error - Openfile"))
		return ;
	if (!(flags & FL_DIR))
	{
		while (entry = readdir(dir))
		{
			if (entry->d_name[0] != '.')
				add_ls(ls->path, entry->d_name, begin);
		}
	}
	closedir(dir);

}

void		recursion(t_ls *begin, int flags, int first)
{
	t_ls	*ls;

	ls = begin;
	if (!(flags & FL_REC) && !first)
		return ;
	while (ls)
	{
		if (S_ISDIR(ls->mode) && (first || (ft_strcmp(ls->name, ".")
			&& ft_strcmp(ls->name, ".."))))
		{
			ft_printf("\n%s:\n", ls->path);
			begin = NULL;
			read_dir(ls, &begin, flags);
			print_ls(begin);
			recursion(begin, flags, 0);
		}
		ls = ls->next;
	}
}

void		print_ls(t_ls *ls)
{
	while (ls)
	{
		ft_printf("%s\n", ls->name);
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
	ft_printf("flags - %b\n", flags);
	init_ls(ac, av, &ls);
	recursion(ls, flags, 1);

//	print_ls(ls);
	
	cleanup(&ls, 0, "Success");
	return (0);
}
