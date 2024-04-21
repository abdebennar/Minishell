# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abennar <abennar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/14 13:36:20 by abennar           #+#    #+#              #
#    Updated: 2024/04/21 17:47:58 by abennar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = *.c */*.c


NAME = minishell


all : 
	rm -rf minishell
	$(MAKE) $(NAME)


$(NAME) :
	cc -g -lreadline $(SRC) -I/Users/abennar/Desktop/bel-oirg/Include  -o $@ #-fsanitize=address #-Wall -Wextra -Werror
