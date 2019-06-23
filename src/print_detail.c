/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_detail.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 19:14:39 by tcase             #+#    #+#             */
/*   Updated: 2019/06/23 17:59:03 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		print_detail_width(t_ls *ls, int flags, int width[7])
{
	int		total;

	total = 0;
	if (!ls)
		return ;
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
	!(flags & FL_OGR) ? width[3]++ : 1;
	!(flags & FL_REGFL) ? ft_printf("total %d\n", total) : 1;
}

static char		*print_perm(t_ls *ls, int flags, char str[11])
{
	str[0] = '-';
	str[1] = (S_IRUSR & ls->mode ? 'r' : '-');
	str[2] = (S_IWUSR & ls->mode ? 'w' : '-');
	str[3] = (S_IXUSR & ls->mode ? 'x' : '-');
	str[4] = (S_IRGRP & ls->mode ? 'r' : '-');
	str[5] = (S_IWGRP & ls->mode ? 'w' : '-');
	str[6] = (S_IXGRP & ls->mode ? 'x' : '-');
	str[7] = (S_IROTH & ls->mode ? 'r' : '-');
	str[8] = (S_IWOTH & ls->mode ? 'w' : '-');
	str[9] = (S_IXOTH & ls->mode ? 'x' : '-');
	S_ISDIR(ls->mode) ? str[0] = 'd' : 1;
	S_ISLNK(ls->mode) ? str[0] = 'l' : 1;
	S_ISFIFO(ls->mode) ? str[0] = 'p' : 1;
	S_ISCHR(ls->mode) ? str[0] = 'c' : 1;
	S_ISBLK(ls->mode) ? str[0] = 'b' : 1;
	if (S_ISUID & ls->mode)
		str[3] = (str[3] == '-' ? 'S' : 's');
	if (S_ISGID & ls->mode)
		str[6] = (str[6] == '-' ? 'S' : 's');
	if (S_ISVTX & ls->mode)
		str[9] = (str[9] == '-' ? 'T' : 't');
	return (str);
}

void			print_color(t_ls *ls, int flags, int width)
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
	ft_printf("%-*s", width, ls->name);
	flags & FL_COL ? ft_printf("%s", RESET) : 1;
	flags & FL_PSL && S_ISDIR(ls->mode) && !width ? ft_printf("/") : 1;
	if (flags & FL_LNG && S_ISLNK(ls->mode))
	{
		ft_printf(" -> ");
		readlink(ls->path, link, NAME_MAX);
		flags & FL_COL ? ft_printf(" %s%-s%s", MAGENTA, link, RESET) :\
			ft_printf("%s", link);
	}
}

void			print_time(t_ls *ls, int flags)
{
	time_t	now;
	time_t	diff;
	char	*str;
	char	*tmp;

	str = ctime(&(ls->time));
	if (flags & FL_FTM)
	{
		tmp = ft_strtrim(str + 4);
		ft_printf("%s ", tmp);
		ft_memdel((void**)&tmp);
		return ;
	}
	now = time(NULL);
	diff = now - ls->time;
	write(1, str + 4, 7);
	if (diff < (-3600 * 24 * 30.5 * 6) || diff > (3600 * 24 * 30.5 * 6))
	{
		tmp = ft_strtrim(str + 20);
		ft_printf(" %s", tmp);
		ft_memdel((void**)&tmp);
	}
	else
		write(1, str + 11, 5);
	ft_printf(" ");
}

void			print_detail(t_ls *ls, int flags)
{
	int		width[4];
	char	perm[11];

	bzero(width, (sizeof(width)));
	bzero(perm, (sizeof(perm)));
	print_detail_width(ls, flags, width);
	while (ls)
	{
		ft_printf("%s", print_perm(ls, flags, perm));
		ft_printf("  %*hu", width[0], ls->link);
		if (!(flags & FL_POS))
			flags & FL_IND ? ft_printf(" %-*d ", width[1], ls->uid) :\
				ft_printf(" %-*s ", width[1], getpwuid(ls->uid)->pw_name);
		flags & FL_OGR && flags & FL_POS ? ft_printf("  ") : 1;
		if (!(flags & FL_OGR))
			flags & FL_IND ? ft_printf(" %-*d", width[2], ls->gid) :\
				ft_printf(" %-*s", width[2], getgrgid(ls->gid)->gr_name);
		ft_printf(" %*lld ", width[3], ls->size);
		print_time(ls, flags);
		print_color(ls, flags, 0);
		ft_printf("\n");
		ls = ls->next;
	}
}
