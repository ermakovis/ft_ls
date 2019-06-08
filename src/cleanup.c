/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 15:23:57 by tcase             #+#    #+#             */
/*   Updated: 2019/06/02 17:25:13 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	cleanup(t_ls **ls, int code, char *message)
{
	t_ls *tmp;

	tmp = NULL;
	while (*ls)
	{
		tmp = *ls;
		(*ls) = (*ls)->next;
		ft_memdel((void**)&tmp);
	}
	if (code < 0)
		ft_dprintf(2, "%s\n", message);
	if (code <= 0)
		exit (code);
}
