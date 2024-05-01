/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 08:22:24 by abennar           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/04/29 14:38:58 by bel-oirg         ###   ########.fr       */
=======
/*   Updated: 2024/04/30 01:21:30 by abennar          ###   ########.fr       */
>>>>>>> 09166f3fa8119fe46a145c0eb5ffa359dfd0927d
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_env	*env;
	t_node	*node;
	
	add_env();
	while (666)
	{
		line = readline("$ ");
		node = parsing(line, env);
		_exec_arch_(node);
	}
}