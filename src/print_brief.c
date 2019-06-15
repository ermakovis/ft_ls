/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_brief.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 19:05:37 by tcase             #+#    #+#             */
/*   Updated: 2019/06/15 21:32:09 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	print_brief_calc_rows(t_ls *ls, int *rows, int *width)
{
	t_wsize		ws;
	int			size;
	int			col;

	size = 0;
	col = 1;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	while (ls)
	{
		*width = ft_max((ft_strlen(ls->name) + 2), *width);
		size++;
		ls = ls->next;
	}
	col = ws.ws_col / *width;
	col = ft_min(col, size);
	col < 1 ? (col = 1) : 1;
	*rows = size / col;
	size % col ? (*rows)++ : 1;
}

static void	print_brief_out(t_ls *ls, int rows, int width, int flags)
{
	int		i;
	int		j;
	t_ls	*tmp;

	i = rows;
	while (i)
	{
		j = 0;
		tmp = ls;
		while (tmp)
		{
			if (((i + j) % rows) == 0)
				print_color(tmp, flags, width);
			j++;
			tmp = tmp->next;
		}
		ft_printf("\n");
		i--;
	}
}

void		print_brief(t_ls *ls, int flags)
{
	int		rows;
	int		width;

	if (!ls)
		return ;
	rows = 1;
	width = 0;
	while (ls && flags & FL_ONE)
	{
		print_color(ls, flags, width);
		ft_printf("\n");
		ls = ls->next;
	}
	if (!(flags & FL_ONE))
	{
		print_brief_calc_rows(ls, &rows, &width);
		print_brief_out(ls, rows, width, flags);
	}
}
