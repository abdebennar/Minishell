/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 08:22:24 by abennar           #+#    #+#             */
/*   Updated: 2024/05/07 10:57:41 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_sig = 0;

int	main()
{
	char	*line;
	t_node	*node;
	
	add_env();
	while (666)
	{
		sig_ign();
		my_malloc(0, 0, 0);
		line = readline("$ ");
		if (!line)
			break;
		g_sig = 1;
		add_history(line);
		node = parsing(line);
		_exec_arch_(node);
		g_sig = 0;
	}
	printf("exit\n");
	my_malloc(0, 0, 0);
	my_malloc(0, 0, 1);
}
