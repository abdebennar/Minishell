/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mng_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 19:50:39 by abennar           #+#    #+#             */
/*   Updated: 2024/05/02 09:28:11 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

t_token	get_token(const char c1, const char c2)
{
	if (c1 == '|' && c2 == '|')
		return (OR);
	if (c1 == '&' && c1 == '&')
		return (AND);
	if (c1 == '<' && c2 == '<')
		return (HEREDOC);
	if (c1 == '>' && c2 == '>')
		return (APPEND);
	if (c1 == '(')
		return (LPR);
	if (c1 == ')')
		return (RPR);
	if (c1 == '|')
		return (PIPE);
	if (c1 == '>')
		return (OUT);
	if (c1 == '<')
		return (IN);
	return (NOT);
}

int	skip_quotes(char *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s == c)
			return (i);
		i++;
		s++;
	}
	return (0);
}

int	get_cmd_area(char *s, int start)
{
	int	len;
	int	j;

	len = 0;
	j = 0;
	while (s[start] && get_token(s[start],0) == NOT)
	{
		if (s[start] == '"' || s[start] == '\'')
		{
			j = skip_quotes((s + start + 1), s[start]);
			len += j;
			start += j;
		}
		len++;
		start++;
	}
	return (len);
}