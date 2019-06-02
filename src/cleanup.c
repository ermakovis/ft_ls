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

void	cleanup(t_stat *stat, int code, char *message)
{
	stat = stat;
	if (code < 0)
		ft_dprintf(2, "%s\n", message);
	exit (code);
}
