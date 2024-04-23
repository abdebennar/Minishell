# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/14 13:36:20 by abennar           #+#    #+#              #
#    Updated: 2024/04/23 02:38:21 by bel-oirg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = *.c */*.c

NAME = minishell

all : 
	rm -rf minishell
	$(MAKE) $(NAME)

$(NAME) :
	cc -g -lreadline $(SRC) -I/Users/$(USER)/Desktop/minishell/Include  -o $@ #-fsanitize=address #-Wall -Wextra -Werror
