/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 16:03:46 by tcase             #+#    #+#             */
/*   Updated: 2019/04/14 13:30:18 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char		*do_norminette(int n)
{
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	return (0);
}

static int		ft_int_len(int n, size_t i)
{
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char			*ft_itoa(int n)
{
	char	*str;
	int		i;

	i = 0;
	if (n == 0 || n == -2147483648)
		return (do_norminette(n));
	if (n < 0)
	{
		n = -n;
		i++;
	}
	i = ft_int_len(n, i);
	if (!(str = (char*)malloc(i + 1)))
		return (NULL);
	str[i] = '\0';
	str[0] = '-';
	while (n > 0)
	{
		str[--i] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}
