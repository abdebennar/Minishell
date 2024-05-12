/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:50:12 by abennar           #+#    #+#             */
/*   Updated: 2024/05/12 17:50:51 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_token	get_next_token(char *cmd, int i)
{
	skip_space(cmd, &i);
	return (get_token(cmd[i], cmd[i + 1]));
}


bool	par_check(char *cmd, int i)
{
	t_token t_tok;
	int		j;

	j = i;
	t_tok = get_next_token(cmd, i);
	if (!(t_tok == NOT || t_tok == RPR || t_tok == LPR))
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
	t_token t_tok;

	i++;
	(tok == HEREDOC || tok == OR || tok == APPEND || tok == AND) && (i++);
	if (tok == LPR)
		return (par_check(cmd, i));
	else if (tok == AND || tok == OR || tok == PIPE)
	{
		t_tok = get_next_token(cmd, i);
		if (!(t_tok == NOT || t_tok == IN || t_tok == OUT || t_tok == HEREDOC 
		|| t_tok == APPEND || t_tok == LPR) || (tok == PIPE && i < 2) || (tok != PIPE && i < 3))
		{
			if ((tok == PIPE && i < 2) || (tok != PIPE && i < 3))
				return (put_tok_err(tok));
			else
				return (put_tok_err(t_tok));
		}
	}
	else if (tok == IN || tok == OUT || tok == APPEND || tok == HEREDOC)
	{
		t_tok = get_next_token(cmd, i);
		if (t_tok != NOT)
			return (put_tok_err(t_tok));
	}
	return (true);
}
