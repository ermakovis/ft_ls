/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 09:55:56 by tcase             #+#    #+#             */
/*   Updated: 2019/04/14 10:05:10 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t i;
	size_t j;

	i = 0;
	j = ft_strlen(src);
	while (*dest && size > 0)
	{
		dest++;
		i++;
		size--;
	}
	while (size-- > 1 && *src)
		*dest++ = *src++;
	if (size == 0 || !*src)
		*dest = '\0';
	return (j + i);
}
