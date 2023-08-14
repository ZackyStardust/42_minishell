# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fpereira <fpereira@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/29 18:35:35 by fpereira          #+#    #+#              #
#    Updated: 2023/03/15 16:50:42 by fpereira         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -fsanitize=address -g -I ./includes
READLINE	=	-lreadline
RM			=	rm -f
MK			=	make
MKD			=	mkdir
#INCLUDES	=	-I ./includes

NAME		=	minishell

OBJ_PATH	=	./obj
SRC_PATH	=	./srcs

SRCS		=	$(SRC_PATH)/parser/parser_main.c \
						$(SRC_PATH)/parser/parser_utils.c \
						$(SRC_PATH)/parser/syntax_errors.c \
						$(SRC_PATH)/parser/token_treat.c \
						$(SRC_PATH)/parser/token_update.c \
						$(SRC_PATH)/parser/tree_main.c \
						$(SRC_PATH)/parser/tree_add.c \
						$(SRC_PATH)/parser/tree_update.c \
						$(SRC_PATH)/parser/tree_utils.c \
						$(SRC_PATH)/parser/expander_main.c \
						$(SRC_PATH)/parser/expander_home.c \
						$(SRC_PATH)/parser/expander_utils.c \
						$(SRC_PATH)/main/main.c \
						$(SRC_PATH)/main/env.c \
						$(SRC_PATH)/main/list_utils.c \
						$(SRC_PATH)/main/main_utils.c \
						$(SRC_PATH)/main/main_frees.c \
						$(SRC_PATH)/main/main_frees2.c \
						$(SRC_PATH)/main/main_signals.c \
						$(SRC_PATH)/main/main_signals2.c \
						$(SRC_PATH)/builtins/builtin_cd.c \
						$(SRC_PATH)/builtins/builtin_echo.c \
						$(SRC_PATH)/builtins/builtin_exit.c \
						$(SRC_PATH)/builtins/builtin_export_utils.c \
						$(SRC_PATH)/builtins/builtin_export.c \
						$(SRC_PATH)/builtins/builtin_main.c \
						$(SRC_PATH)/builtins/builtin_pwd.c \
						$(SRC_PATH)/builtins/builtin_unset.c \
						$(SRC_PATH)/builtins/builtin_env.c \
						$(SRC_PATH)/executor/executor_main.c \
						$(SRC_PATH)/executor/executor_utils.c \
						$(SRC_PATH)/executor/path_utils.c \
						$(SRC_PATH)/executor/relative_path.c \
						$(SRC_PATH)/executor/wait_cmds.c \
						$(SRC_PATH)/redir/heredoc_main.c \
						$(SRC_PATH)/redir/redir_built.c \
						$(SRC_PATH)/redir/redir_main.c \

OBJS		= 	$(patsubst $(SRC_PATH)/parser/%.c,$(SRC_PATH)/parser/%.o,$(SRCS))

SRC_LIBFT	=	./srcs/libft
LIBFT		=	./srcs/libft/libft.a

all: $(LIBFT) $(NAME) clearscreen

$(LIBFT): $(SRC_LIBFT)/Makefile
	make -C $(SRC_LIBFT)

#$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
#	mkdir -p $(OBJ_PATH)
#	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME) : $(SRCS:.c=.o)
	$(CC) $(CFLAGS) $(SRCS:.c=.o) $(LIBFT) $(READLINE) -o $(NAME)

clean:
	$(RM) $(SRCS:.c=.o)
	make fclean -C $(SRC_LIBFT)
	clear
	@echo "\e[1m\e[33m\002 Files cleaned.\e[1m\e[33m\002"

fclean: clean
		make fclean -C $(SRC_LIBFT)
		$(RM) $(NAME)
		clear
		@echo "\e[1m\e[33m\002 Files Fcleaned.\e[1m\e[33m\002"

run: fclean all
		./minishell

clearscreen:
	clear
	@echo  "\e[1m\e[32m\002 SUCESS! Your \e[1m\e[35m\002 minishell \e[32m\002 is ready to launch. \e[32m\002"

re: fclean all
