#include "ft_ls.h"
#include <stdio.h>

void		print_detail_width(t_ls *ls, int flags, int width[7])
{
	int		total;

	total = 0;
	while (ls)
	{
		width[0] = ft_max(ft_nbrlen(ls->link, 10), width[0]);
		width[1] = ft_max(ft_strlen(getpwuid(ls->uid)->pw_name), width[1]);
		width[2] = ft_max(ft_strlen(getgrgid(ls->gid)->gr_name), width[2]);
		width[3] = ft_max(ft_nbrlen(ls->size, 10), width[3]);
		total += ls->blocks;
		ls = ls->next;
	}
	flags & FL_REGFL ? 1 : ft_printf("total %d\n", total);
}

void		print_detail_perm(t_ls *ls, int flags, char str[11])
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
	str[10] = '\0';
}

void		print_detail_link(t_ls *ls)
{
	char	name[NAME_MAX];

	readlink(ls->path, name, NAME_MAX);
	ft_printf(" -> %s", name);
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
		print_detail_perm(ls, flags, perm);
		ft_printf("%s", perm);
		ft_printf("  %*hu", width[0], ls->link);
		ft_printf(" %-*s", width[1], getpwuid(ls->uid)->pw_name);
		ft_printf("  %-*s", width[2], getgrgid(ls->gid)->gr_name);
		ft_printf("  %*lld", width[3], ls->size);
		ft_printf(" %.12s", ctime(&(ls->mtime)) + 4);
		ft_printf(" %-s", ls->name);
		perm[0] == 'l' ? print_detail_link(ls) : 1;	
		ft_printf("\n");
		ls = ls->next;
	}
}

void		print_brief(t_ls *ls, int flags)
{
	while (ls)
	{
		ft_printf("%s\n", ls->name);
		ls = ls->next;
	}
}

void		print(t_ls *ls, int flags)
{
	if (flags & FL_LNG)
		print_detail(ls, flags);
	else
		print_brief(ls, flags);
}
