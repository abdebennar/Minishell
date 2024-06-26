/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:33:42 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/05/31 00:11:19 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dollar(char *raw, int *index, int heredoc)
{
	char	*out;

	raw++;
	(*index)++;
	out = NULL;
	if ((*raw) == '?')
		return ((*index)++, getenv("?"));
	else if (!*raw || *raw == ' ' || *raw == '\t')
		return (ft_strdup("$", 0));
	out = check_envar(raw, index);
	if (!heredoc && out && _wildcard_(prep_w(out)))
		out = _wildcard_(prep_w(out));
	if (!heredoc && out)
		find_replace(out, ' ', '\177');
	return (out);
}

char	*d_q(char *raw, int *index)
{
	char	*new;
	int		mic_index;

	new = NULL;
	mic_index = 0;
	if (raw[mic_index] == '"')
		mic_index++;
	while (raw[mic_index])
	{
		if (raw[mic_index] == '$' && raw[mic_index + 1] != '"')
			new = ft_strjoin(new, dollar(&raw[mic_index], &mic_index, 0), 0);
		else if (raw[mic_index] == '"')
		{
			mic_index++;
			break ;
		}
		else
			new = add_c(new, raw[mic_index++], 0);
	}
	*index += mic_index;
	return (new);
}

char	*s_q(char *raw, int *index)
{
	char	*new;
	int		mic_index;

	new = NULL;
	mic_index = 0;
	if (raw[mic_index] == '\'')
		mic_index++;
	while (raw[mic_index])
	{
		if (raw[mic_index] == '\'')
		{
			mic_index++;
			break ;
		}
		else
			new = add_c(new, raw[mic_index++], 0);
	}
	*index += mic_index;
	return (new);
}

char	*d_q_heredoc(char *raw, int *index)
{
	char	*new;
	int		mic_index;

	new = NULL;
	mic_index = 0;
	if (raw[mic_index] == '"')
		mic_index++;
	while (raw[mic_index])
	{
		if (raw[mic_index] == '"')
		{
			mic_index++;
			break ;
		}
		else
			new = add_c(new, raw[mic_index++], 0);
	}
	*index += mic_index;
	return (new);
}
