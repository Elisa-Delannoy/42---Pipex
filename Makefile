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

CC = cc -g
CFLAGS = -Wall -Wextra -Werror -I ./
NAME = pipex
SRC = pipex.c path.c main.c
OBJ = $(SRC:.c=.o)

SRCBONUS = main_bonus.c pipex.c path.c
OBJBONUS = $(SRCBONUS:.c=.o)

all : $(NAME)
	@echo "\033[32mCompilation successful !\033[0m"

$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)
	@echo "Compilating $@"

$(NAME) : $(OBJ) $(LIBFT)
	@$(CC) $(OBJ) -o $(NAME) $(LIBFT)

%.o: %.c
	@echo "Compilating $@"
	@$(CC) $(CFLAGS) -c $< -o $@

bonus : $(OBJBONUS) $(LIBFT)
	@$(CC) $(OBJBONUS) -o $(NAME) $(LIBFT) 

clean :
	@$(MAKE) -s clean -C $(LIBFT_DIR)
	@rm -f $(OBJ) $(OBJBONUS)
	@echo "\033[32mClean ok\033[0m"

fclean : clean
	@$(MAKE) -s fclean -C $(LIBFT_DIR)
	@rm -f $(NAME)

re : fclean all