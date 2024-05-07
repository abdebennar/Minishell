/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 11:01:06 by abennar           #+#    #+#             */
/*   Updated: 2024/05/07 16:44:40 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

t_node	*check_tokens(char *cmd, t_token tok, int *i)
{	
	t_redir *redir;
	char	*full_cmd; 
	int		j;
	int		f;

	j = *i;
	redir = NULL;
	while (low_pre(tok) && cmd[j])
	{
		if (tok != NOT)
		{
			if (!check_syntax(tok, cmd, j))
				return (NULL);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 
			add_redir_back(new_redir(get_next_word(cmd, &j, tok), tok), &redir);
		}
		else
			j++;
		tok = get_token(cmd[j], cmd[j + 1]);
	}
	f = get_cmd_area(cmd, *i);
	full_cmd = ft_substr(cmd, *i, f, 0);
	*i += f;
	return (new_node(full_cmd, redir, NOT, 0));
}

bool	low_pre(t_token tok)
{
	return (tok == NOT || tok == APPEND || tok == HEREDOC || tok == IN || tok == OUT);
}

int	get_pre(t_token tok)
{
	if (tok == IN || tok == OUT || tok == APPEND || tok == HEREDOC)
		return (4);
	if (tok == PIPE)
		return (3);
	if (tok == OR || tok == AND)
		return (2);
	return (1);
}

void	print_tok(t_token tok) // TMP
{
	if (tok == PIPE)
		printf("pipe\n");
	if (tok == AND)
		printf("and\n");
	if (tok == OR)
		printf("or\n");
	if (tok == HEREDOC)
		printf("herdoc\n");
	if (tok == OUT)
		printf("out\n");
	if (tok == IN)
		printf("in\n");
	if (tok == LPR)
		printf("lrp (\n");
	if (tok == RPR)
		printf("rpr ) \n");
	if (tok == NOT)
		printf("not\n");
	
}

void	skip_space(char *cmd, int *i)
{
	while (cmd[*i])
	{
		if (!ft_strchr(SEP, cmd[*i]))
			break;
		(*i)++;
	} 
}

t_node	*lexer(char *cmd)
{
	t_node	*list;
	t_node	*node;
	t_token	tok;
	int	i;

	i = 0;
	(!i) && (list = NULL, node = NULL);
	while (cmd[i])
	{
		tok = get_token(cmd[i], cmd[i + 1]);
		if (!check_syntax(tok, cmd, i))
			return (NULL);
		if (!low_pre(tok))
		{
			node = new_node(NULL, NULL, tok, get_pre(tok));
			i++;
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
