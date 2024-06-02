/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 09:42:10 by abennar           #+#    #+#             */
/*   Updated: 2024/06/01 00:03:08 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	q_syntax(char *cmd)
{
	char	q;

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

static bool	pr_syntax(char *cmd)
{
	int		i;
	int		o;

	(1337) && (i = 0, o = 0);
	while (cmd[i])
	{
		if (cmd[i] == '"' || cmd[i] == '\'')
			i += skip_quotes((cmd + i + 1), cmd[i]);
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
	t_node		*node;
	char		*cmd;
	extern int	g_sig;

	g_sig = 1;
	node = NULL;
	cmd = ft_strtrim(line, SEP, 0);
	if (ft_strlen(cmd))
		add_history(line);
	free(line);
	if (!q_syntax(cmd) || !pr_syntax(cmd))
		return (NULL);
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
