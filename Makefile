# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lyokoiga <lyokoiga@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/02 14:20:45 by lyokoiga          #+#    #+#              #
#    Updated: 2026/07/31 13:43:38 by lyokoiga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = codexion

SRC = src/codexion.c src/codexion_parsing.c src/threads.c \
	src/coder_actions.c

OBJ_P = $(SRC:%.c=%.o)

%.o: %.c
	gcc -Werror -Wextra -Wall -I . -c $< -o $@

all: $(NAME)

$(NAME) : $(OBJ_P)
	gcc -Werror -Wextra -Wall -I . $(OBJ_P) -o $(NAME)

clean:
	rm -f $(OBJ_P:%.c=%.o)

fclean: clean
	rm -f $(NAME)

re: fclean all


.PHONY: all clean fclean re
