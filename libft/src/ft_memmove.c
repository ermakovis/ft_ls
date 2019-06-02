/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 16:59:42 by tcase             #+#    #+#             */
/*   Updated: 2019/04/14 16:22:27 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char		*destt;
	const char	*srct;

	if (!dest && !src)
		return (0);
	destt = dest;
	srct = src;
	if (dest < src)
		while (len-- > 0)
			*destt++ = *srct++;
	else
		while (len-- > 0)
			*(destt + len) = *(srct + len);
	return (dest);
}
