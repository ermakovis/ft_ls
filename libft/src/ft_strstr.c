/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 19:06:48 by tcase             #+#    #+#             */
/*   Updated: 2019/04/06 19:09:44 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s, const char *c)
{
	char	*p;
	size_t	j;

	j = ft_strlen(c);
	if (!*c)
		return ((char*)s);
	while ((p = (ft_strchr(s, c[0]))))
	{
		if (ft_strnequ(p, c, j))
			return (p);
		s = p + 1;
	}
	return (0);
}
