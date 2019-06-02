/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 12:09:49 by tcase             #+#    #+#             */
/*   Updated: 2019/04/14 14:07:11 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strnlen(const char *str, size_t n)
{
	size_t len;

	len = 0;
	while (str[len])
		len++;
	if (len > n)
		return (n);
	return (len);
}

char		*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t size;

	size = ft_strnlen(src, len);
	if (size != len)
		ft_memset(dst + size, '\0', len - size);
	return (ft_memcpy(dst, src, size));
}
