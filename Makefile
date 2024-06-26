# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dnoll <dnoll@studen.42.com>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/16 14:35:15 by dnoll             #+#    #+#              #
#    Updated: 2024/02/18 15:36:36 by dnoll            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = main.c\
	check_input.c\
	init.c\
	routine_philo.c\
	monitor.c\
	death_flag.c\
	utils.c\
	forks_utils.c\
	exit.c
	
OBJS = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean :
	@rm -rf $(OBJS)

fclean : all clean
	@rm -rf $(NAME)

re :
	@rm -rf $(NAME) $(OBJS)
	@make all
	
.PHONY: all clean fclean re
