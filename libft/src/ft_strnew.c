/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 21:41:48 by tcase             #+#    #+#             */
/*   Updated: 2019/05/10 20:52:07 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_strnew(size_t size)
{
	char	*p;

	p = NULL;
	if (!size)
		return ("");
	if ((int)size < 0)
		return (NULL);
	if (!(p = (char*)malloc(size + 1)))
		return (NULL);
	p[size] = '\0';
	while (size-- > 0)
		p[size] = '\0';
	return (p);
}

wchar_t		*ft_wstrnew(size_t size)
{
	wchar_t	*p;

	p = NULL;
	if (!(p = (wchar_t*)malloc(sizeof(wchar_t) * (size + 1))))
		return (NULL);
	ft_bzero(p, sizeof(wchar_t) * size + 1);
	return (p);
}
