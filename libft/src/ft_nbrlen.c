/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 13:19:22 by tcase             #+#    #+#             */
/*   Updated: 2019/06/01 10:22:23 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int			ft_nbrlen(intmax_t num, int base)
{
	intmax_t i;

	i = 1;
	if (num < 0)
	{
		i++;
		num = -num;
	}
	while (num > (intmax_t)base - 1)
	{
		num /= base;
		i++;
	}
	return (i);
}

int			ft_unbrlen(uintmax_t num, int base)
{
	uintmax_t i;

	i = 1;
	while (num > (uintmax_t)base - 1)
	{
		num /= base;
		i++;
	}
	return (i);
}
