/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:23:01 by ambelghi          #+#    #+#             */
/*   Updated: 2019/11/12 16:32:08 by ambelghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	default_print(t_lslist **p, int p_prms)
{
	t_lslist	*tmp;

	if (p && (tmp = *p))
	{
		while ((tmp = tmp->next))
			ft_putendl(p_prms == 1 ? tmp->entry->full_path : tmp->entry->name);
	}
}

void	ls_print(t_lslist **list, int p_prms, unsigned int flags)
{
	if (flags & FLAG_DEFAULT)
		default_print(list, p_prms);
	else if (flags & FLAG_LST)
		print_list(list, p_prms, flags);
	else
		print_col(list, p_prms);
}

void	print_list(t_lslist **list, int p_prms, unsigned int flags)
{
	t_lslist		*tmp;
	int				tab[4];
	int				total_blocks;

	if (list && (tmp = *list))
	{
		total_blocks = 0;
		list_maxcol(list, tab, &total_blocks);
		if (p_prms < 1 && tmp->next)
		{
			ft_putstr("total ");
			ft_putnbr(total_blocks);
			ft_putchar('\n');
		}
		while ((tmp = tmp->next))
			print_listline(tmp, tab, p_prms, flags);
	}
}
