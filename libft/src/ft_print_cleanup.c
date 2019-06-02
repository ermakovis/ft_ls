/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_cleanup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 14:24:28 by tcase             #+#    #+#             */
/*   Updated: 2019/06/01 12:26:02 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void			ft_printf_buffer(t_pf *pf, t_res *res, char *buff, int len)
{
	char		*tmp;

	if (!(tmp = ft_strnew(res->bufflen + len)))
	{
		ft_printf_cleanup(pf);
		ft_memdel((void**)&(res->str));
		ft_memdel((void**)&(res));
	}
	ft_memcpy(tmp, res->str, res->bufflen);
	ft_memcpy(&tmp[res->bufflen], buff, len);
	ft_memdel((void**)&(res->str));
	res->str = tmp;
	res->bufflen += len;
}

void			ft_printf_cleanup(t_pf *pf)
{
	ft_memdel((void**)&(pf->buff));
	ft_memdel((void**)&(pf));
	exit(-1);
}
