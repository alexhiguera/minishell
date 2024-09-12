# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alex <alex@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/12 15:04:49 by alex              #+#    #+#              #
#    Updated: 2024/09/12 15:04:49 by alex             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME    = minishell
CC      = gcc
CFLAGS  = -Wall -Werror -Wextra -fsanitize=address -g3
LDFLAGS = -lreadline

SRCS		=	built_ins/00_echo.c				built_ins/01_cd.c				\
				built_ins/02_export.c			built_ins/03_unset.c			\
				built_ins/04_pwd.c				built_ins/05_env.c				\
																				\
				parsing/00_heredoc.c			parsing/01_clean_input.c		\
				parsing/02_dollar_exp.c			parsing/03_builtins.c			\
				parsing/04_checker_setup.c		parsing/05_init_mshell.c		\
				parsing/06_init_utils.c			parsing/07_execution.c			\
				parsing/08_exec_setup.c		parsing/09_exec_utils.c			\
				parsing/10_signals.c											\
																				\
				utils/00_dollar_utils.c			utils/01_libft_00.c				\
				utils/02_libft_01.c		utils/03_libft_02.c				\
																				\
				main.c

OBJ     = $(SRCS:.c=.o)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean $(NAME)

.phony:	clean fclean re