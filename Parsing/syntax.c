/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:50:12 by abennar           #+#    #+#             */
/*   Updated: 2024/05/23 16:23:42 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	get_next_token(char *cmd, int i)
{
	skip_space(cmd, &i);
	return (get_token(cmd[i], cmd[i + 1]));
}

bool	is_redir(t_token tok)
{
	return (tok == IN || tok == OUT || tok == HEREDOC || tok == APPEND);
}

bool	par_check(char *cmd, t_token tok, int i)
{
	t_token	t_tok;
	int		j;

	j = i;
	t_tok = get_next_token(cmd, i);
	if (tok == RPR)
	{
		if (is_redir(t_tok) || i < 2)
			return (put_tok_err(tok));
		return (true);
	}
	if (!(t_tok == NOT || t_tok == LPR || is_redir(t_tok)))
		return (put_tok_err(t_tok));
	while (cmd[i])
	{
		t_tok = get_token(cmd[i], cmd[i + 1]);
		if (t_tok == RPR)
			return (true);
		i++;
	}
	t_tok = get_next_token(cmd, j);
	return (put_tok_err(t_tok));
}

bool	check_syntax(t_token tok, char *cmd, int i)
{
	t_token	n;

	++i;
	(tok == HEREDOC || tok == OR || tok == APPEND || tok == AND) && (i++);
	if (tok == LPR || tok == RPR)
		return (par_check(cmd, tok, i));
	else if (tok == AND || tok == OR || tok == PIPE)
	{
		n = get_next_token(cmd, i);
		if (!(n == NOT || is_redir(n) || n == LPR) || (tok == PIPE
				&& (i < 2 || n == LPR)) || (tok != PIPE && i < 3) || n == END)
		{
			if ((tok == PIPE && i < 2) || (tok != PIPE && i < 3))
				return (put_tok_err(tok));
			else
				return (put_tok_err(n));
		}
	}
	else if (tok == IN || tok == OUT || tok == APPEND || tok == HEREDOC)
	{
		n = get_next_token(cmd, i);
		if (n != NOT)
			return (put_tok_err(n));
	}
	return (true);
}
