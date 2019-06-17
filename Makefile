# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yyatsenk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/17 12:34:33 by yyatsenk          #+#    #+#              #
#    Updated: 2019/06/17 12:34:34 by yyatsenk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = ssl_md5

NOC=\033[0m
GRE=\033[32m
RED=\033[31m
YELL=\033[33m

cc = gcc
C_FLAGS = -g# -Wall -Wextra -Werror 

OBJ_PATH = ./obj/
LFT_PATH = ./libft/
INC_PATH = .

OBJ_NAME = $(SRC_NAME:.c=.o)
INC_NAME = ssl.h
SRC_NAME = main.c
SRC = $(addprefix ,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

all: $(NAME)

$(NAME): $(OBJ)
		@make -C $(LFT_PATH)
		@$(CC) -o $(NAME) -L $(LFT_PATH) -lft $^ -o $@ 
		@echo "$(GRE)ssl_md5 DONE!$(GRE)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
		@mkdir -p $(OBJ_PATH) 2> /dev/null || true
		@$(CC) $(C_FLAGS) $(INC) -o $@ -c $<

clean:
		@make -C $(LFT_PATH) clean
		@rm -rf $(OBJ_PATH)
		@echo "$(RED)Removing OBJ path: ./obj$(RED)"

fclean: clean
		@make -C $(LFT_PATH) fclean
		@rm -f $(NAME)
		@echo "$(RED)Removing ssl_md5 executables$(RED)"

re: fclean all
