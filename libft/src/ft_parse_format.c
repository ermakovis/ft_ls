/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 11:48:30 by tcase             #+#    #+#             */
/*   Updated: 2019/05/19 13:28:47 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void			ft_parse_flags(t_pf *pf, char *line, t_res *res)
{
	while (line[res->len] == ' ' || line[res->len] == '#' || \
			line[res->len] == '-' || line[res->len] == '0' || \
			line[res->len] == '+')
	{
		if (line[res->len] == ' ')
			pf->space = 1;
		if (line[res->len] == '#')
			pf->hash = 1;
		if (line[res->len] == '-')
			pf->minus = 1;
		if (line[res->len] == '+')
			pf->plus = 1;
		if (line[res->len] == '0')
			pf->zero = 1;
		(res->len)++;
	}
}

static void			ft_parse_width(t_pf *pf, char *line, t_res *res, \
						va_list valist)
{
	int		i;

	if (ft_isdigit(line[res->len]))
	{
		pf->width = ft_atoi(&line[res->len]);
		res->len += ft_nbrlen(pf->width, 10);
	}
	if (line[res->len] == '*')
	{
		if ((i = va_arg(valist, int)) < 0)
		{
			pf->minus = 1;
			i = -i;
		}
		pf->width = i;
		(res->len)++;
	}
	if (ft_isdigit(line[res->len]))
	{
		pf->width = ft_atoi(&line[res->len]);
		res->len += ft_nbrlen(pf->width, 10);
	}
}

static void			ft_parse_prec(t_pf *pf, char *line, t_res *res, \
						va_list valist)
{
	if (line[res->len] != '.')
		return ;
	pf->prec = 0;
	res->len++;
	if (line[res->len] == '*')
	{
		pf->prec = va_arg(valist, int);
		(res->len)++;
	}
	else if (ft_isdigit(line[res->len]))
	{
		pf->prec = ft_atoi(&line[res->len]);
		res->len += ft_nbrlen(pf->prec, 10);
	}
}

static void			ft_parse_length(t_pf *pf, char *line, t_res *res)
{
	if (ft_strncmp(&line[res->len], "l", 1) == 0)
		pf->length = 3;
	if (ft_strncmp(&line[res->len], "h", 1) == 0)
		pf->length = 4;
	if (ft_strncmp(&line[res->len], "j", 1) == 0)
		pf->length = 5;
	if (ft_strncmp(&line[res->len], "z", 1) == 0)
		pf->length = 6;
	if (ft_strncmp(&line[res->len], "ll", 2) == 0)
		pf->length = 1;
	if (ft_strncmp(&line[res->len], "hh", 2) == 0)
		pf->length = 2;
	if (pf->length > 0 && pf->length <= 2)
		res->len += 2;
	else if (pf->length > 2)
		(res->len)++;
}

void				ft_parse_format(char *line, t_pf *pf, va_list valist, \
							t_res *res)
{
	ft_parse_flags(pf, line, res);
	ft_parse_width(pf, line, res, valist);
	ft_parse_prec(pf, line, res, valist);
	ft_parse_length(pf, line, res);
	pf->type = line[res->len];
	(res->len)++;
	if (pf->type == 'p')
	{
		pf->length = 1;
		pf->hash = 1;
	}
	if (ft_strchr("DUOCS", pf->type))
	{
		pf->length = 3;
		pf->type = ft_tolower(pf->type);
	}
}
