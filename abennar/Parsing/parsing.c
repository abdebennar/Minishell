/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:42:10 by abennar           #+#    #+#             */
/*   Updated: 2024/04/20 21:15:34 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_tree(t_node *root, int level) {
    if (root != NULL) {
        print_tree(root->right, level + 1);
        for (int i = 0; i < level; i++) {
            printf("   ");
        }
        printf("%s\n", root->cmd);
        print_tree(root->left, level + 1);
    }
}


void	Parsing(char *cmd)
{
	t_node *node;

	node = NULL;

	cmd = ft_strtrim(cmd, SEP);
	node = lexer(cmd);
	lst_iter(node, get_args);
	t_node *tmp = node;
	// while (tmp)
	// {
	// 	printf("%s -->", tmp->cmd);
	// 	tmp = tmp->right;
	// }
	
printf("POSTFIX\n");
	node = infix_to_postfix(&node);
	// node = postfix_to_prefex(node);
	// node = tree(node);
	

	// print_tree(node, 0);
	
	while (node)
	{
		printf("%s\t`", node->cmd);
		print_tok(node->tok);
		printf("\n");
		
		node = node->right;
	}
}
// (ls && (ls | wc ))