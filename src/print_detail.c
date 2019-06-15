/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_detail.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 19:14:39 by tcase             #+#    #+#             */
/*   Updated: 2019/06/15 19:16:09 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_detail_width(t_ls *ls, int flags, int width[7])
{
	int		total;

	total = 0;
	while (ls)
	{
		width[0] = ft_max(ft_nbrlen(ls->link, 10), width[0]);
		if (flags & FL_IND)
			width[1] = ft_max(ft_nbrlen(ls->uid, 10), width[1]);
		else
			width[1] = ft_max(ft_strlen(getpwuid(ls->uid)->pw_name), width[1]);
		if (flags & FL_IND)
			width[2] = ft_max(ft_nbrlen(ls->gid, 10), width[2]);
		else
			width[2] = ft_max(ft_strlen(getgrgid(ls->gid)->gr_name), width[2]);
		width[3] = ft_max(ft_nbrlen(ls->size, 10), width[3]);
		total += ls->blocks;
		ls = ls->next;
	}
	flags & FL_REGFL ? 1 : ft_printf("total %d\n", total);
}

void		print_perm(t_ls *ls, int flags, char str[11])
{
	str[0] = '-';
	S_ISDIR(ls->mode) ? str[0] = 'd' : 1;
	S_ISLNK(ls->mode) ? str[0] = 'l' : 1;
	S_ISFIFO(ls->mode) ? str[0] = 'p' : 1;
	S_ISCHR(ls->mode) ? str[0] = 'c' : 1;
	S_ISBLK(ls->mode) ? str[0] = 'b' : 1;
	str[1] = (S_IRUSR & ls->mode ? 'r' : '-');
	str[2] = (S_IWUSR & ls->mode ? 'w' : '-');
	str[3] = (S_IXUSR & ls->mode ? 'x' : '-');
	str[4] = (S_IRGRP & ls->mode ? 'r' : '-');
	str[5] = (S_IWGRP & ls->mode ? 'w' : '-');
	str[6] = (S_IXGRP & ls->mode ? 'x' : '-');
	str[7] = (S_IROTH & ls->mode ? 'r' : '-');
	str[8] = (S_IWOTH & ls->mode ? 'w' : '-');
	str[9] = (S_IXOTH & ls->mode ? 'x' : '-');
}

void		print_detail_link(t_ls *ls)
{
	char	name[NAME_MAX];

	ft_printf(" -> %s", name);
}

void		print_color(t_ls *ls, int flags, int width)
{
	char link[NAME_MAX];

	bzero(link, sizeof(link));
	if (!(flags & FL_COL))
		ft_printf("%-*s", width, ls->name);
	if (S_ISDIR(ls->mode) && flags & FL_COL)
		ft_printf("%s%-*s%s", BOLD_CYAN, width, ls->name, RESET);
	else if (S_ISLNK(ls->mode) && flags & FL_COL)
		ft_printf("%s%-*s%s", MAGENTA, width, ls->name, RESET);
	else if (S_ISBLK(ls->mode) && flags & FL_COL)
		ft_printf("%s%-*s%s", BOLD_GREEN, width, ls->name, RESET);
	else if (S_ISFIFO(ls->mode) && flags & FL_COL)
		ft_printf("%s%-*s%s", GREEN, width, ls->name, RESET);
	else if (S_ISCHR(ls->mode) && flags & FL_COL)
		ft_printf("%s%-*s%s", BLUE, width, ls->name, RESET);
	else if (S_ISREG(ls->mode) && flags & FL_COL)
		ft_printf("%s%-*s%s", RED, width, ls->name, RESET);
	if (flags & FL_LNG && S_ISLNK(ls->mode))
	{
		ft_printf(" -> ");
		readlink(ls->path, link, NAME_MAX);
		flags & FL_COL ? ft_printf(" %s%-s%s", MAGENTA, link, RESET) :\
			ft_printf("%s", link);
	}
}

void		print_detail(t_ls *ls, int flags)
{
	int		width[4];
	char	perm[11];

	bzero(width, sizeof(width));
	print_detail_width(ls, flags, width);
	while (ls)
	{
		bzero(perm, sizeof(perm));
		print_perm(ls, flags, perm);
		ft_printf("%s", perm);
		ft_printf("  %*hu", width[0], ls->link);
		flags & FL_IND ? ft_printf(" %-*d", width[1], ls->uid) :\
			ft_printf(" %-*s", width[1], getpwuid(ls->uid)->pw_name);
		flags & FL_IND ? ft_printf("  %-*d", width[2], ls->gid) :\
			ft_printf("  %-*s", width[2], getgrgid(ls->gid)->gr_name);
		ft_printf("  %*lld", width[3], ls->size);
		ft_printf(" %.12s ", ctime(&(ls->mtime)) + 4);
		print_color(ls, flags, 0);
		ft_printf("\n");
		ls = ls->next;
	}
}
