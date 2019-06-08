#include "ft_ls.h"
#include <stdio.h>

void		print_detail(t_ls *ls, int flags)
{
	while (ls)
	{
		ft_printf("%15s", ls->name);
		printf("%12d\n", ls->mode);
		ls = ls->next;
	}
	ft_printf("\n");
}

void		print_brief(t_ls *ls, int flags)
{
	while (ls)
	{
		ft_printf("%s\n", ls->name);
		ls = ls->next;
	}
	ft_printf("\n");
}

void		print(t_ls *ls, int flags)
{
	if (flags & FL_LNG)
		print_detail(ls, flags);
	else
		print_brief(ls, flags);
}
