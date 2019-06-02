/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 21:16:26 by tcase             #+#    #+#             */
/*   Updated: 2019/04/14 17:00:43 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_overflow(int sign)
{
	if (sign < 0)
		return (0);
	else
		return (-1);
}

int			ft_atoi(const char *str)
{
	size_t	i;
	int		sign;
	long	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while (str[i] == '\n' || str[i] == '\t' || str[i] == '\r' || \
				str[i] == '\v' || str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((nb * 10 + str[i] - '0') / 10 != nb)
			return (ft_overflow(sign));
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(nb * sign));
}
