/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 20:32:47 by ambelghi          #+#    #+#             */
/*   Updated: 2019/11/12 15:42:00 by ambelghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "libft.h"
#include <errno.h>

int			check_opt(char c, unsigned char *flags)
{
	if (!ft_strchr("1lRartu", c))
	{
		*flags |= INVALID_FLAG;
		print_error(&c, 0);
		return (0);
	}
	(c == 'l' ? *flags |= FLAG_LST : *flags);
	(c == 'R' ? *flags |= FLAG_REC : *flags);
	(c == 'a' ? *flags |= FLAG_A : *flags);
	(c == 'r' ? *flags |= FLAG_REV : *flags);
	(c == 't' ? *flags |= FLAG_TME : *flags);
	(c == 'u' ? *flags |= FLAG_U : *flags);
	(c == '1' ? *flags |= FLAG_DEFAULT : *flags);
	if (*flags & FLAG_LST && *flags & FLAG_DEFAULT)
	{
		if (c == 'l')
			*flags ^= FLAG_DEFAULT;
		else
			*flags ^= FLAG_LST;
	}
	return (1);
}

int			check_entry(char *path, char *file)
{
	DIR				*directory;
	struct stat		stats;
	char			*tmp_p;

	if (path && (directory = opendir(path)))
	{
		tmp_p = ft_strjoin(path, file);
		if (stat(tmp_p, &stats) == 0)
		{
			ft_strdel(&tmp_p);
			closedir(directory);
			return (S_ISDIR(stats.st_mode) ? 1 : 0);
		}
		closedir(directory);
		ft_strdel(&tmp_p);
	}
	return (-1);
}

int			check_path(char *path)
{
	struct stat	stats;
	int			ret;
	int			len;

	ret = -1;
	if (path)
	{
		len = ft_strlen(path);
		if (stat(path, &stats) == 0 || lstat(path, &stats) == 0)
		{
			if (S_ISDIR(stats.st_mode))
				ret = 1;
			else
				ret = 0;
		}
		else
			print_error(path, errno);
	}
	return (ret);
}
