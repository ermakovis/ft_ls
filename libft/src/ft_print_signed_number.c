/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_signed_number.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 16:18:46 by tcase             #+#    #+#             */
/*   Updated: 2019/05/19 12:12:31 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "limits.h"
#include "../includes/ft_printf.h"

void	ft_printf_itoa(long long int num, t_pf *pf)
{
	int		size;

	if (num < -9223372036854775807)
	{
		pf->buff = ft_strdup("-9223372036854775808");
		return ;
	}
	size = ft_nbrlen(num, 10);
	if (num < 0)
		num = -num;
	if (!(pf->buff = ft_strnew(size)))
		ft_printf_cleanup(pf);
	pf->buff[0] = '-';
	if (num == 0)
		ft_memset(pf->buff, '0', 1);
	while (num > 0)
	{
		pf->buff[--size] = (num % 10) + '0';
		num /= 10;
	}
}

void	ft_printf_signed_number(va_list valist, t_pf *pf, t_res *res)
{
	if (pf->length == 1)
		ft_printf_itoa(va_arg(valist, long long int), pf);
	else if (pf->length == 2)
		ft_printf_itoa((char)va_arg(valist, int), pf);
	else if (pf->length == 3)
		ft_printf_itoa(va_arg(valist, long int), pf);
	else if (pf->length == 4)
		ft_printf_itoa((short int)va_arg(valist, int), pf);
	else if (pf->length == 5)
		ft_printf_itoa(va_arg(valist, long long int), pf);
	else if (pf->length == 6)
		ft_printf_itoa(va_arg(valist, size_t), pf);
	else
		ft_printf_itoa(va_arg(valist, int), pf);
	ft_printf_digit(pf, res);
}
