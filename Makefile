# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/02 14:20:45 by lyokoiga          #+#    #+#              #
#    Updated: 2026/08/16 15:47:16 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = codexion

SRC = src/codexion.c src/codexion_parsing.c src/threads.c \
	src/coder_actions.c src/time_utils.c src/sim_actions.c \
	src/coder_utils.c src/sim_schedule.c src/heap.c \
	src/scheduler_utils.c src/heap_utils.c src/errors.c \
	src/trash_heap.c src/codexion_parsing2.c src/codexion_spawners.c

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

reclean: all clean


.PHONY: all clean fclean re
