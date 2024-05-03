/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 08:22:24 by abennar           #+#    #+#             */
/*   Updated: 2024/05/03 16:09:56 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main()
{
	char	*line;
	t_node	*node;
	
	add_env();
	while (666)
	{
		line = readline("$ ");
		node = parsing(line);
		_exec_arch_(node);
		my_malloc(0, 0, 0);
	}
}
