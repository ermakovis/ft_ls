/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_digit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 12:08:58 by tcase             #+#    #+#             */
/*   Updated: 2019/05/19 14:30:16 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		ft_printf_dprec(t_pf *pf, char *buff)
{
	int			len;
	int			flag;

	flag = 0;
	if ((!(ft_strcmp(buff, "0"))) || (!(ft_strcmp(buff, ""))))
		pf->eflag = 1;
	if (!(ft_strcmp(buff, "")))
		return ;
	len = ft_strlen(buff);
	if (buff[0] == '-')
		flag = 1;
	if (len > pf->prec + flag)
		return ;
	ft_memmove(&buff[pf->prec - len + flag], buff, len);
	ft_memset(buff, '0', pf->prec - len + flag);
	if (buff[pf->prec - len + flag] == '-' && buff[0])
		ft_swap(&buff[pf->prec - len + flag], &buff[0]);
}

static void		ft_printf_dflags(t_pf *pf, char *buff)
{
	int			len;

	len = ft_strlen(buff);
	if (ft_strchr("di", pf->type) == 0 && (pf->plus != 1 || pf->space != 1))
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

static void		ft_printf_udflags(t_pf *pf, char *buff)
{
	int			len;

	len = ft_strlen(buff);
	if (ft_strchr("poxX", pf->type) != 0 && pf->hash == 0)
		return ;
	if (pf->type == 'o' && buff[0] != '0')
	{
		ft_memmove(&buff[1], buff, len);
		ft_memset(buff, '0', 1);
	}
	if ((pf->type == 'x' || pf->type == 'X') || pf->type == 'p')
	{
		if (pf->eflag == 1 && pf->type != 'p')
			return ;
		if (pf->eflag == 1 && pf->type != 'p')
			return ;
		ft_memmove(&buff[2], buff, len);
		ft_memcpy(buff, "0x", 2);
	}
}

static void		ft_printf_dwidth(t_pf *pf)
{
	char		*tmp;
	int			len;

	len = ft_strlen(pf->buff);
	if (pf->width < len)
		return ;
	if (!(tmp = ft_strnew(pf->width)))
		ft_printf_cleanup(pf);
	if (pf->zero == 1 && pf->minus == 0 && pf->prec < 0)
		ft_memset(tmp, '0', pf->width);
	else
		ft_memset(tmp, ' ', pf->width);
	if (pf->minus == 1)
		ft_memcpy(tmp, pf->buff, len);
	else
		ft_memcpy(&tmp[pf->width - len], pf->buff, len);
	if (tmp[pf->width - len + 1] == 'x' && tmp[1] == '0' && tmp[0] == '0')
		ft_swap(&tmp[1], &tmp[pf->width - len + 1]);
	if (((tmp[pf->width - len] == ' ' && tmp[0] == '0' && pf->space == 1)) ||
		((tmp[pf->width - len] == '+' && tmp[0] == '0' && pf->plus == 1)) ||
		((tmp[pf->width - len] == '-' && tmp[0] == '0')))
		ft_swap(&tmp[0], &tmp[pf->width - len]);
	ft_memdel((void**)&(pf->buff));
	pf->buff = tmp;
}

void			ft_printf_digit(t_pf *pf, t_res *res)
{
	char		buff[128];

	ft_bzero(buff, 128);
	if (!(ft_strcmp(pf->buff, "0")) && pf->prec == 0)
	{
		ft_memdel((void**)&(pf->buff));
		pf->buff = ft_strdup("");
	}
	ft_memcpy(buff, pf->buff, ft_strlen(pf->buff));
	ft_printf_dprec(pf, buff);
	ft_printf_dflags(pf, buff);
	ft_printf_udflags(pf, buff);
	ft_memdel((void**)&(pf->buff));
	pf->buff = ft_strdup(buff);
	ft_printf_dwidth(pf);
	if (pf->type == 'X')
		ft_strtoupper(pf->buff);
	ft_printf_buffer(pf, res, pf->buff, ft_strlen(pf->buff));
	ft_memdel((void**)&(pf->buff));
}
