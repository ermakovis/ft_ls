/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned_number.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 16:13:32 by tcase             #+#    #+#             */
/*   Updated: 2019/05/19 12:13:10 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int		ft_printf_basebyletter(t_pf *pf)
{
	if (pf->type == 'u')
		return (10);
	if (pf->type == 'x' || pf->type == 'X' || pf->type == 'p')
		return (16);
	if (pf->type == 'o')
		return (8);
	if (pf->type == 'b')
		return (2);
	return (0);
}

static void		ft_printf_uitoa(unsigned long long int num, t_pf *pf)
{
	int		size;
	char	*tab;
	int		base;

	tab = "0123456789abcdef";
	base = ft_printf_basebyletter(pf);
	size = 0;
	if (base < 2 || base > 16)
		return ;
	size = ft_unbrlen(num, base);
	pf->buff = ft_strnew(size);
	while (size-- > 0)
	{
		pf->buff[size] = tab[num % base];
		num /= base;
	}
}

void			ft_printf_unsigned_number(va_list valist, t_pf *pf, t_res *res)
{
	if (pf->length == 1)
		ft_printf_uitoa(va_arg(valist, unsigned long long int), pf);
	else if (pf->length == 2)
		ft_printf_uitoa((unsigned char)va_arg(valist, int), pf);
	else if (pf->length == 3)
		ft_printf_uitoa(va_arg(valist, unsigned long int), pf);
	else if (pf->length == 4)
		ft_printf_uitoa((unsigned short)va_arg(valist, int), pf);
	else if (pf->length == 5)
		ft_printf_uitoa(va_arg(valist, unsigned long long int), pf);
	else if (pf->length == 6)
		ft_printf_uitoa(va_arg(valist, size_t), pf);
	else
		ft_printf_uitoa(va_arg(valist, unsigned int), pf);
	ft_printf_digit(pf, res);
}
