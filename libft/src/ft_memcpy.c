/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 12:14:48 by tcase             #+#    #+#             */
/*   Updated: 2019/04/14 13:57:30 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *dstt;
	unsigned char *srct;

	if (!dst && !src)
		return (0);
	dstt = dst;
	srct = (void*)src;
	while (n-- > 0)
		*dstt++ = *srct++;
	return (dst);
}
