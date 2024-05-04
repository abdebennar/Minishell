# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abennar <abennar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/14 13:36:20 by abennar           #+#    #+#              #
#    Updated: 2024/05/04 14:04:36 by abennar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = utils/*.c Parsing/*/*.c Exec/*/*.c main.c

NAME = minishell

FLAGS = -Wall -Wextra -Werror

all : 
	rm -rf minishell
	$(MAKE) $(NAME)

$(NAME) :
	cc  -lreadline $(FLAGS) $(SRC) -I$(PWD)/Include  -o $@ #-fsanitize=address  #-g3   
