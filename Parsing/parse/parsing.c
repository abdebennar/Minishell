/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:42:10 by abennar           #+#    #+#             */
/*   Updated: 2024/05/01 10:00:17 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

// void print_tree(t_node *root, int level)
// {
//     if (root != NULL) {
//         print_tree(root->right, level + 1);
//         for (int i = 0; i < level; i++) {
//             printf("   ");
//         }
// 		if (root->tok == NOT)
//         	printf("%s\n", root->cmd[0]);
// 		else
// 			print_tok(root->tok);
//         print_tree(root->left, level + 1);
//     }
// }

t_node	*parsing(char *line, t_env *env)
{
	t_node	*node;
	char	*cmd;
	
	node = NULL;
	cmd = ft_strtrim(line, SEP, 0);
	free(line);
	if (!cmd || !cmd[0])
		return (NULL);
	node = lexer(cmd);
	if (!node)
		return (NULL);
	lst_iter(node, get_args);
	node = infix_to_postfix(&node);
	add_env(node, env);
	node = postfix_to_prefix(node);
	node = tree(node);
	// print_tree(node, 0);
	// exit(0);
	return (node);
}
