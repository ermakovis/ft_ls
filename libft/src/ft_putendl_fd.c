/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 19:36:40 by tcase             #+#    #+#             */
/*   Updated: 2019/04/08 11:06:22 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

void	ft_putendl_fd(const char *str, int fd)
{
	if (!str || !fd)
		return ;
	write(fd, str, ft_strlen(str));
	ft_putchar_fd('\n', fd);
}
