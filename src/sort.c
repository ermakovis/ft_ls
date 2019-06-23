/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_lex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 21:36:13 by tcase             #+#    #+#             */
/*   Updated: 2019/06/23 16:02:41 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	compare(t_ls *a, t_ls *b, int flags)
{
	if (flags & FL_STM && a->time != b->time)
		return (a->time > b->time);
	if (flags & FL_SSZ && a->size != b->size)
		return (a->size > b->size);
	return (ft_strcmp(a->name, b->name) < 0);
}

static t_ls	*merge(t_ls *a, t_ls *b, int flags) 
{ 
    t_ls	*result;
	
	result = NULL; 
    if (a == NULL) 
        return (b); 
    else if (b == NULL) 
        return (a); 
    if (compare(a, b, flags))
	{ 
        result = a; 
        result->next = merge(a->next, b, flags); 
    } 
    else 
	{ 
        result = b; 
        result->next = merge(a, b->next, flags); 
    } 
    return (result); 
} 
  
static void	split(t_ls *source, t_ls **right, t_ls **left) 
{ 
    t_ls	*fast; 
    t_ls	*slow; 

    slow = source; 
    fast = source->next; 
    while (fast != NULL) 
	{ 
        fast = fast->next; 
        if (fast != NULL) 
		{ 
            slow = slow->next; 
            fast = fast->next; 
        } 
    } 
    *right = source; 
    *left = slow->next; 
    slow->next = NULL; 
} 

static void		sort(t_ls **ls, int flags) 
{ 
    t_ls	*head; 
    t_ls	*a; 
    t_ls	*b; 
  
	head = *ls;
    if (!head || !(head->next)) 
        return; 
    split(head, &a, &b); 
    sort(&a, flags); 
    sort(&b, flags); 
    *ls = merge(a, b, flags); 
} 

static void	sort_reverse(t_ls **ls)
{
	t_ls	*cur;
	t_ls	*prev;
	t_ls	*next;

	prev = NULL;
	next = NULL;
	cur = *ls;
	while (cur)
	{
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	(*ls) = prev;
}

void		sort_ls(t_ls **ls, int flags)
{
	if (flags & FL_SRT)
		return ;
	sort(ls, flags);
	if (flags & FL_REV)
		sort_reverse(ls);
}
