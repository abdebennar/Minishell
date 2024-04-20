/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:42:10 by abennar           #+#    #+#             */
/*   Updated: 2024/04/19 23:25:33 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	Parsing(char *cmd)
{
	t_node *node;

	node = NULL;

	cmd = ft_strtrim(cmd, SEP);
	node = lexer(cmd);
	lst_iter(node, get_args);
	node = infix_to_postfix(&node);
	
	
	while (node)
	{
		printf("%s\t", node->cmd);
		print_tok(node->tok);
		printf("\n");

		// if (node->tok == NOT)
		// 	while(*(node->args))
		// 	{
		// 		printf(" args : %s\n", *(node->args));
		// 		(node->args)++;
		// 	}

		
		node = node->right;
	}
}
// (ls && (ls | wc ))