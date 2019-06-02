/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 19:11:53 by tcase             #+#    #+#             */
/*   Updated: 2019/04/14 15:14:32 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *s, const char *c, size_t n)
{
	size_t i;
	size_t j;

	i = 0;
	j = ft_strlen(c);
	if (!*c)
		return ((char*)s);
	if (!c || j > ft_strlen(s) || j > n)
		return (NULL);
	while (i <= n - j)
	{
		if (*s == c[0])
		{
			if (ft_strnequ(s, c, j))
				return ((char*)s);
		}
		i++;
		s++;
	}
	return (NULL);
}
