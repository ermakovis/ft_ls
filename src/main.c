/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 15:15:48 by tcase             #+#    #+#             */
/*   Updated: 2019/06/02 18:21:42 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		add_stat(t_stat **stat)
{
	t_stat		*new_stat;
	t_stat		*tmp_stat;

	tmp_stat = *stat;
	if (!(new_stat = (t_stat*)malloc(sizeof(t_stat))))
		cleanup(*stat, -1, "Error - malloc failed");
	ft_bzero((void*)new_stat, sizeof(t_stat));
	if (!*stat)
	{
		*stat = new_stat;
		return;
	}
	while (tmp_stat->next)
		tmp_stat = tmp_stat->next;
	tmp_stat->next = new_stat;

}

void		list_dir(char *path, int flags, t_stat **stat)
{
	DIR			*dir;
	t_dir		 *entry;
	size_t		len;
	char		*name;
		
	add_stat(newstat, stat);
	len = ft_strlen(path);
	ft_printf("path -%s\n", path);
	if (!(dir = opendir(path))) 
		cleanup(*stat, -1, "Error - Failed to open dir");
	ft_printf("%s\n", path);
	while ((entry = readdir(dir)) != NULL) 
	{
		name = entry->d_name;
		if (entry->d_type == DT_DIR) 
		{
			if (!strcmp(name, ".") || !strcmp(name, ".."))
				continue;
			if (len + strlen(name) + 2 > PATH_MAX) 
				ft_printf("path too long: %s/%s\n", path, name);
//			else {
//				path[len] = '/';
//				strcpy(path + len + 1, name);
//				list_dir(path, flags, stat);
//				path[len] = '\0';
//			}
		} 
		else 
			ft_printf("%s\n", name);
	}
	closedir(dir);
}

void		print_output(int ac, char **av, int flags)
{
	int		i;
	t_stat	*stat;

	i = -1;
	while (++i < ac)
		list_dir(av[i], flags, &stat);
	
}

int			main(int ac, char **av)
{
	int		flags;

	flags = 0;
	parse_params(&ac, &av, &flags);
	print_output(ac, av, flags);
	
	ft_printf("flags -- %d - %s - %b\n", ac, av[0], flags);
	cleanup(NULL, 0, "Success");
	return (0);
}
