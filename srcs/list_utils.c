/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 19:54:40 by ambelghi          #+#    #+#             */
/*   Updated: 2019/11/13 13:28:39 by ambelghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/stat.h>
#include <sys/types.h>
#include "libft.h"

int			ls_listcount(t_lslist *elem)
{
	int			nb;
	t_lslist	*tmp;

	nb = 0;
	if ((tmp = elem))
	{
		while ((tmp = tmp->next))
			nb++;
	}
	return (nb);
}

t_lslist	*ls_lstnew(t_entry *entry)
{
	t_lslist	*new;

	new = NULL;
	if (!(new = (t_lslist*)malloc(sizeof(t_lslist))))
		exit(2);
	else
	{
		new->entry = entry;
		new->prev = NULL;
		new->next = NULL;
		return (new);
	}
	return (NULL);
}

int			set_lstadd_ascii(t_lslist *p, t_lslist *new, unsigned int flags)
{
	int	cmp;

	if (p->entry && (!new->entry->full_path
		|| ((cmp = ft_strcmp(new->entry->full_path, p->entry->full_path))
		>= -256 && (flags & FLAG_REV ? cmp >= 0 : cmp <= 0))))
	{
		p->prev->next = new;
		new->prev = p->prev;
		p->prev = new;
		new->next = p;
		return (1);
	}
	else if (!p->next && (flags & FLAG_REV ? cmp < 0 : cmp > 0))
	{
		p->next = new;
		new->prev = p;
		return (1);
	}
	return (-1);
}

void		ls_lstadd_ascii(t_lslist **start, t_lslist *new, unsigned int flags)
{
	t_lslist	*p;

	if (start && (p = *start) && new)
	{
		if (p->next)
		{
			p = p->next;
			while (p)
			{
				if (set_lstadd_ascii(p, new, flags) > 0)
					break ;
				p = p->next;
			}
		}
		else
		{
			p->next = new;
			new->prev = p;
		}
	}
}

void		ls_lstadd(t_lslist **start, t_lslist *new, unsigned int flags)
{
	if (start && *start && new)
	{
		if (flags & FLAG_U && flags & FLAG_TME)
			ls_lstadd_atime(start, new, flags);
		else if (flags & FLAG_TME)
			ls_lstadd_mtime(start, new, flags);
		else
			ls_lstadd_ascii(start, new, flags);
	}
}
