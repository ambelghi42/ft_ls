/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 20:35:17 by ambelghi          #+#    #+#             */
/*   Updated: 2019/11/18 12:31:25 by ambelghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "libft.h"
#include <errno.h>

unsigned char	get_opt(char **av)
{
	int				i;
	int				z;
	unsigned char	flags;

	flags = 0;
	if (av)
	{
		i = 1;
		while (av[i] && av[i][0] == '-' && ft_strcmp(av[i], "--") != 0)
		{
			z = 1;
			while (av[i][z] != '\0')
			{
				if (check_opt(av[i][z], &flags) == 0)
					return (flags);
				z++;
			}
			i++;
		}
	}
	return (flags);
}

char			*get_file(char *path)
{
	int		i;
	char	*file;
	char	**tab;

	if (path && (tab = ft_strsplit(path, '/')))
	{
		i = 0;
		file = NULL;
		while (tab[i])
			file = tab[i++];
		file = ft_strdup(file);
		free_tab(tab);
		return (file);
	}
	return (NULL);
}

t_entry			*new_entry(char *full_path, int check_path)
{
	struct stat	*stats;
	t_entry		*entry;

	entry = NULL;
	if (full_path)
	{
		if (!(entry = (t_entry *)malloc(sizeof(t_entry))))
			exit(2);
		stats = NULL;
		set_entry(full_path, entry, check_path);
		if (!(stats = (struct stat*)malloc(sizeof(struct stat))))
			exit(2);
		if (lstat(entry->full_path, stats) != 0)
		{
			ft_memdel((void **)&stats);
			free_entry(entry);
		}
		else
		{
			entry->stats = stats;
			entry->lstats = NULL;
		}
	}
	return (entry);
}

void			set_entry(char *full_path, t_entry *entry, int check_path)
{
	if (entry && full_path)
	{
		entry->is_dir = check_path;
		set_path(full_path, entry, check_path);
	}
}

void			set_path(char *full_path, t_entry *entry, int check_path)
{
	char	**tab;
	int		i;

	if (full_path && check_path != -1)
	{
		if ((tab = ft_strsplit(full_path, '/')))
		{
			i = 0;
			entry->name = NULL;
			while (tab[i])
				entry->name = tab[i++];
			entry->name = ft_strdup(entry->name);
			entry->path = NULL;
			entry->full_path = ft_strdup(full_path);
			free_tab(tab);
		}
	}
}
