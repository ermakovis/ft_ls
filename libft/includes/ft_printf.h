/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/02 18:39:45 by tcase             #+#    #+#             */
/*   Updated: 2019/06/01 10:18:03 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "../includes/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct					s_pf
{
	char						*buff;
	int							eflag;
	int							len;
	int							hash;
	int							zero;
	int							plus;
	int							minus;
	int							space;
	int							width;
	int							prec;
	int							length;
	char						type;
}								t_pf;

typedef struct					s_res
{
	int							len;
	int							bufflen;
	char						*str;
}								t_res;

int								ft_printf(const char *format, ...);
int								ft_dprintf(int fd, const char *format, ...);
void							ft_printf_digit(t_pf *pf, t_res *res);
void							ft_printf_string(va_list valist, t_pf *pf,\
									t_res *res);
void							ft_printf_s(char *str, t_pf *pf, t_res *res);
void							ft_printf_c(char ch, t_pf *pf, t_res *res);
void							ft_printf_float(double dbl, t_pf *pf,\
									t_res *res);
void							ft_printf_buffer(t_pf *pf, t_res *res,\
									char *buff, int len);
int								ft_wchrlen(wchar_t wch);
int								ft_wstrlen(wchar_t *wstr);
char							*ft_convert_wchar(wchar_t wch, int len);
char							*ft_convert_wstr(wchar_t *wstr, t_pf *pf);
void							ft_putwchar(wchar_t wch);
void							ft_parse_format(char *line, t_pf *pf,\
									va_list valist, t_res *res);
void							ft_printf_unsigned_number(va_list valist,\
									t_pf *pf, t_res *res);
void							ft_printf_signed_number(va_list valist, \
									t_pf *pf, t_res *res);
void							ft_printf_cleanup(t_pf *pf);

#endif
