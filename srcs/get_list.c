/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 16:26:20 by ambelghi          #+#    #+#             */
/*   Updated: 2019/11/13 13:23:03 by ambelghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "libft.h"
#include <errno.h>

void		get_list_entry(t_lslist **list, struct stat *stats, char *path,
							unsigned int flags)
{
	struct stat	*lstats;
	t_entry		*l_ent;

	if (!(l_ent = (t_entry *)malloc(sizeof(t_entry))))
		exit(2);
	else
	{
		lstats = NULL;
		if (S_IFLNK == (stats->st_mode & S_IFMT)
				&& !(lstats = (struct stat *)malloc(sizeof(struct stat))))
			exit(2);
		if (S_IFLNK == (stats->st_mode & S_IFMT) && stat(path, lstats) == 0)
		{
			l_ent->stats = lstats;
			l_ent->lstats = stats;
		}
		else
		{
			l_ent->stats = stats;
			l_ent->lstats = NULL;
			ft_memdel((void **)&lstats);
		}
		set_entry(path, l_ent, S_ISDIR(stats->st_mode));
		ls_lstadd(list, ls_lstnew(l_ent), flags);
	}
}

void		get_list_dir(t_lslist **list, DIR *dir, char *path,
		unsigned int flags)
{
	struct dirent	*entry;
	char			*tmp;
	struct stat		*stats;

	while ((entry = readdir(dir)))
	{
		tmp = ft_strjoin(path, entry->d_name);
		if (!(stats = (struct stat *)malloc(sizeof(struct stat))))
			exit(2);
		if (!(!(FLAG_A & flags) && entry->d_name[0] == '.')
			&& lstat(tmp, stats) == 0)
			get_list_entry(list, stats, tmp, flags);
		else
		{
			if (!(!(FLAG_A & flags) && entry->d_name[0] == '.') && errno > 0)
				print_error(tmp, errno);
			ft_memdel((void **)&stats);
		}
		ft_strdel(&tmp);
	}
}

t_lslist	*get_list(char **path, t_lslist **list, unsigned int flags)
{
	DIR		*dir;
	char	*tmp;

	if (path && *path && list && *list && (dir = opendir(*path)))
	{
		tmp = *path;
		if (tmp[ft_strlen(tmp) - 1] != '/' && (*path = ft_strjoin(*path, "/")))
			ft_strdel(&tmp);
		get_list_dir(list, dir, *path, flags);
		closedir(dir);
	}
	else if (path && errno > 0)
		print_error(*path, errno);
	return (*list);
}
