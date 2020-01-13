/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colums.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 22:12:34 by ambelghi          #+#    #+#             */
/*   Updated: 2019/11/18 12:30:58 by ambelghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <sys/stat.h>
#include <sys/types.h>
#include "libft.h"
#include <sys/ioctl.h>

int		lines_col(t_lslist *list, int max_len)
{
	int				nb_elem;
	int				max_col;
	struct winsize	size;

	if (list)
	{
		nb_elem = ls_listcount(list);
		ioctl(0, TIOCGWINSZ, &size);
		max_col = (max_len > 0 && max_len < size.ws_col
			? size.ws_col / (max_len + 1) : 1);
		return (nb_elem / max_col + (nb_elem % max_col == 0 ? 0 : 1));
	}
	return (-1);
}

int		get_maxlen(t_lslist *list)
{
	t_lslist	*tmp;
	int			max_len;
	int			ncol;

	max_len = 0;
	ncol = 0;
	if ((tmp = list))
	{
		while ((tmp = tmp->next))
		{
			if ((ncol = ft_strlen(tmp->entry->name)) > max_len)
				max_len = ncol;
		}
	}
	return (max_len);
}

void	print_col_line(t_lslist *tmp, t_point max, int p_prms)
{
	t_lslist	*tmp2;
	int			i;
	int			z;
	int			spaces;

	i = 0;
	tmp2 = tmp;
	while (tmp2)
	{
		spaces = max.x;
		z = 0;
		while (i > 0 && z++ < max.y && tmp2)
			tmp2 = tmp2->next;
		if (tmp2)
		{
			ft_putstr(p_prms == 1 ? tmp2->entry->full_path : tmp2->entry->name);
			spaces = spaces - ft_strlen(tmp2->entry->name) + 1;
			putchar_n(' ', spaces);
		}
		i++;
	}
}

void	print_col(t_lslist **list, int print_params)
{
	t_point			max;
	int				i;
	t_lslist		*tmp;

	if ((tmp = *list))
	{
		max.x = get_maxlen(*list);
		max.y = lines_col(*list, max.x);
		i = 0;
		while ((tmp = tmp->next) && i++ < max.y)
		{
			print_col_line(tmp, max, print_params);
			ft_putstr("\n");
		}
	}
}
