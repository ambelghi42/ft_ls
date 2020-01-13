# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ambelghi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/13 14:50:28 by ambelghi          #+#    #+#              #
#    Updated: 2019/11/18 12:34:12 by ambelghi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

# Reset
NC=\033[0m

# Regular Colors
BLACK=\033[0;30m
RED=\033[0;31m
GREEN =\033[32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
PURPLE=\033[0;35m
CYAN=\033[0;36m
WHITE=\033[0;37m

CC = Clang
COMPILE = $(CC) -c

MKDIR = mkdir -p
CLEANUP = rm -rf

WFLAGS = -Wall -Werror -Wextra
IFLAGS = -I$(IPATH) -I$(LIPATH)
CFLAGS = $(WFLAGS) $(IFLAGS)
DEBUG = $(CFLAGS) -g -fsanitize=address

PATHO = obj/
SPATH = srcs/
IPATH = includes/
LPATH = libft/
LIPATH = libft/includes/
LIB = $(LPATH)libft.a

INCS += ft_ls.h

SRCS += check.c
SRCS += check_params.c
SRCS += colums.c
SRCS += free.c
SRCS += get.c
SRCS += get_list.c
SRCS += list_add_sort.c
SRCS += list_utils.c
SRCS += main.c
SRCS += print.c
SRCS += print_list.c
SRCS += print_list2.c
SRCS += utils.c


OBJS = $(patsubst %.c, $(PATHO)%.o, $(SRCS))


all : $(NAME)

$(NAME) : $(LIB) $(PATHO) $(OBJS)
	$(CC) -o $@ $< $(OBJS)
	printf "$(GREEN)$@ is ready.\n$(NC)"

$(OBJS) : $(PATHO)%.o : $(SPATH)%.c
	$(COMPILE) $(CFLAGS) $< -o $@

$(PATHO) :
	$(MKDIR) $@

$(LIB) :
	$(MAKE) -C $(LPATH)

clean :
	$(MAKE) -C $(LPATH) clean
	$(CLEANUP) $(OBJS)
	$(CLEANUP) $(PATHO)

fclean : clean
	$(MAKE) -C $(LPATH) fclean
	$(CLEANUP) $(PATHO)
	$(CLEANUP) $(NAME)

re : fclean all

norme:
	norminette srcs
	norminette includes
	norminette libft/srcs
	norminette libft/includes

.PHONY: all clean fclean norme re
