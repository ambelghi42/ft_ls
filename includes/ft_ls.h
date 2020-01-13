/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 18:11:40 by ambelghi          #+#    #+#             */
/*   Updated: 2019/11/12 18:09:24 by ambelghi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H

# define FT_LS_H

# define FLAG_LST 1
# define FLAG_REC 2
# define FLAG_A 4
# define FLAG_REV 8
# define FLAG_TME 16
# define FLAG_U 32
# define INVALID_FLAG 64
# define FLAG_DEFAULT 128
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include "libft.h"
# include <dirent.h>

typedef struct	s_entry
{
	char		*name;
	char		*path;
	char		*full_path;
	int			is_dir;
	struct stat	*stats;
	struct stat	*lstats;
}				t_entry;

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_lslist
{
	t_entry			*entry;
	struct s_lslist	*prev;
	struct s_lslist	*next;
}				t_lslist;

int				check_opt(char c, unsigned char *flags);
int				check_entry(char *path, char *file);
int				check_path(char *path);
int				set_lstadd_mtime(t_lslist *p, t_lslist *new,
					unsigned int flags);
int				set_lstadd_time(t_lslist *p, t_lslist *new, unsigned int f,
					long int c);
int				set_lstadd_atime(t_lslist *p, t_lslist *new,
					unsigned int flags);
int				ls_listcount(t_lslist *elem);
int				set_lstadd_ascii(t_lslist *p, t_lslist *new,
					unsigned int flags);
int				lines_col(t_lslist *list, int max_len);
int				get_maxlen(t_lslist *list);
char			*get_file(char *path);
void			check_oneparam(t_lslist *l, char *av, int check_p,
					unsigned int flags);
void			check_rootdir(t_lslist *list, unsigned int flags);
void			print_col_line(t_lslist *tmp, t_point max, int p_prms);
void			print_col(t_lslist **list, int print_params);
void			free_tab(char **tab);
void			free_entry(t_entry *entry);
void			free_onelist(t_lslist **elem);
void			free_mylist(t_lslist **begin);
void			set_entry(char *full_path, t_entry *entry, int check_path);
void			set_path(char *full_path, t_entry *entry, int check_path);
void			get_list_entry(t_lslist **list, struct stat *stats, char *path,
					unsigned int flags);
void			get_list_dir(t_lslist **list, DIR *dir, char *path,
					unsigned int flags);
void			ls_lstadd_mtime(t_lslist **start, t_lslist *new,
					unsigned int flags);
void			ls_lstadd_atime(t_lslist **start, t_lslist *new,
					unsigned int flags);
void			ls_lstadd_ascii(t_lslist **start, t_lslist *new,
					unsigned int flags);
void			ls_lstadd(t_lslist **start, t_lslist *new, unsigned int flags);
void			recursive(t_lslist *lst, unsigned int flags);
void			default_print(t_lslist **p, int p_prms);
void			ls_print(t_lslist **list, int p_prms, unsigned int flags);
void			print_list(t_lslist **list, int p_prms, unsigned int flags);
void			print_file_type(struct stat *stats);
void			print_modes(struct stat *stats);
void			print_grpwid(struct stat *stats, int *tab);
void			print_slink(struct stat *lstats, char *path);
void			print_acl(char *path);
void			print_listline(t_lslist *tmp, int *tab, int p_prms,
					unsigned int flags);
void			set_lmaxcol(struct stat *stats, int *tab);
void			list_maxcol(t_lslist **list, int *tab, int *blocks);
void			print_mdate(struct timespec *my_clock);
void			print_lsize(struct stat *stats, int spaces);
void			putchar_n(char c, int n);
void			print_error(char *var, int error);
void			tab_sort_ascii(char **tab, int start);
t_entry			*new_entry(char *full_path, int check_path);
t_lslist		*check_params(char **av, unsigned int flags, t_lslist **files);
t_lslist		*ls_lstnew(t_entry *entry);
t_lslist		*get_list(char **path, t_lslist **list, unsigned int flags);
t_lslist		*check_params_maestro(t_lslist **files, char **av,
					unsigned int flgs, int i);
unsigned char	get_opt(char **av);

#endif
