# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aschwere <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 13:16:42 by aschwere          #+#    #+#              #
#    Updated: 2020/11/10 14:39:05 by alexandre        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

CFLAGS	=	-IIncludes/ -g3 -fsanitize=address -fno-omit-frame-pointer -Wall -Werror -Wextra 

CC		=	gcc

SRC		=	built_in.c \
			env_support.c \
			parser.c \
			echo.c \
			env.c \
			env_support_2.c	\
			error.c \
			export.c \
			export_p.c \
			ft_cd.c \
			main.c \
			parse_exec.c \
			parsing.c \
			parser_support.c \
			parser_support_2.c \
			pipe.c \
			replace.c \
			support.c \
			ft_unset.c \
			t_cmd.c \
			t_cmd_support.c


OBJ = $(SRC:%.c=%.o)

%.o : %.c
	$(CC) -o $@ -c $< $(CFLAGS)

$(NAME) : $(ft) $(OBJ)
	@make -C $(lft)
	$(CC) -o $@  $^ $(CFLAGS) -L $(lft) -lft

lft	=	libft

all : $(NAME)

libft:
	@make -C libft fclean
	@make -C libft

clean :
	make clean -C $(lft)
	rm -rf $(SRC:%.c=%.o)

fclean : clean
	@rm -f $(NAME)

re : fclean all
