# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abennar <abennar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/14 13:36:20 by abennar           #+#    #+#              #
#    Updated: 2024/04/30 02:09:45 by abennar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = utils/*.c Parsing/*/*.c Exec/*/*.c main.c

NAME = minishell

all : 
	rm -rf minishell
	$(MAKE) $(NAME)


$(NAME) :
	cc -lreadline $(SRC) -I$(PWD)/Include  -o $@ #-g3  #-fsanitize=address #-Wall -Wextra -Werror
