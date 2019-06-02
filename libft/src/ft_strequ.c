/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 19:37:05 by tcase             #+#    #+#             */
/*   Updated: 2019/04/08 10:34:22 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strequ(const char *s1, const char *s2)
{
	size_t i;
	size_t j;

	if (!s1 || !s2)
		return (0);
	i = 0;
	j = ft_strlen(s1);
	if (j != ft_strlen(s2))
		return (0);
	while (i < j)
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}
