# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/14 13:36:20 by abennar           #+#    #+#              #
#    Updated: 2024/05/02 16:07:39 by bel-oirg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = utils/*.c Parsing/*/*.c Exec/*/*.c main.c

NAME = minishell

FLAGS = -Wall -Wextra -Werror

all : 
	rm -rf minishell
	$(MAKE) $(NAME)

$(NAME) :
	cc -fsanitize=address -lreadline $(FLAGS) $(SRC) -I$(PWD)/Include  -o $@ #-g3  
