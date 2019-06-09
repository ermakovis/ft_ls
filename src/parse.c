/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 16:48:04 by tcase             #+#    #+#             */
/*   Updated: 2019/06/09 17:09:16 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		add_flag(char *str, int *flags)
{
	int		shift;

	shift = 0;
	while (*(++str))
	{
		if ((shift = ft_strchrlen(FLAGS, (*str))) == -1)
			cleanup(NULL, -1, "Error - wrong input");
		*flags = *flags | (1 << shift);
	}
}

void		parse_params(int *ac, char ***av, int *flags)
{
	int		count;
	char	**str;

	count = 0;
	str = *av;
	while (++count < *ac && str[count][0] == '-' && str[count][1])
		add_flag(str[count], flags);
	*av = *av + count;
	*ac = *ac - count;		
}
