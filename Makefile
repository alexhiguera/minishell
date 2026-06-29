# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alex <alex@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/03 19:29:16 by alex              #+#    #+#              #
#    Updated: 2026/06/29 00:00:00 by alex             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			:= minishell

CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror
RM				:= rm -f

SRC_DIR			:= srcs
LIBFT_DIR		:= libft
LIBFT			:= $(LIBFT_DIR)/libft.a

# ----------------------------- readline -------------------------------------- #
UNAME			:= $(shell uname)
ifeq ($(UNAME), Darwin)
	RL_PREFIX	:= $(shell brew --prefix readline)
	CFLAGS		+= -I$(RL_PREFIX)/include
	RL_FLAGS	:= -L$(RL_PREFIX)/lib -lreadline
else
	RL_FLAGS	:= -lreadline
endif

# ----------------------------- sources --------------------------------------- #
SRCS			:= \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/utils/loop_utils.c \
	$(SRC_DIR)/utils/error.c \
	$(SRC_DIR)/utils/cleanup.c \
	$(SRC_DIR)/env/env_init.c \
	$(SRC_DIR)/env/env_get.c \
	$(SRC_DIR)/env/env_set.c \
	$(SRC_DIR)/env/env_array.c \
	$(SRC_DIR)/signals/signals.c \
	$(SRC_DIR)/lexer/lexer.c \
	$(SRC_DIR)/lexer/lex_word.c \
	$(SRC_DIR)/lexer/lex_op.c \
	$(SRC_DIR)/lexer/token.c \
	$(SRC_DIR)/expand/expand.c \
	$(SRC_DIR)/expand/expand_str.c \
	$(SRC_DIR)/expand/expand_dollar.c \
	$(SRC_DIR)/expand/expand_quote.c \
	$(SRC_DIR)/expand/expand_utils.c \
	$(SRC_DIR)/parser/parse.c \
	$(SRC_DIR)/parser/parse_redir.c \
	$(SRC_DIR)/parser/syntax.c \
	$(SRC_DIR)/parser/cmd.c \
	$(SRC_DIR)/exec/exec.c \
	$(SRC_DIR)/exec/exec_pipe.c \
	$(SRC_DIR)/exec/exec_child.c \
	$(SRC_DIR)/exec/path.c \
	$(SRC_DIR)/exec/redir.c \
	$(SRC_DIR)/exec/heredoc.c \
	$(SRC_DIR)/builtins/builtin.c \
	$(SRC_DIR)/builtins/echo.c \
	$(SRC_DIR)/builtins/pwd.c \
	$(SRC_DIR)/builtins/env.c \
	$(SRC_DIR)/builtins/cd.c \
	$(SRC_DIR)/builtins/unset.c \
	$(SRC_DIR)/builtins/exit.c \
	$(SRC_DIR)/builtins/export.c \
	$(SRC_DIR)/builtins/export2.c

OBJS			:= $(SRCS:.c=.o)
HEADER			:= $(SRC_DIR)/minishell.h

# ----------------------------- rules ----------------------------------------- #
all:			$(NAME)

$(NAME):		$(LIBFT) $(OBJS)
				$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(RL_FLAGS) -o $(NAME)

$(LIBFT):
				$(MAKE) -C $(LIBFT_DIR)

%.o:			%.c $(HEADER)
				$(CC) $(CFLAGS) -c $< -o $@

clean:
				$(MAKE) -C $(LIBFT_DIR) clean
				$(RM) $(OBJS)

fclean:			clean
				$(MAKE) -C $(LIBFT_DIR) fclean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
