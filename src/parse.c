/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 16:48:04 by tcase             #+#    #+#             */
/*   Updated: 2019/06/09 21:04:30 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		add_flag(char *str, int *flags)
{
	int		shift;

	shift = 0;
	while (*(++str))
	{
		if ((shift = ft_strchrlen(FLAGS, (*str))) == -1 ||
			(str[0] == '-' && str[1]))
		{
			ft_dprintf(2, "ft_ls: illegal option -- %c\n", *str);
			ft_dprintf(2, "usage: ft_ls [-%s] [file ...]\n", FLAGS);
			exit (1);
		}
		shift == 7 ? *flags |= (1 << 6) : 1;
		*flags |= (1 << shift);
	}
}

void		parse_params(int *ac, char ***av, int *flags)
{
	int		count;
	char	**str;

	count = 0;
	str = *av;
	while (++count < *ac && str[count][0] == '-' && str[count][1]\
			&& !(*flags & FL_MIN))
		add_flag(str[count], flags);
	*av = *av + count;
	*ac = *ac - count;		
	*ac > 1 ? (*flags |= FL_HEADR) : 1;
}
