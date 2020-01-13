/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 22:29:29 by ambelghi          #+#    #+#             */
/*   Updated: 2019/11/12 18:23:57 by ambelghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "libft.h"
#include <errno.h>

void	recursive_each(t_entry *entry, unsigned int flags)
{
	t_lslist	*tmp;

	write(1, "\n", 1);
	ft_putstr(entry->full_path);
	ft_putendl(":");
	tmp = ls_lstnew(NULL);
	if (flags & FLAG_LST && S_IFLNK
			== (entry->stats->st_mode & S_IFMT) && entry->is_dir == 1)
		tmp->next = ls_lstnew(new_entry(entry->full_path, 1));
	else
		tmp = get_list(&entry->full_path, &tmp, flags);
	ls_print(&tmp, 0, flags);
	recursive(tmp, flags);
	free_mylist(&tmp);
}

void	recursive(t_lslist *lst, unsigned int flags)
{
	t_lslist	*list;
	t_entry		*entry;

	if ((list = lst))
	{
		while ((list = list->next))
		{
			entry = list->entry;
			if (entry->is_dir > 0 && !(entry->name[0] == '.'
					&& !(flags & FLAG_A)) && ft_strdchr(entry->name, '.')
					&& !(flags & FLAG_LST && S_IFLNK
					== (entry->stats->st_mode & S_IFMT) && entry->is_dir == 1))
				recursive_each(entry, flags);
		}
	}
}

void	ft_ls_each(t_lslist *list, unsigned int flags)
{
	t_lslist	*tmp;
	t_entry		*entry;

	entry = (t_entry *)list->entry;
	tmp = ls_lstnew(NULL);
	if (flags & FLAG_LST && S_IFLNK
			== (entry->stats->st_mode & S_IFMT) && entry->is_dir == 1)
		tmp->next = ls_lstnew(new_entry(entry->full_path, 1));
	else
		tmp = get_list(&entry->full_path, &tmp, flags);
	ls_print(&tmp, (S_IFLNK == (entry->stats->st_mode & S_IFMT)
				&& FLAG_LST & flags ? 1 : 0), flags);
	if (list->next && list->next->entry->is_dir == 1)
		ft_putchar('\n');
	if (flags & FLAG_REC)
		recursive(tmp, flags);
	free_mylist(&tmp);
	errno = 0;
}

void	ft_ls(char **av, unsigned int flags)
{
	t_lslist	*list;
	t_lslist	*start;
	t_lslist	*files_params;
	int			nb_lst;

	files_params = NULL;
	list = check_params(av, flags, &files_params);
	start = list;
	ls_print(&files_params, 1, flags);
	if (files_params && list->next)
		write(1, "\n", 1);
	nb_lst = ls_listcount(list);
	while ((list = list->next))
	{
		if (nb_lst > 1 || files_params || errno > 0)
		{
			ft_putstr(list->entry->full_path);
			ft_putendl(":");
		}
		ft_ls_each(list, flags);
	}
	free_mylist(&start);
	free_mylist(&files_params);
}

int		main(int ac, char **av)
{
	unsigned int	flags;

	if (av && ac >= 1)
	{
		flags = get_opt(av);
		if (!(flags & INVALID_FLAG))
		{
			errno = 0;
			ft_ls(av, flags);
		}
		else
			return (1);
	}
	return (0);
}
