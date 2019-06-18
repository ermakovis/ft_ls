/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_lex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcase <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 21:36:13 by tcase             #+#    #+#             */
/*   Updated: 2019/06/15 22:18:57 by tcase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_ls	*merge(t_ls *a, t_ls *b) 
{ 
    t_ls	*result;
	
	result = NULL; 
    if (a == NULL) 
        return (b); 
    else if (b == NULL) 
        return (a); 
    if (ft_strcmp(a->name, b->name) > 0) 
	{ 
        result = a; 
        result->next = merge(a->next, b); 
    } 
    else 
	{ 
        result = b; 
        result->next = merge(a, b->next); 
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

void		sort_rev(t_ls **ls) 
{ 
    t_ls	*head; 
    t_ls	*a; 
    t_ls	*b; 
  
	head = *ls;
    if (!head || !(head->next)) 
        return; 
    split(head, &a, &b); 
    sort_rev(&a); 
    sort_rev(&b); 
    *ls = merge(a, b); 
} 
