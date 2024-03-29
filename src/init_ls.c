/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 19:06:44 by tcase             #+#    #+#             */
/*   Updated: 2019/06/24 14:45:59 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		handle_stat(t_ls *new, t_ls **ls, int flags)
{
	t_stat	stat;

	if (!(ft_strcmp(new->path, "")))
		cleanup(ls, -1, "ft_ls: fts_open: No such file or directory");
	if (lstat(new->path, &stat) == -1)
	{
		ft_dprintf(2, "ft_ls: %s: No such file or directory\n", new->path);
		return ;
	}
	new->mode = stat.st_mode;
	new->link = stat.st_nlink;
	new->uid = stat.st_uid;
	new->gid = stat.st_gid;
	new->size = stat.st_size;
	new->blocks = stat.st_blocks;
	if (flags & FL_BTM)
		new->time = stat.st_birthtimespec.tv_sec;
	else if (flags & FL_ATM)
		new->time = stat.st_atime;
	else if (flags & FL_CTM)
		new->time = stat.st_ctime;
	else
		new->time = stat.st_mtime;
}

static void		handle_path(char path[PATH_MAX], char name[NAME_MAX],\
					t_ls *new, t_ls **ls)
{
	int		pathlen;
	int		namelen;
	int		slash_flag;

	slash_flag = 0;
	namelen = ft_strlen(name);
	pathlen = ft_strlen(path);
	ft_memcpy(new->name, name, namelen);
	if (pathlen && path[pathlen - 1] != '/')
		path[pathlen++] = '/';
	namelen + pathlen > PATH_MAX ? cleanup(ls, -1, "Error - Path too long") : 1;
	ft_memcpy(new->path, path, pathlen);
	ft_memcpy(new->path + pathlen, name, namelen);
}

void			add_ls(char path[PATH_MAX], char name[NAME_MAX], t_ls **ls,\
					int flags)
{
	t_ls	*tmp;
	t_ls	*new;

	tmp = *ls;
	if (!(new = (t_ls*)malloc(sizeof(t_ls))))
		cleanup(ls, -1, "Error - Failed to malloc for a ls");
	ft_bzero(new, sizeof(*new));
	handle_path(path, name, new, ls);
	handle_stat(new, ls, flags);
	if (!tmp)
	{
		*ls = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void			init_ls(int ac, char **av, t_ls **ls, int flags)
{
	int		i;

	i = -1;
	if (ac == 0)
		add_ls("", ".", ls, flags);
	while (++i < ac)
		add_ls("", av[i], ls, flags);
}
