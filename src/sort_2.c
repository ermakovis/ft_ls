/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/23 17:49:57 by tcase             #+#    #+#             */
/*   Updated: 2019/06/23 17:52:02 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	sort_reverse(t_ls **ls)
{
	t_ls	*cur;
	t_ls	*prev;
	t_ls	*next;

	prev = NULL;
	next = NULL;
	cur = *ls;
	while (cur)
	{
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	(*ls) = prev;
}

void	sort_av(int ac, char ***av, int flags)
{
	int		i;
	char	**tmp;
	char	*tmpstr;

	i = 0;
	if (ac < 2 || flags & FL_SRT)
		return ;
	tmp = *av;
	while (i < ac - 1)
	{
		if (ft_strcmp(tmp[i], tmp[i + 1]) > 0)
		{
			tmpstr = tmp[i];
			tmp[i] = tmp[i + 1];
			tmp[i + 1] = tmpstr;
			i = 0;
		}
		else
			i++;
	}
	*av = tmp;
}
