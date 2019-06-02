/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 17:36:32 by tcase             #+#    #+#             */
/*   Updated: 2019/04/06 17:37:58 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t i;
	size_t y;

	y = 0;
	i = ft_strlen(dest);
	while (y < n && y <= ft_strlen(src))
	{
		dest[i + y] = src[y];
		y++;
	}
	while (y < ft_strlen(src))
	{
		dest[i + y] = '\0';
		y++;
	}
	return (dest);
}
