# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/14 13:36:20 by abennar           #+#    #+#              #
#    Updated: 2024/04/21 19:36:44 by bel-oirg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = *.c */*.c

NAME = minishell

all : 
	rm -rf minishell
	$(MAKE) $(NAME)

$(NAME) :
	cc -g -lreadline $(SRC) -I/Users/$(USER)/Desktop/bel-oirg/Include  -o $@ #-fsanitize=address #-Wall -Wextra -Werror
