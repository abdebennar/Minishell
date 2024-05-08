/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:41:13 by abennar           #+#    #+#             */
/*   Updated: 2024/05/07 21:42:01 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

static bool	is_sep(char c, char *sep)
{
	if (ft_strchr(sep, c) != NULL)
		return (true);
	return (false);	
}

char *get_next_word(char *str, int *i, t_token tok)
{
	int		start;
	char *substr;

	str[*i] = 127;
	if (tok == HEREDOC || tok == APPEND)
		str[++(*i)] = 127;
	start = 0;
	while (str[*i] && ft_strchr(" \t\n\v\r\f\177", str[*i]))
		(*i)++;
	start = *i;
	while (str[*i])
	{
		if (is_sep(str[*i], " \t\n\v\r\f>|<&()"))
			break;
		(*i)++;
	}
	substr = ft_substr(str, start, *i - start, 0);
	while (start < *i)
		str[start++] = 127;
	return (substr);
}
