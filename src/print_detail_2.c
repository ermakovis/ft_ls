/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_detail_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/24 14:47:01 by tcase             #+#    #+#             */
/*   Updated: 2019/06/24 14:58:49 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static void	print_symbols(t_ls *ls, int flags)
{
	flags & FL_PSL && S_ISDIR(ls->mode) ? ft_printf("/") : 1;
	flags & FL_SYM && S_ISDIR(ls->mode) ? ft_printf("/") : 1;
	flags & FL_SYM && S_ISREG(ls->mode) &&\
		(S_IXUSR & ls->mode || S_IXGRP & ls->mode || S_IXOTH & ls->mode) ?\
			ft_printf("*") : 1;
	flags & FL_SYM && S_ISLNK(ls->mode) ? ft_printf("@") : 1;
	flags & FL_SYM && S_ISSOCK(ls->mode) ? ft_printf("=") : 1;
	flags & FL_SYM && S_ISFIFO(ls->mode) ? ft_printf("|") : 1;
}

void		print_color(t_ls *ls, int flags, int width)
{
	char link[NAME_MAX];

	bzero(link, sizeof(link));
	S_ISDIR(ls->mode) && flags & FL_COL ? ft_printf("%s", COL_DIR) : 1;
	S_ISLNK(ls->mode) && flags & FL_COL ? ft_printf("%s", COL_LNK) : 1;
	S_ISBLK(ls->mode) && flags & FL_COL ? ft_printf("%s", COL_BLK) : 1;
	S_ISCHR(ls->mode) && flags & FL_COL ? ft_printf("%s", COL_CHR) : 1;
	S_ISFIFO(ls->mode) && flags & FL_COL ? ft_printf("%s", COL_FIF) : 1;
	S_ISSOCK(ls->mode) && flags & FL_COL ? ft_printf("%s", COL_SOK) : 1;
	(S_IXUSR & ls->mode || S_IXGRP & ls->mode || S_IXOTH & ls->mode) &&\
		flags & FL_COL && S_ISREG(ls->mode) ? ft_printf("%s", COL_EXE) : 1;
	ft_printf("%s", ls->name);
	flags & FL_COL ? ft_printf("%s", RESET) : 1;
	print_symbols(ls, flags);
	width ? ft_printf("%*s", width - ft_strlen(ls->name), " ") : 1;
	if (flags & FL_LNG && S_ISLNK(ls->mode))
	{
		ft_printf(" -> ");
		readlink(ls->path, link, NAME_MAX);
		ft_printf("%s", link);
	}
}
