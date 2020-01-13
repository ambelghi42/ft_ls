/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:51:00 by ambelghi          #+#    #+#             */
/*   Updated: 2019/11/13 15:08:09 by ambelghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/stat.h>
#include <sys/types.h>
#include "libft.h"
#include <pwd.h>
#include <uuid/uuid.h>
#include <grp.h>
#include <time.h>

void	print_listline(t_lslist *tmp, int *tab, int p_prms, unsigned int flags)
{
	struct stat *stats;

	if (tmp && tab)
	{
		stats = (tmp->entry->lstats ? tmp->entry->lstats : tmp->entry->stats);
		print_modes(stats);
		print_acl(tmp->entry->full_path);
		putchar_n(' ', tab[0] - ft_nbrlen(stats->st_nlink));
		ft_putnbr(stats->st_nlink);
		ft_putchar(' ');
		print_grpwid(stats, tab);
		print_lsize(stats, tab[3]);
		if (flags & FLAG_U)
			print_mdate(&stats->st_atimespec);
		else
			print_mdate(&stats->st_mtimespec);
		ft_putchar(' ');
		ft_putstr(p_prms == 1 ? tmp->entry->full_path : tmp->entry->name);
		print_slink((tmp->entry->lstats ? tmp->entry->lstats
					: tmp->entry->stats), tmp->entry->full_path);
		ft_putchar('\n');
	}
}

void	set_lmaxcol(struct stat *stats, int *tab)
{
	int				j;
	struct passwd	*user;
	struct group	*group;

	if (stats && tab)
	{
		if ((j = ft_nbrlen(stats->st_nlink)) > tab[0])
			tab[0] = j;
		if ((j = ft_nbrlen(stats->st_size)) > tab[3])
			tab[3] = j;
		if ((S_IFCHR == (S_IFMT & stats->st_mode)
					|| S_IFBLK == (S_IFMT & stats->st_mode)))
			tab[3] = 8;
		user = getpwuid(stats->st_uid);
		group = getgrgid(stats->st_gid);
		if (user && (j = ft_strlen(user->pw_name)) > tab[1])
			tab[1] = j;
		if (group && (j = ft_strlen(group->gr_name)) > tab[2])
			tab[2] = j;
	}
}

void	list_maxcol(t_lslist **list, int *tab, int *blocks)
{
	t_lslist		*tmp;
	int				j;

	if (list && tab && (tmp = *list))
	{
		j = 0;
		while (j < 4)
			tab[j++] = 0;
		while ((tmp = tmp->next))
		{
			set_lmaxcol(tmp->entry->stats, tab);
			if (tmp->entry->lstats)
				*blocks += tmp->entry->lstats->st_blocks;
			else
				*blocks += tmp->entry->stats->st_blocks;
		}
	}
}

void	print_mdate(struct timespec *my_clock)
{
	char	**tab;
	char	*tmp;
	time_t	t;

	tmp = ctime(&my_clock->tv_sec);
	if (my_clock && (tab = ft_strsplit(tmp, ' ')))
	{
		t = time(NULL) - my_clock->tv_sec;
		ft_putstr(tab[1]);
		ft_putchar(' ');
		if (!tab[2][1])
			ft_putchar(' ');
		ft_putstr(tab[2]);
		ft_putchar(' ');
		tab[3][5] = '\0';
		tab[4][4] = '\0';
		if (t > (time_t)(31536000 / 2))
			ft_putchar(' ');
		ft_putstr(t < (time_t)(31536000 / 2) ? tab[3] : tab[4]);
		free_tab(tab);
	}
}

void	print_lsize(struct stat *stats, int spaces)
{
	int min_maj;

	if (stats)
	{
		if (S_IFCHR == (S_IFMT & stats->st_mode)
				|| S_IFBLK == (S_IFMT & stats->st_mode))
		{
			min_maj = major(stats->st_rdev);
			putchar_n(' ', spaces - 8);
			putchar_n(' ', 3 - ft_nbrlen(min_maj));
			ft_putnbr(major(stats->st_rdev));
			ft_putstr(", ");
			min_maj = minor(stats->st_rdev);
			putchar_n(' ', 3 - ft_nbrlen(min_maj));
			ft_putnbr(minor(stats->st_rdev));
			ft_putchar(' ');
		}
		else
		{
			putchar_n(' ', spaces - ft_nbrlen(stats->st_size) + 1);
			ft_putnbr(stats->st_size);
			ft_putchar(' ');
		}
	}
}
