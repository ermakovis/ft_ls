/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 13:27:47 by tcase             #+#    #+#             */
/*   Updated: 2019/04/08 10:37:25 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	size_t i;
	size_t y;

	y = 0;
	i = ft_strlen(dest);
	while (y < ft_strlen(src))
	{
		dest[i + y] = src[y];
		y++;
	}
	dest[i + y] = '\0';
	return (dest);
}
