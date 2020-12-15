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

SRC		=	builtins/built_in.c \
			pipe_chevrons/chevron.c \
			env/env_support.c \
			parsing/parser.c \
			builtins/echo.c \
			env/env.c \
			env/env_support_2.c	\
			env/env_support_3.c	\
			support/error.c \
			builtins/export.c \
			builtins/export_p.c \
			builtins/ft_cd.c \
			main.c \
			parsing/parse_exec.c \
			parsing/parsing.c \
			parsing/parser_support.c \
			parsing/parser_support_2.c \
			pipe_chevrons/pipe.c \
			pipe_chevrons/replace.c \
			support/support.c \
			support/support2.c \
			support/signal.c \
			builtins/ft_unset.c \
			parsing/t_cmd.c \
			parsing/t_cmd_support.c


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
