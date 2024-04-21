/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:42:10 by abennar           #+#    #+#             */
/*   Updated: 2024/04/21 16:22:32 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_tree(t_node *root, int level) {
    if (root != NULL) {
        print_tree(root->right, level + 1);
        for (int i = 0; i < level; i++) {
            printf("   ");
        }
		if (root->tok == NOT)
        	printf("%s\n", root->cmd);
		else
			print_tok(root->tok);
        print_tree(root->left, level + 1);
    }
}



void	Parsing(char *line)
{
	t_node *node;
	char *cmd;

	node = NULL;

	cmd = ft_strtrim(line, SEP);
	node = lexer(cmd);
	lst_iter(node, get_args);
	node = infix_to_postfix(&node);
	node = postfix_to_prefex(node);
	node = tree(node);
	print_tree(node, 0);
}