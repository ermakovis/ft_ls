/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 16:00:00 by tcase             #+#    #+#             */
/*   Updated: 2019/05/24 22:13:59 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

static t_bf			*new_buffer(int fd)
{
	t_bf	*new;

	if (!(new = (t_bf*)malloc(sizeof(t_bf))))
		return (0);
	new->fd = fd;
	if (!(new->buff = ft_strnew(1)))
	{
		free(new);
		return (0);
	}
	return (new);
}

static int			get_buffer(const int fd, t_bf *bf)
{
	char		*tmp;
	char		buff[BUFF_SIZE + 1];
	int			ret;

	ret = 1;
	while (!(ft_strchr(bf->buff, '\n')) && ret)
	{
		if ((ret = read(fd, buff, BUFF_SIZE)) < 0)
			return (0);
		buff[ret] = '\0';
		tmp = bf->buff;
		if (!(bf->buff = ft_strjoin(bf->buff, buff)))
			return (0);
		free(tmp);
	}
	return (1);
}

static int			split_buffer(t_bf *bf, char **line)
{
	char		*left;
	char		*right;
	int			i;
	int			j;

	i = 0;
	if ((bf->buff)[0] == '\0')
		return (0);
	j = ft_strlen(bf->buff);
	while ((bf->buff)[i] != '\n' && (bf->buff)[i])
		i++;
	if (!(left = (char*)malloc(i + 1)))
		return (-1);
	ft_memcpy(left, bf->buff, i);
	left[i] = '\0';
	*line = left;
	if (!(right = (char*)malloc(j - i + 1)))
		return (-1);
	ft_memcpy(right, &((bf->buff)[i + 1]), j - i);
	right[j - i] = '\0';
	free(bf->buff);
	bf->buff = right;
	return (1);
}

static t_list		*find_list(t_list *start, int fd)
{
	while (start)
	{
		if (((t_bf*)(start->content))->fd == fd)
			return (start);
		start = start->next;
	}
	return (NULL);
}

int					get_next_line(const int fd, char **line)
{
	static t_list	*list;
	t_list			*tlist;
	t_bf			*bf;
	int				i;
	char			buff[1];

	if (fd < 0 || !line || read(fd, buff, 0) < 0 || BUFF_SIZE < 1)
		return (-1);
	if (!(tlist = find_list(list, fd)))
	{
		if (!(bf = new_buffer(fd)))
			return (-1);
		if (!(tlist = ft_lstnew(bf, sizeof(t_bf))))
			return (-1);
		ft_lstadd(&list, tlist);
		free(bf);
	}
	bf = tlist->content;
	if (!(get_buffer(fd, bf)))
		return (-1);
	if ((i = split_buffer(bf, line)) == -1)
		return (-1);
	if (i == 0)
		return (0);
	return (1);
}
