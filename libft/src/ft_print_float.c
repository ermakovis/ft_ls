/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printfloat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 12:10:46 by tcase             #+#    #+#             */
/*   Updated: 2019/06/01 10:32:36 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char		*ft_printf_ftoa(long long int num, t_pf *pf)
{
	int		size;
	char	*buff;

	if (num < -9223372036854775807)
	{
		buff = ft_strdup("-9223372036854775808");
		return (buff);
	}
	size = ft_nbrlen(num, 10);
	if (num < 0)
		num = -num;
	if (!(buff = ft_strnew(size)))
		ft_printf_cleanup(pf);
	buff[0] = '-';
	if (num == 0)
		if (!(buff = ft_strdup("0")))
			ft_printf_cleanup(pf);
	while (num > 0)
	{
		buff[--size] = (num % 10) + '0';
		num /= 10;
	}
	return (buff);
}

static void		ft_printf_float_comb(long long int left, long long int right, \
					t_pf *pf, char *buff)
{
	int		llen;
	int		rlen;
	char	*tmp;

	llen = ft_nbrlen(left, 10);
	rlen = ft_nbrlen(right, 10);
	pf->prec > rlen ? rlen = pf->prec : rlen;
	if (!(tmp = ft_printf_ftoa(left, pf)))
		ft_printf_cleanup(pf);
	ft_memcpy(buff, tmp, llen);
	ft_memdel((void**)&(tmp));
	(buff)[llen] = '.';
	if (right == 0)
	{
		if (!(tmp = ft_strnew(rlen)))
			ft_printf_cleanup(pf);
		ft_memset(tmp, '0', rlen);
	}
	else if (!(tmp = ft_printf_ftoa(right, pf)))
		ft_printf_cleanup(pf);
	ft_memcpy(&(buff)[llen + 1], tmp, rlen);
	ft_memdel((void**)&(tmp));
}

static void		ft_printf_float_flags(t_pf *pf, char *buff)
{
	int			len;

	len = ft_strlen(buff);
	if (pf->plus != 1 && pf->space != 1)
		return ;
	if ((pf->space == 1 || pf->plus == 1) && buff[0] != '-')
	{
		ft_memmove(&buff[1], buff, len);
		if (pf->space == 1 && pf->plus == 0)
			buff[0] = ' ';
		if (pf->plus == 1)
			buff[0] = '+';
	}
}

static void		ft_printf_float_width(t_pf *pf)
{
	char		*tmp;
	int			len;

	if (!(pf->buff))
		pf->buff = "(null)";
	len = ft_strlen(pf->buff);
	if (pf->width < len)
		return ;
	if (!(tmp = ft_strnew(pf->width)))
		ft_printf_cleanup(pf);
	if (pf->zero == 1 && pf->minus == 0)
		ft_memset(tmp, '0', pf->width);
	else
		ft_memset(tmp, ' ', pf->width);
	if (pf->minus == 1)
		ft_memcpy(tmp, pf->buff, len);
	else
		ft_memcpy(&tmp[pf->width - len], pf->buff, len);
	ft_memdel((void**)&(pf->buff));
	pf->buff = tmp;
}

void			ft_printf_float(double dbl, t_pf *pf, t_res *res)
{
	double				decimal;
	long long int		right;
	long long int		left;
	char				buff[128];

	ft_bzero(buff, 128);
	if (pf->prec == -1)
		pf->prec = 6;
	left = (long long int)dbl;
	decimal = (dbl > 0 ? dbl : -dbl);
	decimal = (decimal - (long long int)(decimal)) * ft_power(10, pf->prec + 1);
	decimal = ((long long int)decimal % 10 > 4) ?\
		decimal / 10 + 1 : decimal / 10;
	right = (long long int)decimal;
	ft_printf_float_comb(left, right, pf, buff);
	ft_printf_float_flags(pf, buff);
	ft_memdel((void**)&(pf->buff));
	pf->buff = ft_strdup(buff);
	ft_printf_float_width(pf);
	ft_printf_buffer(pf, res, pf->buff, ft_strlen(pf->buff));
	ft_memdel((void**)&(pf->buff));
}
