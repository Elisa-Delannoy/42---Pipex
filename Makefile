# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edelanno <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/21 15:49:28 by edelanno          #+#    #+#              #
#    Updated: 2025/01/21 15:49:29 by edelanno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

FTPRINTF_DIR = printf
FTPRINTF = $(FTPRINTF_DIR)/libftprintf.a

CC = cc -g
CFLAGS = -Wall -Wextra -Werror -I ./
NAME = pipex
SRC = pipex_new.c path.c
OBJ = $(SRC:.c=.o)

all : $(NAME)
	@echo "\033[32mCompilation successful !\033[0m"

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)
	@echo "Compilating $@"

$(FTPRINTF):
	@$(MAKE) -s -C $(FTPRINTF_DIR)
	@echo "Compilating $@"

$(NAME) : $(OBJ) $(LIBFT) $(FTPRINTF)
	@$(CC) $(OBJ) -o $(NAME) $(LIBFT) $(FTPRINTF)

%.o: %.c
	@echo "Compilating $@"
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@$(MAKE) -s clean -C $(LIBFT_DIR)
	@$(MAKE) -s clean -C $(FTPRINTF_DIR)
	@rm -f $(OBJ)
	@echo "\033[32mClean ok\033[0m"

fclean : clean
	@$(MAKE) -s fclean -C $(LIBFT_DIR)
	@$(MAKE) -s fclean -C $(FTPRINTF_DIR)
	@rm -f $(NAME) 

re : fclean all