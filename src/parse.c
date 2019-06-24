/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 16:48:04 by tcase             #+#    #+#             */
/*   Updated: 2019/06/24 14:37:04 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		sorts(char ch, int *flags)
{
	if (ch == 'U')
	{
		*flags &= ~FL_CTM;
		*flags &= ~FL_ATM;
	}
	if (ch == 'u')
	{
		*flags &= ~FL_CTM;
		*flags &= ~FL_BTM;
	}
	if (ch == 'c')
	{
		*flags &= ~FL_BTM;
		*flags &= ~FL_ATM;
	}
}

static void		exceptions(char ch, int *flags)
{
	ch == 'p' && *flags & FL_SYM ? *flags ^= FL_SYM : 1;
	ch == 'F' && *flags & FL_PSL ? *flags ^= FL_PSL : 1;
	ch == '1' && *flags & FL_LNG ? *flags ^= FL_LNG : 1;
	ch == 'n' ? *flags |= FL_LNG : 1;
	ch == 'f' ? *flags |= FL_ALL : 1;
	ch == 'g' ? *flags |= FL_LNG : 1;
	ch == 'o' ? *flags |= FL_LNG : 1;
}

static void		add_flag(char *str, int *flags)
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
			exit(1);
		}
		exceptions(*str, flags);
		sorts(*str, flags);
		*flags |= (1 << shift);
	}
	*flags & FL_SSZ && *flags & FL_ATM ? (*flags ^= FL_ATM) : 1;
}

void			parse_params(int *ac, char ***av, int *flags)
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
