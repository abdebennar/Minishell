/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-oirg <bel-oirg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:33:42 by bel-oirg          #+#    #+#             */
/*   Updated: 2024/05/05 16:19:12 by bel-oirg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dollar(char *raw, int *index)
{
	char	*out;
	
	raw++;
	(*index)++;
	if ((*raw) == '?')
		return ((*index)++, getenv("?"));
	else if (!*raw)
		return (ft_strdup("$", 0));
	out = check_envar(raw, index);
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
			new = ft_strjoin(new, dollar(&raw[mic_index], &mic_index), 0);
		else if (raw[mic_index] == '"' || !raw[mic_index]) //maybe remove second arg
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
