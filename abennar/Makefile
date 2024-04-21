# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abennar <abennar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/14 13:36:20 by abennar           #+#    #+#              #
#    Updated: 2024/04/21 14:16:36 by abennar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = *.c */*.c


NAME = minishell


all : 
	rm -rf minishell
	$(MAKE) -C ./libft
	$(MAKE) $(NAME)


$(NAME) :
	cc -g -lreadline $(SRC) -I/Users/abennar/Desktop/minishell/include ./libft/libft.a -o $@ #-fsanitize=address #-Wall -Wextra -Werror
