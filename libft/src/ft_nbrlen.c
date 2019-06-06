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

int			ft_nbrlen(long long int num, int base)
{
	long long int i;

	i = 1;
	if (num < 0)
	{
		i++;
		num = -num;
	}
	while (num > (long long int)base - 1)
	{
		num /= base;
		i++;
	}
	return (i);
}

int			ft_unbrlen(unsigned long long int num, int base)
{
	unsigned long long int i;

	i = 1;
	while (num > (unsigned long long int)base - 1)
	{
		num /= base;
		i++;
	}
	return (i);
}
