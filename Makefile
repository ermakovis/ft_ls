# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcase <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/06 11:31:10 by tcase             #+#    #+#              #
#    Updated: 2019/06/02 16:47:44 by tcase            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_ls

CC=gcc
FLAGS= -Wall -Werror -Wextra

SRC_DIR=./src
LIB_DIR=./libft
OBJ_DIR=./obj

SRC_NAME=main.c\
		 parse.c\
		 cleanup.c

OBJ_NAME=$(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_DIR)/, $(SRC_NAME))
OBJ = $(addprefix $(OBJ_DIR)/, $(OBJ_NAME))

INC = -I ./includes -I $(LIB_DIR)/includes

all: $(NAME)

$(NAME) : $(OBJ) 
	@make -C $(LIB_DIR)
	@$(CC) -o $(NAME) $(OBJ) -L $(LIB_DIR) -lft $(INC)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) -o $@ -c $< $(INC)
	@echo "\033[34m\033[1mCompilation of \033[0m\033[36m$(notdir $<)\033[1m\033[34m done.\033[0m"

clean:
		@rm -f $(OBJ)

fclean: clean
		@make fclean -C $(LIB_DIR)
		@rm -f checker push_swap

test: $(NAME)
	./$(NAME) -Ral

re:	fclean all
