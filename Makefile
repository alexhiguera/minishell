# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: columbux <columbux@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/03 19:29:16 by ahiguera          #+#    #+#              #
#    Updated: 2024/05/12 21:29:53 by columbux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#████████████████████████████ Configuration ███████████████████████████████████#

NAME			:= minishell
CC				:= gcc
CFLAGS			:= -Wall -Wextra -Werror
AUXFLAGS		:= -lreadline

#██████████████████████████████ Colors ████████████████████████████████████████#

DEF_COLOR 		=	\033[0;39m
GRAY 			=	\033[0;90m
RED 			=	\033[0;91m
GREEN 			=	\033[0;92m
YELLOW 			=	\033[0;93m
BLUE 			=	\033[0;94m
MAGENTA 		=	\033[0;95m
CYAN 			=	\033[0;96m
WHITE 			=	\033[0;97m

#█████████████████████████████ SOURCES █████████████████████████████████████████#

LIBFT		:=	libft/
SRC 		:= 	src/minishell.c

#████████████████████████████ Rules ████████████████████████████████████████████#

all:$(NAME)

$(NAME): 	$(SRC)
				@echo "$(CYAN)Compiling $(NAME)...$(WHITE)"
				@make re -C $(LIBFT) -s
				@$(CC) $(CFLAGS) $(SRC) $(LIBFT)/libft.a -o $(NAME) $(AUXFLAGS)
				@echo "$(GREEN)$(NAME) compiled! 🚀$(WHITE)\n"

clean:
				@make -C $(LIBFT) clean -s

fclean: 	clean
				@rm -rf $(NAME)
				@make -C $(LIBFT) fclean -s

re: 		fclean all

.PHONY: 	all clean fclean re normi 

#█████████████████████████████ Custom rules ████████████████████████████████████#

normi:
						@echo "$(YELLOW)Norminette...\n$(WHITE)"
						@norminette $(SRC)
						@echo "$(GREEN)\nNorminette Done!\n"

run:
						clear					
						@make re
						@./minishell