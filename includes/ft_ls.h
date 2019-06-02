/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 15:33:11 by tcase             #+#    #+#             */
/*   Updated: 2019/06/02 18:07:55 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H
# include <stdlib.h>
# include <errno.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <unistd.h>
# include "libft.h"
# define FLAGS "Ralrt"

# define FL_REC (1 << 0)
# define FL_ALL (1 << 1)
# define FL_LNG (1 << 2)
# define FL_REV (1 << 3)
# define FL_STM (1 << 4)

typedef struct	dirent		t_dir;

typedef struct				s_stat
{
	char					path[PATH_MAX];
	char					*name;
	struct s_stat			*next;
}							t_stat;

void						cleanup(t_stat *stat, int code, char *message);
void						parse_params(int *ac, char ***av, int *flags);


#endif
