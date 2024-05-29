/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:01:06 by abennar           #+#    #+#             */
/*   Updated: 2024/05/29 17:51:26 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	low_pre(t_token tok)
{
	return (tok == NOT || tok == APPEND
		|| tok == HEREDOC || tok == IN || tok == OUT);
}

static int	get_pre(t_token tok)
{
	if (tok == IN || tok == OUT || tok == APPEND || tok == HEREDOC)
		return (4);
	if (tok == PIPE)
		return (3);
	if (tok == OR || tok == AND)
		return (2);
	return (1);
}

void	skip_space(char *cmd, int *i)
{
	while (cmd[*i])
	{
		if (!ft_strchr(SEP, cmd[*i]))
			break ;
		(*i)++;
	}
}

static t_node	*check_tokens(char *cmd, t_token tok, int *i)
{
	t_redir	*redir;
	char	*full_cmd;
	int		j;
	int		f;

	(1337) && (j = *i, redir = NULL);
	while (low_pre(tok) && cmd[j])
	{
		if (!check_syntax(tok, cmd, j))
			return (_setenv("?", ft_itoa(1)), NULL); // TODO exit stat on SYNTX ERR
		if (tok != NOT)
			add_redir_back(new_redir(get_next_word(cmd, &j, tok), tok), &redir);
		else
		{
			if (cmd[j] == '"' || cmd[j] == '\'')
				j += skip_quotes((cmd + j + 1), cmd[j]);
			j++;
		}
		tok = get_token(cmd[j], cmd[j + 1]);
	}
	f = get_cmd_area(cmd, *i);
	full_cmd = ft_substr(cmd, *i, f, 0);
	*i += f;
	return (new_node(full_cmd, redir, NOT, 0));
}

t_node	*lexer(char *cmd)
{
	t_node	*list;
	t_node	*node;
	t_token	tok;
	int		i;

	(1337) && (list = NULL, node = NULL, i = 0);
	while (cmd[i])
	{
		tok = get_token(cmd[i], cmd[i + 1]);
		if (!check_syntax(tok, cmd, i))
			return (_setenv("?", ft_itoa(1)), NULL);
		if (!low_pre(tok) && ++i)
		{
			node = new_node(NULL, NULL, tok, get_pre(tok));
			(tok == OR || tok == AND) && (i++);
			skip_space(cmd, &i);
		}
		else
			node = check_tokens(cmd, tok, &i);
		if (!node)
			return (NULL);
		add_node_back(node, &list);
	}
	return (list);
}
