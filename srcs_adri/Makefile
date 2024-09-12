# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/02 20:21:49 by marvin            #+#    #+#              #
#    Updated: 2024/09/02 20:21:49 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -fsanitize=address -g3 -lreadline
SRCS		=	main.c srcs/00_heredoc.c srcs/01_clean_input.c srcs/02_dollar_exp.c srcs/03_builtins.c srcs/04_checker_setup.c srcs/05_init_mshell.c \
				srcs/06_init_utils.c srcs/07_execution.c srcs/08_exec_setup.c srcs/09_exec_utils.c srcs/10_signals.c built_ins/00_echo.c built_ins/01_cd.c \
				built_ins/02_export.c built_ins/03_unset.c built_ins/04_pwd.c built_ins/05_env.c utils/00_dollar_utils.c utils/01_libft_00.c utils/02_libft_01.c utils/03_libft_02.c
OBJ			=	$(SRCS:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)
