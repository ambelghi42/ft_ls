/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 23:18:44 by ambelghi          #+#    #+#             */
/*   Updated: 2019/11/13 13:39:20 by ambelghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include <unistd.h>

void	putchar_n(char c, int n)
{
	while (n-- > 0)
		write(1, &c, 1);
}

void	print_error(char *var, int error)
{
	if (var)
	{
		if (error == 0)
		{
			ft_putstr_fd("ft_ls: illegal option -- ", 2);
			ft_putchar_fd(*var, 2);
			ft_putstr_fd("\n", 2);
			ft_putstr_fd("usage: ft_ls [-1Ralrtu] [file ...]", 2);
			ft_putstr_fd("\n", 2);
		}
		else
		{
			ft_putstr_fd("ft_ls: ", 2);
			if (!var || !*var)
				ft_putstr_fd(": ", 2);
			perror(var);
		}
	}
}

void	tab_sort_ascii(char **tab, int start)
{
	char	*tmp;
	int		i;

	if (tab && *tab)
	{
		i = start;
		while (tab[i])
		{
			if (tab[i + 1] && ft_strcmp(tab[i], tab[i + 1]) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				i = start - 1;
			}
			i++;
		}
	}
}
