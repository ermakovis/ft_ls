/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:21:05 by tcase             #+#    #+#             */
/*   Updated: 2019/04/06 15:43:34 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, void *src, int c, size_t n)
{
	unsigned char *dstt;
	unsigned char *srct;

	dstt = dst;
	srct = src;
	while (n-- > 0)
	{
		if (*srct == (unsigned char)c)
		{
			*dstt = *srct;
			return (dstt + 1);
		}
		*dstt++ = *srct++;
	}
	return (NULL);
}
