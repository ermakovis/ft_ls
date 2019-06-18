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

	bzero(width, (sizeof(int) * 7));
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

static char		*print_perm(t_ls *ls, int flags, char str[11])
{
	bzero(str, 11);
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
	return (str);
}

void		print_color(t_ls *ls, int flags, int width)
{
	char link[NAME_MAX];

	bzero(link, sizeof(link));
	S_ISDIR(ls->mode) && flags & FL_COL ? ft_printf("%s", BOLD_CYAN) : 1;
	S_ISLNK(ls->mode) && flags & FL_COL ? ft_printf("%s", MAGENTA) : 1;
	S_ISBLK(ls->mode) && flags & FL_COL ? ft_printf("%s", BOLD_GREEN) : 1;
	S_ISFIFO(ls->mode) && flags & FL_COL ? ft_printf("%s", GREEN) : 1;
	S_ISCHR(ls->mode) && flags & FL_COL ? ft_printf("%s", BLUE) : 1;
	S_ISREG(ls->mode) && flags & FL_COL ? ft_printf("%s", RESET) : 1;
	S_ISSOCK(ls->mode) && flags & FL_COL ? ft_printf("%s", BOLD_GREEN) : 1;
	ft_printf("%-*s%s", width, ls->name, RESET);
	if (flags & FL_LNG && S_ISLNK(ls->mode))
	{
		ft_printf(" -> ");
		readlink(ls->path, link, NAME_MAX);
		flags & FL_COL ? ft_printf(" %s%-s%s", MAGENTA, link, RESET) :\
			ft_printf("%s", link);
	}
}

void		 *print_time(t_ls *ls)
{	
	time_t	now;
	time_t	then;
	time_t	diff;
	char	*tmp;
	char	str[13];

	ft_bzero(str, sizeof(str));
	then = ls->mtime;
	tmp = ctime(&then);
	now = time(NULL);
	diff = now - then;
	ft_memcpy(str, tmp + 4, 7);
	if (diff < (-3600 * 24 * 30.5 * 6) || diff > (3600 * 24 * 30.5 * 6))
	{
		str[7] = ' ';
		ft_memcpy(str + 8, tmp + 20, 4);
	}
	else
		ft_memcpy(str + 7, tmp + 11, 5);
	ft_printf(" %s ", str);
}

void		print_detail(t_ls *ls, int flags)
{
	int		width[4];
	char	perm[11];

	print_detail_width(ls, flags, width);
	while (ls)
	{
		ft_printf("%s", print_perm(ls, flags, perm));
		ft_printf("  %*hu", width[0], ls->link);
		flags & FL_IND ? ft_printf(" %-*d", width[1], ls->uid) :\
			ft_printf(" %-*s", width[1], getpwuid(ls->uid)->pw_name);
		flags & FL_IND ? ft_printf("  %-*d", width[2], ls->gid) :\
			ft_printf("  %-*s", width[2], getgrgid(ls->gid)->gr_name);
		ft_printf("  %*lld", width[3], ls->size);
		print_time(ls);
		print_color(ls, flags, 0);
		ft_printf("\n");
		ls = ls->next;
	}
}
