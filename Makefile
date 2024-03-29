# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vehernan <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/11 02:11:29 by vehernan          #+#    #+#              #
#    Updated: 2019/09/11 02:12:34 by vehernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = test_gnl
CC = clang
FLAGS = -Wall -Wextra -Werror
INCLUDES = libft/includes
SRC = get_next_line.c
MAIN = main.c
OBJ_C = get_next_line.o
OBJ_M = main.o
LIB_DIR = libft/

$(NAME):
	@make -C $(LIB_DIR) fclean && make -C $(LIB_DIR)
	@$(CC) $(FlAGS) -I $(INCLUDES) -o $(OBJ_C) -c $(SRC)
	@$(CC) $(FLAGS) -I $(INCLUDES) -o $(OBJ_M) -c $(MAIN)
	@$(CC) -o $(NAME) $(OBJ_M) $(OBJ_C) -I $(INCLUDES) -L $(LIB_DIR) -lft
	@echo "[INFO]  Executable [$(NAME)] created (objects remaining in both directories)"

.PHONY: all, clean, fclean, re

all: $(NAME)

clean:
	@rm -f $(OBJ_C) $(OBJ_M)
	@make -C $(LIB_DIR) fclean
	@echo "[INFO] Objects removed in both directories"

fclean: clean
	@rm -f $(NAME)
	@echo "[INFO] Executable [$(NAME)] removed"

re: fclean all
