/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 18:03:20 by tcase             #+#    #+#             */
/*   Updated: 2019/06/01 13:26:09 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static t_pf		*init_pf(void)
{
	t_pf *new;

	if (!(new = (t_pf*)malloc(sizeof(t_pf))))
		return (NULL);
	new->buff = NULL;
	new->eflag = 0;
	new->len = 0;
	new->hash = 0;
	new->zero = 0;
	new->plus = 0;
	new->minus = 0;
	new->space = 0;
	new->width = 0;
	new->prec = -1;
	new->length = 0;
	new->type = '0';
	return (new);
}

static void		ft_print_result(va_list valist, t_pf *pf, t_res *res)
{
	if (ft_strchr("di", pf->type))
		ft_printf_signed_number(valist, pf, res);
	else if (ft_strchr("bpouxX", pf->type))
		ft_printf_unsigned_number(valist, pf, res);
	else if (ft_strchr("sc%", pf->type))
		ft_printf_string(valist, pf, res);
	else if (ft_strchr("fF", pf->type))
		ft_printf_float(va_arg(valist, double), pf, res);
	else
		ft_printf_c(pf->type, pf, res);
}

static int		ft_printf_cycle(char *line, va_list valist, t_res *res)
{
	t_pf		*pf;

	while (line[res->len])
	{
		if (line[res->len] == '%')
		{
			if (!(pf = init_pf()))
				return (-1);
			if (!line[res->len + 1])
				return (res->len);
			(res->len)++;
			ft_parse_format(line, pf, valist, res);
			ft_print_result(valist, pf, res);
			ft_memdel((void**)&pf);
		}
		else
		{
			ft_printf_buffer(pf, res, &line[res->len], 1);
			(res->len)++;
		}
	}
	return (res->bufflen);
}

int				ft_dprintf(int fd, const char *format, ...)
{
	va_list		valist;
	t_res		*res;
	int			i;

	if (!(res = (t_res*)malloc(sizeof(t_res))))
		return (-1);
	res->str = NULL;
	res->len = 0;
	res->bufflen = 0;
	if (!(res->str = ft_strnew(1)))
	{
		ft_memdel((void**)&(res));
		return (-1);
	}
	va_start(valist, format);
	i = ft_printf_cycle((char*)format, valist, res);
	va_end(valist);
	write(fd, res->str, res->bufflen);
	ft_memdel((void**)&(res->str));
	ft_memdel((void**)&res);
	return (i);
}

int				ft_printf(const char *format, ...)
{
	va_list		valist;
	t_res		*res;
	int			i;

	if (!(res = (t_res*)malloc(sizeof(t_res))))
		return (-1);
	res->str = NULL;
	res->len = 0;
	res->bufflen = 0;
	if (!(res->str = ft_strnew(1)))
	{
		ft_memdel((void**)&(res));
		return (-1);
	}
	va_start(valist, format);
	i = ft_printf_cycle((char*)format, valist, res);
	va_end(valist);
	write(1, res->str, res->bufflen);
	ft_memdel((void**)&(res->str));
	ft_memdel((void**)&res);
	return (i);
}
