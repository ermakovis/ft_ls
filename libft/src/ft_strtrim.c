/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 10:19:24 by tcase             #+#    #+#             */
/*   Updated: 2019/04/14 16:20:43 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t		ft_getfirst(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i++;
	return (i);
}

static size_t		ft_getlast(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	i--;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i--;
	return (i);
}

char				*ft_strtrim(const char *s)
{
	char	*trm;
	char	*tmp;
	size_t	first;
	size_t	last;
	size_t	len;

	if (!s)
		return (NULL);
	first = ft_getfirst(s);
	last = ft_getlast(s);
	len = last - first + 1;
	if (first == ft_strlen(s))
		return (ft_strdup(""));
	if (!(trm = (char*)malloc(len + 1)))
		return (NULL);
	tmp = trm;
	while (len-- > 0)
		*trm++ = *(s++ + first);
	trm[len + 1] = '\0';
	return (tmp);
}
