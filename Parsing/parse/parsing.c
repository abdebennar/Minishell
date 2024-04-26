/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:42:10 by abennar           #+#    #+#             */
/*   Updated: 2024/04/26 03:04:32 by bel-oirg         ###   ########.fr       */
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
//         	printf("%s\n", root->(*cmd);
// 		else
// 			print_tok(root->tok);
//         print_tree(root->left, level + 1);
//     }
// }

t_node	*Parsing(char *line, t_env *env)
{
	t_node	*node;
	char	*cmd;
	
	node = NULL;
	cmd = ft_strtrim(line, SEP, 0);
	free(line);
	if (!cmd[0])
		return (NULL);
	node = lexer(cmd);
	lst_iter(node, get_args);
	node = infix_to_postfix(&node);
	add_env(node, env);
	node = postfix_to_prefix(node);
	node = tree(node);
	return (node);
}
