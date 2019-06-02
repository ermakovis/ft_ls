/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 15:09:11 by tcase             #+#    #+#             */
/*   Updated: 2019/04/14 16:22:38 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void		*ft_memalloc(size_t size)
{
	void			*tmp;

	if (!(tmp = (void*)malloc(size)))
		return (NULL);
	ft_memset(tmp, '\0', size);
	return (tmp);
}
