# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dnoll <dnoll@studen.42.com>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/16 14:35:15 by dnoll             #+#    #+#              #
#    Updated: 2024/02/16 14:40:26 by dnoll            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = main.c\
	check_input.c\
	init.c\
	routine_philo.c\
	routine_watcher.c\
	getters_setters.c\
	utils.c\
	eat_utils.c\
	exit.c\
	simulation.c
	
OBJS = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean :
	@rm -rf $(OBJS)

fclean :
	@rm -rf $(NAME)

re :
	@make fclean
	@make all
	
.PHONY: all clean fclean re bonus
