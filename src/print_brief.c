#include "ft_ls.h"

void		get_ls_size(t_ls *ls, int *lsize)
{
	*lsize = 0;
	while (ls)
	{
		(*lsize)++;
		ls = ls->next;
	}
}

static int	print_brief_check_fit(t_ls *ls, int size, int twidth, \
	int width[COL_MAX])
{
	int		i;
	int		sum;

	i = 0;
	sum = 0;
	ft_bzero(width, (COL_MAX * 4));
	while (ls)
	{
		width[i % size] = ft_max((ft_strlen(ls->name) + 1),\
			width[i % size]);
		ls = ls->next;
		i++;
	}
	i = -1;
	while (width[++i])
		sum += width[i];
	i = (sum < twidth ? 1 : 0);
	return (i);
}

static void	print_brief_calc_rows(t_ls *ls, int *rows, int width[COL_MAX])
{
	t_wsize		ws;
	int			size;
	int			lsize;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
	get_ls_size(ls, &lsize);
	size = lsize;
	while (print_brief_check_fit(ls, size, ws.ws_col, width) == 0)
	{
		(*rows)++;
		size = lsize / (*rows);
	}
}

static void print_brief_out(t_ls *ls, int rows, int width[COL_MAX])
{
	int		i;
	int		j;
	t_ls	*tmp;

	i = 0;
	while (i < rows)
	{
		j = 0;
		tmp = ls;
		while (tmp)
		{
			if (((i + j) % rows) == 0)
				; //ft_printf("%*s ", width[j / rows], tmp->name);
			j++;
			tmp = tmp->next;
		}
		ft_printf("\n");
		i++;
	}

}


void		print_brief(t_ls *ls, int flags)
{
	int		rows;
	int		width[COL_MAX];

	rows = 1;
	int i = -1;
	print_brief_calc_rows(ls, &rows, width);
	while (width[++i])
		ft_printf("%d\n", width[i]);
	print_brief_out(ls, rows, width);
	while (ls && flags & FL_ONE)
	{
		print_color(ls, flags);
		ft_printf("\n");
		ls = ls->next;
	}
}
