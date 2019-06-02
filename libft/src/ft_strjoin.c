/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 11:20:52 by tcase             #+#    #+#             */
/*   Updated: 2019/04/14 09:35:07 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*join;
	size_t	s1len;
	size_t	s2len;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	if (!(join = (char*)malloc(s1len + s2len + 1)))
		return (NULL);
	ft_memcpy(join, s1, s1len);
	ft_memcpy((join + s1len), s2, s2len);
	*(join + s1len + s2len) = '\0';
	return (join);
}
