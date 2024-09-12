# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alex <alex@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/03 19:29:16 by ahiguera          #+#    #+#              #
#    Updated: 2024/09/12 15:52:06 by alex             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#████████████████████████████ Configuration ███████████████████████████████████#

NAME    	:= minishell
CC      	:= gcc
CFLAGS  	:= -Wall -Werror -Wextra -fsanitize=address -g3
LDFLAGS 	:= -lreadline

#█████████████████████████████ SOURCES █████████████████████████████████████████#
DIR_BUILTINS		:= srcs/built_ins/
DIR_PARSING			:= srcs/parsing/
DIR_UTILS			:= srcs/utils/

SRCS		=	$(DIR_BUILTINS)00_echo.c			$(DIR_BUILTINS)01_cd.c				\
				$(DIR_BUILTINS)02_export.c			$(DIR_BUILTINS)03_unset.c			\
				$(DIR_BUILTINS)04_pwd.c				$(DIR_BUILTINS)05_env.c				\
																						\
				$(DIR_PARSING)00_heredoc.c			$(DIR_PARSING)01_clean_input.c		\
				$(DIR_PARSING)02_dollar_exp.c		$(DIR_PARSING)03_builtins.c			\
				$(DIR_PARSING)04_checker_setup.c	$(DIR_PARSING)05_init_mshell.c		\
				$(DIR_PARSING)06_init_utils.c		$(DIR_PARSING)07_execution.c		\
				$(DIR_PARSING)08_exec_setup.c		$(DIR_PARSING)09_exec_utils.c		\
				$(DIR_PARSING)10_signals.c												\
																						\
				$(DIR_UTILS)00_dollar_utils.c		$(DIR_UTILS)01_libft_00.c			\
				$(DIR_UTILS)02_libft_01.c			$(DIR_UTILS)03_libft_02.c			\
																						\
				main.c

#████████████████████████████ Rules ████████████████████████████████████████████#

all:		$(NAME)

OBJ     = $(SRCS:.c=.o)

$(NAME):	$(OBJ)
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

%.o: %.c
				@$(CC) $(CFLAGS) -c $< -o $@

clean:
				@rm -f $(OBJ)

fclean: 	clean
				@rm -f $(NAME)

re: 		fclean all

.PHONY:		all clean fclean re

#█████████████████████████████ Custom rules ████████████████████████████████████#

normi:
				@echo "Norminette...\n"
				@norminette $(SRC)
				@echo "nNorminette Done!\n"

run:
				clear
				@make re
				@./minishell