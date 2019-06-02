/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:45:10 by tcase             #+#    #+#             */
/*   Updated: 2019/04/08 14:29:45 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*p;
	char	*tmp;

	len = ft_strlen(s1);
	if (!(p = (char*)malloc(len + 1)))
		return (NULL);
	tmp = p;
	while (len-- > 0)
		*tmp++ = *s1++;
	*tmp = '\0';
	return (p);
}
