/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 15:21:19 by ambelghi          #+#    #+#             */
/*   Updated: 2019/11/13 15:06:58 by ambelghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/stat.h>
#include <sys/types.h>
#include "libft.h"
#include <pwd.h>
#include <uuid/uuid.h>
#include <grp.h>
#include <sys/acl.h>
#include <sys/xattr.h>

void	print_file_type(struct stat *stats)
{
	if (S_IFREG == (S_IFMT & stats->st_mode))
		write(1, "-", 1);
	if (S_IFIFO == (S_IFMT & stats->st_mode))
		write(1, "p", 1);
	if (S_IFCHR == (S_IFMT & stats->st_mode))
		write(1, "c", 1);
	if (S_IFBLK == (S_IFMT & stats->st_mode))
		write(1, "b", 1);
	if (S_IFIFO == (S_IFMT & stats->st_mode))
		write(1, "p", 1);
	if (S_IFSOCK == (S_IFMT & stats->st_mode))
		write(1, "s", 1);
	if (S_IFLNK == (stats->st_mode & S_IFMT))
		write(1, "l", 1);
	if (S_ISDIR(stats->st_mode))
		write(1, "d", 1);
}

void	print_modes(struct stat *stats)
{
	if (stats)
	{
		print_file_type(stats);
		((S_IRUSR & stats->st_mode) ? write(1, "r", 1) : write(1, "-", 1));
		((S_IWUSR & stats->st_mode) ? write(1, "w", 1) : write(1, "-", 1));
		if (S_ISUID & stats->st_mode)
			ft_putchar(S_IXUSR & stats->st_mode ? 's' : 'S');
		else
			ft_putchar((S_IXUSR & stats->st_mode) ? 'x' : '-');
		ft_putchar((S_IRGRP & stats->st_mode) ? 'r' : '-');
		ft_putchar((S_IWGRP & stats->st_mode) ? 'w' : '-');
		if (S_ISGID & stats->st_mode)
			ft_putchar(S_IXGRP & stats->st_mode ? 's' : 'S');
		else
			ft_putchar((S_IXGRP & stats->st_mode) ? 'x' : '-');
		ft_putchar((S_IROTH & stats->st_mode) ? 'r' : '-');
		ft_putchar((S_IWOTH & stats->st_mode) ? 'w' : '-');
		if (S_ISVTX & stats->st_mode)
			ft_putchar(S_IXOTH & stats->st_mode ? 't' : 'T');
		else
			ft_putchar((S_IXOTH & stats->st_mode) ? 'x' : '-');
	}
}

void	print_grpwid(struct stat *stats, int *tab)
{
	struct passwd	*user;
	struct group	*group;
	int				i;

	if (stats)
	{
		user = NULL;
		group = NULL;
		if ((user = getpwuid(stats->st_uid)))
		{
			ft_putstr(user ? user->pw_name : "");
			i = tab[1] - ft_strlen(user->pw_name);
			putchar_n(' ', i + 2);
		}
		if ((group = getgrgid(stats->st_gid)))
		{
			ft_putstr(group ? group->gr_name : "");
			i = tab[2] - ft_strlen(group->gr_name);
			putchar_n(' ', i + 1);
		}
	}
}

void	print_slink(struct stat *lstats, char *path)
{
	char	buf[1025];
	int		i;

	if (lstats && S_IFLNK == (lstats->st_mode & S_IFMT))
	{
		if ((i = readlink(path, buf, 1024)))
		{
			buf[i] = '\0';
			ft_putstr(" -> ");
			ft_putstr(buf);
		}
	}
}

void	print_acl(char *path)
{
	acl_t		acl;
	char		buf[2];

	buf[1] = '\0';
	if (listxattr(path, buf, 0, XATTR_NOFOLLOW) > 0)
		ft_putstr("@ ");
	else if ((acl = acl_get_file(path, ACL_TYPE_EXTENDED)) > 0)
	{
		ft_putstr("+ ");
		free(acl);
	}
	else
		ft_putstr("  ");
}
