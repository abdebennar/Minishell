# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/14 13:36:20 by abennar           #+#    #+#              #
#    Updated: 2024/04/29 14:44:08 by bel-oirg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = utils/*.c Parsing/*/*.c Exec/*/*.c main.c

NAME = minishell

all : 
	rm -rf minishell
	$(MAKE) $(NAME)


$(NAME) :
	cc -lreadline $(SRC) -I$(PWD)/Include  -o $@ #-g3 # -fsanitize=address #-Wall -Wextra -Werror
