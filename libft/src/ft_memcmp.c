/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:34:20 by tcase             #+#    #+#             */
/*   Updated: 2019/04/06 15:42:23 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char *s1t;
	const unsigned char *s2t;

	s1t = s1;
	s2t = s2;
	while (n-- > 0)
	{
		if (*s1t != *s2t)
			return (*s1t - *s2t);
		s1t++;
		s2t++;
	}
	return (0);
}
