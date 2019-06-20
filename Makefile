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


NAME = ft_ssl

NOC=\033[0m
GRE=\033[32m
RED=\033[31m
YELL=\033[33m

cc = gcc
C_FLAGS =  -Wall -Wextra -Werror 

OBJ_PATH = ./obj/
PRINTF_PATH = ./ft_printf
LFT_PATH = ./ft_printf/libft/
INC_PATH = .

OBJ_NAME = $(SRC_NAME:.c=.o)
INC_NAME = ssl.h
SRC_NAME = main.c logging.c md5.c sha256.c sha256_transform.c do_md5.c do_sha256.c
SRC = $(addprefix ,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

all: $(NAME)

$(NAME): $(OBJ)
		@make -C $(LFT_PATH)
		@make -C $(PRINTF_PATH)
		@$(CC) -o $(NAME) $^ -o $@ $(LFT_PATH)/libft.a $(PRINTF_PATH)/libftprintf.a
		@echo "$(GRE)ft_ssl DONE!$(GRE)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
		@mkdir -p $(OBJ_PATH) 2> /dev/null || true
		@$(CC) $(C_FLAGS) $(INC) -o $@ -c $<

clean:
		@make -C $(LFT_PATH) clean
		@make -C $(PRINTF_PATH) clean
		@rm -rf $(OBJ_PATH)
		@echo "$(RED)Removing OBJ path: ./obj$(RED)"

fclean: clean
		@make -C $(LFT_PATH) fclean
		@make -C $(PRINTF_PATH) fclean
		@rm -f $(NAME)
		@echo "$(RED)Removing ft_ssl executables$(RED)"

re: fclean all
