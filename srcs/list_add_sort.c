/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_add_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:15:27 by ambelghi          #+#    #+#             */
/*   Updated: 2019/11/12 16:35:08 by ambelghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/stat.h>
#include <sys/types.h>
#include "libft.h"

void		ls_lstadd_mtime(t_lslist **start, t_lslist *new, unsigned int flags)
{
	t_lslist	*p;

	if (start && (p = *start) && new)
	{
		if (p->next)
		{
			p = p->next;
			while (p)
			{
				if (set_lstadd_mtime(p, new, flags) > 0)
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

int			set_lstadd_mtime(t_lslist *p, t_lslist *new, unsigned int flags)
{
	long int	cmp2;
	struct stat	*stats;
	struct stat	*stats2;
	int			r;

	stats = (new->entry->lstats ? new->entry->lstats : new->entry->stats);
	stats2 = (p->entry->lstats ? p->entry->lstats : p->entry->stats);
	cmp2 = (long int)(stats->st_mtimespec.tv_sec - stats2->st_mtimespec.tv_sec);
	r = (flags & FLAG_REV ? -1 : 1);
	if (cmp2 == 0)
		cmp2 = stats->st_mtimespec.tv_nsec - stats2->st_mtimespec.tv_nsec;
	if (cmp2 * r >= 0)
		return (set_lstadd_time(p, new, flags, cmp2));
	else if (!p->next)
	{
		if (cmp2 == 0)
			return (set_lstadd_time(p, new, flags, cmp2));
		else
		{
			p->next = new;
			new->prev = p;
			return (1);
		}
	}
	return (-1);
}

int			set_lstadd_time(t_lslist *p, t_lslist *new, unsigned int f,
							long int c)
{
	if (p && new)
	{
		if (c == 0)
			return (set_lstadd_ascii(p, new, f));
		else
		{
			p->prev->next = new;
			new->prev = p->prev;
			p->prev = new;
			new->next = p;
			return (1);
		}
	}
	return (-1);
}

int			set_lstadd_atime(t_lslist *p, t_lslist *new, unsigned int flags)
{
	long int	cmp2;
	struct stat	*stats;
	struct stat	*stats2;
	int			r;

	stats = (new->entry->lstats ? new->entry->lstats : new->entry->stats);
	stats2 = (p->entry->lstats ? p->entry->lstats : p->entry->stats);
	cmp2 = (long int)(stats->st_atimespec.tv_sec - stats2->st_atimespec.tv_sec);
	r = (flags & FLAG_REV ? -1 : 1);
	if (cmp2 == 0)
		cmp2 = stats->st_atimespec.tv_nsec - stats2->st_atimespec.tv_nsec;
	if (cmp2 * r >= 0)
		return (set_lstadd_time(p, new, flags, cmp2));
	else if (!p->next)
	{
		if (cmp2 == 0)
			return (set_lstadd_time(p, new, flags, cmp2));
		else
		{
			p->next = new;
			new->prev = p;
			return (1);
		}
	}
	return (-1);
}

void		ls_lstadd_atime(t_lslist **start, t_lslist *new, unsigned int flags)
{
	t_lslist	*p;

	if (start && (p = *start) && new)
	{
		if (p->next)
		{
			p = p->next;
			while (p)
			{
				if (set_lstadd_atime(p, new, flags) > 0)
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
