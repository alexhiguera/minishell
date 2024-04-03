# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alex <alex@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/03 19:29:16 by alex              #+#    #+#              #
#    Updated: 2024/04/03 19:43:15 by alex             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#████████████████████████████ Configuration ███████████████████████████████████#

NAME			:= minishell
CC				:= gcc
CFLAGS			:= -Wall -Wextra -Werror

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

SRC 		:= 	

#████████████████████████████ Rules ████████████████████████████████████████████#

all:$(NAME)

$(NAME): 	$(SRC)
				@echo "$(CYAN)Compiling $(NAME)...$(WHITE)\n"
				@$(CC) $(CFLAGS) -o $(NAME)
				@echo "$(GREEN)Minishell compiled! 🚀$(WHITE)\n"

clean:

fclean: 	clean
				@rm -rf $(NAME)

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