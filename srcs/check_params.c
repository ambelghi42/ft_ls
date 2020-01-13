/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:23:55 by ambelghi          #+#    #+#             */
/*   Updated: 2019/11/12 16:22:24 by ambelghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "libft.h"
#include <errno.h>

void		check_oneparam(t_lslist *l, char *av, int check_p,
							unsigned int flags)
{
	t_entry			*entry;

	if (av && l && av[ft_strlen(av) - 1] == '/' && ft_strcmp(av, "./") != 0)
	{
		if (check_p != 0)
			ls_lstadd(&l, ls_lstnew(new_entry(av, check_p)), flags);
	}
	else if (av && l)
	{
		if (check_p == -1)
			print_error(av, 2);
		else if ((entry = new_entry(av, check_p)))
			ls_lstadd(&l, ls_lstnew(entry), flags);
	}
}

void		check_rootdir(t_lslist *list, unsigned int flags)
{
	DIR		*dir;

	if (list && (dir = opendir("/")))
	{
		ls_lstadd(&list, ls_lstnew(new_entry("/", 1)), flags);
		closedir(dir);
	}
}

t_lslist	*check_params_maestro(t_lslist **files, char **av,
									unsigned int flgs, int i)
{
	t_lslist	*list;
	int			check_p;

	list = ls_lstnew(NULL);
	if (!av[i])
		check_oneparam(list, ".", check_path("."), flgs);
	while (av[i])
	{
		if ((check_p = check_path(av[i])) == 1 && ft_strcmp(av[i], "/") == 0)
			check_rootdir(list, flgs);
		else if (check_p == 0)
		{
			if (!*files)
				*files = ls_lstnew(NULL);
			check_oneparam(*files, av[i], check_p, flgs);
		}
		else if (check_p == 1)
			check_oneparam(list, av[i], check_p, flgs);
		i++;
	}
	return (list);
}

t_lslist	*check_params(char **av, unsigned int flags, t_lslist **files)
{
	int			i;
	int			check_p;

	if (av && files)
	{
		i = 1;
		check_p = -1;
		while (av[i] && av[i][0] == '-' && ft_strcmp(av[i], "-") != 0
				&& ft_strcmp(av[i], "--") != 0)
			i++;
		i = (av[i] && ft_strcmp(av[i], "--") == 0 ? i + 1 : i);
		tab_sort_ascii(av, i);
		return (check_params_maestro(files, av, flags, i));
	}
	return (NULL);
}
