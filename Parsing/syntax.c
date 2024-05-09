/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:50:12 by abennar           #+#    #+#             */
/*   Updated: 2024/05/09 18:09:31 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_token	get_next_token(char *cmd, int i)
{
	skip_space(cmd, &i);
	return (get_token(cmd[i], cmd[i + 1]));
}

char *get_token_format(t_token tok)
{
	if (tok == PIPE)
		return ("|");
	if (tok == AND)
		return ("&&");
	if (tok == OR)
		return ("||");
	if (tok == OUT)
		return (">");
	if (tok == IN)
		return ("<");
	if (tok == APPEND)
		return (">>");
	if (tok == HEREDOC)
		return ("<<");
	if (tok == RPR)
		return (")");
	if (tok == LPR)
		return ("(");
	return ("newline");
}

bool	par_check(char *cmd, int i)
{
	t_token t_tok;
	int		j;

	j = i;
	t_tok = get_next_token(cmd, i);
	if (!(t_tok == NOT || t_tok == RPR || t_tok == LPR))
	{
		t_tok = get_next_token(cmd, j);
		printf(SYNTAX_ERR"`%s'\n", get_token_format(t_tok));
		_setenv("?", ft_itoa(258));
		return (false);
	}
	while (cmd[i])
	{
		t_tok = get_token(cmd[i], cmd[i + 1]);
		if (t_tok == RPR)
			return (true);
		i++;
	}
	t_tok = get_next_token(cmd, j);
	printf(SYNTAX_ERR"`%s'\n", get_token_format(t_tok));
	_setenv("?", ft_itoa(258));
	return (false);
}

bool	check_syntax(t_token tok, char *cmd, int i)
{
	t_token t_tok;

	i++;
	(tok == HEREDOC || tok == OR || tok == APPEND || tok == AND) && (i++);
	if (tok == LPR)
		return (par_check(cmd, i));
	else if (tok == AND || tok == OR || tok == PIPE)
	{
		t_tok = get_next_token(cmd, i);
		if (!(t_tok == NOT || t_tok == IN || t_tok == OUT || t_tok == HEREDOC || t_tok == APPEND || t_tok == LPR))
		{
			printf(SYNTAX_ERR"`%s'\n", get_token_format(t_tok));
			_setenv("?", ft_itoa(258));
			return (false);
		}
	}
	else if (tok == IN || tok == OUT || tok == APPEND || tok == HEREDOC)
	{
		t_tok = get_next_token(cmd, i);
		if (t_tok != NOT)
		{
			printf(SYNTAX_ERR"`%s'\n", get_token_format(t_tok));
			_setenv("?", ft_itoa(258));
			return (false);
		}
	}
	return (true);
}
