/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:50:12 by abennar           #+#    #+#             */
/*   Updated: 2024/05/07 16:51:38 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	unexpected_token(char *cmd, int i)
{
	t_token	tok;

	tok = get_token(cmd[i], cmd[i + 1]);
	if (tok == PIPE || tok == OR || tok == AND)
	{
		printf("syntax error near unexpected token `%c'\n", cmd[i]);
		_setenv("?", ft_itoa(258));
		return (false);
	}
	return (true);
}

bool	check_syntax(t_token tok, char *cmd, int i) //TODO handle unclosed quotes
{
	bool	ret;

	ret = false;
	i++;
	if (tok == AND || tok == OR || tok == APPEND || tok == HEREDOC)
		i++;
		if (tok == HEREDOC || tok == APPEND || tok == IN || tok == OUT)
		{
			skip_space(cmd, &i);
			if (get_token(cmd[i], cmd[i + 1]) != NOT)
			{
				printf("syntax error near unexpected token `%c'\n", cmd[i]);
				_setenv("?", ft_itoa(258));
				return (false);
			}
		}
	if (tok == LPR)
	{
		while (cmd[i])
		{
			if (get_token(cmd[i], cmd[i + 1]) == RPR)
			{
				ret = true;
				break;
			}
			i++;		
		}
		if (!ret)
		printf("syntax error near unexpected token `%c'\n", cmd[i]);
		_setenv("?", ft_itoa(258));
	}
	else 
	{
		skip_space(cmd, &i);
		ret = unexpected_token(cmd, i);
	}
	return (ret);
}
