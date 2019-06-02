/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 19:55:56 by tcase             #+#    #+#             */
/*   Updated: 2019/04/14 11:32:03 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_strmap(const char *s, char (*f)(char))
{
	char	*str;
	char	*tmp;

	if (!s || !f)
		return (NULL);
	if (!(str = (char*)malloc(ft_strlen(s) + 1)))
		return (NULL);
	tmp = str;
	while (*s)
	{
		*str = f((char)*s);
		s++;
		str++;
	}
	*str = '\0';
	return (tmp);
}
