/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_detail.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 19:14:39 by tcase             #+#    #+#             */
/*   Updated: 2019/06/24 14:55:10 by tcase            ###   ########.fr       */
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

static char		print_ext_acl(t_ls *ls)
{
	char	buff[255];
	acl_t	type;

	if (listxattr(ls->path, buff, sizeof(buff), XATTR_NOFOLLOW) > 0)
		return ('@');
	if ((type = acl_get_link_np(ls->path, ACL_TYPE_EXTENDED)))
	{
		acl_free(type);
		return ('+');
	}
	return (' ');
}

static char		*print_perm(t_ls *ls, int flags, char str[12])
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
	S_ISSOCK(ls->mode) ? str[0] = 's' : 1;
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
	str[10] = print_ext_acl(ls);
	return (str);
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
	char	perm[12];

	bzero(width, (sizeof(width)));
	bzero(perm, (sizeof(perm)));
	print_detail_width(ls, flags, width);
	while (ls)
	{
		ft_printf("%s", print_perm(ls, flags, perm));
		ft_printf(" %*hu", width[0], ls->link);
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
