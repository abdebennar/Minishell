/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 17:40:17 by abennar           #+#    #+#             */
/*   Updated: 2024/05/12 19:21:38 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_token_format(t_token tok)
{
	if (tok == PIPE)
		return ("`|'");
	if (tok == AND)
		return ("`&&'");
	if (tok == OR)
		return ("`||'");
	if (tok == OUT)
		return ("`>'");
	if (tok == IN)
		return ("`<'");
	if (tok == APPEND)
		return ("`>>'");
	if (tok == HEREDOC)
		return ("`<<'");
	if (tok == RPR)
		return ("`)'");
	if (tok == LPR)
		return ("`('");
	return ("`newline'");
}

bool	put_tok_err(t_token tok)
{
	char *tok_f;

	tok_f = get_token_format(tok);
	write(2, SYNTAX_ERR, ft_strlen(SYNTAX_ERR));
	write(2, tok_f, ft_strlen(tok_f));
	_setenv("?", ft_itoa(2));
	write(2, "\n", 1);
	return (false);
}

void	put_str_err(char *err, char *str)
{
	write(2, "shell: ", 7);
	if (str)
		write(2, str, ft_strlen(str));
	write(2, ":", 1);
	write(2, err, ft_strlen(err));
	write(2, "\n", 1);
}

void	put_err(char *err)
{
	write (2, err, ft_strlen(err));
}