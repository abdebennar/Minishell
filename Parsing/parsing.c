/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:42:10 by abennar           #+#    #+#             */
/*   Updated: 2024/05/27 16:07:03 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

bool	q_syntax(char *cmd)
{
	char q;
	while (*cmd)
	{
		if (*cmd == '"' || *cmd == '\'')
		{
			q = *cmd++;
			while (*cmd && *cmd != q)
			{
				cmd++;
			}
			if (!(*cmd))
			{
				put_err("shell: unclosed quotes\n");
				_setenv("?", ft_itoa(1));
				return (false);
			}
		}
		cmd++;
	}
	return (true);
}

bool	pr_syntax(char *cmd)
{
	int		i = 0;
	int		o = 0;

	while (cmd[i])
	{
		if (cmd[i] == '"' || cmd[i] == '\'')
			i+= skip_quotes((cmd + i + 1), cmd[i]);
		if (get_token(cmd[i], cmd[i + 1]) == LPR)
			o++;
		else if (get_token(cmd[i], cmd[i + 1]) == RPR)
			o--;
		i++;
	}
	if (o > 0)
	{
		put_err("shell: syntax error near unexpected token `('\n");
		return (_setenv("?", ft_itoa(258)), false);
	}
	else if (o < 0)
	{
		put_err("shell: syntax error near unexpected token `)'\n");
		return (_setenv("?", ft_itoa(258)), false);
	}
	return (true);
}

t_node	*parsing(char *line)
{
	t_node	*node;
	char	*cmd;
	
	g_sig = 1;
	node = NULL;
	cmd = ft_strtrim(line, SEP, 0);
	if (ft_strlen(cmd))
		add_history(line);
	if (!q_syntax(cmd) || !pr_syntax(cmd))
		return (NULL);
	free(line);
	if (!cmd || !cmd[0])
		return (NULL);
	node = lexer(cmd); 
	if (!node)
		return (NULL);
	lst_iter(node, get_args);
	node = infix_to_postfix(&node);
	node = postfix_to_prefix(node);
	node = tree(node); 
	return (node);
}

