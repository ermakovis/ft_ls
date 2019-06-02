/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_wchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 13:45:55 by tcase             #+#    #+#             */
/*   Updated: 2019/06/01 10:33:41 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int				ft_wstrlen(wchar_t *str)
{
	int len;

	len = 0;
	while (*str)
	{
		len += ft_wchrlen(*str);
		str++;
	}
	return (len);
}

int				ft_wchrlen(wchar_t wch)
{
	int len;

	len = 0;
	if (wch <= 0x7F)
		len = 1;
	else if (wch <= 0x7FF)
		len = 2;
	else if (wch <= 0xFFFF)
		len = 3;
	else if (wch <= 0x10FFFF)
		len = 4;
	return (len);
}

char			*ft_convert_wchar(wchar_t wch, int len)
{
	char	*new;

	new = ft_strnew(3);
	if (wch <= 0x7F)
		new[len++] = wch;
	else if (wch <= 0x7FF)
	{
		new[len++] = ((wch >> 6) | 0xC0);
		new[len++] = (((wch >> 0) & 0x3F) | 0x80);
	}
	else if (wch <= 0xFFFF)
	{
		new[len++] = ((wch >> 12) | 0xE0);
		new[len++] = (((wch >> 6) & 0x3F) | 0x80);
		new[len++] = ((wch & 0x3F) | 0x80);
	}
	else if (wch <= 0x10FFFF)
	{
		new[len++] = ((wch >> 18) | 0xF0);
		new[len++] = (((wch >> 12) & 0x3F) | 0x80);
		new[len++] = (((wch >> 6) & 0x3F) | 0x80);
		new[len++] = ((wch & 0x3F) | 0x80);
	}
	return (new);
}

char			*ft_convert_wstr(wchar_t *wstr, t_pf *pf)
{
	int		len;
	int		tmplen;
	int		i;
	char	*str;
	char	*tmp;

	i = 0;
	tmplen = 0;
	len = ft_wstrlen(wstr);
	if (pf->prec >= 0)
		pf->prec < len ? len = pf->prec : len;
	str = ft_strnew(len);
	while (*wstr)
	{
		tmp = ft_convert_wchar(*wstr, 0);
		tmplen = ft_strlen(tmp);
		if (len < i + tmplen)
			return (str);
		ft_memcpy(&str[i], tmp, ft_strlen(tmp));
		free(tmp);
		i += tmplen;
		wstr++;
	}
	return (str);
}

void			ft_putwchar(wchar_t wch)
{
	char	*new;

	new = ft_convert_wchar(wch, 0);
	free(new);
	write(1, new, ft_strlen(new));
}
