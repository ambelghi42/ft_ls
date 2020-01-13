/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 19:50:59 by ambelghi          #+#    #+#             */
/*   Updated: 2019/11/12 15:10:27 by ambelghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "libft.h"
#include <pwd.h>
#include <uuid/uuid.h>
#include <grp.h>
#include <time.h>

void	free_tab(char **tab)
{
	int	i;

	if (tab)
	{
		i = 0;
		while (tab[i])
			ft_strdel(&tab[i++]);
		free(tab);
		tab = NULL;
	}
}

void	free_entry(t_entry *entry)
{
	if (entry)
	{
		ft_strdel(&entry->name);
		ft_strdel(&entry->path);
		ft_strdel(&entry->full_path);
		ft_memdel((void **)&entry->stats);
		ft_memdel((void **)&entry->lstats);
		free(entry);
		entry = NULL;
	}
}

void	free_onelist(t_lslist **elem)
{
	t_lslist	*prev;
	t_lslist	*next;
	t_lslist	*tmp;

	if (elem && *elem)
	{
		tmp = *elem;
		if ((prev = tmp->prev))
			prev->next = tmp->next;
		if ((next = tmp->next))
			next->prev = prev;
		free_entry(tmp->entry);
		free(*elem);
		*elem = NULL;
	}
}

void	free_mylist(t_lslist **begin)
{
	t_lslist	*tmp;
	t_lslist	*next;

	if (begin && *begin)
	{
		tmp = *begin;
		if (tmp->prev)
		{
			while (tmp && tmp->prev)
				tmp = tmp->prev;
		}
		while (tmp)
		{
			next = tmp->next;
			free_onelist(&tmp);
			tmp = next;
		}
		*begin = NULL;
	}
}
