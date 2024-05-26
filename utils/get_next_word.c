/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abennar <abennar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 16:41:13 by abennar           #+#    #+#             */
/*   Updated: 2024/05/26 23:03:01 by abennar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

static bool	is_sep(char c, char *sep)
{
	if (ft_strchr(sep, c) != NULL)
		return (true);
	return (false);	
}

char *get_next_word(char *str, int *j, t_token tok)
{
	int		start;
	char *substr;

	str[*j] = 127;
	if (tok == HEREDOC || tok == APPEND)
		str[++(*j)] = 127;
	start = 0;
	while (str[*j] && ft_strchr(" \t\n\v\r\f\177", str[*j]))
		(*j)++;
	start = *j;
	while (str[*j])
	{
		if (str[*j] == '"' || str[*j] == '\'')
			*j += skip_quotes((str + *j + 1), str[*j]);
		if (is_sep(str[*j], " \t\n\v\r\f") || get_token(str[*j], str[(*j) + 1]) != NOT
			|| get_token(str[*j], str[(*j) + 1]) == END)
			break;
		(*j)++;
	}
	substr = ft_substr(str, start, *j - start, 0);
	while (start < *j)
		str[start++] = 127;
	return (substr);
}
