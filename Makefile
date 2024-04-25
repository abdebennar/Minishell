# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/14 13:36:20 by abennar           #+#    #+#              #
#    Updated: 2024/04/25 06:02:01 by bel-oirg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = utils/*.c Parsing/*/*.c Exec/command/*.c Exec/builtins/*.c main.c

NAME = minishell

all : 
	rm -rf minishell
	$(MAKE) $(NAME)

$(NAME) :
	cc -g -lreadline $(SRC) -I/Users/$(USER)/Desktop/new_mini/Include  -o $@ #-fsanitize=address #-Wall -Wextra -Werror
